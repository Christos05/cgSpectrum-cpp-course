#pragma once
#include <string>
#include <vector>

class PlacableActor;

using namespace std;

class Level
{
	char* m_pLevelData;
	int m_height;
	int m_width;
	
	vector<PlacableActor*> m_pActors;

public:
	Level();
	~Level();

	int Load(string levelName, int* playerX, int* playerY);
	void Draw();
	PlacableActor* UpdateActors(int x, int y);

	bool IsSpace(int x, int y);
	bool IsWall(int x, int y);

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width; }

private:
	bool Convert(int* playerX, int* playerY);
	int GetIndexFromCordinates(int x, int y);
};
