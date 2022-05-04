#include <stdio.h>
#include <math.h>
#pragma warning (disable:4996)

#define m1_TRANSC 2.40706
#define M2_TRANSC 5.26296
#define m1_POLY 13.241
#define M2_POLY 52
double transcendental(double x)
{
	return (x * cos(x) + 3 * x * x - 1);
}
double polynom(double x)
{
	return (4 * pow(x, 5) - 8 * pow(x, 4) - x * x + 3 * x + 5);
}
typedef struct 
{
	double root;
	int iterations;
} result_t;

result_t bisection(double (f)(double), double a, double b, double eps)
{
	result_t result = { 0 ,0 };
	while (fabs(b - a) > 2 * eps)
	{
		double c = (a + b) / 2;
		if (f(a) * f(c) < 0)
			b = c;
		else
			a = c;
		result.iterations++;
	}
	result.root = (a + b) / 2;
	return result;
}

result_t secant(double (f)(double), double x0, double x1, double eps, double m1, double M2)
{

	result_t result = { 0 ,0 };
	double prev = x0, cur = x1, next;
	next = prev;
	prev = cur;
	cur = cur + (cur - next) / (f(next) / f(cur) - 1);

	while (M2 / (2 * m1) * fabs(next - cur) * fabs(cur - prev) > eps)
	{
		next = prev;
		prev = cur;
		cur = cur + (cur - next) / (f(next) / f(cur) - 1);
		result.root = cur;
		result.iterations++;
	}
	result.root = cur;
	return result;
}
void bisection_file(double (f)(double), double a, double b, double eps, FILE* file)
{
	result_t result = { 0 ,0 };
	while (fabs(b - a) > 2 * eps)
	{
		double c = (a + b) / 2;
		if (f(a) * f(c) < 0)
			b = c;
		else
			a = c;
		fprintf(file, "%0.16lf,", c);
		result.iterations++;
	}
	result.root = (a + b) / 2;
	return result;
}

void secant_file(double (f)(double), double x0, double x1, double eps, double m1, double M2, FILE* file)
{
	result_t result = { 0 ,0 };
	double prev = x0, cur = x1, next;
	next = prev;
	prev = cur;
	cur = cur + (cur - next) / (f(next) / f(cur) - 1);

	while (M2 / (2 * m1) * fabs(next - cur) * fabs(cur - prev) > eps)
	{
		next = prev;
		prev = cur;
		cur = cur + (cur - next) / (f(next) / f(cur) - 1);
		result.iterations++;
		fprintf(file, "%0.16lf,", cur);
	}
	result.root = (prev + cur) / 2;
	return result;
}
int main(void)
{
	FILE* g = fopen("middle_results.csv", "w");
	FILE* f = fopen("results.csv", "w");
	FILE* h = fopen("diff_segments.csv","w");
	double polyleft = 1.7;
	double polyright = 2.0;
	double transcleft = 0.25;
	double transcright = 0.5;
	double delta = 0;
	if ((!f) || (!g) || (!h))
		perror("");

	bisection_file(transcendental, 0.25, 0.5, pow(10, -12), g);
	fprintf(g, "\n");
	bisection_file(polynom, 1.7, 2.0, pow(10, -12), g);
	fprintf(g, "\n");
	secant_file(transcendental, 0.5, 0.75, pow(10, -12), m1_TRANSC, M2_TRANSC, g);
	fprintf(g, "\n");
	secant_file(polynom, 2.0, 2.5, pow(10, -12), m1_POLY, M2_POLY, g);

	for (int i = 0; i < 14; i++) {
		result_t result = bisection(transcendental, 0.25, 0.5, pow(10,	-i-1));
		fprintf(f, "eps: %e, root: %0.16lf, iterations: %d\n", pow(10,-i-1), result.root, result.iterations);
	}
	printf("\nSecant\n");
	for (int i = 0; i < 14; i++) {
		result_t result = secant(transcendental, 0.5, 0.75, pow(10, -i - 1), m1_TRANSC, M2_TRANSC);
		fprintf(f, "eps: %e, root: %0.16lf, iterations: %d\n", pow(10, -i - 1), result.root, result.iterations);
	}
	for (int i = 0; i < 14; i++) {
		result_t result = bisection(polynom, 1.5, 2.0, pow(10, -i - 1));
		fprintf(f, "eps: %e, root: %0.16lf, iterations: %d\n", pow(10, -i - 1), result.root, result.iterations);
	}
	printf("\nsecant\n");
	for (int i = 0; i < 14; i++) {
		result_t result = secant(polynom, 2.0, 2.5, pow(10, -i - 1), m1_POLY, M2_POLY);
		fprintf(f, "eps: %e, root: %0.16lf, iterations: %d\n", pow(10, -i - 1), result.root, result.iterations);
	}

	while (delta != 10)
	{
		transcright = transcright + delta;
		result_t bistransc = bisection(transcendental, transcleft, transcright, pow(10, -12));
		fprintf(h, "eps: %e, iterations: %d, delta: %lf\n", pow(10, -12), bistransc.iterations, delta);
		delta += 1;
	}
	transcleft = 0.5;
	transcright = 0.75;
	delta = 0.0;
	while (delta != 10)
	{
		transcright = transcright + delta;
		result_t sectransc = secant(transcendental, transcleft, transcright, pow(10, -12), m1_TRANSC, M2_TRANSC);
		fprintf(h, "eps: %e, iterations: %d, delta: %lf\n", pow(10, -12), sectransc.iterations, delta);
		delta += 1;
	}
	delta = 0.0;
	while (delta != 10)
	{
		polyright = polyright + delta;
		result_t bispoly = bisection(polynom, polyleft, polyright, pow(10, -12));
		fprintf(h, "eps: %e, iterations: %d, delta: %lf\n", pow(10, -12), bispoly.iterations, delta);
		delta += 1;
	}
	polyleft = 2.0;
	polyright = 2.5;
	delta = 0.0;
	while (delta != 10)
	{
		polyright = polyright + delta;
		result_t secpoly = secant(polynom, polyleft, polyright, pow(10, -12), m1_POLY, M2_POLY);
		fprintf(h, "eps: %e, iterations: %d, delta: %lf\n", pow(10, -12), secpoly.iterations, delta);
		delta += 1;
	}
	fclose(f);
	fclose(g);
	fclose(h);
	return 0;
}