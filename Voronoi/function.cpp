#include "function.h"

double distanceEuclidienne(Point& P1, Point& P2) {
	return sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
}

double distance(Point& P1, Point& P2) {
	return (abs(P1.x - P2.x) + abs(P1.y - P2.y));
}

double distanceInf(Point& P1, Point& P2) {
	return max(abs(P1.x - P2.x), abs(P1.y - P2.y));
}