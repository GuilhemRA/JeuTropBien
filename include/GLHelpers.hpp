#pragma once

#include <img/img.hpp>
#include "glad/glad.h"
#include "Map.hpp"

GLuint loadTexture(uint8_t const* data, int width, int height);
inline GLuint loadTexture(img::Image const& image) { return loadTexture(image.data(), image.width(), image.height()); }

void draw_quad_with_texture(float x, float y, GLuint textureId, MAP const &Map);
void draw_quad_with_tower(GLuint textureId);