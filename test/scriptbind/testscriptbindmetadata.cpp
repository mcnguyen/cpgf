#include "cpgf/gmetaclass.h"
#include "cpgf/gscopedptr.h"

#include "testscriptbindmetadata.h"

#include <string>

namespace testscript {

void bindBasicData(cpgf::GScriptObject * script, cpgf::IMetaService * service)
{
	using namespace cpgf;

	GApiScopedPointer<IMetaClass> metaClass;
	
	metaClass.reset(service->findClassByName("testscript::TestObject"));
	GCHECK(metaClass);
	
	script->bindClass("TestObject", metaClass.get());
	
	metaClass.reset(service->findClassByName("testscript::TestData"));
	GCHECK(metaClass);
	
	script->bindClass("TestData", metaClass.get());
	
	script->setFundamental("Magic1", Magic1);
	script->setFundamental("Magic2", Magic2);
	script->setFundamental("Magic3", Magic3);
}


void bindBasicData(cpgf::IScriptObject * script, cpgf::IMetaService * service)
{
	using namespace cpgf;

	GApiScopedPointer<IMetaClass> metaClass;
	
	metaClass.reset(service->findClassByName("testscript::TestObject"));
	GCHECK(metaClass);
	
	GApiScopedPointer<IScriptName> scriptName;

	scriptName.reset(script->createName("TestObject"));
	script->bindClass(scriptName.get(), metaClass.get());
	
	metaClass.reset(service->findClassByName("testscript::TestData"));
	GCHECK(metaClass);

	scriptName.reset(script->createName("TestData"));
	script->bindClass(scriptName.get(), metaClass.get());

	GVariant v;

	v = Magic1;
	scriptName.reset(script->createName("Magic1"));
	script->setFundamental(scriptName.get(), &v.data);
	
	v = Magic2;
	scriptName.reset(script->createName("Magic2"));
	script->setFundamental(scriptName.get(), &v.data);
	
	v = Magic3;
	scriptName.reset(script->createName("Magic3"));
	script->setFundamental(scriptName.get(), &v.data);
}


GMETA_DEFINE_CLASS(TestData, TestData, "testscript::TestData") {
	using namespace cpgf;

	GMETA_FIELD(x);
	GMETA_FIELD(name);
}

GMETA_DEFINE_CLASS(TestObject, TestObject, "testscript::TestObject") {
	using namespace cpgf;
	using namespace std;

	reflectConstructor<void * (const TestObject &)>();
	reflectConstructor<void * (int)>();
	reflectConstructor<void * (int, const string &)>();
	
	GMETA_FIELD(value);
	
	GMETA_METHOD(self);
	GMETA_METHOD(selfConst);
	GMETA_METHOD(selfVolatile);
	GMETA_METHOD(selfConstVolatile);
	
	reflectMethod("methodConst", (int (TestObject::*)())&TestObject::methodConst);
	reflectMethod("methodConst", (int (TestObject::*)() const)&TestObject::methodConst);
	
	reflectMethod("methodVolatile", (int (TestObject::*)())&TestObject::methodVolatile);
	reflectMethod("methodVolatile", (int (TestObject::*)() volatile)&TestObject::methodVolatile);
	
	reflectMethod("methodConstVolatile", (int (TestObject::*)())&TestObject::methodConstVolatile);
	reflectMethod("methodConstVolatile", (int (TestObject::*)() const volatile)&TestObject::methodConstVolatile);

	reflectMethod("methodOverload", (int (TestObject::*)(const TestObject &, int) const)&TestObject::methodOverload);
	reflectMethod("methodOverload", (int (TestObject::*)(int, const TestObject &) const)&TestObject::methodOverload);
	reflectMethod("methodOverload", (int (TestObject::*)(int, int) const)&TestObject::methodOverload);
	reflectMethod("methodOverload", (int (TestObject::*)(const char *, int) const)&TestObject::methodOverload);
	reflectMethod("methodOverload", (int (TestObject::*)(int, const char *) const)&TestObject::methodOverload);
	reflectMethod("methodOverload", (int (TestObject::*)(const string &, int) const)&TestObject::methodOverload);
	reflectMethod("methodOverload", (int (TestObject::*)(int, const string &) const)&TestObject::methodOverload);
}



}
