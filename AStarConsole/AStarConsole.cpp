/*
	MAP values:
	9 - end point
	1 - open nodes
	2 - closed nodes
*/

#include "stdafx.h"
#include "stdlib.h"

const int x = 20, y = 20;
int map[x][y] = {0};
int parentNodes[x][y] = { 0 };
int heurestic[x][y] = { 0 };
int endpointX = 5, endpointY = 13;
int startpointX = 3, startpointY = 12;

void setEndpoint();
void calculateHeurestic();
void printMap(int(*)[x]);
void findPath(int, int);
int openNodes(int, int);

int main()
{
	setEndpoint();
	calculateHeurestic();

	printf("****** CURRENT MAP ******\n");
	printMap(map);
	printf("****** CURRENT HEURESTIC ******\n");
	printMap(heurestic);

	map[startpointX][startpointY] = 1;
	findPath(startpointX, startpointY);

	return 0;
}

void setEndpoint() {
	map[endpointX][endpointY] = 9;
}

void calculateHeurestic() {
	int distanceToEndpointX;
	int distanceToEndpointY;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			distanceToEndpointX = endpointX - i;
			distanceToEndpointY = endpointY - j;
			heurestic[i][j] = abs(distanceToEndpointX) + abs(distanceToEndpointY);
		}
	}
}

void printMap(int(*map)[x]) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			printf("%d\t", map[i][j]);
		}
		printf("\n");
	}
}

void findPath(int n, int m) {
	map[n][m] = 2;
	for (int i = n - 1; i <= n + 1; i++) {
		for (int j = m - 1; j <= m + 1; j++) {
			if (i >= 0 && j >= 0) {
				if (map[i][j] == 0) {
					map[i][j] = 1;
				}
				if (map[i][j] == 9) {
					printf("FINISHED");
					exit;
				}
				findPath(i, j);
			}
		}
	}
	printf("****** CURRENT MAP ******\n");
	printMap(map);
}

int openNodes(int n, int m) {
	return 1;
}