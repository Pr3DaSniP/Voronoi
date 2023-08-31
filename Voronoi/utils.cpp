#include "utils.h"

void affiche(const vector<vector<int>>& tab) {
	for (int i = 0; i < tab.size(); ++i) {
		for (int j = 0; j < tab[i].size(); ++j) {
			if (tab[i][j] == INT_MAX)
				std::cout << "INF\t";
			else
				std::cout << tab[i][j] << "\t";
		}
		std::cout << endl;
	}
}

Case minMasque(bool avant,
	double TL, double T, double TR,
	double L, double R,
	double BL, double B, double BR
) {
	Case indice;
	if (avant) {
		double min = TL; indice.value = TL; indice.x = 0; indice.y = 0;
		if (T < min) { min = T; indice.value = T; indice.x = 1; indice.y = 0; }
		if (TR < min) { min = TR; indice.value = TR; indice.x = 2; indice.y = 0; }
		if (L < min) { min = L; indice.value = L; indice.x = 0; indice.y = 1; }
		return indice;
	}
	else {
		double min = R; indice.value = R; indice.x = 2; indice.y = 1;
		if (BR < min) { min = BR; indice.value = BR; indice.x = 2; indice.y = 2; }
		if (B < min) { min = B; indice.value = B; indice.x = 1; indice.y = 2; }
		if (BL < min) { min = BL; indice.value = BL; indice.x = 0; indice.y = 2; }
		return indice;
	}
}

int moyenne(int r, int g, int b) {
	return (r + g + b) / 3;
}

double ecarttype(int moy, int nbPoints) {
	if (nbPoints == 0)
		return 0;
	else
		return sqrt(moy / nbPoints);
}

double moyenne(vector<double> n) {
	double somme = 0;
	for (int i = 0; i < n.size(); ++i) {
		somme += n[i];
	}
	return somme / n.size();
}

double variance(vector<double> n) {
	double nmoyenne = moyenne(n);

	double var = 0;
	for (int i = 0; i < n.size(); ++i) {
		var += (1.0 / n.size()) * ((n[i] - nmoyenne) * (n[i] - nmoyenne));
	}

	return var;
}

void placePointsOnImage(cv::Mat& image, vector<cv::Point>& points) {
	for (int i = 0; i < points.size(); ++i) {
		circle(image, points[i], 3, cv::Scalar(0, 0, 0), -1);
	}
}

vector<cv::Point> generatePoints(int nbPoints, int width, int height) {
	vector<cv::Point> pts(nbPoints);
	for (int i = 0; i < nbPoints; ++i) {
		pts[i] = cv::Point(rand() % width, rand() % height);
	}
	return pts;
}

vector<Color> generateColors(int nbColors) {
	vector<Color> colors(nbColors);
	for (int i = 0; i < nbColors; ++i) {
		colors[i] = Color{ rand() % 256, rand() % 256, rand() % 256 };
	}
	return colors;
}