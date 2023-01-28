// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT1L
// Names: MD RAKIBUL HASSAN SHEAM | VISHNU KARMEGAM | MEMBER_NAME_3
// IDs: 1211306276 | 1211103388 | MEMBER_ID_3
// Emails: 1211306276@student.mmu.edu.my | 1211103388@student.mmu.edu.my | MEMBER_EMAIL_3
// Phones: +601160738949 | +601123041303| MEMBER_PHONE_3
// *********************************************************

// TODO: Fill in the missing information above and delete this line.

#include "pf/helper.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <math.h>




using namespace std;

namespace pf
{
    const int rowMx = 19;
    const int coloumMx = 19;
    const int zCountMx = 10;

    char gameBoard[rowMx][coloumMx];
    int aAxisX = 0, aAxisY = 0;
    int gameRow = 3;
    int gameColumn = 5;

    int zCount = 1;

    int zLife[zCountMx];
    int zAttack[zCountMx];
    int zRange[zCountMx];
    int zAxisX[zCountMx], zAxisY[zCountMx];
    int aLife = 100;
    int aAttack = 0;



    int clearScreen()
    {
        #if defined(_WIN32)
            return std::system("cls");
        #elif defined(__linux__) || defined(__APPLE__)
            return std::system("clear");
        #endif
    }



    int pause()
    {
       #if defined(_WIN32)
            return std::system("pause");
        #elif defined(__linux__) || defined(__APPLE__)
        return std::system(R"(read -p "Press any key to continue . . . " dummy)");
        #endif
    }




//this funtion is using getting random elements for gameBoard
    char getRendomCharacter() {
        int rNumber = std::rand() % 8;
        if (rNumber == 0)
            return ' ';

        else if (rNumber == 1)
            return '^';
        else if (rNumber == 2)
            return 'v';
        else if (rNumber == 3)
            return '<';
        else if (rNumber == 4)
            return '>';

        else if (rNumber == 5)
            return 'h';
        else if (rNumber == 6)
            return 'p';
        else if (rNumber == 7)
            return 'r';

        return '0';
    }




// this fuction will use for put the random variable in the gameboard and fixed the alien postion
// and help to create the board

    void buildGameBoard()
    {
        for (int r = 0; r < gameRow; ++r)
            for (int c = 0; c < gameColumn; ++c)
                gameBoard[r][c] = pf::getRendomCharacter();

        
        
        aAxisY = gameRow / 2;
        aAxisX = gameColumn / 2;

        gameBoard[aAxisY][aAxisX] = 'A';


        for (int i = 1; i <= zCount; i++) {
            zAxisX[i - 1] = std::rand() % gameColumn;
            zAxisY[i - 1] = std::rand() % gameRow;

            while (gameBoard[zAxisY[i - 1]][zAxisX[i - 1]] <= '0' && gameBoard[zAxisY[i - 1]][zAxisX[i - 1]] >= '9') {
                zAxisX[i - 1] = std::rand() % gameColumn;
                zAxisY[i - 1] = std::rand() % gameRow;
            }
            gameBoard[zAxisY[i - 1]][zAxisX[i - 1]] = i + '0';
        }
    }







// this fuctio is using for display the full gameboard
    void displayBoard()
    {
        cout << "-------------------" << endl
            << "  ALIEN VS ZOMBIE" << endl
            << "-------------------" << endl;

        for (int r = 0; r < gameRow; ++r)
        {
            cout << "\t";
            for (int c = 0; c < gameColumn; ++c)
            {
                cout << "-+-+";
            }
            cout << "-+" << std::endl;


            cout << r + 1 << "\t";
            for (int c = 0; c < gameColumn; ++c)
            {
                cout << " | " << gameBoard[r][c];
            }
            cout << " | " << std::endl;
        }

        cout << "\t";
        for (int c = 0; c < gameColumn; ++c)
        {
            cout << "-+-+";
        }
        cout << "-+" << endl << "\t  ";


        
        
        for (int c = 0; c < gameColumn; ++c)
        {
            cout << c + 1;
            if (c + 1 <= 9)   cout << "   ";
            else if (c + 1 <= 99)   cout << "  ";
        }

        cout << endl << endl;
    }







//this fuction change the game row and columns and take input for the number of zombie
    void configureGameSettings() {
        cout << "Default game settings" << endl
            << "---------------------" << endl
            << "Board Rows: " << gameRow << endl
            << "Board Columns: " << gameColumn << endl
            << "Zombie Count: " << zCount << endl << endl;

        char ch;
        cout << "Do you want to change settings? (y/n)? => ";
        cin >> ch;
        if (ch == 'y' || ch == 'Y') {
            clearScreen();
            cout << "Board settings" << endl
                << "--------------" << endl;

            gameRow = gameColumn = zCount = 0;

            while (gameRow % 2 == 0 || gameRow <= 0 || gameRow > rowMx) {
                cout << "Enter rows => ";
                cin >> gameRow;
                if (gameRow % 2 == 0)
                    cout << "Please enter an odd positive value" << endl;
            }

            while (gameColumn % 2 == 0 || gameColumn <= 0 || gameColumn > coloumMx) {
                cout << "Enter column => ";
                cin >> gameColumn;
                if (gameColumn % 2 == 0)
                    cout << "Please enter an odd positive value" << endl;
            }

            cout << endl << "Zombie settings" << endl
                << "--------------" << endl;
            while (zCount <= 0 || zCount > zCountMx) {
                cout << "Enter number of Zombies => ";
                cin >> zCount;
                if (zCount <= 0)
                    cout << "Please enter a value greater than 0" << endl;
            }
        }

    }




