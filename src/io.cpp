#include "snek.hpp"

void setNonBlockingInput(bool enable) {
#ifdef _WIN32
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;

	GetConsoleMode(hStdin, &mode);
	if (enable) {
		mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
		mode |= ENABLE_PROCESSED_INPUT;
	} else {
		mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	}
	SetConsoleMode(hStdin, mode);
#else
	static termios oldt;
	termios newt;

	if(enable){
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
	}
	else{
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, 0);
	}
#endif
}

char readInput(){
	char in = '\0';
	char last = '\0';

	while(read(STDIN_FILENO, &in, 1) > 0){		// clears the input buffer letting the user hold down a key
		last = in;
	}

	return last;
}