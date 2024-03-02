// LERP.cpp
#include "LERP.h"

float lerp(float a, float b, float weight) {
    return a * (1 - weight) + b * weight;
}
