#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	if (!marioSpriteSheet.loadFromFile("gfx/MarioSheetT.png")) {
		std::cout << "Couldn't load mario sprite sheet\n";
	}

	marioSpr.setTexture(marioSpriteSheet);
	marioSpr.setPosition(sf::Vector2f((window->getSize().x) / 2, (window->getSize().y) / 2));

	marioAnimations[0].setFrameSpeed(0.2);
	marioAnimations[1].setFrameSpeed(0.2);
	marioAnimations[2].setFrameSpeed(0.2);

	for (size_t i = 0; i < 4; i++) {
		marioAnimations[0].addFrame(sf::IntRect(i * 15, 0, 15, 21));
	}
	for (size_t i = 0; i < 3; i++) {
		marioAnimations[1].addFrame(sf::IntRect(i * 16, 21, 16, 20));
	}
	for (size_t i = 0; i < 2; i++) {
		marioAnimations[2].addFrame(sf::IntRect(i * 16, 41, 16, 20));
	}
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Left)) {
		marioAnimations[currentAnimation].play(true);
		marioAnimations[currentAnimation].setFlipped(true);
	}
	else if (input->isKeyDown(sf::Keyboard::Right)) {
		marioAnimations[currentAnimation].play(true);
		marioAnimations[currentAnimation].setFlipped(false);
	}
	else if (input->isKeyDown(sf::Keyboard::Space)) {
		currentAnimation = 1;
	}
	else if (input->isKeyDown(sf::Keyboard::Down)) {
		currentAnimation = 2;
	}
	else {
		currentAnimation = 0;
		marioAnimations[currentAnimation].stop();
	}
}

// Update game objects
void Level::update(float dt)
{
	marioAnimations[currentAnimation].animate(dt);
	marioSpr.setTextureRect(marioAnimations[currentAnimation].getCurrentFrame());
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(marioSpr);
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