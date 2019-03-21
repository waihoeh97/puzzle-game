#include <iostream>
#include <Windows.h>
#include "conio_yp.h"
#include <cmath>
#include <limits>
#include <fstream>

using namespace std;

enum GRID_TYPE
{
	SOURCE = 0,
	TARGET,
	TARGET_DONE,
	EMPTY,
	STRAIGHT_VERTICAL,
	STRAIGHT_HORIZONTAL,
	L_SHAPE_0_DEGREE,
	L_SHAPE_90_DEGREE,
	L_SHAPE_180_DEGREE,
	L_SHAPE_270_DEGREE,
	T_SHAPE_0_DEGREE,
	T_SHAPE_90_DEGREE,
	T_SHAPE_180_DEGREE,
	T_SHAPE_270_DEGREE,
	TOTAL_TYPE
};

enum DIRECTION
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST,
	NONE,
	TOTAL_DIRECTION
};

struct Node
{
	GRID_TYPE type;
	char **sprite;
	int color;

	int x;
	int y;
	int xOld;
	int yOld;

	//! handle connection
	Node *northNode;
	Node *southNode;
	Node *eastNode;
	Node *westNode;
	bool isNorthConnectable;
	bool isSouthConnectable;
	bool isEastConnectable;
	bool isWestConnectable;

	//! construct the grid type
	void Initialize(GRID_TYPE type);
	void SetType(GRID_TYPE type);
	void CopySprite(char tempSprite[][3]);
};

//! global variables
Node** gridNode;
Node** gridNode1;
int totalRow = 0;
int totalCol = 0;
int totalRowGuide = 0;
int totalColGuide = 0;
int sourceRow = 0;
int sourceCol = 0;
bool isSolved = false;
int targetNumber = 0;
int targetCount = 0;
int totalSteps = 0;
string GridType = "";

int xGrid = 0;
int yGrid = 0;

void Node::Initialize(GRID_TYPE type)
{
	for (int i = 0; i < 3; i++)
	{
		sprite = new char*[3];
		for (int j = 0; j < 3; j++)
		{
			sprite[j] = new char[3];
		}
	}
	SetType(type);
}

