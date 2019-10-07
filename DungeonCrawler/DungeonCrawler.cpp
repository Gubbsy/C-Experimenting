#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//char mapArray[10][31];
vector<vector<char> >mapArray;
int currentRow,currentCol;
bool gameOver = false;
int gold = 0;


// load map into array
void LoadMap()
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
void PrintMap() 
{
	system("CLS");
	for(int row = 0; row < 10; row++) {
		for (int col = 0; col < 31; col++) {
			cout << mapArray[row][col];
		}
		cout << endl;
	}
}

void Move(int newRow, int newCol) 
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

		PrintMap();

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
	else
	{
		cout << "You cannot walk through walls" << endl;
	}
}

int main()
{
	LoadMap();
	PrintMap();

	while (!gameOver){
		char direction;
		cout << "Please enter your move with W,A,S,D" << endl;
		cin >> direction;
		direction = toupper(direction);

		if (direction == 'W') {
			// move up
			int newRow = currentRow - 1;
			int newCol = currentCol;
			Move(newRow, newCol);
		}
		else if (direction == 'A')
		{
			//move left
			int newRow = currentRow;
			int newCol = currentCol - 1;
			Move(newRow, newCol);
		}
		else if (direction == 'S')
		{
			//move down
			int newRow = currentRow + 1;
			int newCol = currentCol;
			Move(newRow, newCol);
		}
		else if (direction == 'D')
		{
			//move right
			int newRow = currentRow;
			int newCol = currentCol + 1;
			Move(newRow, newCol);
		}
		else
		{
			cout << "Please enter a valid move" << endl;
		}
	}
}