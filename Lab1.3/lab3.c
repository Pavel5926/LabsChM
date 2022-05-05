#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdbool.h>
#pragma warning (disable:4996)
#define MAX_DIMENSION 2000
#define NUM_OF_IMPORTED_MATRICES 10
#define TRUE 1
#define FALSE 0 
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
		printf("%0.9lf ", vector[i]);
	}
}
void PrintMatrixScreen(double** matrix, int dimension) {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			printf("%0.9lf ", matrix[i][j]);
		}
		printf("\n");
	}
}
int ParseMatrix(FILE* f, double** matrix, int dimension) {
	if (!f) {
		perror("");
		return FALSE;
	}
	int control;
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			control = fscanf(f, "%lf;", &matrix[i][j]);
		}
	}
	return TRUE;
}

double* ParseVector(FILE* g, double* vector, int dimension) {
	if (!g) {
		perror("");
		return NULL;
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
double Norm(double** C, int dimension) {
	double sum = 0;
	double max = 0;
	for (int i = 0; i < dimension; i++) {
		sum = 0;
		for (int j = 0; j < dimension; j++) {
			sum += fabs(C[i][j]);
		}
		if (sum > max) {
			max = sum;
		}
	}
	return max;
 }


int ConditionStop(double* cur, double* prev, int dimension, double eps, double Cnorm) {
	int check = TRUE;
	for (int i = 0; i < dimension - 1; i++) {
		if (fabs(cur[i] - prev[i]) > (1 - Cnorm) * eps / (Cnorm)) {
			check = FALSE;
			break;
		}
	}
	return check;
}
double* MPI(double** A, double* B, int dimension, double eps, double alpha, double Cnorm, double** C, int* iter)
{
	double* Xtmp = VectorInit(dimension);
	double* Xprev = VectorInit(dimension);
	
	if (!Xprev) {
		perror("");
		return NULL;
	}

	for (int i = 0; i < dimension; i++)
	{
		Xprev[i] = B[i] * alpha;
	}

	double* Xcur = VectorInit(dimension);
	
	if (!Xcur) {
		perror("");
		free(Xprev);
		return NULL;
	}

	do {
		(*iter)++;
		for (int i = 0; i < dimension; i++) {
			Xcur [i] = B[i]*alpha;
			for (int j = 0; j < dimension; j++) {
					Xcur[i] += C[i][j] * Xprev[j];
			}
		}
		for (int i = 0; i < dimension; i++) {
			Xtmp[i] = Xprev[i];
		}

		for (int i = 0; i < dimension; i++) {
			Xprev[i] = Xcur[i];
		}

	} while (!ConditionStop(Xcur, Xtmp, dimension, eps, Cnorm));
	free(Xcur);
	free(Xtmp);
	//free(C);
	return Xprev;
}


int main(void) {
	char const* FILENAME_MATRIX_A = "D:\\ChislenniyeMetodi\\Lab3\\MATLAB_EXPORT_MatrixA.csv";
	char const* FILENAME_VECTOR_B = "D:\\ChislenniyeMetodi\\Lab3\\MATLAB_EXPORT_VectorB.csv";
	char const* FILENAME_VECTOR_X = "D:\\ChislenniyeMetodi\\Lab3\\C_EXPORT_VectorX.csv";
	FILE* m_A = fopen(FILENAME_MATRIX_A, "r");
	FILE* v_B = fopen(FILENAME_VECTOR_B, "r");
	FILE* v_X_out = fopen(FILENAME_VECTOR_X, "w");
	if (!m_A || !v_B) {
		perror("");
		return -1;
	}

	int dimension = 10;
	double eps = 0.000000000000001;
	for (int i = 0; i < NUM_OF_IMPORTED_MATRICES; i++) {
		double** matrix_A = MatrixInit(dimension);
		double* vector_B = VectorInit(dimension);
		double* result_X = VectorInit(dimension);
		int check = ParseMatrix(m_A, matrix_A, dimension);
		vector_B = ParseVector(v_B, vector_B, dimension);
		double Anorm = Norm(matrix_A, dimension);
		double alpha = 1 / Anorm;
		int iterations = 0;
		double** C = MatrixInit(dimension);
		for (int i = 0; i < dimension; i++) {
			C[i][i] = 1;
		}
		//PrintMatrixScreen(C, dimension);
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				C[i][j] -= matrix_A[i][j] * alpha;
				//printf("%lf ", C[i][j]);
			}
			//printf("\n");
		}
		PrintMatrixScreen(C, dimension);
		//printf("\n");
		double Cnorm = Norm(C, dimension);
		result_X = MPI(matrix_A, vector_B, dimension, eps, alpha, Cnorm, C, &iterations);
		PrintVector(v_X_out, result_X,dimension);
		//PrintVectorScreen(result_X, dimension);
		MatrixDelete(matrix_A,dimension);
		VectorDelete(vector_B);
		VectorDelete(result_X);
		free(C);
	}
	fclose(m_A);
	fclose(v_B);
	fclose(v_X_out);
	return 0;
}

