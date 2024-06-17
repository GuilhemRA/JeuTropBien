#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>
#include "Map.hpp"

struct Map;

// Type d'ennemi
enum class typeEnnemi
{
    elisabeth,
    colin,
    milan,
};

struct Ennemi 
{
    Position position{0,0};

    // Détermine si l'ennemi est dans la zone de dégâts
    void SiDansZoneDegats();

    int Chemin{0};
    int numeroNoeudActuel{0};
    int numeroNoeudCible{1};

    float TempsEcoule{0};

    typeEnnemi typedEnnemi{};
    GLuint texture;

    float PdVEnnemi{};
    float VitesseEnnemi{2.f};
    float DegatsEnnemi{};

    bool SiEnnemiBouge{};
    bool SiEnnemiMort{};
    bool aNiqueLaBase{false};

    void recupereTemps(const double &elapsedTime);

    void deplacement(std::vector<std::vector<Noeud>> &ListePlusCourtChemin, MAP &map);

};