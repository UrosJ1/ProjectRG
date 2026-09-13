//
// Created by matfrg on 9/13/26.
//

#include "App.hpp"

#include "MainController.hpp"

#include <spdlog/spdlog.h>

namespace app {
void App::app_setup() {
    spdlog::info("MyApp");
    auto controller = register_controller<app::MainController>();
    controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
}

}// app