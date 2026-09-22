//
// Created by matfrg on 9/15/26.
//

#include "GuiController.hpp"

#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>
#include <imgui.h>

namespace app {
void GUIController::initialize() {
    set_enable(true);
}

void GUIController::poll_events() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KEY_TAB).state() == engine::platform::Key::State::JustPressed) { set_enable(!is_enabled()); }
}

void GUIController::draw() {
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    graphics->begin_gui();

    ImGui::Begin("Zdravo!");

    ImGui::SetWindowSize(ImVec2(800, 400));
    ImGui::Text("Dobrodosli u aplikaciju. \nPritiskom na dugme G, svetlost koja se pojavljuje na planetu ce se promeniti u zelenu. \nPritiskom na dugme B, svetlost ce se promeniti u plavu, dok pritiskom na dugme R promenice se u crvenu. \nPritiskom na dugme C, vratice te podrazumevanu boju svetla. \nPritiskom na dugme P, boje svetla ce se menjati na svake dve sekunde, pocinje i zavrsava se podrazumevanom bojom. \nPritiskom na dugme O, mozete ocekivati bilo koju boju svetla. \nMozete se kretati na dugme W, A, S i D, takodje mozete pomerati kameru tako sto pomerite Vas mis. \nZa zatvaranje (i po potrebi ponovo otvaranje) ovog prostora, pretisnite TAB. \nMozete pritisnuti ESCAPE kako biste izasli iz aplikacije.");

    ImGui::End();

    graphics->end_gui();
}
}// namespace app