// ConsoleGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
#ifdef _WIN32
#include <windows.h>

void sleep(unsigned milliseconds)
{
    Sleep(milliseconds);
}
#else
#include <unistd.h>

void sleep(unsigned milliseconds)
{
    usleep(milliseconds * 1000); // takes microseconds
}
#endif

#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
void createWindow(int, int, char**);

class Game {

public:
    Game() {
        width = 80;
        height = 20;
        usrRow = 1;
        usrCol = 3;
        matrix = new char* [height];
        for (int i = 0; i < height; i++)
            matrix[i] = new char[width];
    }

    void construct() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width - 1) {
                    matrix[i][j] = '#';
                }
                else if (i == 0 || i == height - 1) {
                    matrix[i][j] = '#';
                }
                else if (i == usrRow && j == usrCol) {
                    matrix[i][j] = '@';
                }
                else {
                    matrix[i][j] = '-';
                }
            }
        }
    }

    void operatorJob()
    {
        std::cout << "\n\n\n";
        std::cout << "\t\t\tControls:\n";
        std::cout << "\t\t\tDown: z key\n";
        std::cout << "\t\t\tUp: w key\n";
        std::cout << "\t\t\tRight: s key\n";
        std::cout << "\t\t\tLeft: a key\n";
        std::cout << "\t\t\tQuit: Q key\n";
        printf("\t\t\tEnter E to start and Q to Stop!!\n");
        printf("\t\t\t-> ");
        if (_getch() == 'E') {
            system("cls");
            construct();
            gameLoop();
        }
        else {
            printf("Success exited: [0x01]");
            printf("Stoped");
        }
    }
    ~Game() {
        delete(matrix);
    }

    bool validBoundary(int i, int j) {
        if (i > 0 && i < height - 1 && j>0 && j < width - 1)
            return true;
        return false;
    }
    
    void gameLoop();

private:
    int width, height;
    char** matrix;
    int usrRow, usrCol;
};

/***
* increase the speed of update to instant we like use of '\b' or '\c'
*/
void Game::gameLoop(void) {
    while (1) {
        int flag = 0;
        createWindow(height, width, matrix);
        switch (_getch())
        {
            case 'Q':flag = 1;
            break;

            case 'w': //up 
                if (validBoundary(usrRow - 1, usrCol)) {
                    matrix[usrRow][usrCol] = '-';
                    matrix[usrRow-1][usrCol] = '@';
                    usrRow -= 1;
                }
            break;

            case 'z': //down index+1
                if (validBoundary(usrRow + 1, usrCol)) {
                    matrix[usrRow][usrCol] = '-';
                    matrix[usrRow + 1][usrCol] = '@';
                    usrRow += 1;
                }
            break;

            case 's': // right
                if (validBoundary(usrRow , usrCol+1)) {
                    matrix[usrRow][usrCol] = '-';
                    matrix[usrRow][usrCol + 1] = '@';
                    usrCol += 1;
                }
            break;

            case 'a': //left
                if (validBoundary(usrRow , usrCol-1)) {
                    matrix[usrRow][usrCol] = '-';
                    matrix[usrRow][usrCol - 1] = '@';
                    usrCol -= 1;
                }
            break;
        }
        if (flag)
            break;
        system("cls");
        //createWindow(height, width, matrix);
        //sleep(10000);
    }
}


void createWindow(int h, int w, char** m)
{
    int ii, cc;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            std::cout << m[i][j];
            if (m[i][j] == '@') {
                ii = i;
                cc = j;
            }
        }
        printf("\n");
    }
    std::cout << "\n DEBUG!\n" << "usr row: " << ii << "\nusr col: " << cc << std::endl;
}

int main()
{
    system("cls");
    Game gg;
    gg.operatorJob();
    return EXIT_SUCCESS;
}
