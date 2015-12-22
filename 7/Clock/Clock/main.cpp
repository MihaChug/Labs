#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include "source.h"


using namespace sf;
using namespace std;

void processEvents(RenderWindow & window, Program & program) {
	Event event;
	while (window.pollEvent(event))
	{
		if ((event.type == Event::Closed) || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			window.close();
	}
}

void update(Program & program, SYSTEMTIME & sysTime) {
	GetSystemTime(&sysTime);
	program.secondHand->setRotation(float(sysTime.wSecond * 6));
	program.minuteHand->setRotation(float((sysTime.wMinute) * 6));
	program.hourHand->setRotation(float((sysTime.wHour + 3) * 30));
}

void render(RenderWindow & window, Program & program) {
	window.clear(Color::White);
	window.draw(*program.circle);
	window.draw(*program.hourHand);
	window.draw(*program.minuteHand);
	window.draw(*program.secondHand);
	DrawDivides(program);
	window.display();
}

int main()
{
	Program *program = new Program;
	InitializeProgram(*program);
	InitPosition(*program);

	RenderWindow & window = *program->window;

	SYSTEMTIME sysTime;
	while (window.isOpen())
	{
		processEvents(window, *program);
		update(*program, sysTime);
		render(window, *program);

	}
	Delete(*program);
	delete program;
	return 0;
}