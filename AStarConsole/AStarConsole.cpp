#include "stdafx.h"
#include "stdlib.h"
#include "fstream"

const int x = 20, y = 20;
int map[x][y];
int openCloseMap[x][y];
int parentNodesX[x][y];
int parentNodesY[x][y];
int gMap[x][y];
int heurestic[x][y];
int endpointX = 19, endpointY = 19;
int startpointX = 0, startpointY = 0;
int openNodesCounter = 0;

bool readGridFromFile();
void calculateHeurestic();
void printGrid(int(*)[x]);
void findPath(int, int);
void openNodes(int, int);
void closeNode(int, int);
int * findMinF();
bool calculateCost(int, int, int, int);
void printPath();

int main()
{
	if (!readGridFromFile()) {
		printf("Cannot read grid from file");
		return(1);
	}

	for (int i = 0; i < y ; i++) {
		for (int j = 0; j < x; j++) {
			gMap[j][i] = 99999;
		}
	}

	calculateHeurestic();

	printf("****** START MAP ******\n");
	printGrid(map);

	gMap[startpointX][startpointY] = 0;
	openCloseMap[startpointX][startpointY] = 1;
	findPath(startpointX, startpointY);
	
	printPath();

	getchar();
	return 0;
}

bool readGridFromFile() {
	std::ifstream plik("grid.txt");
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			plik >> map[j][i];
		}
	}
	plik.close();
	return true;
}

void calculateHeurestic() {
	int distanceToEndpointX;
	int distanceToEndpointY;

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			distanceToEndpointX = endpointX - j;
			distanceToEndpointY = endpointY - i;
			heurestic[j][i] = abs(distanceToEndpointX * 10) + abs(distanceToEndpointY * 10);
		}
	}
}

void printGrid(int(*map)[x]) {
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (map[j][i] > 0 && map[j][i] < 9)
				printf("# ");
			else if (map[j][i] == 9)
				printf("X ");
			else
				printf(". ");
		}
		printf("\n");
	}
}

void findPath(int n, int m) {
	closeNode(n, m);
	if (openCloseMap[endpointX][endpointY] != 2) {
		if (openNodesCounter != 0) {
			openNodes(n, m);

			int * minF = findMinF();
			findPath(minF[1], minF[2]);
		}
		else {
			printf("Path not found");
		}
	}
}

void openNodes(int n, int m) {
	for (int i = m - 1; i <= m + 1; i++) {
		for (int j = n - 1; j <= n + 1; j++) {
			if (i >= 0 && j >= 0 && i < y && j < x)
				if (openCloseMap[j][i] < 2 && map[j][i] == 0) {
					openCloseMap[j][i] = 1;
					openNodesCounter++;
					if (calculateCost(n, m, j, i)) {
						parentNodesX[j][i] = n;
						parentNodesY[j][i] = m;
					}
				}
		}
	}

}

void closeNode(int n, int m) {
	openCloseMap[n][m] = 2;
	openNodesCounter--;
}

int * findMinF() {
	int f = 0, minF[3] = {999999, 0, 0};
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (openCloseMap[j][i] == 1) {
				f = gMap[j][i] + heurestic[j][i];
				if (minF[0] > f) {
					minF[0] = f;
					minF[1] = j;
					minF[2] = i;
				}
			}
		}
	}

	return minF;	
}

bool calculateCost(int parentX, int parentY, int currentX, int currentY) {
	int cost = 10;
	if (parentX != currentX && parentY != currentY)
		cost = 14;
	if (gMap[currentX][currentY] > gMap[parentX][parentY] + cost) {
		gMap[currentX][currentY] = gMap[parentX][parentY] + cost;
		return true;
	}
	return false;
}

void printPath() {
	int currentPointX = endpointX;
	int currentPointY = endpointY;
	int tempX, tempY;
	do {
		tempX = currentPointX;
		tempY = currentPointY;
		map[tempX][tempY] = 9;
		currentPointX = parentNodesX[tempX][tempY];
		currentPointY = parentNodesY[tempX][tempY];
	} while (currentPointX != startpointX || currentPointY != startpointY);
	map[startpointX][startpointY] = 9;
	printf("\n##### END MAP #####\n");
	printGrid(map);
}