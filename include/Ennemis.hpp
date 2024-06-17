#pragma once

#include <img/img.hpp>

// Type d'ennemi
enum class typeEnnemi
{
    elisabeth,
    colin,
    milan,
};

struct Ennemi 
{
    // Détermine si l'ennemi est dans la zone de dégâts
    // void SiDansZoneDegats() {
        
    // }
    typeEnnemi typedEnnemi{};

    float PdVEnnemi{};
    float VitesseEnnemi{};
    float DegatsEnnemi{};

    bool SiEnnemiBouge{};
    bool SiEnnemiMort{};

};