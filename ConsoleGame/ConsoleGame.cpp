// ConsoleGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
#ifdef _WIN32
#include <windows.h>

void sleep(unsigned milliseconds)
{
    Sleep(milliseconds);
}
#endif

#include <iostream>
#include <time.h>
#include <conio.h>
#include <ios>

class Game {

public:
    Game() {
        width = 20;
        height = 7;
        usrRow = 1;
        usrCol = 2;
        usr = '@';
        boundary = '#';
        empty = '.';
        wonRow = height - 2;
        wonCol = width - 2;
        matrix = new char* [height];
        for (int i = 0; i < height; i++)
            matrix[i] = new char[width];
        
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                matrix[i][j] = empty;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width - 1) {
                    matrix[i][j] = boundary;
                }
                else if (i == 0 || i == height - 1) {
                    matrix[i][j] = boundary;
                }
                else if (i == usrRow && j == usrCol) {
                    matrix[i][j] = usr;
                }
            }
        }
        matrix[wonRow][wonCol] = 'X';

        console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void construct() {
        //matrix[height / 2][width / 2] = boundary;
        for (int row = 1; row < height / 2; row++)
            matrix[row][3] = boundary;
           
        for(int row=0; row<height/2; row++)
            matrix[height - 2 - row][width - 4] = boundary;
        matrix[2][7] = boundary;

        matrix[height - 2][3] = boundary;
        for (int col = 3; col < 6; col++)
            matrix[height - 3][col] = boundary;
        
        for (int row = 1; row <= height / 2; row++)
            matrix[row][width - 7] = boundary;

        for (int row = height/2; row <height; row++)
            matrix[row][width - 10] = boundary;

    }

    void operatorJob()
    {
        SetConsoleTextAttribute(console_color, 3);
        printf( "\n\n\n");
        printf( "\t\t\tControls:\n");
        printf( "\t\t\tDown: z key\n");
        printf( "\t\t\tUp: w key\n");
        printf( "\t\t\tRight: s key\n");
        printf( "\t\t\tLeft: a key\n");
        printf( "\t\t\tQuit: Q key\n");
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
        if (i > 0 && i < height - 1 && j>0 && j < width - 1 && matrix[i][j]!=boundary)
            return true;
        return false;
    }
    
    void gameLoop();
    void createWindow();

private:
    int width, height;
    char** matrix;
    HANDLE console_color;
    int usrRow, usrCol;
    char usr, boundary, empty;
    int wonRow, wonCol;
};

/***
* increase the speed of update to instant we like use of '\b' or '\c'
*/
void Game::gameLoop(void) {
    SetConsoleTextAttribute(console_color, 10);
    Game::createWindow();
    while (1) {
        int flag = 0;
        int used = 0;
        switch (_getch())
        {
            case 'Q':flag = 1;
            break;

            case 'w': //up 
                if (validBoundary(usrRow - 1, usrCol)) {
                    matrix[usrRow][usrCol] = empty;
                    matrix[usrRow-1][usrCol] = usr;
                    usrRow -= 1;
                }
                else {
                    used = 1;
                }
            break;

            case 'z': //down index+1
                if (validBoundary(usrRow + 1, usrCol)) {
                    matrix[usrRow][usrCol] = empty;
                    matrix[usrRow + 1][usrCol] = usr;
                    usrRow += 1;
                }
                else {
                    used = 1;
                }
            break;

            case 's': // right
                if (validBoundary(usrRow , usrCol+1)) {
                    matrix[usrRow][usrCol] = empty;
                    matrix[usrRow][usrCol + 1] = usr;
                    usrCol += 1;
                }
                else {
                    used = 1;
                }
            break;

            case 'a': //left
                if (validBoundary(usrRow , usrCol - 1)) {
                    matrix[usrRow][usrCol] = empty;
                    matrix[usrRow][usrCol - 1] = usr;
                    usrCol -= 1;
                }
                else {
                    used = 1;
                }
            break;
            default:continue;
        }
        if (flag)
            break;
        if (usrRow == wonRow && usrCol== wonCol) {
            system("cls");
            printf("\n\n\t\tYou WON!!");
            return;
        }
        if (used == 0)
        {
            system("cls");

            Game::createWindow();
        }
    }
}


void Game::createWindow()
{
    int ii=0, cc=0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix[i][j] == empty)
            {
                printf(" ");
                continue;
            }
            printf("%c", matrix[i][j]);
            if (matrix[i][j] == usr) {
                ii = i;
                cc = j;
            }
            
        }
        printf("\n");
    }

    printf("\nDebug\nusr row: %d\nusr col: %d", ii, cc);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    system("cls");
    Game gg;
    gg.operatorJob();
    printf("press key to exit...  ");
    _getch();
    return EXIT_SUCCESS;
}
