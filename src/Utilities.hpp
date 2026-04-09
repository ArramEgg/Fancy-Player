#pragma once

using namespace geode::prelude;

namespace FancyPlayer {
    cocos2d::ccColor4F HSVtoRGB(float h, float s, float v, float a);
    cocos2d::ccColor3B color4Fto3B(cocos2d::ccColor4F color);
} // namespace FancyPlayer