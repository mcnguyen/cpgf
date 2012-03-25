#include "testserializationcommon.h"
#include "cpgf/gmetadefine.h"

#include "gmetatextstreamarchive.h"

#include "cpgf/ginterface.h"
#include "cpgf/gflags.h"
#include "cpgf/gfunctionextractor.h"

#include "gmetaarchivetypemap.h"

#include <sstream>
#include <string>

#include <iostream>

using namespace std;
using namespace cpgf;


namespace {

class C;

class A
{
public:
	A() : a(0), pc(NULL) {}
	~A();
	
	void init();
	bool verify() const;
	
	int a;
	A * pself;
	C * pc;
};

class B
{
public:
	B() : b(0), pa(NULL) {}

	int b;
	B * pself;
	A * pa;
};

class C
{
public:
	C() : c(0), pb(NULL) {}

	int c;
	C * pself;
	B * pb;
};

A::~A()
{
	if(this->pc != NULL) {
		delete this->pc->pb;
		delete this->pc;
	}
}

void A::init()
{
	this->pc = new C;
	this->pc->pb = new B;
	this->pc->pb->pa = this;
	this->pself = this;
	this->pc->pself = this->pc;
	this->pc->pb->pself = this->pc->pb;
	this->a = 1;
	this->pc->c = 3;
	this->pc->pb->b = 2;
}

bool A::verify() const
{
	return
		this->pc != NULL
		&& this->pc->pb != NULL
		&& this->pc->pb->pa == this
		&& this->a == 1
		&& this->pc->c == 3
		&& this->pc->pb->b == 2
	;
}


template <typename Define>
void register_TestSerializeClass(Define define)
{
	GDefineMetaClass<A> classDefineA = GDefineMetaClass<A>::declare("TestSerializeClassA");
	
	classDefineA
		FIELD(A, a)
		FIELD(A, pself)
		FIELD(A, pc)
	;
	define._class(classDefineA);
	
	GDefineMetaClass<B> classDefineB = GDefineMetaClass<B>::declare("TestSerializeClassB");
	
	classDefineB
		FIELD(B, b)
		FIELD(B, pself)
		FIELD(B, pa)
	;
	define._class(classDefineB);

	GDefineMetaClass<C> classDefineC = GDefineMetaClass<C>::declare("TestSerializeClassC");
	
	classDefineC
		FIELD(C, c)
		FIELD(C, pself)
		FIELD(C, pb)
	;
	define._class(classDefineC);
	
}

template <typename AR>
void doTestCyclicGraph(IMetaWriter * writer, IMetaReader * reader, const AR & ar)
{
	GDefineMetaNamespace define = GDefineMetaNamespace::declare("global");
	register_TestSerializeClass(define);

	GScopedInterface<IMetaService> service(createMetaService(createMetaModule(define.getMetaClass())));

	GScopedInterface<IMetaClass> metaClass(service->findClassByName("TestSerializeClassA"));

	GScopedInterface<IMetaArchiveWriter> archiveWriter(createMetaArchiveWriter(GMetaArchiveConfig().getFlags(), service.get(), writer));
	GScopedInterface<IMetaArchiveReader> archiveReader(createMetaArchiveReader(GMetaArchiveConfig().getFlags(), service.get(), reader));

	A instance;
	instance.init();
	
	GCHECK(instance.verify());

	serializeWriteObjectValue(archiveWriter.get(), "", &instance, metaClass.get());

	ar.rewind();

	A readInstance;
	
	serializeReadObject(archiveReader.get(), "", &readInstance, metaClass.get());
	
	GCHECK(readInstance.verify());
}

GTEST(testCyclicGraph)
{
	GDefineMetaNamespace define = GDefineMetaNamespace::declare("global");
	register_TestSerializeClass(define);

	GScopedInterface<IMetaService> service(createMetaService(createMetaModule(define.getMetaClass())));

	stringstream stream;

	GTextStreamMetaWriter<stringstream> outputStream(stream);
	GTextStreamMetaReader<stringstream> inputStream(service.get(), stream);
	
	doTestCyclicGraph(&outputStream, &inputStream, TestArchiveStream<stringstream>(stream));
	
//	cout << stream.str().c_str() << endl;
}


} // unnamed namespace