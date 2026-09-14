//
// Created by matfrg on 9/14/26.
//

#include "MainController.hpp"
#include "../../engine/test/app/include/app/MainController.hpp"

#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <spdlog/spdlog.h>

namespace app {
void MainController::initialize() {
    spdlog::info("MainController");
    engine::graphics::OpenGL::enable_depth_testing();
}

bool MainController::loop() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KEY_ESCAPE).is_down()) { return false; }
    return true;
}

void MainController::draw_planet() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    engine::resources::Model *planet = resources->model("earth");

    engine::resources::Shader *shader = resources->shader("implementation");
    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(10.0f, 0.0f, -100.0f));
    model = glm::scale(model, glm::vec3(0.3f));
    shader->set_mat4("model", model);
    planet->draw(shader);
}

void MainController::update_camera() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto camera = graphics->camera();
    float dt = 2.0f;
    if (platform->key(engine::platform::KEY_W).is_down() || platform->key(engine::platform::KEY_UP).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt); }
    if (platform->key(engine::platform::KEY_W).is_down() || platform->key(engine::platform::KEY_UP).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt); }
    if (platform->key(engine::platform::KEY_D).is_down() || platform->key(engine::platform::KEY_RIGHT).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt); }
    if (platform->key(engine::platform::KEY_A).is_down() || platform->key(engine::platform::KEY_LEFT).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt); }
    if (platform->key(engine::platform::KEY_S).is_down() || platform->key(engine::platform::KEY_DOWN).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt); }
}

void MainController::update() { update_camera(); }

void MainController::begin_draw() { engine::graphics::OpenGL::clear_buffers(); }

void MainController::draw() { draw_planet(); }

void MainController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}
}// app