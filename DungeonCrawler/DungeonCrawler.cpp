#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

//char mapArray[10][31];



// load map into array
void LoadMap(vector<vector<char> >& mapArray, int& currentRow, int& currentCol)
{
	string line;
	ifstream mapFile("Map.txt");

	if (mapFile.is_open()) {
		while (getline(mapFile, line)) {
			vector<char> newRow;
			for (int i = 0; i < line.size(); i++) {
				newRow.push_back(line[i]);
				if (line[i] == 'S') {
					currentRow = mapArray.size();
					currentCol = i;
					cout << "Start position is " << currentRow << ',' << currentCol << endl;
				}
			}
			mapArray.push_back(newRow);
		}
		mapFile.close();
	}
}

// print map
void PrintMap(vector<vector<char> >& mapArray)
{
	system("CLS");
	for(int row = 0; row < 10; row++) {
		for (int col = 0; col < 31; col++) {
			cout << mapArray[row][col];
		}
		cout << endl;
	}
}

void Move(vector<vector<char> >& mapArray, int& gold, int& currentRow, int& currentCol, int& newRow, int& newCol, bool& gameOver) 
{
	char newTileType = mapArray[newRow][newCol];
	char currentTileType = mapArray[currentRow][currentCol];

	if (newTileType != '#') {
		mapArray[newRow][newCol] = 'S';
		mapArray[currentRow][currentCol] = '.';
		
		currentCol = newCol;
		currentRow = newRow;

		if (newTileType == 'G')
		{
			gold++;
		}

		PrintMap(mapArray);

		if (newTileType == 'E')
		{
			cout << "Game Won with " << gold << " gold" << endl;
			gameOver = true;
		}
		if (newTileType == 'M')
		{
			cout << "Game Lost" << endl;
			gameOver = true;
		}
	}
}

int main()
{
	vector<vector<char> >mapArray;
	int currentRow, currentCol, newRow, newCol;
	bool gameOver = false;
	int gold = 0;
	LoadMap(mapArray, currentRow, currentCol);
	PrintMap(mapArray);
	cout << "Please enter your move with W,A,S,D" << endl;

	while (!gameOver){
		char direction;
		direction = _getch();
		direction = toupper(direction);

		if (direction == 'W') {
			// move up
			newRow = currentRow - 1;
			newCol = currentCol;
			Move(mapArray, gold, currentRow, currentCol, newRow, newCol, gameOver);
		}
		else if (direction == 'A')
		{
			//move left
			newRow = currentRow;
			newCol = currentCol - 1;
			Move(mapArray, gold, currentRow, currentCol, newRow, newCol, gameOver);
		}
		else if (direction == 'S')
		{
			//move down
			newRow = currentRow + 1;
			newCol = currentCol;
			Move(mapArray, gold, currentRow, currentCol, newRow, newCol, gameOver);
		}
		else if (direction == 'D')
		{
			//move right
			newRow = currentRow;
			newCol = currentCol + 1;
			Move(mapArray, gold, currentRow, currentCol, newRow, newCol, gameOver);
		}
		else
		{
			cout << "Please enter a valid move" << endl;
		}
	}
}