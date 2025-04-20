#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

Matrix createMatrix(int rows, int cols) {
    Matrix m;
    int i;

    m.rows = rows;
    m.cols = cols;
    m.data = (double**)malloc(rows * sizeof(double*));

    for (i = 0; i < rows; i++) {
        m.data[i] = (double*)calloc(cols, sizeof(double));
    }

    return m;
}

void freeMatrix(Matrix* m) {
    int i;
    for (i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    m->data = NULL;
}

void inputMatrix(Matrix* m, const double* arr) {
    int i, j;
    int counter = 0;

    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            m->data[i][j] = arr[counter++];
        }
    }
}

void displayMatrix(const Matrix* m) {
    int i, j;
    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            printf("%lf ", m->data[i][j]);
        }
        printf("\n");
    }
}

Matrix addMatrix(const Matrix* a, const Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        fprintf(stderr, "Matrix addition dimension mismatch.\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = createMatrix(a->rows, a->cols);
    int i, j;

    for (i = 0; i < a->rows; i++) {
        for (j = 0; j < a->cols; j++) {
            result.data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }

    return result;
}

Matrix transposeMatrix(const Matrix* m) {
    Matrix result = createMatrix(m->cols, m->rows);
    int i, j;

    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            result.data[j][i] = m->data[i][j];
        }
    }

    return result;
}

Matrix multiplyMatrix(const Matrix* a, const Matrix* b) {
    if (a->cols != b->rows) {
        fprintf(stderr, "Matrix multiplication size mismatch.\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = createMatrix(a->rows, b->cols);
    int i, j, k;

    for (i = 0; i < a->rows; i++) {
        for (j = 0; j < b->cols; j++) {
            for (k = 0; k < a->cols; k++) {
                result.data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }

    return result;
}

Matrix scalarMultMatrix(const Matrix* m, double scalar) {
    Matrix result = createMatrix(m->rows, m->cols);
    int i, j;

    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            result.data[i][j] = m->data[i][j] * scalar;
        }
    }

    return result;
}

int main(void) {
    Matrix A = createMatrix(2, 2);
    double Anum[4] = {6, 4, 8, 3};
    inputMatrix(&A, Anum);

    Matrix B = createMatrix(2, 3);
    double Bnum[6] = {1, 2, 3, 4, 5, 6};
    inputMatrix(&B, Bnum);

    Matrix C = createMatrix(2, 3);
    double Cnum[6] = {2, 4, 6, 1, 3, 5};
    inputMatrix(&C, Cnum);

    Matrix CT = transposeMatrix(&C);
    Matrix Bx3 = scalarMultMatrix(&B, 3.0);
    Matrix Bx3CT = multiplyMatrix(&Bx3, &CT);
    Matrix D = addMatrix(&Bx3CT, &A);

    displayMatrix(&D);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&CT);
    freeMatrix(&Bx3);
    freeMatrix(&Bx3CT);
    freeMatrix(&D);

    return 0;
}