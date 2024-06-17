#pragma once

#include <img/img.hpp>

// type de Case
enum class typeCase
{
    chemin,
    
    chemin_vertical,
    chemin_horizontal,

    chemin_haut_gauche,
    chemin_haut_droite,
    chemin_gauche_bas,
    chemin_droite_bas,

    chemin_T,
    chemin_T_inverse,
    chemin_T_gauche,

    chemin_depart,
    chemin_arrivee,

    nonchemin,

    nonchemin_1,
    nonchemin_2,
    nonchemin_3,
    
    emplacement_tour,
};

struct Case
{
    // Position début de case
    int posx{};
    int posy{};
    // Position fin de case
    int posx_plus20{};
    int posy_plus20{};   

    // Couleur
    int R{};
    int G{};
    int B{};

    typeCase typeDeCase{};
};

struct Node 
{
    
};

std::vector<Case> ChargeVectMap(img::Image *image);
std::vector<Case> VerifPlacementTourVectMap(img::Image* image);