void Node::SetType(GRID_TYPE type)
{
	this->type = type;
	if (type == SOURCE)
	{
		color = YELLOW;
		char tempSprite[3][3] =
			{
				{ '#', '#', '#' },
				{ '#', '#', '#' },
				{ '#', '#', '#' }
			};

        isNorthConnectable = true;
        isSouthConnectable = true;
        isEastConnectable = true;
        isWestConnectable = true;

		CopySprite(tempSprite);
	}
	else if (type == TARGET)
	{
		color = BLUE;
		char tempSprite[3][3] =
			{
				{ '#', '#', '#' },
				{ '#', '#', '#' },
				{ '#', '#', '#' }
			};

        isNorthConnectable = true;
        isSouthConnectable = true;
        isEastConnectable = true;
        isWestConnectable = true;

		CopySprite(tempSprite);
	}
	else if (type == TARGET_DONE)
	{
		color = BLUE;
		char tempSprite[3][3] =
			{
				{ '#', '#', '#' },
				{ '#', '#', '#' },
				{ '#', '#', '#' }
			};

        isNorthConnectable = true;
        isSouthConnectable = true;
        isEastConnectable = true;
        isWestConnectable = true;

		CopySprite(tempSprite);
	}
	else if (type == EMPTY)
	{
		color = BLUE;
            char tempSprite[3][3] =
            {
                { ' ', ' ', ' ' },
                { ' ', ' ', ' ' },
                { ' ', ' ', ' ' }
            };

        isNorthConnectable = false;
        isSouthConnectable = false;
        isEastConnectable = false;
        isWestConnectable = false;

		CopySprite(tempSprite);
	}
	else if (type == STRAIGHT_VERTICAL)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', '#', ' ' },
				{ ' ', '#', ' ' },
				{ ' ', '#', ' ' }
			};

		isNorthConnectable = true;
        isSouthConnectable = true;
        isEastConnectable = false;
        isWestConnectable = false;

		CopySprite(tempSprite);
	}
	else if (type == STRAIGHT_HORIZONTAL)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', ' ', ' ' },
				{ '#', '#', '#' },
				{ ' ', ' ', ' ' }
			};

        isNorthConnectable = false;
        isSouthConnectable = false;
        isEastConnectable = true;
        isWestConnectable = true;

		CopySprite(tempSprite);
	}
	else if (type == L_SHAPE_0_DEGREE)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', '#', ' ' },
				{ ' ', '#', '#' },
				{ ' ', ' ', ' ' }
			};

        isNorthConnectable = true;
        isSouthConnectable = false;
        isEastConnectable = true;
        isWestConnectable = false;

		CopySprite(tempSprite);
	}
	else if (type == L_SHAPE_90_DEGREE)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', ' ', ' ' },
				{ ' ', '#', '#' },
				{ ' ', '#', ' ' }
			};

        isNorthConnectable = false;
        isSouthConnectable = true;
        isEastConnectable = true;
        isWestConnectable = false;

		CopySprite(tempSprite);
	}
	else if (type == L_SHAPE_180_DEGREE)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', ' ', ' ' },
				{ '#', '#', ' ' },
				{ ' ', '#', ' ' }
			};

        isNorthConnectable = false;
        isSouthConnectable = true;
        isEastConnectable = false;
        isWestConnectable = true;

		CopySprite(tempSprite);
	}
	else if (type == L_SHAPE_270_DEGREE)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', '#', ' ' },
				{ '#', '#', ' ' },
				{ ' ', ' ', ' ' }
			};

        isNorthConnectable = true;
        isSouthConnectable = false;
        isEastConnectable = false;
        isWestConnectable = true;

		CopySprite(tempSprite);
	}
	else if (type == T_SHAPE_0_DEGREE)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', ' ', ' ' },
				{ '#', '#', '#' },
				{ ' ', '#', ' ' }
			};

        isNorthConnectable = false;
        isSouthConnectable = true;
        isEastConnectable = true;
        isWestConnectable = true;

		CopySprite(tempSprite);
	}
	else if (type == T_SHAPE_90_DEGREE)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', '#', ' ' },
				{ '#', '#', ' ' },
				{ ' ', '#', ' ' }
			};

        isNorthConnectable = true;
        isSouthConnectable = true;
        isEastConnectable = false;
        isWestConnectable = true;

		CopySprite(tempSprite);
	}
	else if (type == T_SHAPE_180_DEGREE)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', '#', ' ' },
				{ '#', '#', '#' },
				{ ' ', ' ', ' ' }
			};

        isNorthConnectable = true;
        isSouthConnectable = false;
        isEastConnectable = true;
        isWestConnectable = true;

		CopySprite(tempSprite);
	}
	else if (type == T_SHAPE_270_DEGREE)
	{
		color = LIGHTRED;
		char tempSprite[3][3] =
			{
				{ ' ', '#', ' ' },
				{ ' ', '#', '#' },
				{ ' ', '#', ' ' }
			};

        isNorthConnectable = true;
        isSouthConnectable = true;
        isEastConnectable = true;
        isWestConnectable = false;

		CopySprite(tempSprite);
	}
}

void Node::CopySprite(char tempSprite[][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sprite[i][j] = tempSprite[i][j];
		}
	}
}

void InvalidChoice ()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	gotoxy(50, totalRow * 3 + totalCol + 4);
	cout << "The shape you have chosen is not applicable...";
	gotoxy(50, totalRow * 3 + totalCol + 8);
	system("PAUSE>NUL");
}

void MainMenu()
{
    textcolor(GREEN);
    gotoxy(20, 10);
    cout << "*************************************************";
    gotoxy(20, 11);
    cout << "||                                             ||";
    gotoxy(20, 12);
    cout << "||              PIPE PUZZLE GAME               ||";
    gotoxy(20, 13);
    cout << "||                                             ||";
    gotoxy(20, 14);
    cout << "*************************************************";
}

void MarkLink(Node* node, DIRECTION direction)
{
    node->color = YELLOW;
    if (node->northNode != NULL && direction != NORTH)
    {
        MarkLink(node->northNode,SOUTH);
    }
    if (node->southNode != NULL && direction != SOUTH)
    {
        MarkLink(node->southNode,NORTH);
    }
    if (node->eastNode != NULL && direction != EAST)
    {
        MarkLink(node->eastNode,WEST);
    }
    if (node->westNode != NULL && direction != WEST)
    {
        MarkLink(node->westNode,EAST);
    }
}

