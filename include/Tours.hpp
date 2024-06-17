#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Type de Tour
enum class typeTour
{
    archer,
    chevalier,
    sorcier,
};

struct Tour
{
    typeTour typeDeTour{};

};

int calibrageTour(int xpos);
void dessineZoneDegats(float r, float g, float b);
void draw_square(int r, int g, int b);
