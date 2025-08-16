// TODO clean up and organize this file

#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>
#include <cstdlib>
#include <deque>
#include <algorithm>
#include <random>
#include <limits>

/* #ifdef _WIN32
	#include <windows.h>
	#include <conio.h>
#else */
	#include <termios.h>
	#include <unistd.h>
	#include <fcntl.h>
	
	constexpr char ANSI_RESET[] = "\033[0m";
	constexpr char ANSI_RED[] = "\033[31m";
	constexpr char ANSI_GREEN[] = "\033[32m";
	constexpr char ANSI_YELLOW[] = "\033[33m";
	constexpr char ANSI_BLUE[] = "\033[34m";
// #endif
	
using Position = std::pair<int, int>;

static constexpr int WIDTH = 48;
static constexpr int HEIGHT = 27;

void setNonBlockingInput(bool enable);
char readInput();

enum class Level{
	NORMAL,
	HARD
};

enum class Direction{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake{
	private:
	std::deque<Position> body;
	Direction dir;
	
	public:
	Snake(Position start);
	~Snake();

	void move(bool grow);
	void changeDirection(Direction newDir);
	
	Position getHeadPosition() const;
	Position getNextHeadPosition() const;
	std::deque<Position> getBody() const;
	
	bool checkSelfCollision() const;
	bool checkWallCollision() const;
};

Position getRandomPosition(const Snake& snake);

class App{
	private:
	void clearScreen();
	void drawSnake(const Snake& snek, std::vector<std::vector<char>>& grid);
	void render(const std::vector<std::vector<char>>& grid);
	bool keepPlaying(Level& d);
	void gameLoop(Level diff);

	std::vector<std::vector<char>> initGrid();

public:
	App();
	~App();

	int run();
};