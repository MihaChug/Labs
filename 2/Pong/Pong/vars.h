#ifndef VARS_H
#define VARS_H

#include <SFML\Graphics.hpp>

using namespace sf;

const int width = 640;
const int height = 480;
const int borderSize = 12;
const int margin = 50;
const int moveDistance = 5;

RectangleShape top;
RectangleShape left;
RectangleShape right;
RectangleShape bottom;
RectangleShape ball;
Vector2f BallSpeed(0.1, 0.1);
RectangleShape player1;
RectangleShape player2;
RectangleShape MiddleLine;
enum states { INTRO, PLAYING, P1WON, P1LOST };
Font font;
Text title("Pong", font, 100);
Text start("Press any key to start", font, 60);
Text won("You have won this game.\nCongratulations!", font, 40);
Text lost("You have lost this game,\nbetter luck next time!", font, 40);
Text score("0   0", font, 50);
unsigned Player1Score = 0, Player2Score = 0;
#endif