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

void MainController::draw_earth(glm::vec3 colorLight) {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    engine::resources::Model *earth = resources->model("earth");

    engine::resources::Shader *shader = resources->shader("earth");
    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(10.0f, 0.0f, -50.0f));
    model = glm::scale(model, glm::vec3(0.1f));
    shader->set_mat4("model", model);
    resources->texture("earth_texture")->bind(GL_TEXTURE0);
    shader->set_int("texture_earth", 0);
    glm::vec3 lightSourceDirection = glm::normalize(glm::vec3(0.0) - glm::vec3(-1.0f, 0.0f, 10.0f));
    shader->set_vec3("lightDirection", lightSourceDirection);
    shader->set_vec3("lightPos", graphics->camera()->Position);
    shader->set_vec3("viewPos", glm::vec3((1.0f, 0.2f, 0.5f)));
    shader->set_vec3("lightColor", colorLight);
    earth->draw(shader);
}

void MainController::draw_sun() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    engine::resources::Model *sun = resources->model("sun");
    engine::resources::Shader *shader = resources->shader("sun");
    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, -10.0f));
    model = glm::scale(model, glm::vec3(3.0f));
    model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    unsigned int rotate = glGetUniformLocation(shader->id(), "model");
    glUniformMatrix4fv(rotate, 1, GL_FALSE, glm::value_ptr(model));
    shader->set_mat4("model", model);
    resources->texture("sun")->bind(GL_TEXTURE0);


    sun->draw(shader);
}
void MainController::update_light() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KEY_B).state() == engine::platform::Key::State::JustPressed) { colorLight = glm::vec3(0.15f, 0.1f, 1.0f); }
    if (platform->key(engine::platform::KEY_R).state() == engine::platform::Key::State::JustPressed) { colorLight = glm::vec3(1.0f, 0.2f, 0.15f); }
    if (platform->key(engine::platform::KEY_G).state() == engine::platform::Key::State::JustPressed) { colorLight = glm::vec3(0.0f, 1.0f, 0.75f); }
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

void MainController::update() {
    update_camera();
    update_light();
}

void MainController::begin_draw() { engine::graphics::OpenGL::clear_buffers(); }

void MainController::draw_background() {
    auto resource = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto background = resource->skybox("space");
    auto shader = resource->shader("background");
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    graphics->draw_skybox(shader, background);
}

void MainController::draw() {
    draw_earth(colorLight);
    draw_sun();
    draw_background();
}

void MainController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}
}// app