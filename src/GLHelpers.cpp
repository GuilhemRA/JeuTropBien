#include "GLHelpers.hpp"

#include "glad/glad.h"

GLuint loadTexture(uint8_t const* data, int width, int height) {
    GLuint textureId {};

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // Error on MACOS (segmentation fault) when using glGenerateMipmap
    // glGenerateMipmap(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);

    return textureId;
}

void draw_quad_with_texture(GLuint textureId) {

    // Calibrage du quad sur la grille
    glTranslatef(1.f/10, -1.f/10, 0.f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);
        glVertex2f(-1.f/10, -1.f/10);

        glTexCoord2d(1,0);
        glVertex2f(1.f/10, -1.f/10);

        glTexCoord2d(1,1);
        glVertex2f(1.f/10, 1.f/10);

        glTexCoord2d(0,1);
        glVertex2f(-1.f/10, 1.f/10);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void draw_quad_with_tower(GLuint textureId) {

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // glBindTexture(GL_BLEND, textureId);

    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);
        glVertex2f(-1.f/12.715, -1.f/16.6f);

        glTexCoord2d(1,0);
        glVertex2f(1.f/12.715, -1.f/16.6f);

        glTexCoord2d(1,1);
        glVertex2f(1.f/12.715, 1.f/4.75f);

        glTexCoord2d(0,1);
        glVertex2f(-1.f/12.715, 1.f/4.75f);
    glEnd();

    // glBindTexture(GL_BLEND, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    // glDisable(GL_BLEND);
}