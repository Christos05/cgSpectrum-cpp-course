#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>

using namespace std;

constexpr char kCursor = '_';

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;

constexpr int kEascape = 27;
constexpr int kBackspace = 8;

void getLevelDimensions(int& width, int& height);
void displayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
int GetIndexFromXY(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int Width, int Height);
void saveLevel(char* pLevel, int width, int height);
void DisplayLegend();

int main()
{
    int levelWidth;
    int levelHeight;

    getLevelDimensions(levelWidth, levelHeight);

    char* pLevel = new char[levelWidth * levelHeight];

    for (int i = 0; i < levelWidth * levelHeight; i++)
    {
        pLevel[i] = ' ';
    }

    int cursorX = 0;
    int cursorY = 0;
    bool doneEditing = false;
    while (!doneEditing)
    {
        system("cls");
        displayLevel(pLevel, levelWidth, levelHeight, cursorX, cursorY);
        DisplayLegend();
        doneEditing = EditLevel(pLevel, cursorX, cursorY, levelWidth, levelHeight);
    }

    system("cls");
    displayLevel(pLevel, levelWidth, levelHeight, -1, -1);

    saveLevel(pLevel, levelHeight, levelWidth);

    delete[] pLevel;
    pLevel = nullptr;
}

void DisplayLegend()
{
    cout << "Arrows to move cursor" << endl;
    cout << "ESC to finish editing" << endl;
    cout << "+ | - for walls" << endl;
    cout << "@ for player start" << endl;
    cout << "r g b for key" << endl;
    cout << "R G B for door" << endl;
    cout << "$ for money" << endl;
    cout << "v for vertical moving enemy" << endl;
    cout << "h for horizontal moving enemy" << endl;
    cout << "e for non-moving enemy" << endl;
    cout << "X for end" << endl;
}

void saveLevel(char* pLevel, int width, int height)
{
    cout << "Pick a name for your level file (eg: level1.txt): ";
    string levelName;
    cin >> levelName;

    levelName.insert(0, "../");
    
    ofstream levelFile;
    levelFile.open(levelName);
    if (!levelFile)
    {
        cout << "Opening file Failed!" << endl;
    }
    else
    {
        levelFile << width << endl;
        levelFile << height << endl;
        levelFile.write(pLevel, height * width);
        if (!levelFile)
        {
            cout << "Write Failed!" << endl;
        }
        levelFile.close();
    }
}

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int Width, int Height)
{
    int newCursorX = cursorX;
    int newCursorY = cursorY;

    int intInput = _getch();

    if (intInput == kArrowInput)
    {
        int arrowInput = _getch();
        switch (arrowInput)
        {
        case kLeftArrow:
            newCursorX--;
            break;
        case kRightArrow:
            newCursorX++;
            break;
        case kUpArrow:
            newCursorY--;
            break;
        case kDownArrow:
            newCursorY++;
            break;
        }

        if (newCursorX < 0)
        {
            newCursorX = 0;
        }    
        else if (newCursorX == Width)
        {
            newCursorX = Width - 1;
        }    
        if (newCursorY < 0)
        {
            newCursorY = 0;
        }   
        else if (newCursorY == Width)
        {
            newCursorY = Width - 1;
        }   
        
        cursorX = newCursorX;
        cursorY = newCursorY;
    }
    else
    {
        if (intInput == kEascape)
        {
            return true;
        }
        else if (intInput == kBackspace)
        {
            //Ignore
        }
        else
        {
            int index = GetIndexFromXY(newCursorX, newCursorY, Width);
            pLevel[index] = (char)intInput;
        }
    }
    return false;
}

void getLevelDimensions(int& width, int& height)
{
    cout << "Enter the Width of you level: ";
    cin >> width;

    cout << "Enter the Height of you level: ";
    cin >> height;
}

void displayLevel(char* pLevel, int width, int height, int cursorX, int cursorY)
{
    DisplayTopBorder(width);

    for (int y = 0; y < height; y++)
    {
        DisplayLeftBorder();
        for (int x = 0; x < width; x++)
        {
            if (cursorX == x && cursorY == y)
            {
                cout << kCursor;
            }
            else
            {
                int index = GetIndexFromXY(x, y, width);
                cout << pLevel[index];
            }
        }
        DisplayRightBorder();
    }

    DisplayBottomBorder(width);
}

void DisplayTopBorder(int width)
{
    cout << kTopLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kTopRightBorder << endl;
}
void DisplayBottomBorder(int width)
{
    cout << kBottomLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kBottomRightBorder << endl;
}
void DisplayLeftBorder()
{
    cout << kVerticalBorder;
}
void DisplayRightBorder()
{
    cout << kVerticalBorder << endl;
}

int GetIndexFromXY(int x, int y, int width)
{
    return x + y * width;
}