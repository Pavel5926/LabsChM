//#include <iostream>
//#include <vector>
//#include "matrix.h"
//#include <iterator>
#include "matrix.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double y(double x) {
	return (sqrt(x) + cos(x));
}

double yn(double x) {
	return (sqrt(x) + fabs(cos(x)));
}
//double dd(double (*y) (double), double x_i, double x_j) {
//	double res = 0;
//	res = (y(x_j) - y(x_i)) / (x_j - x_i);
//	return res;
//}
vector <double> meshGen(double a, double b, int count) {
	vector <double> mesh(count + 1);
	for (int i = 0; i <= count; i++) {
		mesh[i] = b - (b - a) * (double)(count - i) / count;
	}
	return mesh;
}
vector <double> hcount(vector <double>& x) {
	const int count = x.size();
	vector <double> h(count);
	h[0] = -999;
	for (int i = 1; i < count; i++) {
		h[i] = x[i] - x[i - 1];
	}
	return h;
}
matrix_t Mcount(double (*y) (double), vector <double>& x, vector <double>& h, const int& count) /* Матрица БЕЗ граничных элементов M_0 и M_n */ {
	matrix_t M(count - 1, 4 /*- 1*/); 
	
	M(0, 0) = 2;
	M(0, 1) = h[2] / (h[1] + h[2]);
	M(0, 2) = 0;
	for (int i = 1; i < count - 1; i++) {
		M(i, 1) = 2;
		M(i, 0) = h[i] / (h[i] + h[i + 1]);
		/*if (i + 1 < count - 1) {*/
		M(i, 2) = h[i + 1] / (h[i] + h[i + 1]);
		//}
	}		
	for (int j = 1; j <= count - 1; j++) {
		M(j - 1, 3) = ((6) / (h[j] + h[j + 1])) * ((y(x[j + 1]) - y(x[j])) / (h[j + 1]) - ((y(x[j]) - y(x[j - 1])) / h[j]));
	}
	//cout << M;
	return M;
}

//matrix_t Mcount(double (*y) (double), vector <double>& x, vector <double>& h, const int& count) /* Матрица БЕЗ граничных элементов M_0 и M_n */ {
//	matrix_t M(count - 1, count /*- 1*/); /*Здесь уже есть столбец свободных коэффициентов*/
//	M(0, 0) = 2; /* Мой вариант*/
//	M(0, 1) = h[2] / (h[1] + h[2]);
//	for (int i = 1; i < count - 1; i++) {
//		M(i, i) = 2;
//		M(i, i - 1) = h[i] / (h[i] + h[i + 1]);
//		if (i + 1 < count - 1) {
//			M(i, i + 1) = h[i + 1] / (h[i] + h[i + 1]);
//		}
//	}
//	for (int j = 1; j <= count - 1; j++) {
//		//cout << (6) / (h[j] + h[j + 1]);
//		//cout << y(x[j]);
//		M(j - 1, count - 1) = ((6) / (h[j] + h[j + 1])) * ((y(x[j + 1]) - y(x[j])) / (h[j + 1]) - ((y(x[j]) - y(x[j - 1])) / h[j]));
//	}
//	return M;
//}
// 
//matrix_t Mcount(double (*y) (double), vector <double>& x, vector <double>& h, const int& count) /* Матрица БЕЗ граничных элементов M_0 и M_n */ {
//	matrix_t M(count - 1, count /*- 1*/); /*Здесь уже есть столбец свободных коэффициентов*/
//	M(0, 0) = 2; /*Сашин вариант*/
//	M(0, 1) = h[2] / (h[1] + h[2]);
//	for (int i = 1; i < count - 1; i++) {
//		M(i, i) = 2;
//		M(i, i - 1) = h[i] / (h[i] + h[i + 1]);
//		if (i + 1 < count - 1) {
//			M(i, i + 1) = h[i + 1] / (h[i] + h[i + 1]);
//		}
//	}
//	for (int j = 1; j <= count - 1; j++) {
//		cout << (6) / (h[j] + h[j + 1]);
//		cout << y(x[j]);
//		M(j - 1, count - 1) = ((6) / (h[j] + h[j + 1])) * ((y(x[j + 1]) - y(x[j])) / (h[j + 1]) - ((y(x[j]) - y(x[j - 1])) / h[j]));
//	}
//	return M;
//}
//vector <double> Thomas(matrix_t matrix, int count)
//{ /*Мой вариант*/
//	vector <double> b(count - 1);
//	vector <double> d(count - 1);
//	b[0] = 0;
//	d[count - 2] = 0;
//	vector <double> c(count - 1);
//	for (int i = 0; i < count - 1; i++) {
//		c[i] = matrix(i, i);
//		if (i != count - 2)
//			d[i] = matrix(i, i + 1);
//		if (i != 0)
//			b[i] = matrix(i, i - 1);
//	}
//	vector <double> delta(count - 1);
//	vector <double> lambda(count - 1);
//	delta[0] = -d[0] / c[0];
//	lambda[0] = matrix(0, count - 1) / c[0];
//	for (int i = 1; i < count - 1; i++) {
//		delta[i] = -d[i] / (b[i] * delta[i - 1] + c[i]);
//		lambda[i] = (matrix(i, count - 1) - b[i] * lambda[i - 1]) / (b[i] * delta[i - 1] + c[i]);
//	}
//	vector <double> M(count - 1);
//	M[count - 2] = lambda[count - 2];
//	for (int i = count - 3; i >= 0; i--) {
//		M[i] = delta[i] * M[i + 1] + lambda[i];
//	}
//
//	M.insert(M.begin(), 0);
//	M.push_back(0);
//	/*reverse(M.begin(), M.end());*/
//	return M;
//}

