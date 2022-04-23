#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define GRAY sf::Color(153, 153, 153)
#define WHITE sf::Color::White
#define RED sf::Color::Red
#define BLACK sf::Color::Black

using namespace std;


// generate a random number in range [min,max]
int random(int min,int max){
    srand(time(0) + rand());
    return rand() % (max - min + 1) + min;
}

// x of a cell
inline int x(int num, int tableSize){
    return (num-1) % tableSize;
}

// y of a cell
inline int y(int num, int tableSize){
    return (num-1) / tableSize;
}

inline bool isValid(int num,int numMax){
    if (num >= 0 && num < numMax) return true;
    else return false;
}


// initialize array with value
void initialize(int** array,int arraySize,int value = 0){
    for(int i = 0;i < arraySize;i++){
        for(int j = 0;j < arraySize;j++){
            array[i][j] = value;
        }
    }
}

// count of a cell neighbors
int Neighbors(int x, int y, int tableSize, int** table){
    int cntAliv = 0;
    for (int i = -1;i < 2;i++){
        for(int j = -1;j < 2;j++){
            if (isValid(y + i,tableSize) && isValid(x + j,tableSize) && table[y + i][x + j] && (i != 0 || j != 0)){
                cntAliv++;
            }
        }
    }
    return cntAliv;
}

// check game condition for a cell
void CheckCondition(int x, int y, int tableSize, int** table, int** NextTable){
    if(table[y][x] && Neighbors(x, y, tableSize,table) < 2) NextTable[y][x] = 0;
    if(table[y][x] && Neighbors(x, y, tableSize,table) > 3) NextTable[y][x] = 0;
    if(table[y][x] && (Neighbors(x, y, tableSize, table) == 2 || Neighbors(x, y, tableSize, table) == 3)) NextTable[y][x] = 1;
    if(!table[y][x] && Neighbors(x, y, tableSize, table) == 3) NextTable[y][x] = 1;
}

int main()
{
    const int TableSize = 100;
    int** table; //Game table
    int** NewTable; //next level table

    // special case for home button
    int special[100][100] = {   {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,1,0,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                            };

    table = new int*[TableSize];
    NewTable = new int*[TableSize];
    for (int i = 0;i < TableSize;i++){
        table[i] = new int[TableSize];
        NewTable[i] = new int[TableSize];
    }
    initialize(table,TableSize,0);
    initialize(NewTable,TableSize,0);

    // generate a random num range [1000,5000]
    int cnt = random(10 * TableSize,50 * TableSize); //count of alive cells 
    
    // set which cells to be alive
    int* AliveCells; // Coordinates of alive cells
    AliveCells = new int[cnt];
    for(int i = 0;i < cnt;i++){
        AliveCells[i] = random(1,TableSize * TableSize);
        for(int j = i;j > 0;j--){
            if (AliveCells[i] == AliveCells[j - 1]){
                i--;
            }
        }
    }


    // set cells in "AliveCell" array alive
    for(int i = 0;i < cnt;i++){
        // alive -> 1
        // dead -> 0
        table[y(AliveCells[i],TableSize)][x(AliveCells[i],TableSize)] = 1;
        NewTable[y(AliveCells[i],TableSize)][x(AliveCells[i],TableSize)] = 1;
    }
    
    // window horizontal position 
    int ScreenWidthPos = (sf::VideoMode::getDesktopMode().width - (TableSize * 6 + 10)) / 2;

    sf::Image icon;
    icon.loadFromFile("images/image.png");

    // create a window
    sf::RenderWindow window(sf::VideoMode(TableSize * 6 + 10,TableSize * 6 + 40),"Game of Life");
    window.setPosition(sf::Vector2i(ScreenWidthPos,20));
    window.setIcon(20,20,icon.getPixelsPtr());
    
    // home icon
    sf::Texture texture;
    texture.loadFromFile("images/home.png");

    sf::RectangleShape home(sf::Vector2f(36.f,36.f));
    home.setTexture(&texture);
    home.setPosition(TableSize * 3 - 18,-2);

    sf::Font font;
    font.loadFromFile("fonts/arial.ttf");


    // pause option text
    sf::Text text;
    text.setFont(font);
    text.setString("Paused");
    text.setPosition((TableSize - 13) * 6,5);
    text.setCharacterSize(20);
    text.setFillColor(WHITE);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    // level info
    sf::Text level;
    level.setFont(font);
    level.setPosition(10,5);
    level.setCharacterSize(20);
    level.setFillColor(WHITE);
    level.setStyle(sf::Text::Bold);
    
    
    sf::RectangleShape header;
    header.setSize(sf::Vector2f(TableSize * 6 + 2.F, 25.F));
    header.setOutlineThickness(0);
    header.setPosition(4.f,5.f);
    header.setFillColor(RED);


    int lvlCnt = 0; // level count
    bool isPlay = true;
    float delay = 55; // delay time in milliseconds


    // game loop
    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::EventType::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    
                    // close window by pressing "Escape" key
                    if(event.key.code == sf::Keyboard::Key::Escape)
                        window.close();
                    
                    // pause and unpause by pressing "Space" key
                    else if(event.key.code == sf::Keyboard::Key::Space)
                        isPlay = !isPlay;
                    
                    // increase delay time,50 milliseconds
                    else if(event.key.code == sf::Keyboard::Key::Right)
                            delay += 50;
                    
                    // decrease delay time,50 milliseconds
                    else if(event.key.code == sf::Keyboard::Key::Left)
                        if(delay - 50 > 0)
                            delay -= 50;
                    break;
                default:
                    break;
            }    
        }

        // if mouse clicked on home icon
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i MousePos = sf::Mouse::getPosition(window);
            if (MousePos.x > TableSize * 3 - 18 && MousePos.x < TableSize * 3 + 18 && MousePos.y < 34){
                //special case
                for (int y = 0; y < TableSize; y++){ 
                    for (int x = 0; x < TableSize; x++){
                        table[y][x] = special[y][x];
                        NewTable[y][x] = special[y][x];
                    }
                }
                lvlCnt = 0;
            }
        }

        window.clear(WHITE);

        window.draw(header);


                 
        // draw grid
        for (int y = 0; y < TableSize; y++) {
            for (int x = 0; x < TableSize; x++) {
                sf::RectangleShape Cell;
                Cell.setSize(sf::Vector2f(6.f, 6.f));
                Cell.setOutlineColor(GRAY);
                Cell.setOutlineThickness(1);
                Cell.setPosition(x * 6.F + 5,y * 6.F + 35);
                Cell.setFillColor(WHITE);
                    
                if (table[y][x]){
                    Cell.setFillColor(BLACK);
                }
                window.draw(Cell);
            }
        }

        
        if(isPlay){
            for (int y = 0; y < TableSize; y++){
                for (int x = 0; x < TableSize; x++){
                    CheckCondition(x, y, TableSize, table, NewTable);
                }
            }


            for (int y = 0; y < TableSize; y++){
                for (int x = 0; x < TableSize; x++){
                    table[x][y] = NewTable[x][y];
                }
            }
            lvlCnt++;

        }

        string str = to_string(lvlCnt);
        level.setString("level " + str);

        window.draw(level);

        // paused option text
        if(!isPlay){
            window.draw(text);
        }

        window.draw(home);

        window.display();
        sf::sleep(sf::milliseconds(delay));
    }

    return 1;
}