    void init() {
        for (int i = 0; i < zCount; i++) {
            zLife[i] = (5 + (rand() % 20)) * 10;
            zRange[i] = 1 + (rand() % 4);
            zAttack[i] = (1 + (rand() % 2)) * 10;
        }
    }




 
    void showValues( int turn) {
        if (turn == 0)
            cout << "-> ";
        else
            cout << "   ";
        cout << "Alien :\tLife\t" << aLife << ", Attack\t" << aAttack << endl;

        for (int i = 0; i < zCount; i++) {
            if (turn == i + 1)
                cout << "-> ";
            else
                cout << "   ";
            cout << "Zombie " << i + 1 << " :\tLife\t" << zLife[i] << ", Attack\t" << zAttack[i] << ", Range\t" << zRange[i] << endl;
        }
    }


    int finishGame() {
        if (aLife <= 0) {
            aLife = 0;
            gameBoard[aAxisY][aAxisX] = ' ';
            pf::clearScreen();
            pf::displayBoard();
            pf::showValues(0);
            return -1;
        }

        for (int i = 0; i < zCount; i++) {
            if (zLife[i] > 0)
                return 0;
        }
        gameBoard[aAxisY][aAxisX] = ' ';
        pf::clearScreen();
        pf::displayBoard();
        pf::showValues(0);
        return 1;
    }




