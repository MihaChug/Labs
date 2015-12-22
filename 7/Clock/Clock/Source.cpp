#include "source.h"
#include "Config.h"

using namespace sf;
using namespace std;

void InitializeProgram(Program & program) {
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	program.window = new RenderWindow(VideoMode(SIZE_WINDOW.x, SIZE_WINDOW.y), "Simple clock", sf::Style::Default, settings);

	program.hourHand = new RectangleShape(Vector2f(SIZE_HOUR_HAND));
	InitHand(*program.hourHand, SIZE_HOUR_HAND);
	program.hourHand->setFillColor(Color::Black);

	program.minuteHand = new RectangleShape(Vector2f(SIZE_MINUTE_HAND));
	InitHand(*program.minuteHand, SIZE_MINUTE_HAND);
	program.minuteHand->setFillColor(Color::Black);

	program.secondHand = new RectangleShape(Vector2f(SIZE_SECOND_HAND));
	InitHand(*program.secondHand, SIZE_SECOND_HAND);
	program.secondHand->setFillColor(Color::Red);

	program.circle = new CircleShape;
	program.circle->setRadius(RADIUS);
	program.circle->setPointCount(2000);
	program.circle->setOrigin(RADIUS, RADIUS);
	program.circle->setPosition(SIZE_WINDOW.x / 2, SIZE_WINDOW.y / 2);
	program.circle->setOutlineThickness(300);
	program.circle->setOutlineColor(Color::Black);

	program.divide = new RectangleShape;
	program.divide->setFillColor(Color::Black);
}

void InitHand(RectangleShape & rectangle, const Vector2f & size) {
	rectangle.setOrigin(size.x / 2, size.y);
	rectangle.setPosition(SIZE_WINDOW.x / 2, SIZE_WINDOW.y / 2);
}

void InitPosition(Program & program) {
	for (int i = 0; i < 12; i++) {
		float x = SIZE_WINDOW.x / 2 + RADIUS * cos(i * 30 * M_PI / 180);
		float y = SIZE_WINDOW.y / 2 + RADIUS * sin(i * 30 * M_PI / 180);
		float angle = (i + 3) * 30;
		program.positionDivide.push_back(Vector3f(x, y, angle));
	}
}

void DrawDivides(Program & program) {
	RectangleShape & divide = *program.divide;
	for (int i = 0; i < 12; ++i) {
		float x = program.positionDivide[i].x;
		float y = program.positionDivide[i].y;
		float angle = program.positionDivide[i].z;
		if (i % 3 == 0) {
			divide.setSize(Vector2f(SIZE_BIG_DIVIDE));
			divide.setOrigin(SIZE_BIG_DIVIDE.x / 2, 0);

		}
		else {
			divide.setSize(Vector2f(SIZE_SMALL_DIVIDE));
			divide.setOrigin(SIZE_SMALL_DIVIDE.x / 2, 0);
		}
		divide.setPosition(x, y);
		divide.setRotation(angle);
		program.window->draw(divide);
	}
}

void Delete(Program & program) {
	delete program.circle;
	delete program.hourHand;
	delete program.minuteHand;
	delete program.secondHand;
	delete program.window;
	delete program.divide;
}