//int main(void) {
//	char const* FILENAME_MATRIX_A = "D:\\ChislenniyeMetodi\\Lab3\\MATLAB_EXPORT_MatrixA.csv";
//	char const* FILENAME_VECTOR_B = "D:\\ChislenniyeMetodi\\Lab3\\MATLAB_EXPORT_VectorB.csv";
//	char const* FILENAME_VECTOR_X = "D:\\ChislenniyeMetodi\\Lab3\\C_EXPORT_VectorX.csv";
//	char const* FILENAME_ITERATIONS = "D:\\ChislenniyeMetodi\\Lab3\\C_EXPORT_Iterations.csv";
//	FILE* m_A = fopen(FILENAME_MATRIX_A, "r");
//	FILE* v_B = fopen(FILENAME_VECTOR_B, "r");
//	FILE* v_X_out = fopen(FILENAME_VECTOR_X, "w");
//	FILE* iters = fopen(FILENAME_ITERATIONS, "w");
//	if (!m_A || !v_B || !iters) {
//		perror("");
//		return -1;
//	}
//
//	int dimension = 10;
//	double eps = 0.00001;
//	for (eps; eps > 0.00000000000001;) {
//		double** matrix_A = MatrixInit(dimension);
//		double* vector_B = VectorInit(dimension);
//		double* result_X = VectorInit(dimension);
//		int check = ParseMatrix(m_A, matrix_A, dimension);
//		vector_B = ParseVector(v_B, vector_B, dimension);
//		double Anorm = Norm(matrix_A, dimension);
//		double alpha = 1 / Anorm;
//		int iterations = 0;
//		double** C = MatrixInit(dimension);
//		for (int i = 0; i < dimension; i++) {
//			C[i][i] = 1;
//		}
//		PrintMatrixScreen(C, dimension);
//		for (int i = 0; i < dimension; i++) {
//			for (int j = 0; j < dimension; j++) {
//				C[i][j] -= matrix_A[i][j] * alpha;
//				printf("%lf ", C[i][j]);
//			}
//			printf("\n");
//		}
//		PrintMatrixScreen(C, dimension);
//		printf("\n");
//		double Cnorm = Norm(C, dimension);
//		result_X = MPI(matrix_A, vector_B, dimension, eps, alpha, Cnorm, C, &iterations);
//		int itercheck = fprintf(iters, "%d;", iterations);
//		iterations = 0;
//		PrintVector(v_X_out, result_X, dimension);
//		PrintVectorScreen(result_X, dimension);
//		MatrixDelete(matrix_A, dimension);
//		VectorDelete(vector_B);
//		VectorDelete(result_X);
//		free(C);
//		eps = eps / 10;
//	}
//	fclose(m_A);
//	fclose(v_B);
//	fclose(v_X_out);
//	fclose(iters);
//	return 0;
//}

//int main(void) {
//	double eps = 0.000000000000001;
//	LARGE_INTEGER clockFrequency, before, after;
//	double time = 0;
//	QueryPerformanceFrequency(&clockFrequency);
//	char const* FILENAME_MATRIX = "D:\\ChislenniyeMetodi\\Lab3\\MATLAB_EXPORT_MatrixA.csv";
//	char const* FILENAME_VECTOR_B = "D:\\ChislenniyeMetodi\\Lab3\\MATLAB_EXPORT_VectorB.csv";
//	char const* FILENAME_TIME_PROFILE = "D:\\ChislenniyeMetodi\\Lab3\\C_EXPORT_Time_Profile.csv";
//	FILE* amat = fopen(FILENAME_MATRIX, "r");
//	FILE* bvec = fopen(FILENAME_VECTOR_B, "r");
//	FILE* time_f = fopen(FILENAME_TIME_PROFILE, "w");
//
//	if (!amat) {
//		perror("");
//		return -1;
//	}
//	if (!bvec) {
//		perror("");
//		fclose(amat);
//		return -1;
//	}
//	if (!time_f) {
//		perror("");
//		fclose(amat);
//		fclose(bvec);
//		return -1;
//	}
//
//	int dimension = 50;
//	for (dimension; dimension <= MAX_DIMENSION; dimension += 50) {
//		double** matrix_A = MatrixInit(dimension);
//		double* vector_B = VectorInit(dimension);
//		matrix_A = ParseMatrix(amat, matrix_A, dimension);
//		vector_B = ParseVector(bvec, vector_B, dimension);
//		QueryPerformanceCounter(&before);
//		double* X = MPI(matrix_A, vector_B, dimension, eps);
//		QueryPerformanceCounter(&after);
//		time = ((double)(after.QuadPart - before.QuadPart) / clockFrequency.QuadPart);
//		fprintf(time_f, "%lf;", time);
//		MatrixDelete(matrix_A, dimension);
//		VectorDelete(vector_B);
//	}
//	fclose(amat);
//	fclose(bvec);
//	fclose(time_f);
//	return 0;
//}