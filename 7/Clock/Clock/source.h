#pragma once

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>
#include <vector>
#include "Config.h"

using namespace sf;
using namespace std;

struct Program {
	RectangleShape *hourHand;
	RectangleShape *minuteHand;
	RectangleShape *secondHand;
	RectangleShape *divide;
	CircleShape *circle;
	RenderWindow *window;
	vector<Vector3f> positionDivide;
};

void InitializeProgram(Program & program);
void InitPosition(Program & program);
void InitHand(RectangleShape & rectangle, const Vector2f & size);
void DrawDivides(Program & program);
void Delete(Program & program);