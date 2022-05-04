#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <fstream>
int counter = 0;
double f(double x, double y) {
	/*return 3 * x * exp(-x) - (x + 1) * y / x;*/
	counter++;
	return y / x + x * cos(x);
}
double sol(double x) {
	/*return pow(x, 2) * exp(-x);*/
	return x * sin(x);
}
double a = M_PI_2;
double b = 2 * M_PI;
double RK(std::function<double(double, double)> f, double xprev, double yprev, double h) {
	double k1 = f(xprev, yprev);
	double k2 = f(xprev + h / 3, yprev + h * k1 / 3);
	double k3 = f(xprev + 2 * h / 3, yprev + 2 * h * k2 / 3);
	double ycur = yprev + h / 4 * (k1 + 3 * k3);
	/*double k1 = f(xprev, yprev);
	double k2 = f(xprev + h / 2, yprev + h / 2 * k1);
	double k3 = f(xprev + h / 2, yprev + h / 2 * k2);
	double k4 = f(xprev + h, yprev + h * k3);
	double ycur = yprev + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);*/
	return ycur;
}

std::tuple<double, double, int, double> RKE(std::function<double(double, double)> f, double xprev, double yprev, double h, double eps) {
	double yold = RK(f, xprev, yprev, h);
	double ytmp = RK(f, xprev, yprev, h / 2);
	//double ynew = RK(f, xprev, yprev, h / 2);
	double ynew = RK(f, xprev + h / 2, ytmp, h / 2);
	int iter = 1;
	double error = 0;
	while (abs(yold - ynew) / 7 > eps) {
		iter++;
		yold = ytmp;
		h /= 2;
		ytmp = RK(f, xprev, yprev, h / 2);
		ynew = RK(f, xprev + h / 2, ytmp, h / 2);
	}
	error = abs(sol(xprev + h) - ynew);
	return { error, ynew, iter, h };
}

//void LocalErrPlot() {
//
//	double n = 10;
//	std::ofstream out("localerr.csv");
//	out.precision(16);
//	double yprev = sol(a);
//	double xprev = a;
//	int iter = 500;
//	for (int i = 10; i < iter; i++) {
//		double h_0 = (b - a) / i;
//		double ycur = yprev;
//		out << abs(sol(a + h_0) - RK(f, xprev, yprev, h_0)) << ';';
//		for (int j = 0; j < i; j++) {
//			xprev = a + j * h_0;
//			ycur = RK(f, xprev, ycur, h_0);
//		}
//		out << abs(sol(a + (i) * h_0) - ycur) << ';' << h_0 << std::endl;
//	}
//}
void LocalErrPlot() {
	double n = 10;
	double h_0 = (b - a) / n;
	std::ofstream out("localerr.csv");
	out.precision(16);

	double yprev = sol(a);
	int iter = 15;
	for (int i = 0; i < iter; i++) /*Увеличение количества h (степень)*/ {
		double h = h_0 / pow(2, i);
		double ycur = yprev;
		double merr = 0;
		for (int k = 0; k < n; k++) /*измерение ошибки каждые 10 узлов*/ {
			for (int j = 0; j < pow(2, i); j++)/* проход по h*/ {
				double xprev = a + k * h_0 + j * h;
				ycur = RK(f, xprev, ycur, h);
				double err = abs(sol(a + k * h_0 + h*(j+1)) - ycur);
				if (j == 0 && k==0)
					out << err << ';';
				merr = std::max(err, merr);
			}
		}
		out << merr << ';';
		out << h << ';' << std::endl;

	}
}

void Plot() {

	double n = 10;
	double h = (b - a) / n;
	std::ofstream out("approx.csv");

	double yprev = sol(a);
	out << yprev << ';';
	for (int i = 0; i < n; i++) {
		double xprev = a + i * h;
		double ycur = RK(f, xprev, yprev, h);
		out.precision(16);
		out << ycur << ';';
		yprev = ycur;
	}
	return;
}
void EpsPlot() {
	double n = 4;
	double h = (b - a) / n;
	double yprev = sol(a);
	double eps = 0.1;
	std::ofstream out("epsplot.csv");
	out.precision(16);
	std::tuple < double, double, int, double> res = { 0,0,0,(b - a) / n };
	while (eps >= 1e-15) {
		counter = 0;
		double merr = 0;
		//for (int i = 0; i < n; i++) {
 		double xprev = a;
		int i = 0;
		while (xprev < b) {
			res = RKE(f, xprev, yprev, h, eps);
			double err = std::get<0>(res);
			if (i == 0) {
				out << err << ';';
			}
			merr = std::max(err, merr);
			yprev = std::get<1>(res);
			h = std::get<3>(res);
			i++;
			xprev += h;
		}
		out << merr << ';' <<counter / 3 << ';' << std::endl;
		eps /= 10;
		h = (b - a) / n;
		yprev = sol(a);
	}
}
int main() {
	Plot();
	LocalErrPlot();
	EpsPlot();
}