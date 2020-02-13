#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	if (!zombieSpriteSheet.loadFromFile("gfx/animZombie.png")) {
		std::cout << "Couldn't load zombie sprite sheet\n";
	}

	zombieSprite.setTexture(zombieSpriteSheet);
	zombieSprite.setPosition(sf::Vector2f((window->getSize().x - 55) / 2, (window->getSize().y - 108) / 2));

	walkAnimation = Animation();
	walkAnimation.setFrameSpeed(0.1);
	for (size_t i = 0; i < 8; i++) {
		walkAnimation.addFrame(sf::IntRect(i*55, 0, 55, 108));
	}
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Left)) {
		walkAnimation.play(true);
		walkAnimation.setFlipped(true);
	}
	else if (input->isKeyDown(sf::Keyboard::Right)) {
		walkAnimation.play(true);
		walkAnimation.setFlipped(false);
	}
	else {
		walkAnimation.stop();
	}
}

// Update game objects
void Level::update(float dt)
{
	walkAnimation.animate(dt);
	zombieSprite.setTextureRect(walkAnimation.getCurrentFrame());
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(zombieSprite);
	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}