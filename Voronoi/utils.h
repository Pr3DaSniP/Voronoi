#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <cmath>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

struct Color {
	int r;
	int g;
	int b;
};

struct Region {
	int label;
	int nbPoints;
	Color color;
	int grey = 0;
	double coefVariation = 0;
	bool isHomogen = false;
};

struct Case {
	int x;
	int y;
	int value;
};

void affiche(const vector<vector<int>>& tab);

Case minMasque(bool avant,
	double TL, double T, double TR,
	double L, double R,
	double BL, double B, double BR
);

int moyenne(int r, int g, int b);

double ecarttype(int moy, int nbPoints);

double moyenne(vector<double> n);

double variance(vector<double> n);

void placePointsOnImage(cv::Mat& image, vector<cv::Point>& points);

vector<cv::Point> generatePoints(int nbPoints, int width, int height);

vector<Color> generateColors(int nbColors);

#endif // !UTILS_H