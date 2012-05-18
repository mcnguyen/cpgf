// Auto generated file, don't modify.

#ifndef __META_SFML_RENDERWINDOW_H
#define __META_SFML_RENDERWINDOW_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gnamereplacer.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace sf;


namespace meta_sfml { 


template <typename D>
void buildMetaClass_RenderWindow(const cpgf::GMetaDataConfigFlags & config, D _d, const cpgf::GMetaDataNameReplacer * _r)
{
    (void)config; (void)_d; (void)_r; (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (VideoMode, const std::string &, unsigned long, const WindowSettings &)>(cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<1> >())
        ._default(copyVariantFromCopyable(WindowSettings()))
        ._default(copyVariantFromCopyable(Style::Resize|Style::Close))
    ;
    _d.CPGF_MD_TEMPLATE _constructor<void * (WindowHandle, const WindowSettings &)>()
        ._default(copyVariantFromCopyable(WindowSettings()))
    ;
    _d.CPGF_MD_TEMPLATE _method(replaceName("GetWidth", _r), &D::ClassType::GetWidth);
    _d.CPGF_MD_TEMPLATE _method(replaceName("GetHeight", _r), &D::ClassType::GetHeight);
    _d.CPGF_MD_TEMPLATE _method(replaceName("Capture", _r), &D::ClassType::Capture);
    _d.CPGF_MD_TEMPLATE _method(replaceName("ConvertCoords", _r), &D::ClassType::ConvertCoords)
        ._default(copyVariantFromCopyable((const View *)NULL))
    ;
}


} // namespace meta_sfml




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
