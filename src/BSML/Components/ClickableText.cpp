#include "BSML/Components/ClickableText.hpp"
#include "logging.hpp"

#include "VRUIControls/VRPointer.hpp"

DEFINE_TYPE(BSML, ClickableText);

namespace BSML {
    void ClickableText::ctor() {
        INVOKE_CTOR();

        isHighlighted = false;
        highlightColor = UnityEngine::Color(0.60f, 0.80f, 1.0f, 1.0f);
        defaultColor = UnityEngine::Color(1.0f, 1.0f, 1.0f, 1.0f);

        onClick = nullptr;
        onEnter = nullptr;
        onExit = nullptr;

        buttonClickedSignal = nullptr;
        hapticFeedbackController = nullptr;
        hapticFeedbackPresetSO = nullptr;

        static auto base_ctor = il2cpp_functions::class_get_method_from_name(classof(HMUI::CurvedTextMeshPro*), ".ctor", 0);
        if (base_ctor) { il2cpp_utils::RunMethod(this, base_ctor); }
        else { ERROR("Could not run base ctor for ClickableText"); }
    }

    void ClickableText::UpdateHighlight() {
        set_color(get_isHighlighted() ? get_highlightColor() : get_defaultColor());
    }

    void ClickableText::OnPointerClick(UnityEngine::EventSystems::PointerEventData* eventData) {
        INFO("Click");
        if (buttonClickedSignal) buttonClickedSignal->Raise();
        set_isHighlighted(false);
        if (onClick) onClick();
    }

    void ClickableText::OnPointerEnter(UnityEngine::EventSystems::PointerEventData* eventData) {
        INFO("Enter");
        set_isHighlighted(true);
        if (onEnter) onEnter();
        Vibrate(!VRUIControls::VRPointer::_get__lastControllerUsedWasRight());
    }

    void ClickableText::OnPointerExit(UnityEngine::EventSystems::PointerEventData* eventData) {
        INFO("Exit");
        set_isHighlighted(false);
        if (onExit) onExit();
    }

    void ClickableText::Vibrate(bool left)
    {
        UnityEngine::XR::XRNode node = left ? UnityEngine::XR::XRNode::LeftHand : UnityEngine::XR::XRNode::RightHand;
        if (hapticFeedbackController && hapticFeedbackPresetSO) hapticFeedbackController->PlayHapticFeedback(node, hapticFeedbackPresetSO);
    }

    void ClickableText::set_highlightColor(UnityEngine::Color color) {
        highlightColor = color;
        UpdateHighlight();
    }

    UnityEngine::Color ClickableText::get_highlightColor() {
        return highlightColor;
    }

    void ClickableText::set_defaultColor(UnityEngine::Color color) {
        defaultColor = color;
        UpdateHighlight();
    }

    UnityEngine::Color ClickableText::get_defaultColor() {
        return defaultColor;
    }

    bool ClickableText::get_isHighlighted() {
        return isHighlighted;
    }

    void ClickableText::set_isHighlighted(bool value) {
        isHighlighted = value;
        UpdateHighlight();
    }
}