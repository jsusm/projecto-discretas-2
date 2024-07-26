build:
	g++ main.cpp -o main

debug:
	clang++ main.cpp -g -o main

run: build
	./main

