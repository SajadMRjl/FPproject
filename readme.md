Game of life
============
This is the program of "Game of life" writen in c++ using SFML library.
This program is my project for FP semester.

## files
* fonts: folder contains font used in program
* images: images folder
* src: folder contains SFML librarys and headers
* main.cpp: main code file
* dll files: SFML's dlls

## how to run
1. install mingw32-make
    - download and install [mingw-get](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download).
    - lunch [git bash](https://git-scm.com/download/win).
    - type  `mingw-get install mingw32-make` into command line.
2. lunch cmd.
3. change directory to project directory(/1.GameOfLife/).
4. type `mingw32-make -f makefile` into command line.
5. run executable file (type `main.exe` into command line).

## how to run game
1. User can back to home page by pressing game icon.(on home page shown a special case of this game).
2. alive cells generate randomly.
3. The game automatically goes to the next level.
4. User can pause/play by pressing the Space key.
5. User can change speed using left/right arrow keys.
6. User can close the window by pressing Esc key.