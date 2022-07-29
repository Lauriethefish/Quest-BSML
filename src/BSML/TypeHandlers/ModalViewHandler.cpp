#include "BSML/TypeHandlers/ModalViewHandler.hpp"

namespace BSML {
    static ModalViewHandler modalViewHandler{};

    ModalViewHandler::Base::PropMap ModalViewHandler::get_props() const {
        return {
            {"showEvent", {"show-event"}},
            {"hideEvent", {"hide-event"}},
            {"clickOffCloses", {"click-off-closes", "clickerino-offerino-closerino"}},
            {"moveToCenter", {"move-to-center"}}
        };
    }

    ModalViewHandler::Base::SetterMap ModalViewHandler::get_setters() const {
        return {
            {"clickOffCloses", [](auto component, auto value){ component->dismissOnBlockerClicked = value; }},
            {"moveToCenter", [](auto component, auto value){ component->moveToCenter = value; }},
        };
    }

    void ModalViewHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto modalView = reinterpret_cast<BSML::ModalView*>(componentType.component);
        auto host = parserParams.host;
        auto& data = componentType.data;

        auto showEventItr = data.find("showEvent");
        if (showEventItr != data.end()) {
            // TODO: events
        }

        auto hideEventItr = data.find("hideEvent");
        if (hideEventItr != data.end()) {
            // TODO: events
        }

        Base::HandleType(componentType, parserParams);
    }
}