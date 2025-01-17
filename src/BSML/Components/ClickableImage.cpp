#include "BSML/Components/ClickableImage.hpp"
#include "logging.hpp"

#include "VRUIControls/VRPointer.hpp"

DEFINE_TYPE(BSML, ClickableImage);

namespace BSML {
    void ClickableImage::ctor() {
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

        static auto base_ctor = il2cpp_functions::class_get_method_from_name(classof(HMUI::ImageView*), ".ctor", 0);
        if (base_ctor) { il2cpp_utils::RunMethod(this, base_ctor); }
        else { ERROR("Could not run base ctor for ClickableImage"); }
    }

    void ClickableImage::UpdateHighlight() {
        set_color(get_isHighlighted() ? get_highlightColor() : get_defaultColor());
    }

    void ClickableImage::OnPointerClick(UnityEngine::EventSystems::PointerEventData* eventData) {
        INFO("Click");
        if (buttonClickedSignal) buttonClickedSignal->Raise();
        set_isHighlighted(false);
        if (onClick) onClick();
    }

    void ClickableImage::OnPointerEnter(UnityEngine::EventSystems::PointerEventData* eventData) {
        INFO("Enter");
        set_isHighlighted(true);
        if (onEnter) onEnter();
        Vibrate(!VRUIControls::VRPointer::_get__lastControllerUsedWasRight());
    }

    void ClickableImage::OnPointerExit(UnityEngine::EventSystems::PointerEventData* eventData) {
        INFO("Exit");
        set_isHighlighted(false);
        if (onExit) onExit();
    }

    void ClickableImage::Vibrate(bool left)
    {
        UnityEngine::XR::XRNode node = left ? UnityEngine::XR::XRNode::LeftHand : UnityEngine::XR::XRNode::RightHand;
        if (hapticFeedbackController && hapticFeedbackPresetSO) hapticFeedbackController->PlayHapticFeedback(node, hapticFeedbackPresetSO);
    }

    void ClickableImage::set_highlightColor(UnityEngine::Color color) {
        highlightColor = color;
        UpdateHighlight();
    }

    UnityEngine::Color ClickableImage::get_highlightColor() {
        return highlightColor;
    }

    void ClickableImage::set_defaultColor(UnityEngine::Color color) {
        defaultColor = color;
        UpdateHighlight();
    }

    UnityEngine::Color ClickableImage::get_defaultColor() {
        return defaultColor;
    }

    bool ClickableImage::get_isHighlighted() {
        return isHighlighted;
    }

    void ClickableImage::set_isHighlighted(bool value) {
        isHighlighted = value;
        UpdateHighlight();
    }
}