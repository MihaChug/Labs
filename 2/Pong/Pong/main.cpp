#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <algorithm>
#include <sstream>
#include "vars.h"

using namespace sf;

bool intersects(const RectangleShape & rect1, const RectangleShape & rect2)
{
	FloatRect r1 = rect1.getGlobalBounds();
	FloatRect r2 = rect2.getGlobalBounds();
	return r1.intersects(r2);
}

int clamp(const int x, const int a, const int b)
{
	return std::min(std::max(a, x), b);
}

int vars()
{
	top.setPosition(0, 0);
	top.setSize(Vector2f(width, borderSize));

	left.setPosition(-borderSize, 0);
	left.setSize(Vector2f(borderSize, height));

	right.setPosition(width, 0);
	right.setSize(Vector2f(borderSize, height));

	bottom.setPosition(0, height - borderSize);
	bottom.setSize(Vector2f(width, borderSize));

	top.setFillColor(Color::Black);
	left.setFillColor(Color::Black);
	right.setFillColor(Color::Black);
	bottom.setFillColor(Color::Black);

	ball.setPosition(width / 2, height / 2);
	ball.setSize(Vector2f(20, 20));
	ball.setFillColor(Color::White);
	ball.setOutlineColor(Color::White);
	ball.setOutlineThickness(1);

	player1.setSize(Vector2f(borderSize, 90));
	player1.setPosition(margin - borderSize, height / 2 - 25);
	player1.setFillColor(Color::White);

	player2.setSize(Vector2f(borderSize, 90));
	player2.setPosition(width - margin, height / 2 - 25);
	player2.setFillColor(Color::White);

	MiddleLine.setFillColor(Color::White);
	MiddleLine.setOutlineColor(Color::White);
	MiddleLine.setOutlineThickness(2);
	MiddleLine.setPosition(width / 2, 0);
	MiddleLine.setSize(Vector2f(0, height));

	if (!font.loadFromFile("ARCADECLASSIC.TTF"))
		return EXIT_FAILURE;

	title.setPosition(width / 2 - title.getGlobalBounds().width / 2, 100);
	title.setColor(Color::White);

	start.setPosition(width / 2 - start.getGlobalBounds().width / 2, 400);
	start.setColor(Color::White);
	
	won.setPosition(width / 2 - won.getGlobalBounds().width / 2, height / 2 - won.getGlobalBounds().height / 2);
	won.setColor(Color::White);
	
	lost.setPosition(width / 2 - lost.getGlobalBounds().width / 2, height / 2 - lost.getGlobalBounds().height / 2);
	lost.setColor(Color::White);
	
	score.setPosition(width / 2 - score.getGlobalBounds().width / 2, 40);
	score.setColor(Color::White);

	return 0;
}

int move()
{
	if (ball.getPosition().y < player2.getPosition().y)
	{
		player2.move(0, -moveDistance / 10.0);
	}
	else if (ball.getPosition().y + ball.getSize().y > player2.getPosition().y + player2.getSize().y)
		player2.move(0, moveDistance / 10.0);

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		player1.move(0, -moveDistance / 20.0);
	}
	else
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player1.move(0, moveDistance / 20.0);
		}
	return 0;
}

