#include "App.hpp"
#include "../../engine/test/app/include/app/TestApp.hpp"

#include <engine/core/Engine.hpp>
#include <engine/core/App.hpp>

using namespace std;

int main(int argc, char **argv) {
    auto app = make_unique<app::App>();
    return app->run(argc, argv);
}
