#pragma once
#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../chip8/TypesChip8.h"
#include "../chip8/RomLoader.h"
#include "../chip8/Chip8.h"
#include "../utils/Radix.h"

enum SCREEN_COLOR{
	BLACK,
	WHITE,
	BLUE,
	GREEN,
	RED,
	YELLOW
};

class Window_SFML
{
public:
	Window_SFML(std::string CURRENT_DIRECTORY, SCREEN_COLOR backColor, SCREEN_COLOR frontColor);
	~Window_SFML();

	void run(std::string romFile);

private:

	SCREEN_COLOR background;
	SCREEN_COLOR frontground;

	RomLoader loader;

	std::string CURRENT_DIRECTORY;

	bool keys[16] = {};

	Chip8 chip;

	sf::RenderWindow* m_window;
	sf::RenderWindow* m_windowInfo;

	sf::RectangleShape pixels[SCREEN_WIDTH * SCREEN_HEIGHT];

	sf::SoundBuffer buffer;
	sf::Sound sound;
	
	sf::Font font;

	//-----for printing chip8 values-------
	sf::Text regs[16];
	sf::Text keyboard[16];
	sf::Text PC;//program counter
	sf::Text indexReg;
	sf::Text SP;//stack pointer

	sf::Text delayTimer;
	sf::Text soundTimer;
	//-------------------------------------
	
	sf::Clock clock;
	sf::Time time;

	void createPixels();
	void createWindows();
	void createTexts();
	void createSound();

	void getInputs();
	void updateKeys();

	void drawTexts();

	void reFreshScreen();
	void clearScreen();

	void updateChip8();

	void waitForKeys();

	void drawPixels();
	
};
