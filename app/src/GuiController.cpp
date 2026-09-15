//
// Created by matfrg on 9/15/26.
//

#include "GuiController.hpp"

#include <imgui.h>
#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>

namespace app {
void GUIController::initialize() {
    set_enable(true
            );
}

void GUIController::poll_events() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KEY_TAB).state() == engine::platform::Key::State::JustPressed) { set_enable(!is_enabled()); }
}

void GUIController::draw() {
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    graphics->begin_gui();

    ImGui::Begin("Zdravo!");

    ImGui::Text("Dobrodosli u aplikaciju. Pritiskom na dugme *DUGME*...");

    ImGui::End();

    graphics->end_gui();
}
}// app