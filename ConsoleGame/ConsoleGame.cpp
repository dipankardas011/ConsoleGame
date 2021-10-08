/***
* Future goals
* have to read from the file making sure of SHA 256 code of the file (look for the internet)
* to add the '*' as bombs , '%' as the get way for moving from one place to other liek a ladder
* to add the matrix like scene in background
* @author Dipankar Das
* @version 1.1
*/

#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <ios>
#include <cwchar>

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
        /*
        * 3,5
          1,10
          4,13
        */
        matrix[3][5] = matrix[1][10] = matrix[4][13] = '*';
    }

    void operatorJob()
    {
        SetConsoleTextAttribute(console_color, 3);
        start:
        fprintf(stdout, "\n\n\n");
        fprintf(stdout, "\t\t\t\tControls:\n");
        fprintf(stdout, "\t\t\t\tDown: z key\n");
        fprintf(stdout, "\t\t\t\tUp: w key\n");
        fprintf(stdout, "\t\t\t\tRight: s key\n");
        fprintf(stdout, "\t\t\t\tLeft: a key\n");
        fprintf(stdout, "\n\t\t\t\tRules: R key\n");
        fprintf(stdout, "\t\t\t\tQuit: Q key\n");
        fprintf(stdout, "\n\n");
        fprintf(stdout, "\t\t\t\tEnter E to start the game\n");
        fprintf(stdout, "\t\t\t\t-> ");

        if (_getch() == 'R') {
            system("cls");
            rulesOfGame();
            system("cls");
            goto start;
        }
        if (_getch() == 'E') {
            system("cls");
            construct();
            gameLoop();
        }
        else {
            fprintf(stderr, "INV Key bindings\n");
            exit(EXIT_FAILURE);
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
    bool isBomb(int i, int j) {
        return matrix[i][j]=='*';
    }
    
    void gameLoop();
    void createWindow();
    void rulesOfGame();

    void welcomePage();

private:
    int width, height;
    char** matrix;
    HANDLE console_color;
    int usrRow, usrCol;
    char usr, boundary, empty;
    int wonRow, wonCol;
};

void Game::rulesOfGame() {
    printf("\n\n");
    printf("\t\tRULES\n");
    printf("\t\t> # denotes the boundary\n");
    printf("\t\t> * denotes the bombs\n");
    printf("\t\t> @ denotes the you\n");
    printf("\t\tPress any key to go back...");
    _getch();
}

/***
* increase the speed of update to instant we like use of '\b' or '\c'
*/
void Game::gameLoop(void) {
    SetConsoleTextAttribute(console_color, 12);
    Game::createWindow();
    while (1) {
        bool flag = 0;
        bool used = 0;
        bool exitStatus = 0;
        switch (_getch())
        {
            case 'Q':flag = 1;
            break;

            case 'w': //up 
                if (validBoundary(usrRow - 1, usrCol)) {
                    if (isBomb(usrRow - 1, usrCol)) {
                        exitStatus = true;
                        break;
                    }
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
                    if (isBomb(usrRow +1, usrCol)) {
                        exitStatus = true;
                        break;
                    }
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
                    if (isBomb(usrRow, usrCol+1)) {
                        exitStatus = true;
                        break;
                    }
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
                    if (isBomb(usrRow, usrCol-1)) {
                        exitStatus = true;
                        break;
                    }
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
            fprintf(stdout, "\n\n\t\tYou WON!!");
            return;
        }
        if (exitStatus) {
            system("cls");
            fprintf(stdout, "\n\n\t\tYou LOST!!");
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
                fprintf(stdout, " ");
                continue;
            }
            fprintf(stdout, "%c", matrix[i][j]);
            if (matrix[i][j] == usr) {
                ii = i;
                cc = j;
            }
            
        }
        fprintf(stdout, "\n");
    }

    printf("\nDebug\nusr row: %d\nusr col: %d", ii, cc);
}


void Game::welcomePage() {
    SetConsoleTextAttribute(console_color, 5);
    fprintf(stdout,"\n\n\n");
    
    printf("\t\t***      ***         ****       *********    *******       *******    ****    ****\n");
    printf("\t\t****   *****        *** **         ***       ***   ***       ***        ***  ***\n");
    printf("\t\t*** ***  ***       ***   **        ***       *** * ***       ***          ****\n");
    printf("\t\t***      ***      *** ******       ***       ***   **        ***        ***  ***\n");
    printf("\t\t***      ***     ***     ****      ***       ***   ****    *******    ****    ****\n");
    fprintf(stdout, "\t\t\t\tPress e to ENTER the Game and Q to QUIT\n\t\t\t\t-> ");
    if (_getch() == 'e') {
        system("cls");
    }
    else {
        fprintf(stdout, "Success exited: [0x01]");
        fprintf(stdout, "Stoped");
        exit(EXIT_SUCCESS);
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    system("cls");
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 20;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    Game gg;
    /*another method for the welcome controls, */
    gg.welcomePage();
    gg.operatorJob();
    fprintf(stdout, "press key to exit...  ");
    _getch();
    return EXIT_SUCCESS;
}
