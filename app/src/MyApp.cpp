//
// Created by matfrg on 9/13/26.
//

#include "MyApp.hpp"

#include "GuiController.hpp"
#include "MainController.hpp"

#include <spdlog/spdlog.h>

namespace app {
void MyApp::app_setup() {
    spdlog::info("MyApp");
    auto controller = register_controller<app::MainController>();
    auto gui_controller = register_controller<app::GUIController>();
    controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
    controller->before(gui_controller);
}

}// namespace app