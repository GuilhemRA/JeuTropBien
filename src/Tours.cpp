#include "Tours.hpp"

int calibrageTour(int pos) {
    int posTour{};
        if(pos>108 && pos<216) {
            posTour = 162;
        }
        if(pos>216 && pos<324) {
            posTour = 270;
        }
        if(pos>324 && pos<432) {
            posTour = 378;
        }
        if(pos>432 && pos<540) {
            posTour = 486;
        }
        if(pos>540 && pos<648) {
            posTour = 594;
        }
        if(pos>648 && pos<756) {
            posTour = 702;
        }
        if(pos>864 && pos<972) {
            posTour = 918;
        }

    return posTour;
}

// Fonction pour faire un cercle avec choix de couleur et taille fixée
void dessineZoneDegats(float r, float g, float b) {

    glColor3f(r, g, b);
    glScalef(.5f,.5f,.5f);
    glBegin(GL_LINE_LOOP);
        float pi = 3.141592654f;
        int n = 100;
            for(int i = 0; i<n; i++) {
                glVertex2f(cos(i*(2*pi/n)),sin(i*(2*pi/n)));
            }
    glEnd();
}

// Fonction pour faire un carré avec choix de taille et de couleur
void draw_square(int r, int g, int b) {
    glColor3f(r, g, b);
    // glScalef(1.f/54,1.f/54,1.f/54);
    glTranslatef(0.f, 0.f, 0.f);
    glBegin(GL_QUADS);
        glVertex2f(0.f, 0.f);
        glVertex2f(1.f/5, 0.f);
        glVertex2f(1.f/5, -1.f/5);
        glVertex2f(0.f, -1.f/5);
    glEnd();
}