    int configureBehavoirForAlien(char character, char& replace, int axisX, int axisY) {
        if (character == 'r') {
            cout << "Alien stumbled upn a rock" << endl;
            while (character == 'r')
                character = gameBoard[aAxisY + axisY][aAxisX + axisX] = getRendomCharacter();
            return -1;
        }
        else if (character >= '1' && character <= '9') {
            int zNum = character - '1';
            zLife[zNum] -= aAttack;
            if (zLife[zNum] > 0) {
                cout << "Alien attacks upon zombie " << zNum + 1 << endl
                    << "Zombie " << zNum + 1 << " receives the damage of " << aAttack << endl
                    << "Zombie " << zNum + 1 << " is still alive" << endl;
                return -1;
            }
            else {
                gameBoard[zAxisY[zNum]][zAxisX[zNum]] = ' ';
                zLife[zNum] = 0;
                cout << "Alien attacks upon zombie " << zNum + 1 << endl
                    << "Zombie " << zNum + 1 << " receives the damage of " << aAttack << std::endl
                    << "Zombie " << zNum + 1 << " is dead" <<  endl;
                return 0;
            }
        }
        else if (character == 'h') {
            cout << "Alien finds a health pack" << endl << "Alien's life is increased by 20" << endl;
            aLife += 20;
            if (aLife > 100) aLife = 100;
        }
        else if (character == 'p') {
            int zNear = 0;
            float mappingDistance = 3.40282e+038;
            for (int i = 0; i < zCount; i++) {
                float zDistance = sqrt(pow(zAxisX[i] - aAxisX, 2) + pow(zAxisY[i] - aAxisY, 2));
                if (zDistance < mappingDistance && zLife[i] > 0) {
                    mappingDistance = zDistance;
                    zNear = i;
                }
            }

            zLife[zNear] -= 10;
            if (zLife[zNear] <= 0) {
                cout << "Alien finds a pod " << endl
                    << "Zombie " << zNear + 1 << " receives the damage of 10" << endl
                    << "Zombie " << zNear + 1 << " is dead" << endl;
                gameBoard[zAxisY[zNear]][zAxisX[zNear]] = ' ';
                zLife[zNear] = zAxisX[zNear] = zAxisY[zNear] = 0;

            }
            else
                std::cout << "Alien finds a pod " << endl
                << "Zombie " << zNear + 1 << " receives the damage of 10" << endl
                << "Zombie " << zNear + 1 << " is still alive" << endl;
        }

        else if (character == '>') {
            std::cout << "Alien finds an arrow" << endl << "Alien's attack is increased by 20" << endl;
            aAttack += 20;
            replace = 'r';
        }
        else if (character == '<') {
            std::cout << "Alien finds an arrow" << endl << "Alien's attack is increased by 20" << endl;
            aAttack += 20;
            replace = 'l';
        }
        else if (character == '^') {
            std::cout << "Alien finds an arrow" << endl << "Alien's attack is increased by 20" << endl;
            aAttack += 20;
            replace = 'u';
        }
        else if (character == 'v') {
            std::cout << "Alien finds an arrow" << endl << "Alien's attack is increased by 20" << endl;
            aAttack += 20;
            replace = 'd';
        }
        else if (character == ' ' || character == '.') {
            std::cout << "Alien finds an empty space" << endl;
        }
        return 0;
    }




void clearEnd(){
    aAttack = 0;
    for (int row = 0; row < gameRow; ++row)
        for (int col = 0; col < gameColumn; ++col)
            if (gameBoard[row][col] == '.')
                gameBoard[row][col] = getRendomCharacter();
}





    
}


void gameInterface(int turn) {
    pf::clearScreen();
    pf::displayBoard();
   
}


int alienTurn() {
    string command;
    cout << "Command> ";
    cin >> command;
    

     if (command == "help") {
        cout << "1. up\t\t- Move up\n2. down\t\t- Move down\n3. left\t\t- Move left\n4. right\t- Move right\n5. arrow\t- Change the direction of an arrow\n6. help\t\t- Display these user commands\n7. save\t\t- Save the game\n8. load\t\t- Load a game\n9. quit\t\t- Quit the game\n";
    }

    else if (command == "arrow") {
        int row, col;
        string dir;
        cout << "Enter row => ";
        cin >> row;
        cout << "Enter Column => ";
        cin >> col;
        cout << "Enter direction => ";
        cin >> dir;
        
        
       
    }




    else if (command == "quit") {
        exit(0);
    }
    else {
        cout << "Invalid command" << endl;
    }
    pf::pause();
    return -1;
}





void mainGame() {
    pf::configureGameSettings();
    pf::init();
    pf::buildGameBoard();

    

    while (pf::finishGame()==0) {
        
        pf::clearScreen();
        pf::displayBoard();
        pf::showValues(0);

        while (pf::finishGame() == 0 && alienTurn() == -1) {
            pf::clearScreen();
            pf::displayBoard();
            pf::showValues(0);
        }
        pf::pause();

    }

    if (pf::finishGame() == -1)
        cout << "You Lose" << endl;
    else if(pf::finishGame() == 1)
        cout << "You Won" << endl;


}






int main()
{
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;
    
    char choice = 'y';
    while (choice == 'y') {
        mainGame();
        cout << "Play again(y/n) => ";
        cin >> choice;
        if(choice=='y')
            pf::pause();
        pf::clearScreen();
    }
    return 0;
    
}
