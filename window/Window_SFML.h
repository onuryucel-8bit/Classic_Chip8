#pragma once
#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../chip8/TypesChip8.h"
#include "../chip8/RomLoader.h"
#include "../chip8/Chip8.h"


class Window_SFML
{
public:
	Window_SFML(std::string CURRENT_DIRECTORY);
	~Window_SFML();

	void run(std::string romFile);

	uint8_t flag;
private:

	RomLoader loader;

	std::string CURRENT_DIRECTORY;

	bool keys[16] = {};

	Chip8 chip;

	sf::RenderWindow* m_window;
	sf::RenderWindow* m_windowInfo;

	sf::RectangleShape pixels[SCREEN_WIDTH * SCREEN_HEIGHT];

	sf::SoundBuffer buffer;
	sf::Font font;

	sf::Text regs[16];
	sf::Text keyboard[16];
	sf::Text PC;//program counter
	sf::Text indexReg;
	sf::Text SP;//stack pointer

	sf::Text delayTimer;
	sf::Text soundTimer;

	sf::Sound sound;

	void createPixels();
	void createWindows();
	void createTexts();
	void createSound();

	void getInputs();
	void updateKeys();

	void drawTexts();

	void clearScreen();

	void updateChip8();

	void waitForKeys();

	void drawPixels();
	
};
