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
    bool tourPlacee = false;
    float degats{0};
    int x{};
    int y{};

    typeTour typeDeTour{typeTour::archer};
    GLuint texture;
};