void Unlink()
{
    for (int i = 0; i < totalRow; i++)
    {
        for (int j = 0; j < totalCol; j++)
        {
            if (gridNode[i][j].type == TARGET)
            {
                gridNode[i][j].color = LIGHTBLUE;
            }
            else if (gridNode[i][j].type == SOURCE)
            {
                gridNode[i][j].color = YELLOW;
            }
            else
            {
                gridNode[i][j].color = LIGHTRED;
            }
            gridNode[i][j].northNode = NULL;
            gridNode[i][j].southNode = NULL;
            gridNode[i][j].eastNode = NULL;
            gridNode[i][j].westNode = NULL;
        }
    }
}

bool ParseLink()
{
    Node *currentNode = &gridNode[sourceRow][sourceCol];
    MarkLink(currentNode, NONE);

    for (int i = 0; i < totalRow; i++)
    {
        for (int j = 0; j < totalCol; j++)
        {
            if (gridNode[i][j].type == TARGET)
            {
                if (gridNode[i][j].color == YELLOW)
                {
                    targetCount += 1;
                    gridNode[i][j].type = TARGET_DONE;
                }
            }
            else if (gridNode[i][j].type == TARGET_DONE)
            {
                if (gridNode[i][j].color != YELLOW)
                {
                    targetCount--;
                    gridNode[i][j].type = TARGET;
                }
            }
        }
    }

    if (targetCount == targetNumber)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ReinitializeLink()
{
    for (int i = 0; i < totalRow; i++)
    {
        for (int j = 0; j < totalCol; j++)
        {
            if (i < totalRow - 1)
            {
                if (gridNode[i][j].isSouthConnectable == true && gridNode[i+1][j].isNorthConnectable == true)
                {
                    gridNode[i][j].southNode = &gridNode[i+1][j];
                }
            }
            if (i > 0)
            {
                if (gridNode[i][j].isNorthConnectable == true && gridNode[i-1][j].isSouthConnectable == true)
                {
                    gridNode[i][j].northNode = &gridNode[i-1][j];
                }
            }
            if (j < totalCol - 1)
            {
                if (gridNode[i][j].isEastConnectable == true && gridNode[i][j+1].isWestConnectable == true)
                {
                    gridNode[i][j].eastNode = &gridNode[i][j+1];
                }
            }
            if (j > 0)
            {
                if (gridNode[i][j].isWestConnectable == true && gridNode[i][j-1].isEastConnectable == true)
                {
                    gridNode[i][j].westNode = &gridNode[i][j-1];
                }
            }
        }
    }
}
//! create the game board
void InitializeGrid()
{
    textcolor(WHITE);
    int choice = 0;
    gotoxy(40, 20);
    cout << "1. Easy" << endl;
    gotoxy(40, 22);
    cout << "2. Medium" << endl;
    gotoxy(40, 24);
    cout << "3. Hard" << endl;
    textcolor(YELLOW);
    gotoxy(36, 26);
    cout << "Choose your level: ";
    cin >> choice;
    if (choice == 1)
    {//! Easy mode (1 source, 1 target, shape = all except t-shape)
        GridType = "Easy";
        targetNumber = 1;
        totalRow = 6;
        totalCol = 8;

        GRID_TYPE easy [6][8] =
        {
            {SOURCE, STRAIGHT_VERTICAL, L_SHAPE_0_DEGREE, STRAIGHT_HORIZONTAL, L_SHAPE_90_DEGREE, STRAIGHT_VERTICAL, EMPTY, EMPTY},
            {EMPTY, EMPTY, STRAIGHT_HORIZONTAL, L_SHAPE_0_DEGREE, L_SHAPE_270_DEGREE, STRAIGHT_VERTICAL, STRAIGHT_VERTICAL, L_SHAPE_180_DEGREE},
            {L_SHAPE_90_DEGREE, L_SHAPE_270_DEGREE, L_SHAPE_90_DEGREE, L_SHAPE_180_DEGREE, STRAIGHT_HORIZONTAL, L_SHAPE_270_DEGREE, L_SHAPE_90_DEGREE, EMPTY},
            {STRAIGHT_VERTICAL, L_SHAPE_90_DEGREE, STRAIGHT_HORIZONTAL, L_SHAPE_90_DEGREE, L_SHAPE_270_DEGREE, L_SHAPE_0_DEGREE,L_SHAPE_180_DEGREE, EMPTY},
            {STRAIGHT_HORIZONTAL, L_SHAPE_90_DEGREE, L_SHAPE_270_DEGREE, STRAIGHT_VERTICAL, L_SHAPE_90_DEGREE, L_SHAPE_0_DEGREE, STRAIGHT_HORIZONTAL, EMPTY},
            {L_SHAPE_0_DEGREE, L_SHAPE_180_DEGREE, EMPTY, L_SHAPE_90_DEGREE, L_SHAPE_180_DEGREE, EMPTY, L_SHAPE_180_DEGREE, TARGET},
        };
        gridNode = new Node*[totalRow];
        for (int i = 0; i < totalRow; i++)
        {
            gridNode[i] = new Node[totalCol];
            for (int j = 0; j < totalCol; j++)
            {
                Node tempNode;
                tempNode.Initialize(easy[i][j]);
                if (easy[i][j] == SOURCE)
                {
                    sourceRow = i;
                    sourceCol = j;
                }
                gridNode[i][j] = tempNode;
            }
        }
    }
    else if (choice == 2)
    {//! Medium mode (1 source, 3 target, shape = all)
        GridType = "Medium";
        targetNumber = 3;
        totalRow = 8;
        totalCol = 6;

        GRID_TYPE medium [8][6] =
        {
            {EMPTY, STRAIGHT_VERTICAL, L_SHAPE_270_DEGREE, TARGET, EMPTY, EMPTY},
            {SOURCE, T_SHAPE_270_DEGREE, T_SHAPE_0_DEGREE, T_SHAPE_180_DEGREE, T_SHAPE_180_DEGREE, L_SHAPE_90_DEGREE},
            {EMPTY, EMPTY, EMPTY, L_SHAPE_0_DEGREE, T_SHAPE_270_DEGREE, STRAIGHT_VERTICAL},
            {STRAIGHT_HORIZONTAL, L_SHAPE_270_DEGREE, L_SHAPE_0_DEGREE, L_SHAPE_270_DEGREE, L_SHAPE_270_DEGREE, STRAIGHT_HORIZONTAL},
            {L_SHAPE_90_DEGREE, EMPTY, EMPTY, L_SHAPE_180_DEGREE, L_SHAPE_90_DEGREE, STRAIGHT_VERTICAL},
            {STRAIGHT_HORIZONTAL, L_SHAPE_270_DEGREE, T_SHAPE_0_DEGREE, EMPTY, T_SHAPE_270_DEGREE, T_SHAPE_90_DEGREE},
            {TARGET, STRAIGHT_VERTICAL, STRAIGHT_VERTICAL, EMPTY, T_SHAPE_0_DEGREE, T_SHAPE_90_DEGREE},
            {L_SHAPE_0_DEGREE, L_SHAPE_180_DEGREE, L_SHAPE_180_DEGREE, STRAIGHT_HORIZONTAL, L_SHAPE_270_DEGREE, TARGET},
        };
        gridNode = new Node*[totalRow];
        for (int i = 0; i < totalRow; i++)
        {
            gridNode[i] = new Node[totalCol];
            for (int j = 0; j < totalCol; j++)
            {
                Node tempNode;
                tempNode.Initialize(medium[i][j]);
                if (medium[i][j] == SOURCE)
                {
                    sourceRow = i;
                    sourceCol = j;
                }
                gridNode[i][j] = tempNode;
            }
        }
    }
    else if (choice == 3)
    {//! Hard mode (1 source, 2 target, shape = all)
        GridType = "Hard";
        targetNumber = 2;
        totalRow = 5;
        totalCol = 9;

        GRID_TYPE hard [5][9] =
        {
            {TARGET, L_SHAPE_0_DEGREE, L_SHAPE_270_DEGREE, L_SHAPE_0_DEGREE, L_SHAPE_0_DEGREE, L_SHAPE_180_DEGREE, L_SHAPE_270_DEGREE, L_SHAPE_180_DEGREE, TARGET},
            {EMPTY, L_SHAPE_90_DEGREE, L_SHAPE_0_DEGREE, STRAIGHT_HORIZONTAL, STRAIGHT_HORIZONTAL, STRAIGHT_HORIZONTAL, L_SHAPE_90_DEGREE, L_SHAPE_0_DEGREE, EMPTY},
            {L_SHAPE_180_DEGREE, STRAIGHT_HORIZONTAL, L_SHAPE_180_DEGREE, L_SHAPE_0_DEGREE, STRAIGHT_VERTICAL, L_SHAPE_90_DEGREE, L_SHAPE_270_DEGREE, STRAIGHT_HORIZONTAL, L_SHAPE_270_DEGREE},
            {L_SHAPE_0_DEGREE, T_SHAPE_0_DEGREE, L_SHAPE_90_DEGREE, L_SHAPE_270_DEGREE, EMPTY, L_SHAPE_0_DEGREE, L_SHAPE_180_DEGREE, T_SHAPE_270_DEGREE, L_SHAPE_270_DEGREE},
            {L_SHAPE_0_DEGREE, STRAIGHT_VERTICAL, T_SHAPE_180_DEGREE, L_SHAPE_90_DEGREE, SOURCE, L_SHAPE_0_DEGREE, T_SHAPE_270_DEGREE, STRAIGHT_HORIZONTAL, L_SHAPE_270_DEGREE},
        };
        gridNode = new Node*[totalRow];
        for (int i = 0; i < totalRow; i++)
        {
            gridNode[i] = new Node[totalCol];
            for (int j = 0; j < totalCol; j++)
            {
                Node tempNode;
                tempNode.Initialize(hard[i][j]);
                if (hard[i][j] == SOURCE)
                {
                    sourceRow = i;
                    sourceCol = j;
                }
                gridNode[i][j] = tempNode;
            }
        }
    }
    ReinitializeLink();
}

void DrawGrid()
{
	system("CLS");
	//! Bottom Col Guide
	for (int i = 0; i < totalCol; i++)
	{
		textcolor(WHITE);
		gotoxy(i * 4 + 3, 3 * totalRow + 1 + totalRow);
		cout << "-----";
		gotoxy(i * 4 + 5, 3 * totalRow + 2 + totalRow);
		cout << i;
	}
	//! Left Row Guide
    for (int i = 0; i < totalRow; i++)
    {
        textcolor(WHITE);
        gotoxy(1, i * 4 + 4);
        cout << i;
    }

    for (int i = 0; i < totalRow; i++)
    {
        for (int j = 0; j < totalCol; j++)
        {
            //! drawing Top border
            textcolor(WHITE);
            int xPos = 2 * j + 3 + j;
            int yPos = 3 * i + 1 + i;
            gotoxy(xPos, yPos);
            cout << "-------------";
            //! drawing Left border
            gotoxy(xPos + j, yPos + 1);
            cout << "|";
            gotoxy(xPos + j, yPos + 2);
            cout << "|";
            gotoxy(xPos + j, yPos + 3);
            cout << "|";

            //! Draw Grid
            textcolor(gridNode[i][j].color);
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    gotoxy(xPos + y + j + 1, yPos + x + 1);
                    cout << gridNode[i][j].sprite[x][y];
                }
            }
        }
    }

    //! Right border
    for (int i = 0; i < totalRow; i++)
    {
        textcolor(WHITE);
        int xPos = 2 * totalCol + 3 + totalCol;
        int yPos = 3 * i + 1 + i;
        gotoxy(xPos + totalCol, yPos + 1);
        cout << "|";
        gotoxy(xPos + totalCol, yPos + 2);
        cout << "|";
        gotoxy(xPos + totalCol, yPos + 3);
        cout << "|";
    }

    //! draw navigator
    textcolor(LIGHTMAGENTA);
    gotoxy(yGrid*4 + 6, xGrid*4 + 2);
    cout << "#";
    gotoxy(yGrid*4 + 4, xGrid*4 + 4);
    cout << "#";
    gotoxy(yGrid*4 + 6, xGrid*4 + 4);
    cout << "#";
    gotoxy(yGrid*4 + 4, xGrid*4 + 2);
    cout << "#";
}

