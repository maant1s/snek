#include "snek.hpp"

Position getRandomPosition(const Snake& snake){
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> disX(1, WIDTH - 2);
	std::uniform_int_distribution<int> disY(1, HEIGHT - 2);
	
	Position pos;
	do{
		pos = {disX(rng), disY(rng)};
	}while(std::find(snake.getBody().begin(), snake.getBody().end(), pos) == snake.getBody().end());		// ??????????? works, but why? shouldn't it be the opposite?
																											// even the AI knows lol

	return pos;
}	