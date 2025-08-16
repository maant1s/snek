#include "snek.hpp"

App::App() = default;
App::~App(){
	this->clearScreen();
	setNonBlockingInput(false);
}

int App::run(){
	setNonBlockingInput(true);
	Level diff;
	
	while(this->keepPlaying(diff)){
		gameLoop(diff);
	}
	
	return EXIT_SUCCESS;
}

void App::gameLoop(Level diff){
	Snake snake(std::pair<int, int>(WIDTH / 2, HEIGHT / 2));
	Position foodPos = getRandomPosition(snake);

	while(true){
		auto grid = this->initGrid();
		char input = readInput();
		bool grow = false;

		switch(input){
			case 'w': snake.changeDirection(Direction::UP); break;
			case 's': snake.changeDirection(Direction::DOWN); break;
			case 'a': snake.changeDirection(Direction::LEFT); break;
			case 'd': snake.changeDirection(Direction::RIGHT); break;
		}

		grid[foodPos.second][foodPos.first] = '*';

		if(snake.getHeadPosition() == foodPos){
			grow = true;
			foodPos = getRandomPosition(snake);
		}

		snake.move(grow);

		if(snake.checkSelfCollision() || snake.checkWallCollision()){
			std::cout << "ded, exiting...\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			break;
		}

		this->drawSnake(snake, grid);
		this->render(grid);

		std::this_thread::sleep_for(
			std::chrono::milliseconds(1000 / ((diff == Level::NORMAL) ? 10 : 15))
		); // max 15 FPS, terminal cannot handle more than that
	}
}

void App::clearScreen(){
/* #ifdef _WIN32
	system("cls");	// TODO change it to something faster
#else */
	std::cout << "\033c";
// #endif
}

bool App::keepPlaying(Level& d){
	std::cout << "Press 'n' for NORMAL, 'h' for HARD, or 'q' to quit: ";
	std::cout.flush();
	
	setNonBlockingInput(false);
	while(read(STDIN_FILENO, nullptr, 0) > 0); // clear the input buffer, still bugged anyway

	char input;
	std::cin >> input;

	while(read(STDIN_FILENO, nullptr, 0) > 0);

	if(input == 'q'){
		return false;
	}
	else if(input == 'n'){
		d = Level::NORMAL;
	}
	else if(input == 'h'){
		d = Level::HARD;
	}
	else{
		std::cout << input;
		std::cout << "Invalid input, assuming NORMAL Level.\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		d = Level::NORMAL;
	}

	setNonBlockingInput(true);
	return true;
}

void App::drawSnake(const Snake& snake, std::vector<std::vector<char>>& grid){
	auto body = snake.getBody();
	
	for(const auto& pos : body){
		grid[pos.second][pos.first] = 'o';
	}

	auto headPos = snake.getHeadPosition();
	grid[headPos.second][headPos.first] = 'O';
}

void App::render(const std::vector<std::vector<char>>& grid){
	this->clearScreen();

	std::string output;
	output.reserve(HEIGHT * (WIDTH + 1));

	for(const auto& row : grid){
		for(const char& cell : row){
			switch(cell){
				case '#': output += ANSI_GREEN; output += cell; break;
				case 'o': output += ANSI_YELLOW; output += cell; break;
				case 'O': output += ANSI_YELLOW; output += cell; break;
				case '*': output += ANSI_RED; output += cell; break;
				default: output += cell; break;
			}
		}
		output += '\n';
	}
	std::cout << output;

	std::cout << ANSI_RESET;
}

std::vector<std::vector<char>> App::initGrid(){
	std::vector<std::vector<char>> grid(HEIGHT, std::vector<char>(WIDTH, ' '));

	for(int i = 0; i < WIDTH; ++i){
		grid[0][i] = '#';
		grid[HEIGHT - 1][i] = '#';
	}
	for(int i = 0; i < HEIGHT; ++i){
		grid[i][0] = '#';
		grid[i][WIDTH - 1] = '#';
	}

	return grid;
}
