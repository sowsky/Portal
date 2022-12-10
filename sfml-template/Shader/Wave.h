#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#pragma warning(disable:4996)

using namespace sf;

struct Wave
{
    Wave();
    void Update(float dt);

    Shader shader;
    Texture distortionMap;

    float distortionFactor = .05f;
    float riseFactor = .2f;
    float time = 0.f;
};
