#ifndef FUNCTION_H
#define FUNCTION_H

#include <opencv2/core.hpp>

using namespace cv;

using func = double(*)(Point&, Point&);

double distanceEuclidienne(Point& P1, Point& P2);

double distance(Point& P1, Point& P2);

double distanceInf(Point& P1, Point& P2);

#endif // !FUNCTION_H