void RotateGrid()
{
    bool isRotating = true;
    if (gridNode[xGrid][yGrid].type == SOURCE || gridNode[xGrid][yGrid].type == TARGET)
    {
        gotoxy(50, totalRow * 3 + totalCol + 4);
        cout << "Place not applicable for rotation";
        gotoxy(50, totalRow * 3 + totalCol + 8);
        system("PAUSE>NUL");
        return;
    }
    gotoxy(50, totalRow * 3 + totalCol + 2);
    cout << "Which Rotation? (Refer to the guide on top) : ";

    do
    {
        int choice = -1;
        cin >> choice;
        if (gridNode[xGrid][yGrid].type == SOURCE || gridNode[xGrid][yGrid].type == TARGET || gridNode[xGrid][yGrid].type == EMPTY)
        {
            InvalidChoice();
        }
        else if (gridNode[xGrid][yGrid].type == STRAIGHT_HORIZONTAL || gridNode[xGrid][yGrid].type == STRAIGHT_VERTICAL)
        {
            if (choice == 1)
            {
                gridNode[xGrid][yGrid].SetType(STRAIGHT_HORIZONTAL);
                isRotating = false;
            }
            else if (choice == 2)
            {
                gridNode[xGrid][yGrid].SetType(STRAIGHT_VERTICAL);
                isRotating = false;
            }
            else
            {
                InvalidChoice();
                totalSteps -= 1;
                break;
            }
        }
        else if (gridNode[xGrid][yGrid].type == L_SHAPE_0_DEGREE ||
                 gridNode[xGrid][yGrid].type == L_SHAPE_90_DEGREE ||
                 gridNode[xGrid][yGrid].type == L_SHAPE_180_DEGREE ||
                 gridNode[xGrid][yGrid].type == L_SHAPE_270_DEGREE)
        {
            if (choice == 3)
            {
                gridNode[xGrid][yGrid].SetType(L_SHAPE_0_DEGREE);
                isRotating = false;
            }
            else if (choice == 4)
            {
                gridNode[xGrid][yGrid].SetType(L_SHAPE_90_DEGREE);
                isRotating = false;
            }
            else if (choice == 5)
            {
                gridNode[xGrid][yGrid].SetType(L_SHAPE_180_DEGREE);
                isRotating = false;
            }
            else if (choice == 6)
            {
                gridNode[xGrid][yGrid].SetType(L_SHAPE_270_DEGREE);
                isRotating = false;
            }
            else
            {
                InvalidChoice();
                totalSteps -= 1;
                break;
            }
        }
        else if (gridNode[xGrid][yGrid].type == T_SHAPE_0_DEGREE ||
                 gridNode[xGrid][yGrid].type == T_SHAPE_90_DEGREE ||
                 gridNode[xGrid][yGrid].type == T_SHAPE_180_DEGREE ||
                 gridNode[xGrid][yGrid].type == T_SHAPE_270_DEGREE)
        {
            if (choice == 7)
            {
                gridNode[xGrid][yGrid].SetType(T_SHAPE_0_DEGREE);
                isRotating = false;
            }
            else if (choice == 8)
            {
                gridNode[xGrid][yGrid].SetType(T_SHAPE_90_DEGREE);
                isRotating = false;
            }
            else if (choice == 9)
            {
                gridNode[xGrid][yGrid].SetType(T_SHAPE_180_DEGREE);
                isRotating = false;
            }
            else if (choice == 10)
            {
                gridNode[xGrid][yGrid].SetType(T_SHAPE_270_DEGREE);
                isRotating = false;
            }
            else
            {
                InvalidChoice();
                totalSteps -= 1;
                break;
            }
        }
    } while (isRotating);
    totalSteps += 1;
}

