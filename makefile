run: main
	./main

main: main.cpp
	g++ main.cpp -o main -lraylib

main.cpp:
	echo "sdf"