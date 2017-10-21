/*
	Open Close MAP values:
	1 - open nodes
	2 - closed nodes
*/

#include "stdafx.h"
#include "stdlib.h"

const int x = 20, y = 20;
int map[x][y];
int openCloseMap[x][y];
int parentNodesX[x][y];
int parentNodesY[x][y];
int gMap[x][y];
int heurestic[x][y];
int endpointX = 19, endpointY = 19;
int startpointX = 13, startpointY = 17;

void calculateHeurestic();
void printMap(int(*)[x]);
void findPath(int, int);
void openNodes(int, int);
void closeNode(int, int);
int * findMaxF();
void calculateCost(int, int, int, int);
void printPath();

int main()
{
	for (int i = 0; i < y ; i++) {
		for (int j = 0; j < x; j++) {
			gMap[j][i] = 99999;
		}
	}
	calculateHeurestic();

	printf("****** START MAP ******\n");
	printMap(map);
	printf("****** START HEURESTIC ******\n");
	printMap(heurestic);

	gMap[startpointX][startpointY] = 0;
	openCloseMap[startpointX][startpointY] = 1;
	findPath(startpointX, startpointY);

	printPath();

	getchar();
	return 0;
}

void calculateHeurestic() {
	int distanceToEndpointX;
	int distanceToEndpointY;

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			distanceToEndpointX = endpointX - j;
			distanceToEndpointY = endpointY - i;
			heurestic[j][i] = abs(distanceToEndpointX) + abs(distanceToEndpointY);
		}
	}
}

void printMap(int(*map)[x]) {

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (openCloseMap[j][i] == 1)
				printf("O");
			else if (openCloseMap[j][i] == 2)
				printf("C");
			printf("%d\t", map[j][i]);
		}
		printf("\n");
	}
}

void findPath(int n, int m) {
	closeNode(n, m);
	if (openCloseMap[endpointX][endpointY] != 2) {
		openNodes(n, m);

		int * maxF = findMaxF();

		findPath(maxF[1], maxF[2]);
	}
}

void openNodes(int n, int m) {
	for (int i = m - 1; i <= m + 1; i++) {
		for (int j = n - 1; j <= n + 1; j++) {
			if (i >= 0 && j >= 0)
				if (openCloseMap[j][i] < 2) {
					openCloseMap[j][i] = 1;
					parentNodesX[j][i] = n;
					parentNodesY[j][i] = m;
					calculateCost(n, m, j, i);
				}
		}
	}
//	printf("****** CURRENT OPEN CLOSE MAP ******\n");
//	printMap(openCloseMap);

//	printf("****** CURRENT Cost Map ******\n");
//	printMap(gMap);

	printf("****** CURRENT Parent Map ***/****\n");
	printMap(parentNodesX);
	printf("\n");
	printMap(parentNodesY);
}

void closeNode(int n, int m) {
	openCloseMap[n][m] = 2;
}

int * findMaxF() {
	int f = 0, maxF[3] = {999999, 0, 0};
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (openCloseMap[j][i] == 1) {
				f = gMap[j][i] + heurestic[j][i];
				if (maxF[0] >= f) {
					maxF[0] = f;
					maxF[1] = j;
					maxF[2] = i;
				}
			}
		}
	}

	return maxF;	
}

void calculateCost(int parentX, int parentY, int currentX, int currentY) {
	if (gMap[currentX][currentY] > gMap[parentX][parentY] + 1) {
		gMap[currentX][currentY] = gMap[parentX][parentY] + 1;
	}
}

void printPath() {
	int currentPointX = endpointX;
	int currentPointY = endpointY;
	int tempX, tempY;
	do {
		tempX = currentPointX;
		tempY = currentPointY;
		printf("\n %d : %d", tempX, tempY);
		currentPointX = parentNodesX[tempX][tempY];
		currentPointY = parentNodesY[tempX][tempY];
	} while (currentPointX != startpointX && currentPointY != startpointY);
	printf("\n %d : %d", startpointX, startpointY);
}