void RotateGridMenu()
{
    //! Determine borders of the grid for movement
    int TotalRow = 0;
    int TotalCol = 0;

    if (GridType == "Easy")
    {
        TotalRow = 5;
        TotalCol = 7;
    }
    else if (GridType == "Medium")
    {
        TotalRow = 7;
        TotalCol = 5;
    }
    else if (GridType == "Hard")
    {
        TotalRow = 4;
        TotalCol = 8;
    }

    //! Movement
    if (GetAsyncKeyState(VK_LEFT))
    {
        if (yGrid > 0)
        {
            yGrid--;
        }
    }
    else if(GetAsyncKeyState(VK_RIGHT))
    {
        if(yGrid < TotalCol)
        {
            yGrid++;
        }
    }
    else if(GetAsyncKeyState(VK_UP))
    {
        if(xGrid > 0)
        {
           xGrid--;
        }
    }
    else if(GetAsyncKeyState(VK_DOWN))
    {
        if(xGrid < TotalRow)
        {
            xGrid++;
        }
    }
    else if(GetAsyncKeyState(VK_SPACE))
    {
        textcolor(WHITE);
        RotateGrid();
        Unlink();
        ReinitializeLink();
        isSolved = ParseLink();
    }
}
//! init - guide for shape number
void InitializeGuide()
{
    totalRowGuide = 3;
    totalColGuide = 7;

    GRID_TYPE guide [3][7] =
    {
        {STRAIGHT_HORIZONTAL, EMPTY, STRAIGHT_VERTICAL, EMPTY, EMPTY, EMPTY, EMPTY},
        {L_SHAPE_0_DEGREE, EMPTY, L_SHAPE_90_DEGREE, EMPTY, L_SHAPE_180_DEGREE, EMPTY, L_SHAPE_270_DEGREE},
        {T_SHAPE_0_DEGREE, EMPTY, T_SHAPE_90_DEGREE, EMPTY, T_SHAPE_180_DEGREE, EMPTY, T_SHAPE_270_DEGREE},
    };
    gridNode1 = new Node*[totalRowGuide];
    for (int i = 0; i < totalRowGuide; i++)
    {
        gridNode1[i] = new Node[totalColGuide];
        for (int j = 0; j < totalColGuide; j++)
        {
            Node tempNode;
            tempNode.Initialize(guide[i][j]);
            if (guide[i][j] == SOURCE)
            {
                sourceRow = i;
                sourceCol = j;
            }
            gridNode1[i][j] = tempNode;
        }
    }
}
//! draw - guide for shape number
void DrawGuide()
{
    //! Display guides
    textcolor(WHITE);
    gotoxy(50, 5);
    cout << "Number of steps taken: " << totalSteps;
    gotoxy(50, totalRow * 3 + totalCol);
    cout << "Use the directional keys to move around";
    gotoxy(50, totalRow * 3 + totalCol + 2);
    cout << "Press space to initialize rotation";

    for (int i = 0; i < totalRowGuide; i++)
    {
        for (int j = 0; j < totalColGuide; j++)
        {
            int xPos = 2 * j + 3 + j;
            int yPos = 3 * i + 1 + i;
            //! Draw Grid
            textcolor(gridNode1[i][j].color);
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    gotoxy(xPos + y + j + 50, yPos + x + 10);
                    cout << gridNode1[i][j].sprite[x][y];
                }
            }
        }
    }

    //! guide number position
    textcolor(WHITE);
    gotoxy(50, 12);
    cout << "1";
    gotoxy(58, 12);
    cout << "2";
    gotoxy(50, 16);
    cout << "3";
    gotoxy(58, 16);
    cout << "4";
    gotoxy(66, 16);
    cout << "5";
    gotoxy(74, 16);
    cout << "6";
    gotoxy(50, 20);
    cout << "7";
    gotoxy(58, 20);
    cout << "8";
    gotoxy(66, 20);
    cout << "9";
    gotoxy(74, 20);
    cout << "10";
}

void HighScore()
{
    textcolor(WHITE);
    cout << "Congratulations!! You Win!" << endl;
    cout << "Please enter your name below" << endl;
    ofstream myFile ("PuzzleGameHighScore.txt", ios::app);

    string n = "";
    int s = totalSteps;
    string gridtype = GridType;

    cin >> n;

    if (myFile.is_open())
    {
        myFile << n << endl;
        myFile << s << endl;
        myFile << gridtype << endl;
        myFile.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    string line;
    ifstream myfile("PuzzleGameHighScore.txt");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << endl;
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

int main()
{
    system("mode con: cols=100 lines=40");
    MainMenu();
    InitializeGrid();
    DrawGrid();
    InitializeGuide();
    DrawGuide();

    do
    {
        RotateGridMenu();
        DrawGrid();
        DrawGuide();
        gotoxy(50, totalRow * 3 + totalCol + 8);
        system("PAUSE>NUL");
    } while (!isSolved);

    system("CLS");
    HighScore();
    system("PAUSE");
	return 0;
}
