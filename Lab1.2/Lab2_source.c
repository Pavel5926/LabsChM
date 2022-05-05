#include <stdio.h>
#include <math.h>
#include <windows.h>
#pragma warning (disable:4996)
#define MAX_DIMENSION 2000

double* VectorInit(int dimension) {
	double* vector = (double*)malloc(sizeof(double) * dimension);
	if (!vector) {
		perror("");
		return NULL;
	}
	for (int i = 0; i < dimension; i++) {
		vector[i] = 0;
	}
	return vector;
}
//double* CreateNullVector(int elements) {
//	double* vector;
//	for (int i = 0; i < NUM_OF_ELEMENTS; i++) {
//		vector.coordinates[i] = 0;
//	}
//	return vector;
//}
double** MatrixInit(int dimension) {
	if (dimension < 1) {
		return NULL;
	}
	double** matrix = (double**)malloc(sizeof(double*) * dimension);
	if (!matrix) {
		return NULL;
	}
	for (int i = 0; i < dimension; i++) {
		matrix[i] = (double*)malloc(sizeof(double) * dimension);
		if (!matrix[i]) {
			for (int j = 0; j < i; j++) {
				free(matrix[j]);
			}
			return NULL;
		}
	}
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			matrix[i][j] = 0;
		}
	}
	return matrix;
}
void VectorDelete(double* vector) {
	free(vector);
}
void  MatrixDelete(double** matrix, int dimension) {
	for (int j = 0; j < dimension; j++) {
		free(matrix[j]);
	}
	free(matrix);
}

void PrintVectorScreen(double* vector, int dimension) {
	for (int i = 0; i < dimension; i++) {
		printf("%lf", vector[i]);
	}
}
void PrintMatrixScreen(double** matrix, int dimension) {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			printf("%lf", matrix[i][j]);
		}
		printf("\n");
	}
}
double** ParseMatrix(FILE* f, double** matrix, int dimension) {
	if (!f) {
		perror("");
		return;
	}
	int control;
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			control = fscanf(f, "%lf;", &matrix[i][j]);
		}
	}
	return matrix;
}

double* ParseVector(FILE* g, double* vector, int dimension) {
	if (!g) {
		perror("");
		return;
	}
	int control;
	for (int i = 0; i < dimension; i++) {
		control = fscanf(g, "%lf;", &vector[i]);
	}
	return vector;
}

