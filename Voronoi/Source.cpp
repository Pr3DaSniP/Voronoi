#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "function.h"
#include "utils.h"

using namespace std;
using namespace cv;

const int nbPoints = 10;
const int width = 500;
const int height = 500;

vector<vector<int>> voronoi(func fonction, Mat& image, int nbGermes, vector<Point>& germes) {
	vector<vector<int>> voronoi(image.rows, vector<int>(image.cols));
	for (int y = 0; y < image.rows; ++y) {
		for (int x = 0; x < image.cols; ++x) {
			Point p(x, y);
			double min = fonction(p, germes[0]);
			int index = 0;
			for (int i = 1; i < nbGermes; i++) {
				double dist = fonction(p, germes[i]);
				if (dist < min) {
					min = dist;
					index = i;
				}
			}
			voronoi[y][x] = index;
		}
	}
	return voronoi;
}

// Voronoi Discret, brute force - Fonctionne
void voronoiDiscret_BruteForce(func fonction, string nom) {
	Mat image = Mat::zeros(height, width, CV_8UC3);
	
	vector<Point> points = generatePoints(nbPoints, width, height);	
	vector<Color> colors = generateColors(nbPoints);

	vector<vector<int>> v = voronoi(fonction, image, nbPoints, points);
	
	for (int y = 0; y < v.size(); ++y) {
		for (int x = 0; x < v[y].size(); ++x) {
			int index = v[y][x];
			image.at<Vec3b>(y, x) = Vec3b(colors[index].b, colors[index].g, colors[index].r);
		}
	}
	
	placePointsOnImage(image, points);
	
	// Affichage de l'image
	imshow("Voronoi Discret " + nom, image);
	imwrite("output/Voronoi Discret " + nom + ".jpg", image);
}

// Voronoi Discret, algorithme s�quentiel - Fonctionne
void voronoiDiscret_sequentiel(const vector<vector<int>>& masque) {
	Mat image = Mat::zeros(height, width, CV_8UC3);
	vector<Point> points(nbPoints);
	vector<Color> colors(nbPoints);

	// Generation de nbPoints points aleatoires
	for (int i = 0; i < nbPoints; i++) {
		points[i] = Point(rand() % width, rand() % height);
		colors[i] = Color{ rand() % 255, rand() % 255, rand() % 255 };
	}

	int diagonale = sqrt((width * width) + (height * height));

	vector<vector<int>> distance(height, vector<int>(width, 2 * diagonale));
	vector<vector<int>> voronoi(height, vector<int>(width, 0));
	for (int i = 0; i < nbPoints; i++) {
		distance[points[i].y][points[i].x] = 0;
		voronoi[points[i].y][points[i].x] = i + 1;
	}

	// Parcourt de l'image avec le masque avant
	for (int y = 1; y < distance.size() - 1; ++y) {
		for (int x = 1; x < distance[y].size() - 1; ++x) {
			if (distance[y][x] != 0) {
				Case ind = minMasque(true,
					distance[y - 1][x - 1], distance[y - 1][x], distance[y - 1][x + 1],
					distance[y][x - 1], distance[y][x + 1],
					distance[y + 1][x - 1], distance[y + 1][x], distance[y + 1][x + 1]
				);

				distance[y][x] = ind.value + masque[ind.y][ind.x];
				voronoi[y][x] = voronoi[y + ind.y - 1][x + ind.x - 1];
			}
		}
	}

	// Parcourt de l'image avec le masque arriere
	for (int y = distance.size() - 2; y > 0; --y) {
		for (int x = distance[y].size() - 2; x > 0; --x) {
			if (distance[y][x] != 0) {
				Case ind = minMasque(false,
					distance[y - 1][x - 1], distance[y - 1][x], distance[y - 1][x + 1],
					distance[y][x - 1], distance[y][x + 1],
					distance[y + 1][x - 1], distance[y + 1][x], distance[y + 1][x + 1]
				);

				if (distance[y][x] > ind.value + masque[ind.y][ind.x]) {
					distance[y][x] = ind.value + masque[ind.y][ind.x];
					voronoi[y][x] = voronoi[y + ind.y - 1][x + ind.x - 1];
				}
			}
		}
	}

	for (int y = 0; y < voronoi.size(); ++y) {
		for (int x = 0; x < voronoi[y].size(); ++x) {
			int index = voronoi[y][x];
			if (index == 0)
				image.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
			else
				image.at<Vec3b>(y, x) = Vec3b(colors[index - 1].b, colors[index - 1].g, colors[index - 1].r);
		}
	}
	placePointsOnImage(image, points);

	// Affichage de l'image
	imshow("Voronoi Discret", image);
	imwrite("output/Voronoi Discret Sequentiel.jpg", image);
}

