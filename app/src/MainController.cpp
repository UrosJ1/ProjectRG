//
// Created by matfrg on 9/14/26.
//

#include "MainController.hpp"
#include "../../engine/test/app/include/app/MainController.hpp"

#include "GuiController.hpp"
#include "../../engine/libs/glad/include/glad/glad.h"
#include "../../engine/libs/glfw/include/GLFW/glfw3.h"

#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

using namespace std;

namespace app {

class MainPlatformEventObserver : public engine::platform::PlatformEventObserver {
    void on_mouse_move(engine::platform::MousePosition position) override;
};

void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition position) {
    auto gui = engine::core::Controller::get<GUIController>();
    if (!gui->is_enabled()) {
        auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
        camera->rotate_camera(position.dx, position.dy);
    }
}

void MainController::initialize() {
    spdlog::info("MainController");
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->register_platform_event_observer(make_unique<MainPlatformEventObserver>());
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
    engine::resources::Model *earth = resources->model("earth");
    engine::resources::Model *sun = resources->model("sun");

    engine::resources::Shader *shader = resources->shader("implementation");
    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(10.0f, 0.0f, -50.0f));
    model = glm::scale(model, glm::vec3(0.1f));
    model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    unsigned int rotate = glGetUniformLocation(shader->id(), "model");
    glUniformMatrix4fv(rotate, 1, GL_FALSE, glm::value_ptr(model));
    shader->set_mat4("model", model);
    earth->draw(shader);
    engine::resources::Shader *shader1 = resources->shader("implementation");
    shader1->use();
    shader1->set_mat4("projection", graphics->projection_matrix());
    shader1->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model1 = glm::mat4(1.0f);
    model1 = glm::translate(model1, glm::vec3(1.0f, 0.0f, -10.0f));
    model1 = glm::scale(model1, glm::vec3(1.0f));
    shader1->set_mat4("model", model1);
    sun->draw(shader1);
}

void MainController::update_camera() {
    auto gui = engine::core::Controller::get<GUIController>();
    if (gui->is_enabled()) { return; }
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto camera = graphics->camera();
    float dt = 0.2f;
    if (platform->key(engine::platform::KEY_W).is_down() || platform->key(engine::platform::KEY_UP).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt); }
    if (platform->key(engine::platform::KEY_W).is_down() || platform->key(engine::platform::KEY_UP).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt); }
    if (platform->key(engine::platform::KEY_D).is_down() || platform->key(engine::platform::KEY_RIGHT).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt); }
    if (platform->key(engine::platform::KEY_A).is_down() || platform->key(engine::platform::KEY_LEFT).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt); }
    if (platform->key(engine::platform::KEY_S).is_down() || platform->key(engine::platform::KEY_DOWN).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt); }
}

void MainController::update() { update_camera(); }

void MainController::begin_draw() { engine::graphics::OpenGL::clear_buffers(); }

void MainController::draw_background() {
    auto resource = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto background = resource->skybox("space");
    auto shader = resource->shader("background");
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    graphics->draw_skybox(shader, background);
}

void MainController::draw() {
    draw_planet();
    draw_background();
}

void MainController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}
}// app