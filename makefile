Tum: compile run

compile:
	g++ -I ./include/ -o ./lib/drag.o -c ./src/drag.cpp
	g++ -I ./include/ -o ./bin/Test ./lib/drag.o ./src/main.cpp
	
run:
	cls
	./bin/Test