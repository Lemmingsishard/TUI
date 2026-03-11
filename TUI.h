//#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>

int CurrentSelectedButton = 0; //button x posiiton
int CurrentGroup = 0; //button y position

//the struct for the buttons
struct TextButton {
    int SelectedNumber;
    char *text;
    int ButtonGroup;
    int color;
    int x;
    int y;
};

//the position of the cursor
COORD CursorPos;

//sets the color of the next set of text
void BackgroundColorSetter(HANDLE console, int color) {
    if (color != 0) {
        if (color == 1) {
            SetConsoleTextAttribute(console, BACKGROUND_BLUE);
        } else if (color == 2) {
            SetConsoleTextAttribute(console, BACKGROUND_GREEN);
        } else if (color == 3) {
            SetConsoleTextAttribute(console, BACKGROUND_BLUE | BACKGROUND_GREEN);
        } else if (color == 4) {
            SetConsoleTextAttribute(console, BACKGROUND_RED);
        } else if (color == 5) {
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_BLUE);
        } else if (color == 6) {
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN);
        } else if (color == 7) {
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        } else if (color == 8) {
            SetConsoleTextAttribute(console, BACKGROUND_INTENSITY);
        } else if (color == 9) {
            SetConsoleTextAttribute(console, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (color == 10) {
            SetConsoleTextAttribute(console, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
        } else if (color == 11) {
            SetConsoleTextAttribute(console, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
        } else if (color == 12) {
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_INTENSITY);
        } else if (color == 13) {
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (color == 14) {
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
        } else if (color == 15) {
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
    } else {
        SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    }
}

void ForegroundColorSetter(HANDLE console, int color) {
    if (color != 0) {
        if (color == 1) {
            SetConsoleTextAttribute(console, FOREGROUND_BLUE);
        } else if (color == 2) {
            SetConsoleTextAttribute(console, FOREGROUND_GREEN);
        } else if (color == 3) {
            SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN);
        } else if (color == 4) {
            SetConsoleTextAttribute(console, FOREGROUND_RED);
        } else if (color == 5) {
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_BLUE);
        } else if (color == 6) {
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN);
        } else if (color == 7) {
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else if (color == 8) {
            SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
        } else if (color == 9) {
            SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        } else if (color == 10) {
            SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        } else if (color == 11) {
            SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        } else if (color == 12) {
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
        } else if (color == 13) {
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        } else if (color == 14) {
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        } else if (color == 15) {
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        }
    } else {
        SetConsoleTextAttribute(console, NULL);
    }
}

//sets the cursor position
void CursorPositionSetter(HANDLE console, int x, int y) {
    CursorPos.X = x;
    CursorPos.Y = y;
    SetConsoleCursorPosition(console, CursorPos);
}

//updates variables for a variable display
void VarUpdater(HANDLE console, COORD CursorPos, int var, int color) {
    BackgroundColorSetter(console, color);
    printf("%d ", var);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

//checks if the current selected button is highlighted. If not, it highlights it. This is used inside of the Create_Button variable
int HighLightChecker(HANDLE console, int SelectedNumber, int ButtonGroup, int color) {
    if (SelectedNumber == CurrentSelectedButton && ButtonGroup == CurrentGroup) {
        SetConsoleTextAttribute(console, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    } else {
        SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
        BackgroundColorSetter(console, color);
    }
}

//renders a button to the screen
int Create_Button(HANDLE console, struct TextButton button, int color, int x, int y) {
    CursorPositionSetter(console, x, y);
    HighLightChecker(console, button.SelectedNumber, button.ButtonGroup, color);
    printf("%s", button.text);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

//creates a text display
void Create_Display(HANDLE console, char* text, int color, int x, int y) {
    CursorPositionSetter(console, x, y);
    BackgroundColorSetter(console, color);
    printf("%s", text);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

//creates a display that has an integer variable attached to it
void CreateIntDisplay(HANDLE console, char* text, int color, int value, int x, int y) {
    CursorPositionSetter(console, x, y);
    BackgroundColorSetter(console, color);
    printf("%s%d  ", text, value);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

//clears the screen
void clear(HANDLE console) {
    CONSOLE_SCREEN_BUFFER_INFO csbi; //feeds dwConSize
    DWORD dwConSize; //console dimensions
    DWORD cCharsWritten; //amt of characters written (yes this is necessary)

    CursorPositionSetter(console, 0, 0);
    GetConsoleScreenBufferInfo(console, &csbi);
    /*dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(console, (TCHAR)' ', dwConSize, CursorPos, &cCharsWritten);
    GetConsoleScreenBufferInfo(console, &csbi);
    FillConsoleOutputAttribute(console, csbi.wAttributes, dwConSize, CursorPos, &cCharsWritten);*/

}