#include <vector>
#include <iostream>
#include <fstream>
#include "matrix.h"

using namespace std;
double function(double x) {
	return (sqrt(x) + cos(x));
}

double nonSmooth(double x) {
	return (sqrt(x) + abs(cos(x)));
}

vector <double> divDifference(double(*function) (double), vector <double> mesh) {
	int degree = mesh.size();
	matrix_t divMatrix(degree, degree);
	vector <double> res(degree);
	for (int i = 0; i < degree; i++) {
		divMatrix(i,0) = function(mesh[i]);
	}
	for (int j = 1; j < degree; j++) {
		for (int i = 0; i < degree - j; i++) {
			divMatrix(i,j) = (divMatrix(i + 1, j - 1) - divMatrix(i,j - 1)) / (mesh[i + j] - mesh[i]);
		}
	}
 	for (int i = 0; i < degree; i++) {
		res[i] = divMatrix(degree - i - 1, i);
	}
	return res;

}

//vector <double> meshGen(double a, double b, int count) {
//	vector <double> nodes(count);
//	double coef = 2;
//	double breakpoint = 1.7;
//	int k = count / 2;
//	double reverse_coef = 1.0 / coef;
//	for (int i = 0; i < k; i++) {
//		nodes[i] = a + (breakpoint - a) * pow(((double)i / (double)k), reverse_coef);
//		//cout << nodes[i];
//	}
//	for (int i = k; i < count; i++) {
//		nodes[i] = breakpoint + (b - breakpoint) * pow(((double)(i - k) / (k - 1)), coef);
//		//cout << nodes[i];
//	}
//	return nodes;
//}
vector <double> linspaceGen(int a, int b, int number) {
	vector <double> mesh(number);
	for (int i = 0; i < number; i++) {
		mesh[i] = b - (b - a) * (double)(number - i) / number;
	}
	return mesh;
}
vector <double> meshGen(int a, int b, int number) {
	vector <double> mesh (number);
	for (int i = 0; i < number; i++) {
		mesh[i] = b - (b - a) * pow((double)(number - i) / number, 1);
	}
	return mesh;
}

double NewtonRightLeft(vector <double> divMas, vector <double> mesh, double x) {
	int degree = mesh.size() - 1;
	double product = 1;
	double polyval = 0;
	for (int i = degree; i >= 0; i--) {
		for (int j = degree; j > i; j--) {
			product *= (x - mesh[j]);
		}
		polyval += divMas[degree - i] * product;
		product = 1;
	}
	return polyval;
}

//int main() {
//	int a = 5;
//	int b = 10;
//	vector <double> linspace;
//	linspace = linspaceGen(a, b, 1000);
//	//vector <double> net = CreateNet(a, b, 30);
//	ofstream y357("y357.csv");
//	ofstream linspace_out("linspace_out.csv");
//	for (int size : {4, 6, 8}) {
//		vector <double> testMesh = meshGen(a, b, size);
//		vector <double> divMas = divDifference(function, testMesh);
//		/*for (double x : linspace) {
//			y357.precision(13);
//			y357 << NewtonRightLeft(divMas, testMesh, x) << ";";
//		}
//		y357 << endl;*/
//		for (int i = 0; i < linspace.size(); i++) {
//			linspace_out.precision(16);
//			y357.precision(16);
//			linspace_out << linspace[i] << ";";
//			y357 << NewtonRightLeft(divMas, testMesh, linspace[i]) << ";";
//		}
//		linspace_out << endl;
//		y357 << endl;
//	}
//
//	int n_low = 3;
//	int n_high = 100;
//	ofstream dmax ("max.csv");;
//	for (int size = n_low; size <= n_high;size++) {
//		double maxerr = 0;
//		vector <double> testMesh = meshGen(a, b, size);
//		vector <double> divMas = divDifference(function, testMesh);
//		for (double x : linspace) {
//			dmax.precision(16);
//			maxerr = max(maxerr, abs(NewtonRightLeft(divMas, testMesh, x)-function(x)));
//		}
//		dmax << maxerr << ";";
//	}
//
//}

int main() {
	int a = 5;
	int b = 10;
	vector <double> linspace;
	linspace = linspaceGen(a, b, 1000);
	//vector <double> net = CreateNet(a, b, 30);
	ofstream y357("nsmoothy357.csv");
	ofstream linspace_out("nsmoothlinspace_out.csv");
	for (int size : {4, 6, 8}) {
		vector <double> testMesh = meshGen(a, b, size);
		vector <double> divMas = divDifference(nonSmooth, testMesh);
		/*for (double x : linspace) {
			y357.precision(13);
			y357 << NewtonRightLeft(divMas, testMesh, x) << ";";
		}
		y357 << endl;*/
		for (int i = 0; i < linspace.size(); i++) {
			linspace_out.precision(16);
			y357.precision(16);
			linspace_out << linspace[i] << ";";
			y357 << NewtonRightLeft(divMas, testMesh, linspace[i]) << ";";
		}
		linspace_out << endl;
		y357 << endl;
	}

	int n_low = 3;
	int n_high = 100;
	ofstream dmax("nsmoothmax.csv");;
	for (int size = n_low; size <= n_high; size++) {
		double maxerr = 0;
		vector <double> testMesh = meshGen(a, b, size);
		vector <double> divMas = divDifference(nonSmooth, testMesh);
		for (double x : linspace) {
			dmax.precision(16);
			maxerr = max(maxerr, abs(NewtonRightLeft(divMas, testMesh, x) - nonSmooth(x)));
		}
		dmax << maxerr << ";";
	}

}