vector <double> Thomas(matrix_t matrix, int count)
{
	vector <double> b(count - 1);
	vector <double> d(count - 1);
	b[0] = 0;
	d[count - 2] = 0;
	vector <double> c(count - 1);
	c[0] = matrix(0, 0);
	d[0] = matrix(0, 1);
	for (int i = 1; i < count - 1; i++) {
		c[i] = matrix(i, 1);
		if (i != count - 2)
			d[i] = matrix(i, 2);
		//if (i != 0)
			b[i] = matrix(i, 0);
	}
	vector <double> delta(count - 1);
	vector <double> lambda(count - 1);
	delta[0] = -d[0] / c[0];
	lambda[0] = matrix(0, 3) / c[0];
	for (int i = 1; i < count - 1; i++) {
		delta[i] = -d[i] / (b[i] * delta[i - 1] + c[i]);
		lambda[i] = (matrix(i, 3) - b[i] * lambda[i - 1]) / (b[i] * delta[i - 1] + c[i]);
	}
	vector <double> M(count - 1);
	M[count - 2] = lambda[count - 2];
	for (int i = count - 3; i >= 0; i--) {
		M[i] = delta[i] * M[i + 1] + lambda[i];
	}

	M.insert(M.begin(), 0);
	M.push_back(0);
	/*reverse(M.begin(), M.end());*/
	return M;
}
//matrix_x SplineMatrix ()

double Spline(double (*y) (double), const vector <double>& M, const vector <double>& xm, const vector <double>& h, int count, double x) {
	int i = 0;
	for (i = 1; i < xm.size(); i++) {
		if (x < xm[i]) {
			break;
		}
	}
	if (i == xm.size()) {
		i--;
	}
	double Ct = y(xm[i - 1]) - M[i - 1] * h[i] * h[i] / 6;
	double C = (y(xm[i]) - y(xm[i - 1])) / h[i] - h[i] / 6 * (M[i] - M[i - 1]);
	return M[i - 1] * pow(xm[i] - x, 3) / (6 * h[i]) + M[i] * pow(x - xm[i - 1], 3) / (6 * h[i]) + C * (x - xm[i - 1]) + Ct;

}
int main() {
	double a = 5;
	double b = 10;
	//int count = 999;
	int graphCount = 1000 - 1;
	vector <double> x = meshGen(a, b, graphCount);
	ofstream g357("g357.csv");
	ofstream xout("xout.csv");
	for (int count : {4, 9, 15}) {
		vector <double> mesh = meshGen(a, b, count);
		vector <double> h = hcount(mesh);
		//vector <double> g = meshGen(a, b, graphCount);
		matrix_t Matr = Mcount(y, mesh, h, count);
		//cout << Matr;
		vector <double> M = Thomas(Matr, count);
		for (int i = 0; i < x.size(); i++) {
			xout.precision(16);
			g357.precision(16);
			xout << x[i] << ";";
			g357 <</*g[i] = */ Spline(y, M, mesh, h, count, x[i]) << ";";
		}
		g357 << endl;
		xout << endl;
	}

	int n_low = 3;
	int n_high = 100;
	ofstream dmax("gmax.csv");
	ofstream hf("h.csv");
	for (int size = n_low; size <= n_high; size++) {
		vector <double> x = meshGen(a, b, size+1);
		double maxerr = 0;
		vector <double> mesh = meshGen(a, b, size);
		vector <double> h = hcount(mesh);
		matrix_t Matr = Mcount(y, x, h, size);
		vector <double> M = Thomas(Matr, size);

		for (double x_i : x) {
			dmax.precision(16);
			maxerr = max(maxerr, fabs(Spline(y, M, mesh, h, size, x_i) - y(x_i)));
			hf << h[1] << ";";
		}
			dmax << maxerr << ";";
	}
	return 0;
}

//int main() {
//	double a = 5;
//	double b = 10;
//	//int count = 999;
//	int graphCount = 1000 - 1;
//	vector <double> x = meshGen(a, b, graphCount);
//	ofstream g357("gn357.csv");
//	ofstream xout("xout.csv");
//	for (int count : {5, 9, 15}) {
//		vector <double> mesh = meshGen(a, b, count);
//		vector <double> h = hcount(mesh);
//		//vector <double> g = meshGen(a, b, graphCount);
//		matrix_t Matr = Mcount(yn, mesh, h, count);
//		//cout << Matr;
//		vector <double> M = Thomas(Matr, count);
//		for (int j = 0; j < M.size(); j++) {
//			//cout << M[j] << ' ';
//		}
//		for (int i = 0; i < x.size(); i++) {
//			xout.precision(16);
//			g357.precision(16);
//			xout << x[i] << ";";
//			g357 <</*g[i] = */ Spline(yn, M, mesh, h, count, x[i]) << ";";
//		}
//		g357 << endl;
//		xout << endl;
//	}
//
//	int n_low = 3;
//	int n_high = 100;
//	ofstream dmax("gnmax.csv");
//	for (int size = n_low; size <= n_high; size++) {
//		vector <double> x = meshGen(a, b, size + 1);
//		double maxerr = 0;
//		vector <double> mesh = meshGen(a, b, size);
//		vector <double> h = hcount(mesh);
//		matrix_t Matr = Mcount(yn, x, h, size);
//		vector <double> M = Thomas(Matr, size);
//
//		for (double x_i : x) {
//			dmax.precision(16);
//			maxerr = max(maxerr, fabs(Spline(yn, M, mesh, h, size, x_i) - yn(x_i)));
//		}
//		dmax << maxerr << ";";
//	}
//	return 0;
//}