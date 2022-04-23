all: compile link

compile:
# 	only compile and assemble main.cpp and not link the object code to produce executable file.
#  	It will generate a main.o object code
	g++ -c main.cpp -I../src/include

link:
#	Compiles and links main.o and generates executable target file with main
	g++ main.o -o main -L../src/lib -lsfml-graphics -lsfml-window -lsfml-system