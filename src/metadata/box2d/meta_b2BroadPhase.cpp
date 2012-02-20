#include "Box2D/Box2D.h"
#include "Box2D/Collision/b2BroadPhase.h"

#include "cpgf/metadata/box2d/meta_b2BroadPhase.h"

#include "cpgf/gmetapolicy.h"
#include "cpgf/goutmain.h"

extern const char * _mEta_nS_box2d;

using namespace cpgf;

namespace {

G_AUTO_RUN_BEFORE_MAIN()
{
    {
    GDefineMetaClass<void> _d = GDefineMetaClass<void>::define(_mEta_nS_box2d);
    buildMetaClass_Global_b2broadphase(0, _d, NULL, GMetaPolicyCopyAllConstReference());

    }
    

    {
    GDefineMetaClass<void> _ns = GDefineMetaClass<void>::define(_mEta_nS_box2d);
    GDefineMetaClass<b2BroadPhase> _d = GDefineMetaClass<b2BroadPhase>::declare("b2BroadPhase");
    _ns._class(_d);
    buildMetaClass_B2BroadPhase(0, _d, NULL, GMetaPolicyCopyAllConstReference());

    }
    

    {
    GDefineMetaClass<void> _ns = GDefineMetaClass<void>::define(_mEta_nS_box2d);
    GDefineMetaClass<b2Pair> _d = GDefineMetaClass<b2Pair>::declare("b2Pair");
    _ns._class(_d);
    buildMetaClass_B2Pair(0, _d, NULL, GMetaPolicyCopyAllConstReference());

    }
    

}

} // unnamed namespace
