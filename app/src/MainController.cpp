//
// Created by matfrg on 9/14/26.
//

#include "MainController.hpp"
#include "../../engine/test/app/include/app/MainController.hpp"

#include <engine/platform/PlatformController.hpp>
#include <spdlog/spdlog.h>

namespace app {
void MainController::initialize() { spdlog::info("MainController"); }

bool MainController::loop() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KEY_ESCAPE).is_down()) { return false; }
    return true;
}
}// app