int collisions()
{
	if (intersects(player1, bottom) || intersects(player1, top))
	{
		FloatRect t = top.getGlobalBounds();
		FloatRect b = bottom.getGlobalBounds();
		Vector2f p = player1.getPosition();
		p.y = clamp(p.y, t.top + t.height + 5, b.top - player1.getSize().y - 5);
		player1.setPosition(p);
	}
	if (intersects(player2, bottom) || intersects(player2, top))
	{
		FloatRect t = top.getGlobalBounds();
		FloatRect b = bottom.getGlobalBounds();
		Vector2f p = player2.getPosition();
		p.y = clamp(p.y, t.top + t.height + 5, b.top - player2.getSize().y - 5);
		player2.setPosition(p);
	}

	if (intersects(ball, top))
	{
		FloatRect t = top.getGlobalBounds();
		FloatRect b = ball.getGlobalBounds();
		BallSpeed.y = -BallSpeed.y;
		int u = t.top + t.height - b.top;
		ball.move(0, 2 * u);
	}

	if (intersects(ball, bottom))
	{
		FloatRect bot = bottom.getGlobalBounds();
		FloatRect b = ball.getGlobalBounds();
		BallSpeed.y = -BallSpeed.y;
		int u = bot.top - b.height - b.top;
		ball.move(0, 2 * u);
	}

	if (intersects(ball, player1))
	{
		FloatRect p = player1.getGlobalBounds();
		FloatRect b = ball.getGlobalBounds();
		BallSpeed.x = -BallSpeed.x;
		BallSpeed.y = (b.top + b.height / 2 - p.top - p.height / 2) / 100;
		int u = p.left + p.width - b.left;
		b.left = p.left + p.width + u;
		ball.setPosition(b.left, b.top);
		BallSpeed *= 2.f;
	}
	if (intersects(ball, player2))
	{
		FloatRect p = player2.getGlobalBounds();
		FloatRect b = ball.getGlobalBounds();
		BallSpeed.x = -BallSpeed.x;
		BallSpeed.y = (b.top + b.height / 2 - p.top - p.height / 2) / 100;
		int u = b.left + b.width - p.left;
		b.left = p.left - b.width - u;
		ball.setPosition(b.left, b.top);
		BallSpeed.x = BallSpeed.x*2;
		BallSpeed.y = BallSpeed.y*2;
	}

	if (intersects(ball, left))
	{
		Player2Score++;
		std::stringstream str;
		str << Player1Score << "   " << Player2Score;
		score.setString(str.str());
		score.setPosition(width / 2 - score.getGlobalBounds().width / 2, 40);
		FloatRect p = player2.getGlobalBounds();
		FloatRect b = ball.getGlobalBounds();
		ball.setPosition(p.left - b.width - 5, height / 2);
		BallSpeed.x = -0.1;
		BallSpeed.y = 0.1;

	}

	if (intersects(ball, right))
	{
		Player1Score++;
		std::stringstream str;
		str << Player1Score << "   " << Player2Score;
		score.setString(str.str());
		score.setPosition(width / 2 - score.getGlobalBounds().width / 2, 40);
		FloatRect p = player1.getGlobalBounds();
		FloatRect b = ball.getGlobalBounds();
		ball.setPosition(p.left + p.width + 5, height / 2);
		BallSpeed.x = 0.1;
		BallSpeed.y = 0.1;
	}
	return 0;
}

int main()
{
	vars();
	VideoMode videoMode(width, height);
	RenderWindow window(videoMode, "Pong");

	int gameState = INTRO;

	while (window.isOpen())
	{
		window.clear(Color::Black);
		switch (gameState)
		{
		case INTRO:
			window.draw(title);
			window.draw(start);
			break;
		case PLAYING:
			window.draw(MiddleLine);
			window.draw(left);
			window.draw(right);
			window.draw(player1);
			window.draw(player2);
			window.draw(ball);
			window.draw(score);
			window.draw(top);
			window.draw(bottom);
			break;
		case P1WON:
			window.draw(won);
			break;
		case P1LOST:
			window.draw(lost);
			break;
		}

		window.display();

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) ||
				((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
				window.close();
			else
				if ((event.type == Event::KeyPressed) && (gameState == INTRO))
					gameState = PLAYING;
		}

		if (gameState != PLAYING)
			continue;

		if (Player1Score >= 1 && Player1Score >= Player2Score + 2)
			gameState = P1WON;
		if (Player2Score >= 1 && Player2Score >= Player1Score + 2)
			gameState = P1LOST;
		
		move();
		collisions();
		ball.move(BallSpeed.x, BallSpeed.y);

	}
	return EXIT_SUCCESS;
}