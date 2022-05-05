#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdbool.h>
#pragma warning (disable:4996)
#define MAX_DIMENSION 2000
#define NUM_OF_IMPORTED_MATRICES 10
#define TRUE 1
#define FALSE 0
#define MAX_STEPS 20000
#define NUMBER_OF_TESTS 10
double* VectorInit(int dimension) {
	if (!dimension) {
		printf("Incorrect dimension");
	}
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
void MatrixDelete(double** matrix, int dimension) {
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

int ParseVector(FILE* g, double* vector, int dimension) {
	if (!g) {
		perror("");
		return FALSE;
	}
	int control;
	for (int i = 0; i < dimension; i++) {
		control = fscanf(g, "%lf;", &vector[i]);
	}
	return TRUE;
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
double NormVec(double* B, int dimension) {
	double sum = 0;
	double Euclidian = 0;
	for (int i = 0; i < dimension; i++) {
		Euclidian += B[i] * B[i];
	}
	return pow(Euclidian, 0.5);
}
double NormVecInf(double* B, int dimension) {
	double max = 0;
	for (int i = 0; i < dimension; i++) {
		if ((fabs(B[i]) > max)) {
			max = B[i];
		}
	}
	return max;
}
void MMBV(double** A, double* B, double* result, int dimension) /*Multiply Matrix By Vector*/ {
	for (int i = 0; i < dimension; i++) {
		result[i] = 0;
	}
	if (!dimension) {
		return;
	}
	if (!A || !B || !result) {
		return;
	}
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			result[i] += A[i][j] * B[j];
		}
	}
	return;
}
void DV(double* A, double* B, double* result, int dimension) /* Difference Of Vectors */ {
	for (int i = 0; i < dimension; i++) {
		result[i] = 0;
	}
	for (int i = 0; i < dimension; i++) {
		result[i] = A[i] - B[i];
	}
	return;
}
void MVBN(double* B, double* result, double num, int dimension)/*Multiply Vector By Number */ {
	for (int i = 0; i < dimension; i++) {
		result[i] = 0;
	}
	for (int i = 0; i < dimension; i++) {
		result[i] = num * B[i];
	}
	return;
}
void DVBN(double* B, double* result, double num, double dimension) /*Division Vector By Number */ {
	for (int i = 0; i < dimension; i++) {
		result[i] = 0;
	}
	for (int i = 0; i < dimension; i++) {
		result[i] = B[i] / num;
	}
	return;
}
int ConditionStop(double** A, double* Xcur, double* eigenvalues, int dimension, int eignum, double eps) {
	double* AX = VectorInit(dimension);
	double* diff = VectorInit(dimension);
	double* LX = VectorInit(dimension);
#pragma region MEMCHECK
	if (!AX) {
		return FALSE;
	}
	if (!diff) {
		VectorDelete(AX);
		return FALSE;
	}
	if (!LX) {
		VectorDelete(AX);
		VectorDelete(diff);
		return FALSE;
	}
#pragma endregion
	MMBV(A, Xcur, AX, dimension);
	MVBN(Xcur, LX, eigenvalues[eignum], dimension);
	DV(AX, LX, diff, dimension);

	if (NormVec(diff, dimension) / NormVec(Xcur, dimension) <= eps) {
		VectorDelete(AX);
		VectorDelete(diff);
		VectorDelete(LX);
		return TRUE;
	}
	return FALSE;
}
int MVBV(double* V1, double* V2, double* result, int dimension) /*Multiply Vector By Vector. Inner product.*/ {
	*result = 0;
	for (int i = 0; i < dimension; i++) {
		*(result) += V1[i] * V2[i];
	}
	return TRUE;
}
int Shift(double* prev, double* Xcur, int dimension) {
	if (!prev || !Xcur) {
		return FALSE;
	}
	for (int i = 0; i < dimension; i++) {
		prev[i] = Xcur[i];
	}
	return TRUE;
}
double* PMM1(double** A, int dimension, double* eigenvalues, int* iter, double eps)/*with norm*/ {
	double* Y = VectorInit(dimension);
	double* X = VectorInit(dimension);
	double* Xprev = VectorInit(dimension);
	double* NormedAns = VectorInit(dimension);
	double AnsNorm = 0;
	double Ynorm = 0;

	for (int i = 0; i < dimension; i++) {
		Y[i] = 1.25;
	}
	Ynorm = NormVecInf(Y, dimension);
	DVBN(Y, Xprev, Ynorm, dimension);
	for (int k = 1; k < MAX_STEPS; k++) {
		MMBV(A, Xprev, Y, dimension);
		Ynorm = NormVecInf(Y, dimension);
		DVBN(Y, X, Ynorm, dimension);
		eigenvalues[0] = Y[0] / Xprev[0];
		if (ConditionStop(A, X, eigenvalues, dimension, 0, 100 * eps)) /*without norm*/ {
			break;
		}
		int check = Shift(Xprev, X, dimension);
		(*iter)++;
	}
	AnsNorm = NormVecInf(X, dimension);
	DVBN(X, NormedAns, AnsNorm, dimension);
	free(X);
	return NormedAns;
}
double* PMM2(double** A, int dimension, double* eigenvalues, int* iter, double eps, double* FirstEigVec) {
	double* X = VectorInit(dimension);
	double* Xprev = VectorInit(dimension);
	for (int i = 0; i < dimension; i++) {
		X[i] = 1.25;
		Xprev[i] = 1.00;
	}
	for (int k = 1; k < MAX_STEPS; k++) {
		MMBV(A, Xprev, X, dimension);
		eigenvalues[1] = X[0] / Xprev[0];
		if (ConditionStop(A, X, eigenvalues, dimension, 1, 1000 * eps)) {
			break;
		}
		int check = Shift(Xprev, X, dimension);
		(*iter)++;
	}
	return X;

}
//double* PMM2(double** A, int dimension, double* eigenvalues, int* iter, double eps, double* FirstEigVec) {
//	double* X = VectorInit(dimension);
//	double* Yprev = VectorInit(dimension);
//	double* Ycur = VectorInit(dimension);
//	double* Ynext = VectorInit(dimension);
//	double* gammaW = VectorInit(dimension);
//	double* AYcur = VectorInit(dimension);
//	double norm = 0;
//	double gamma = 0;
//	double XW = 0;
//	double WW = 0;
//	for (int i = 0; i < dimension; i++) {
//		X[i] = 1.64;
//		Yprev[i] = 1.15;
//		Ycur[i] = 1.25;
//		Ynext[i] = 1.35;
//
//	}
//	MVBV(X, FirstEigVec, &XW, dimension);
//	MVBV(FirstEigVec, FirstEigVec, &WW, dimension);
//	gamma = XW / WW;
//	MVBN(FirstEigVec, gammaW, gamma, dimension);
//	DV(X, gammaW, Yprev, dimension);
//	do {
//		MVBV(Yprev, FirstEigVec, &XW, dimension);
//		MVBV(FirstEigVec, FirstEigVec, &WW, dimension);
//		gamma = XW / WW;
//		MVBN(FirstEigVec, gammaW, gamma, dimension);
//		DV(Yprev, gammaW, Ycur, dimension);
//		MMBV(A, Ycur, AYcur, dimension);
//		int check = Shift(Ycur, AYcur, dimension);
//		norm = NormVecInf(Ycur, dimension);
//		DVBN(Ycur, Ynext, norm, dimension);
//		eigenvalues[1] = norm;
//		check = Shift(Yprev, Ynext, dimension);
//		if (iter) {
//			(*iter)++;
//		}
//		if (iter && (*iter) > MAX_STEPS) {
//			break;
//		}
//	} while (!ConditionStop(A, Ynext, eigenvalues, dimension, 1, 1000 * eps));
//	free(Yprev);
//	free(Ycur);
//	free(gammaW);
//	free(AYcur);
//	free(X);
//	return Ynext;
//}

//
//double* PMM2(double** A, int dimension, double* eigenvalues, int* iter, double eps, double* EigVec) {
//	double* Yprev = VectorInit(dimension);
//	double* Ycur = VectorInit(dimension);
//	double* Ynext = VectorInit(dimension);
//	double* LY = VectorInit(dimension);
//	double* Diff = VectorInit(dimension);
//	double* SEigVec = VectorInit(dimension);
//	int check = -1;
//	for (int i = 0; i < dimension; i++) {
//		Yprev[i] = 0.25;
//		Ycur[i] = 0.25;
//		Ynext[i] = 0.25;
//	}
//	//Second Max Eig Num
//	for (int k = 1; k < MAX_STEPS; k++) {
//		MMBV(A, Ycur, Ynext, dimension);
//		eigenvalues[1] = (Ynext[1] - eigenvalues[0] * Ycur[1]) / (Ycur[1] - eigenvalues[0] * Yprev[1]);
//		printf("%lf", eigenvalues[1]);
//		MVBN(Ycur, LY, eigenvalues[0], dimension);
//		DV(Ynext, LY, Diff, dimension);
//		DVBN(Diff, SEigVec, pow(eigenvalues[1], k), dimension);
//		if (ConditionStop(A, SEigVec, eigenvalues, dimension, 1, eps)) {
//			break;
//		}
//		check = Shift(Yprev, Ycur, dimension);
//		check = Shift(Ycur, Ynext, dimension);
//		(*iter)++;
//	}
//	VectorDelete(Ycur);
//	VectorDelete(Yprev);
//	VectorDelete(Ynext);
//	VectorDelete(LY);
//	VectorDelete(Diff);
//	return SEigVec;
//}

int main(void) {
	char const* FILENAME_MATRIX_A = "MATLAB_EXPORT_Matrix_A.csv";
	char const* FILENAME_FIRST_EIG_VEC = "C_EXPORT_First_Eig_Vec.csv";
	char const* FILENAME_FIRST_EIG = "C_EXPORT_First_Eig.csv";
	char const* FILENAME_FIRST_ITER = "C_EXPORT_First_Iter.csv";
	char const* FILENAME_SECOND_EIG_VEC = "C_EXPORT_Second_Eig_Vec.csv";
	char const* FILENAME_SECOND_EIG = "C_EXPORT_Second_Eig.csv";
	char const* FILENAME_SECOND_ITER = "C_EXPORT_Second_Iter.csv";
	char const* FILENAME_SEP_VAL_A = "MATLAB_EXPORT_Sep_Val_Matrix_A.csv";
	char const* FILENAME_F_SEP_VAL_ITER = "C_EXPORT_F_Sep_Val_Iter.csv";
	char const* FILENAME_S_SEP_VAL_ITER = "C_EXPORT_S_Sep_Val_Iter.csv";
	char const* FILENAME_F_SEP_VAL_EIG = "C_EXPORT_F_Sep_Val_Eig.csv";
	char const* FILENAME_S_SEP_VAL_EIG = "C_EXPORT_S_Sep_Val_Eig.csv";
	FILE* m_A = fopen(FILENAME_MATRIX_A, "r");
	FILE* f_E_V = fopen(FILENAME_FIRST_EIG_VEC, "w");
	FILE* f_E = fopen(FILENAME_FIRST_EIG, "w");
	FILE* f_ITER = fopen(FILENAME_FIRST_ITER, "w");
	FILE* s_E_V = fopen(FILENAME_SECOND_EIG_VEC, "w");
	FILE* s_E = fopen(FILENAME_SECOND_EIG, "w");
	FILE* s_ITER = fopen(FILENAME_SECOND_ITER, "w");
	FILE* sep_val_F_ITER = fopen(FILENAME_F_SEP_VAL_ITER, "w");
	FILE* sep_val_S_ITER = fopen(FILENAME_S_SEP_VAL_ITER, "w");
	FILE* sep_val_F_EIG = fopen(FILENAME_F_SEP_VAL_EIG, "w");
	FILE* sep_val_S_EIG = fopen(FILENAME_S_SEP_VAL_EIG, "w");
	if (!m_A || !f_E || !f_ITER || !s_E || !s_ITER || !f_E_V || !s_E_V || !sep_val_F_ITER || !sep_val_S_ITER || !sep_val_F_EIG || !sep_val_S_EIG) {
		perror("");
		return -1;
	}
	int dimension = 10;
	int iter = 0;
	int Siter = 0;
	double eps = 0.00000000000001;
	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		double** A = MatrixInit(dimension);
		double* EigVecResult = VectorInit(dimension);
		double* SEigVecResult = VectorInit(dimension);
		double* eigs = VectorInit(dimension);
		int check = ParseMatrix(m_A, A, dimension);
		EigVecResult = PMM1(A, dimension, eigs, &iter, eps);
		PrintVector(f_E_V, EigVecResult, dimension);
		fprintf(f_E, "%0.15lf;", eigs[0]);
		fprintf(f_ITER, "%d;", iter);


		SEigVecResult = PMM2(A, dimension, eigs, &Siter, eps, EigVecResult);
		PrintVector(s_E_V, SEigVecResult, dimension);
		fprintf(s_E, "%0.15lf;", eigs[1]);
		fprintf(s_ITER, "%d;", Siter);

		//eps = eps / 10;
		iter = 0;
		Siter = 0;
		MatrixDelete(A, dimension);
		VectorDelete(EigVecResult);
		VectorDelete(SEigVecResult);
		VectorDelete(eigs);
	}

	eps = 0.00001;
	while (eps > 1e-15) {
		FILE* sep_val_A = fopen(FILENAME_SEP_VAL_A, "r");
		double** A = MatrixInit(dimension);
		double* EigVecResult = VectorInit(dimension);
		double* SEigVecResult = VectorInit(dimension);
		double* eigs = VectorInit(dimension);
		int check = ParseMatrix(sep_val_A, A, dimension);
		EigVecResult = PMM1(A, dimension, eigs, &iter, eps);
		fprintf(sep_val_F_EIG, "%0.15lf;", eigs[0]);
		fprintf(sep_val_F_ITER, "%d;", iter);

		SEigVecResult = PMM2(A, dimension, eigs, &Siter, eps, EigVecResult);
		fprintf(sep_val_S_EIG, "%0.15lf;", eigs[1]);
		fprintf(sep_val_S_ITER, "%d;", Siter);

		eps = eps / 10;
		iter = 0;
		Siter = 0;
		//MatrixDelete(A, dimension);
		VectorDelete(EigVecResult);
		VectorDelete(SEigVecResult);
		VectorDelete(eigs);
		fclose(sep_val_A);
	}

	fclose(m_A);
	fclose(f_E_V);
	fclose(f_E);
	fclose(f_ITER);
	fclose(s_E_V);
	fclose(s_E);
	fclose(s_ITER);
	return 0;
}