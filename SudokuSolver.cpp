//Sudoku Solver
//By Steven Hricenak

//A C++ program that takes a board from the text file Sudoku.txt
//and prints a solution to it to the console.

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void findNextEmptyDigit();
void solveSquare(int i, int j);
bool rowIsLegal(int row);
bool colIsLegal(int col);
bool squareIsLegal(int row, int col);
void printBoard();

int board[9][9];

/**
 * Initializes the board, prints unsolved board, makes
 * the first recursive call, then prints the solved board.
 */
int main()
{
    ifstream in;
	in.open("Sudoku.txt");
	
	char nextChar;
	
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9;)
		{
			nextChar = in.get();
			if(nextChar <= '9' && nextChar >= '0')
			{
				board[i][j] = nextChar - 48;
				j++;
			}
		}
	
	printBoard();
	findNextEmptyDigit();
	
	cin.get();
		
	return 0;
}

/**
 * Searches the game board for the next empty square.
 */
void findNextEmptyDigit()
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			if(board[i][j] == 0)
			{
				solveSquare(i, j);
				return;
			}
	
	printBoard();
}

/**
 * The recursive call. Checks each possible value a square could be,
 * from 1 to 9. If the value it tries is legal, then it calls
 * findNextEmptyDigit to continue solving th board. If none of the 
 * nine numbers work, then the call staack returns to the previous 
 * square and continues seaching for the next number that works.
 */
void solveSquare(int i, int j)
{
	for(int n = 1; n <= 9; n++)
	{
		board[i][j] = n;
		if(rowIsLegal(i) && colIsLegal(j) && squareIsLegal(i, j))
			findNextEmptyDigit();
	}
		
	board[i][j] = 0;
}

/**
 * A helper function to check if there are any duplicate numbers in
 * the given row.
 */
bool rowIsLegal(int row)
{
	bool numbers[9];
	
	for(int i = 0; i < 9; i++)
		numbers[i] = false;
	
	int index;
	for(int i = 0; i < 9; i++)
	{
		index = board[row][i];
		if(index != 0)
		{
			if(!numbers[index - 1])
			{
				numbers[index - 1] = true;
			}
			else
			{
				return false;
			}
		}
	} 
	
	return true;
}

/**
 * A helper function to check if there are any duplicate numbers in
 * the given column.
 */
bool colIsLegal(int col)
{
	bool numbers[9];
	
	for(int i = 0; i < 9; i++)
		numbers[i] = false;
	
	int index;
	for(int i = 0; i < 9; i++)
	{
		index = board[i][col];
		if(index != 0)
		{
			if(!numbers[index - 1])
			{
				numbers[index - 1] = true;
			}
			else
			{
				return false;
			}
		}
	} 
	
	return true;
}

/**
 * A helper function to check if the larger square where the 
 * given coordinates lie have any duplicate numbers in it.
 */
bool squareIsLegal(int row, int col)
{
	int squareRow = row/3;
	int squareCol = col/3;
	
	bool numbers[9];
	
	for(int i = 0; i < 9; i++)
		numbers[i] = false;	   
		
	int index;
	
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		{
			index = board[3*squareRow + i][3*squareCol + j];
			if(index != 0)
			{
				if(!numbers[index - 1])
				{
					numbers[index - 1] = true;
				}
				else
				{
					return false;
				}
			}
		}
		
	return true;
}

/**
 * Prints the board to the console.
 */ 
void printBoard()
{
	for(int i = 0; i < 9; i++)
	{
		if(i > 0 && i%3==0)
			cout << "-----------\n";
			
		for(int j = 0; j < 9; j++)
		{
			if(j > 0 && j%3==0)
				cout << "|";
			cout << board[i][j];
		}
		
		cout << endl;
	}
	
	cout << endl;
}

