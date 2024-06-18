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
    double _previousTime{};
    float _viewSize {};

    // Add your variables here
    GLuint _texture {};
    float _angle {};

    SimpleText TextRenderer {};


// Partie MAP

    MAP MAP1;
    int Jeu{0};
    // uMap map
    std::unordered_map<typeCase, GLuint> tiles_textures {};
    std::unordered_map<typeChemin, GLuint> paths_textures {};


// Partie ENNEMIS

    // uMap ennemis
    std::unordered_map<typeEnnemi, GLuint> ennemis_textures {};
    // Ennemis
    Ennemi Elisabeth;
    Ennemi Colin;
    Ennemi Milan;

    bool degatOuNonE{false};
    bool degatOuNonC{false};
    bool degatOuNonM{false};

    int CompteurVagueEnnemis{1};

// Partie TOURS

    // uMap Tours
    std::unordered_map<typeTour, GLuint> tours_textures {};

    Tour Archer;
    Tour Chevalier;
    Tour Sorcier;

    std::vector<Tour> VectTours {};

    void dessineTourCurseur(Tour tour, int x, int y, MAP &Map);
    bool determineSiCaseTourClique(int x, int y, MAP &Map);

    // Enclenche le placement des tours si égale à 1
    bool ActionPlacementTour{0};

    // Compte combien de tours ont été placées
    int CompteurPlacementTour{0};

    // Transforme les coordonnées brutes en coordonnées dans le carré 9x9
    int sourisX{};
    int sourisY{};

    // Coordonnées Tour
    int xposTour{};
    int yposTour{};
    std::vector<int> VectPosTour{};
    std::vector<Ennemi> VectEnnemis{};
    std::vector<int> VectVagueEnnemis = {0,0,1,1,0,1,1,1,0,0,2};

    int PdVCible{100};

    int xEnnemi{0};
    int yEnnemi{0};
};