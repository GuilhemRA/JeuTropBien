#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <iostream>
#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"
#include "Map.hpp"
#include "Ennemis.hpp"
#include "Tours.hpp"

struct App {
    App();

    void setup();
    void update();
    
    // GLFW callbacks binding
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);

    int xposCursor{};
    int yposCursor{};

    void size_callback(int width, int height);

    void render();

    int _width {};
    int _height {};
    double _previousTime {};
    float _viewSize {};

    // Add your variables here
    GLuint _texture {};
    float _angle {};

    SimpleText TextRenderer {};

// Partie MAP

    bool JeuStart{0};

    // uMap map
    std::unordered_map<typeCase, GLuint> tiles_textures {};
    img::Image map10x10 {img::load(make_absolute_path("images/Tuiles/map10x10.png", true), 3, false)};
    img::Image map1080x1080 {img::load(make_absolute_path("images/Tuiles/map_design2_v2.png", true), 3, false)};


// Partie ENNEMIS

    // uMap ennemis
    std::unordered_map<typeEnnemi, GLuint> ennemis_textures {};

// Partie TOURS

    std::unordered_map<typeTour, GLuint> tours_textures {};

    // Enclenche le placement des tours si égale à 1
    bool ActionPlacementTour{0};

    // Compte combien de tours ont été placées
    int CompteurPlacementTour{0};

    // Transforme les coordonnées brutes en coordonnées dans le carré 1080x1080
    int xposTourVerif{};
    int yposTourVerif{};

    // Coordonnées Tour 1
    int xposTour1{};
    int yposTour1{};

    // Coordonnées Tour 2
    int xposTour2{};
    int yposTour2{};

    // Coordonnées Tour 3
    int xposTour3{};
    int yposTour3{};

    bool ZoneDegatTour{0};

};