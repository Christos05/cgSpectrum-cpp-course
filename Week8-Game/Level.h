#pragma once
#include <string>

using namespace std;

class Level
{
	char* m_pLevelData;
	int m_height;
	int m_width;
	
public:
	Level();
	~Level();

	int Load(string levelName, int* playerX, int* playerY);
	void Draw(int x, int y);

	bool IsSpace(int x, int y);
	bool IsDoor(int x, int y);
	bool IsKey(int x, int y);
	bool IsGoal(int x, int y);

	void PickupKey(int x, int y);
	void OpenDoor(int x, int y);

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width; }

private:
	bool Convert(int* playerX, int* playerY);
	int GetIndexFromCordinates(int x, int y);
};
