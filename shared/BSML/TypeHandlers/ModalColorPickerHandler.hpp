#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Components/ModalColorPicker.hpp"

namespace BSML {
    class ModalColorPickerHandler : public TypeHandler<BSML::ModalColorPicker*> {
        public:
            using Base = TypeHandler<BSML::ModalColorPicker*>;
            ModalColorPickerHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    
            virtual void HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
    };
}