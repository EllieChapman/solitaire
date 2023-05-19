top: run

run: main.exe
	./main.exe

main.exe: main.o state.o utils.o
	g++ $^ -l stdc++ -o $@

main.o: main.cpp state.h utils.h
	g++ -Wall -Werror $< -c -o $@

state.o: state.cpp state.h utils.h
	g++ -Wall -Werror $< -c -o $@

utils.o: utils.cpp utils.h
	g++ -Wall -Werror $< -c -o $@