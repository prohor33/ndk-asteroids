#pragma once

#include <vector>
#include "utils.h"

class Graphic {
public:
	static void DrawPolygon(const std::vector<float>& points, const Vec2& p,
     float angle, utils::Color color);
};