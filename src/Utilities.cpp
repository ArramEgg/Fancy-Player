#include "Utilities.hpp"

ccColor3B FancyPlayer::color4Fto3B(cocos2d::ccColor4F c) {
    return {
        static_cast<GLubyte>(c.r * 255),
        static_cast<GLubyte>(c.g * 255),
        static_cast<GLubyte>(c.b * 255)
    };
} // get 3 byte color from 4 float color (output from hue shifter) for sprites


ccColor4F FancyPlayer::HSVtoRGB(float h, float s, float v, float a) {
    float r, g, b;
    int i = static_cast<int>(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);
    switch (i % 6) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return {r, g, b, a};
} // hue shifter