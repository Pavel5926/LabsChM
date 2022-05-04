#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

double y(double x) {
	return (sqrt(x) + cos(x));
}

double Integrate(double a, double b, int count, double (*f) (double)) {
	double sum = 0;
	double h = (b - a) / count;
	for (int i = 0; i < count; i++) {
		sum += (h)*f(a + h * i + h / 2);
	}
	return sum;
}
void AbsErrPlot() /*abs err of num of nodes*/ {
	ofstream out("approx_count.csv");
	const double a = 0.1;
	const double b = 1;
	const double accurate_value = 1.387222383759946;
	int count = 2;
	double cur = 0;
	double eps = 1e-1;
	for (eps; eps > 1e-12; eps /= 10) {
		count = 2;
		do {
			cur = Integrate(a, b, count, y);
			out.precision(16);
			count *= 2;
		} while (abs(accurate_value - cur) > eps);
		double theormax = (b - a) / 24 * (8.901) * pow(((b - a) / count), 2);
		double theormin = (b - a) / 24 * (0.79) * pow(((b - a) / count), 2);
		out << abs(accurate_value - cur) << ';' << count << ';' << theormax << ';' << theormin << ';' << endl;
	}
	return;
}

void NodesEpsPlot() {
	ofstream out("nodes_eps.csv");
	const double a = 0.1;
	const double b = 1;
	for (double eps = 0.01; eps >= 1e-12; eps /= 10) {
		int count = 2;
		double prev = 0;
		double cur = Integrate(a, b, count, y);
		do {
			prev = cur;
			count *= 2;
			cur = Integrate(a, b, count, y);
		} while (fabs(cur - prev) > eps);
		out.precision(16);
		out << fabs(cur - prev) << ';' << count << ';' << eps << ';' << endl;
	}
}

int main() {
	
	AbsErrPlot();
	NodesEpsPlot();
	return 0;
}