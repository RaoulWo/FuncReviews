all: ticTacToe

.outputFolder:
	mkdir -p out
	
ticTacToe: .outputFolder
	clang -std=c++17 -lstdc++ -lm ticTacToe.cc -Wall -Wextra -o out/ticTacToe
	./out/ticTacToe