void PrintVector(FILE* g, double* vector, int dimension) {
	if (!g) {
		perror("");
		return;
	}
	int control;
	for (int i = 0; i < dimension; i++) {
		control = fprintf(g, "%0.15lf;", vector[i]);
	}
	fprintf(g, "\n");
}
double** MergeMatrix(double** A, double* B, int dimension)
{
	int i = 0;
	double** result = MatrixInit(dimension);
	if (!result) {
		printf("Init FAILED");
		return NULL;
	}
	for (i; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			result[i][j] = A[i][j];
		}
	}
	for (i; i < dimension + 1; i++) {
		for (int j = 0; j < dimension; j++) {
			result[j][i] = B[j];
		}
	}
	return result;
}
double* RotationsMethod(double** A, double* B, int dimension) {
	double** result = MergeMatrix(A, B, dimension);
	double* X = VectorInit(dimension);
	double cos, sin, a, b, tmp;
	for (int i = 0; i < dimension; i++) { //column counter
		for (int j = i + 1; j < dimension; j++) { //string numer counter
			a = result[i][i];
			b = result[j][i];
			cos = a / sqrt(a * a + b * b);
			sin = b / sqrt(a * a + b * b);
			// cycle for inner product k is number of a column that * on cos and sin matrix
			for (int k = i; k <= dimension; k++) {
				tmp = result[i][k];
				result[i][k] = cos * result[i][k] + sin * result[j][k];
				result[j][k] = -sin * tmp + cos * result[j][k];
			}
		}
	}
	for (int i = dimension - 1; i >= 0; i--) {
		double right_sum = 0.0;
		for (int j = i + 1; j < dimension; j++) {
			right_sum += result[i][j] * X[j];
		}
		right_sum = result[i][dimension] - right_sum;
		X[i] = right_sum / result[i][i];
	}
	free(result);
	return X;
}
int main(void) {
	int dimension = 10;
	int num_of_imported_matr = 10;
	char const* FILENAME_MATRIX = "D:\\ChislenniyeMetodi\\Lab2\\MATLAB_EXPORT_Matrix_A.csv";
	char const* FILENAME_VECTOR_B = "D:\\ChislenniyeMetodi\\Lab2\\MATLAB_EXPORT_Vector_B.csv";
	char const* FILENAME_VECTOR_X_APPROX = "D:\\ChislenniyeMetodi\\Lab2\\C_EXPORT_Vector_X_APPROX.csv";

	char const* FILENAME_MATRIX_SECOND = "D:\\ChislenniyeMetodi\\Lab2\\MATLAB_EXPORT_Matrix_A_SECOND.csv";
	char const* FILENAME_VECTOR_B_SECOND = "D:\\ChislenniyeMetodi\\Lab2\\MATLAB_EXPORT_Vector_B_SECOND.csv";
	char const* FILENAME_VECTOR_X_APPROX_SECOND = "D:\\ChislenniyeMetodi\\Lab2\\C_EXPORT_Vector_X_APPROX_SECOND.csv";

	char const* FILENAME_TIME_PROFILE = "D:\\ChislenniyeMetodi\\Lab2\\C_EXPORT_Time_Profile.csv";

	FILE* amat = fopen(FILENAME_MATRIX, "r");
	FILE* bvec = fopen(FILENAME_VECTOR_B, "r");
	FILE* xappr = fopen(FILENAME_VECTOR_X_APPROX, "w");

	FILE* amat_SECOND = fopen(FILENAME_MATRIX_SECOND, "r");
	FILE* bvec_SECOND = fopen(FILENAME_VECTOR_B_SECOND, "r");
	FILE* xappr_SECOND = fopen(FILENAME_VECTOR_X_APPROX_SECOND, "w");

	FILE* time_profile = fopen(FILENAME_TIME_PROFILE, "a");

	if (!amat || !bvec || !xappr || !amat_SECOND || !bvec_SECOND || !xappr_SECOND || !time_profile) {
		perror("");
		return 0;
	}
	double** matrix = MatrixInit(dimension);
	double* vector = VectorInit(dimension);

	double** matrix_SECOND = MatrixInit(dimension);
	double* vector_SECOND = VectorInit(dimension);
	for (int i = 0; i < num_of_imported_matr; i++) {
		matrix = ParseMatrix(amat, matrix, dimension);
		vector = ParseVector(bvec, vector, dimension);
		double* X = RotationsMethod(matrix, vector, dimension);
		PrintVector(xappr, X, dimension);
	}

	matrix_SECOND = ParseMatrix(amat_SECOND, matrix_SECOND, dimension);
	for (int j = 0; j < num_of_imported_matr; j++) {
		vector_SECOND = ParseVector(bvec_SECOND, vector_SECOND, dimension);
		double* X_SECOND = RotationsMethod(matrix_SECOND, vector_SECOND, dimension);
		PrintVector(xappr_SECOND, X_SECOND, dimension);

	}

	fclose(amat);
	fclose(bvec);
	fclose(xappr);

	fclose(amat_SECOND);
	fclose(bvec_SECOND);
	fclose(xappr_SECOND);

	//fprintf(time_profile, "%lf;", time_spent);
	fclose(time_profile);
	//PrintVectorScreen(vector, dimension);
	//printf("\n.........................\n");
	//PrintMatrixScreen(matrix, dimension);
	VectorDelete(vector, dimension);
	MatrixDelete(matrix, dimension);
	VectorDelete(vector_SECOND);
	MatrixDelete(matrix_SECOND, dimension);

	//third part of work, time profile plot
	//LARGE_INTEGER clockFrequency, before, after;
	//double time = 0;
	//QueryPerformanceFrequency(&clockFrequency);
	//char const* FILENAME_MATRIX = "D:\\ChislenniyeMetodi\\Lab2\\MATLAB_EXPORT_Matrix_A_THIRD.csv";
	//char const* FILENAME_VECTOR_B = "D:\\ChislenniyeMetodi\\Lab2\\MATLAB_EXPORT_Vector_B_THIRD.csv";
	//char const* FILENAME_TIME_PROFILE = "D:\\ChislenniyeMetodi\\Lab2\\C_EXPORT_Time_Profile.csv";
	//FILE* amat = fopen(FILENAME_MATRIX, "r");
	//FILE* bvec = fopen(FILENAME_VECTOR_B, "r");
	//FILE* time_f = fopen(FILENAME_TIME_PROFILE, "w");

	//if (!amat) {
	//	perror("");
	//	return -1;
	//}
	//if (!bvec) {
	//	perror("");
	//	fclose(amat);
	//	return -1;
	//}
	//if (!time_f) {
	//	perror("");
	//	fclose(amat);
	//	fclose(bvec);
	//	return -1;
	//}

	//int dimension = 50;
	//for (dimension; dimension <= MAX_DIMENSION; dimension += 50) {
	//	double** matrix_A_THIRD = MatrixInit(dimension);
	//	double* vector_B_THIRD = VectorInit(dimension);
	//	matrix_A_THIRD = ParseMatrix(amat, matrix_A_THIRD, dimension);
	//	vector_B_THIRD = ParseVector(bvec, vector_B_THIRD, dimension);
	//	QueryPerformanceCounter(&before);
	//	double* X = RotationsMethod(matrix_A_THIRD, vector_B_THIRD, dimension);
	//	QueryPerformanceCounter(&after);
	//	time = ((double)(after.QuadPart - before.QuadPart) / clockFrequency.QuadPart);
	//	fprintf(time_f, "%lf;", time);
	//	MatrixDelete(matrix_A_THIRD, dimension);
	//	VectorDelete(vector_B_THIRD);
	//}
	//fclose(amat);
	//fclose(bvec);
	//fclose(time_f);
	//return 0;
}