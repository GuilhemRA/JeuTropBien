#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>
#include <vector>

#include "utils.hpp"
#include "Graph.hpp"

struct Position
{
    float x{0};
    float y{0};
};

struct Couleur
{
    int R{0};
    int G{0};
    int B{0};
};

// type de Case
enum class typeCase
{
    chemin,

    chemin_depart,
    chemin_arrivee,

    nonchemin,

    nonchemin_1,
    nonchemin_2,
    nonchemin_3,
    
    emplacement_tour,
};

enum class typeChemin
{
    chemin_vertical,
    chemin_horizontal,

    chemin_haut_gauche,
    chemin_haut_droite,
    chemin_gauche_bas,
    chemin_droite_bas,

    chemin_T,
    chemin_T_inverse,
    chemin_T_gauche,
};

struct Case
{
    Position position;
    Couleur couleur;
    typeCase typeDeCase{typeCase::nonchemin};
    typeChemin typeDeChemin{};
    
    bool EstUnNoeud{false};
    GLuint texture;
};

struct Noeud
{
    int numeroNoeud{0};
    Position position;
    std::vector<int> NoeudsConnectado{};
};

struct MAP
{
    img::Image imageMap {img::load(make_absolute_path("images/Map/map10x10.png", true), 3,true)};
    int nombreDePixelEnLigne = 10;

    float tailleMap = 1.f;
    float semiTailleMap = tailleMap/2;
    float taillePixel = tailleMap/nombreDePixelEnLigne;

    std::vector<Case> ListeCase;
    std::vector<Noeud> ListeNoeud;

    std::vector<std::vector<Noeud>> ListePlusCourtChemin;

    Graph::WeightedGraph Graph;

    void recupereNoeudsITD();

    void determineCouleursCase();
    Couleur couleurITD(std::string const &type);
    void associeCouleurTypeCase();

    void determineTypeCase();

    // void connexionNoeudsCase();
    void creationGraph();
    void plusCourtChemin();

    void dessineMap(std::unordered_map<typeCase, GLuint> &tiles_textures, std::unordered_map<typeChemin, GLuint> &paths_textures);
};

std::vector<Case> ChargeVectMap(img::Image *image);
std::vector<Case> VerifPlacementTourVectMap(img::Image* image);