#include "GLHelpers.hpp"

#include "glad/glad.h"
#include "Map.hpp"

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

    // glGenerateMipmap(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);

    return textureId;
}

void draw_quad_with_texture(float x, float y, GLuint textureId, MAP const &Map) {

    float X0 = x / Map.nombreDePixelEnLigne - Map.semiTailleMap;
    float X1 = X0 + Map.taillePixel;
    float Y0 = y / Map.nombreDePixelEnLigne - Map.semiTailleMap;
    float Y1 = Y0 + Map.taillePixel;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glBegin(GL_QUADS);
    
    glTexCoord2d(0, 0);
    glVertex2f(X0, Y0);

    glTexCoord2d(1, 0);
    glVertex2f(X1, Y0);

    glTexCoord2d(1, 1);
    glVertex2f(X1, Y1);

    glTexCoord2d(0, 1);
    glVertex2f(X0, Y1);

    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}