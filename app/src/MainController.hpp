//
// Created by matfrg on 9/14/26.
//

#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP
#include <engine/core/Controller.hpp>

namespace app {

class MainController : public engine::core::Controller {
    void initialize() override;

    bool loop() override;

    void draw_planet();

    void draw() override;
};

}// app

#endif //MAINCONTROLLER_HPP
