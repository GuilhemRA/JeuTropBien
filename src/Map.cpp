#include "Map.hpp"
#include <vector>
#include <iostream>

std::vector<Case> ChargeVectMap(img::Image* image) {
    std::vector<Case> VectCaseMap{};

    const uint8_t* data { image->data() };
    const unsigned int width { image->width() };
    const unsigned int height { image->height() };

    for(unsigned int i{0}; i<10; i++) {
        for(unsigned int j{0}; j<10; j++) {
            uint8_t r = data[(i+width*j)*3+0];
            uint8_t g = data[(i+width*j)*3+1];
            uint8_t b = data[(i+width*j)*3+2];
            Case C;

            C.R = r;
            C.G = g;
            C.B = b;

            if(r == 0 && g == 0 && b == 0) {
                    C.typeDeCase = typeCase::nonchemin;
            }
            if(r == 0 && g != 0 && b == 0) {
                C.typeDeCase = typeCase::emplacement_tour;
            }
            if(r != 0 && g != 0 && b != 0) {
                C.typeDeCase = typeCase::chemin;
            }
            if(r != 0 && g == 0 && b == 0) {
                C.typeDeCase = typeCase::chemin_depart;
            }
            if(r == 0 && g == 0 && b != 0) {
                C.typeDeCase = typeCase::chemin_arrivee;
            }

            VectCaseMap.push_back(C);
        
        }
    }

    return VectCaseMap;
}

std::vector<Case> VerifPlacementTourVectMap(img::Image* image) {
    std::vector<Case> VectPixelMap{};

    const uint8_t* data { image->data() };
    const unsigned int width { image->width() };
    const unsigned int height { image->height() };

    for(unsigned int i{0}; i<width; i++) {
        for(unsigned int j{0}; j<height; j++) {
            uint8_t r = data[(i+width*j)*3+0];
            uint8_t g = data[(i+width*j)*3+1];
            uint8_t b = data[(i+width*j)*3+2];
            Case P;
            P.R = r;
            P.G = g;
            P.B = b;
            VectPixelMap.push_back(P);
        }
    }

    return VectPixelMap;
}
