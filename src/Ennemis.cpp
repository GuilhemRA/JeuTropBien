#include <iostream>
#include "Ennemis.hpp"
#include "Map.hpp"
#include "GLHelpers.hpp"

void Ennemi::siDansZoneDegats(int x, int y, std::vector<int> VectPosTour) {
    int xPosCase{0};
    int yPosCase{0};
    int xZoneGauche{0};
    int xZoneDroite{0};
    int yZoneBas{0};
    int yZoneHaut{0};

    for(int count{0}; count<=4; count+=2) {

        xPosCase = VectPosTour[count];
        yPosCase = VectPosTour[count+1];

        xZoneGauche = xPosCase - 1;
        xZoneDroite = xPosCase + 1;

        yZoneBas = yPosCase - 1;
        yZoneHaut = yPosCase + 1;

        for(int i = xZoneGauche; i <= xZoneDroite; i++) {
            for(int j = yZoneBas; j <= yZoneHaut; j++) {
                if(x==i && y==j) {
                    this->PdVEnnemi-=.1f; // Dégâts similaires pour chaque Tour
                }
            }
        }
    }
}

void Ennemi::deplacement(std::vector<std::vector<Noeud>> &ListePlusCourtChemin, MAP &Map)
{
    Noeud noeudActuel{ListePlusCourtChemin[this->Chemin][this->numeroNoeudActuel]};
    Noeud noeudCible{ListePlusCourtChemin[this->Chemin][this->numeroNoeudCible]};

        int directionEnX{1};
        int directionEnY{1};

        if (noeudCible.position.x < noeudActuel.position.x)
            directionEnX = -1;

        if (noeudCible.position.y < noeudActuel.position.y)
            directionEnY = -1;

        if (abs(noeudCible.position.x - noeudActuel.position.x) > abs(noeudCible.position.y - noeudActuel.position.y))
        {
            if (std::round(this->position.x * 10) / 10 == noeudCible.position.x)
            {
                this->numeroNoeudCible++;
                this->numeroNoeudActuel++;
            }
            else
                this->position.x += directionEnX * this->VitesseEnnemi * this->TempsEcoule;
        }
        else
        {
            if (std::round(this->position.y * 10) / 10 == noeudCible.position.y)
            {
                this->numeroNoeudCible++;
                this->numeroNoeudActuel++;
            }
            else
                this->position.y += directionEnY * this->VitesseEnnemi * this->TempsEcoule;

        }
    draw_quad_with_texture(this->position.x,  this->position.y, this->texture, Map);
}

void Ennemi::recupereTemps(const double &elapsedTime) {
    this->TempsEcoule = elapsedTime;
}