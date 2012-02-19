#include "Box2D/Box2D.h"
#include "Box2D/Common/b2StackAllocator.h"

#include "cpgf/metadata/box2d/meta_b2StackAllocator.h"

#include "cpgf/gmetapolicy.h"
#include "cpgf/goutmain.h"

using namespace cpgf;

namespace {

G_AUTO_RUN_BEFORE_MAIN()
{
    {
    GDefineMetaClass<void> _d = GDefineMetaClass<void>::define("box2d");
    buildMetaClass_Global_b2stackallocator(0, _d, NULL, GMetaPolicyCopyAllConstReference());
    }
    

    {
    GDefineMetaClass<void> _ns = GDefineMetaClass<void>::define("box2d");
    GDefineMetaClass<b2StackAllocator> _d = GDefineMetaClass<b2StackAllocator>::Policy<MakePolicy<GMetaRuleDestructorAbsent> >::declare("b2StackAllocator");
    _ns._class(_d);
    buildMetaClass_B2StackAllocator(0, _d, NULL, GMetaPolicyCopyAllConstReference());
    }
    

    {
    GDefineMetaClass<void> _ns = GDefineMetaClass<void>::define("box2d");
    GDefineMetaClass<b2StackEntry> _d = GDefineMetaClass<b2StackEntry>::declare("b2StackEntry");
    _ns._class(_d);
    buildMetaClass_B2StackEntry(0, _d, NULL, GMetaPolicyCopyAllConstReference());
    }
    

}

} // unnamed namespace