// Approximation brute force - Fonctionne
void approximationImage_bruteForce(Mat& image, int nbGermes, func fonction) {
	// Etape 1 
	cout << "Etape 1" << endl;
	Mat approxImageG = Mat::zeros(image.rows, image.cols, CV_8UC3);
	Mat approxImageRGB = Mat::zeros(image.rows, image.cols, CV_8UC3);
	vector<Point> points = generatePoints(nbGermes, image.rows, image.cols);
	///////////

	// Etape 2
	cout << "Etape 2" << endl;
	vector<vector<int>> v = voronoi(fonction, image, nbGermes, points);
	///////////

	// Etape 3
	cout << "Etape 3" << endl;
	vector<Region> r(nbGermes);
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[i].size(); ++j) {
			int index = v[i][j];		
			r[index].color.r += image.at<Vec3b>(i, j)[0];
			r[index].color.g += image.at<Vec3b>(i, j)[1];
			r[index].color.b += image.at<Vec3b>(i, j)[2];
			r[index].grey += moyenne(
				image.at<Vec3b>(i, j)[0],
				image.at<Vec3b>(i, j)[1],
				image.at<Vec3b>(i, j)[2]
			);
			r[index].label = index;
			r[index].nbPoints++;
		}
	}

	for (int y = 0; y < image.rows; ++y) {
		for (int x = 0; x < image.cols; ++x) {
			int index = v[y][x];
			approxImageG.at<Vec3b>(y, x) = Vec3b(
				r[index].grey / r[index].nbPoints,
				r[index].grey / r[index].nbPoints,
				r[index].grey / r[index].nbPoints
			);
			
			approxImageRGB.at<Vec3b>(y, x) = Vec3b(
				r[index].color.r / r[index].nbPoints,
				r[index].color.g / r[index].nbPoints,
				r[index].color.b / r[index].nbPoints
			);
		}
	}
	imshow("Approximation Gris", approxImageG);
	imshow("Approximation RBG", approxImageRGB);
	imshow("Image", image);

	imwrite("output/Approximation Gris.jpg", approxImageG);
	imwrite("output/Approximation RBG.jpg", approxImageRGB);
}

// Approximation adaptif
void approximationImage_adaptif(Mat& image, int nbGermes, func fonction) {
	// Etape 1 : Générer aléatoirement un nombre faible de points n, sur le support de l’image
	cout << "Etape 1" << endl;
	vector<Point> points = generatePoints(nbGermes, image.rows, image.cols);
	///////////

	// Etape 2 : Calculer le diagramme de Voronoï associé à ces points
	cout << "Etape 2" << endl;
	vector<vector<int>> v = voronoi(fonction, image, nbGermes, points);
	///////////
	
	// Etape 3 : Associer aux pixels de chaque région la moyenne des niveaux de gris
	cout << "Etape 3" << endl;
	vector<Region> r(nbGermes);
	
	
	
	
}

int main() {
	srand(time(NULL));
	
	/*
	* 
	* Voronoi Discret, brute force
	* 
	*/
	/*
	voronoiDiscret_BruteForce(distanceEuclidienne, "Euclidienne");
	voronoiDiscret_BruteForce(distance, "distance");
	voronoiDiscret_BruteForce(distanceInf, "distanceInf");
	*/
	

	/*
	* 
	* Voronoi Discret, séquentiel
	* 
	*/
	/*
	vector<vector<int>> masque =
	{
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	};
	voronoiDiscret_sequentiel(masque);
	*/
	
	/*
	* 
	* Approximation brute force
	* 
	*/
	/*
	Mat image = imread("img.jpg");
	approximationImage_bruteForce(
		image,
		(int)(image.rows * image.cols * 0.1),
		distanceEuclidienne
	);
	*/

	/*
	* 
	* Approximation adaptif
	*
	*/
	/*
	Mat image = imread("img.jpg");
	approximationImage_adaptif(
		image,
		(int)(image.rows * image.cols * 0.02),
		distanceEuclidienne
	);
	*/
	
	waitKey(0);

	return 0;
}