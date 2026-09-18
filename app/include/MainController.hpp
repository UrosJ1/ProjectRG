//
// Created by matfrg on 9/14/26.
//

#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP
#include <engine/core/Controller.hpp>
#include <glm/vec3.hpp>

namespace app {

class MainController : public engine::core::Controller {
    glm::vec3 colorLight = glm::vec3(1.0f, 1.0f, 0.75f);

    void initialize() override;

    bool loop() override;

    void draw_earth(glm::vec3 colorLight);

    void draw_moon();

    void draw_sun();

    void update_light();

    void update_camera();

    void update() override;

    void begin_draw() override;

    void draw_background();

    void draw() override;

    void end_draw() override;
};

}// app

#endif //MAINCONTROLLER_HPP
