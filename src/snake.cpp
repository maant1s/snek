#include "snek.hpp"

Snake::Snake(Position start) : dir(Direction::UP){
	body.push_front(start);
}

Snake::~Snake() = default;

void Snake::move(bool grow){
	auto nextHead = getNextHeadPosition();

	body.push_front(nextHead);
	if(!grow) body.pop_back();
}

void Snake::changeDirection(Direction newDir){
	if((dir == Direction::UP && newDir != Direction::DOWN) ||
	   (dir == Direction::DOWN && newDir != Direction::UP) ||			// TODO think if this can be simplified
	   (dir == Direction::LEFT && newDir != Direction::RIGHT) ||
	   (dir == Direction::RIGHT && newDir != Direction::LEFT)){
		dir = newDir;
	}
}

Position Snake::getHeadPosition() const{
	// if(body.empty()) return {0, 0}; 									// TODO handle empty body error case, maybe throw an exception or kill the game
	return body.front();
}

Position Snake::getNextHeadPosition() const{
	auto head = getHeadPosition();

	switch(dir){
		case Direction::UP:    return {head.first, head.second - 1};
		case Direction::DOWN:  return {head.first, head.second + 1};
		case Direction::LEFT:  return {head.first - 1, head.second};
		case Direction::RIGHT: return {head.first + 1, head.second};
	}

	return head;
}

std::deque<Position> Snake::getBody() const{
	return body;
}

bool Snake::checkSelfCollision() const{
	Position head = getHeadPosition();

	return std::count(body.begin() + 1, body.end(), head) > 0;
}

bool Snake::checkWallCollision() const{
	Position head = getHeadPosition();

	return head.first < 1 || head.first >= WIDTH - 1 || head.second < 1 || head.second >= HEIGHT - 1;		// TODO think if this can be simplified
}