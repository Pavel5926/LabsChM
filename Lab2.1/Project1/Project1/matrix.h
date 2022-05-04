#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>
#ifndef MATRIX_H_
#define MATRIX_H_

namespace mat {
double random(double a, double b);
}

struct matrix_t {
    std::vector<double> data;
    int rows;
    int cols;

    ~matrix_t() {}
    matrix_t(const matrix_t& M);
    matrix_t(int h, int w = 1); //height width
    double& operator()(int i, int j);
    double operator()(int i, int j) const;
    double& el(int i, int j);
    double el(int i, int j) const;
    double& operator[](const int i);
    double operator[](const int i) const;
    matrix_t operator*(const matrix_t R) const;
    matrix_t operator*(const double n) const;
    matrix_t operator/(const double n) const;
    matrix_t operator-(const matrix_t R) const;
    matrix_t operator+(const matrix_t R) const;
    void operator=(const matrix_t& R);
    matrix_t T();
    double norm() const;
    double infnorm() const;
};
matrix_t eyes(int size);
std::ostream& operator<<(std::ostream& os, const matrix_t& M);
double norm(const matrix_t& M);
double infnorm(const matrix_t& M);
void matPrint(const matrix_t& M);

#endif // MATRIX_H_
