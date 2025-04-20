#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std; 

class Matrix {
private:
    vector<vector<double> > data;
    int m_rows;
    int m_cols;

public:
    Matrix(int r, int c) : m_rows(r), m_cols(c), data(r, vector<double>(c)) {}

    void inputMatrix(double arr[]) {
        int counter = 0;
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                data[i][j] = arr[counter];
                counter = counter + 1;
            }
        }
    }

    void display() const {
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                cout << data[i][j] << " ";
            }
            cout << "\n";
        }
    }

    Matrix add(const Matrix& other) const {
        if (m_rows != other.m_rows || m_cols != other.m_cols) {
            throw invalid_argument("Matrices must have the same dimensions to add.");
        }

        Matrix result(m_rows, m_cols);
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix transpose() const {
        Matrix result(m_cols, m_rows);
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    Matrix multiply(const Matrix& other) const {
        if (m_cols != other.m_rows)
            throw runtime_error("Matrix multiplication size mismatch.");
        Matrix result(m_rows, other.m_cols);
        for (int i = 0; i < m_rows; ++i)
            for (int j = 0; j < other.m_cols; ++j)
                for (int k = 0; k < m_cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }


    Matrix scalarMult(double num){
        Matrix result(m_rows, m_cols);
        for(int i = 0; i < m_rows; i++){
            for(int j = 0; j < m_cols; j++){
                result.data[i][j] = data[i][j] * num;
            }
        }
        return result;
    }
};

int main() {
    Matrix A(2, 2);
    double Anum[4] = {6, 4, 8, 3} ;
    A.inputMatrix(Anum);

    Matrix B(2,3);
    double Bnum[6] = {1, 2, 3, 4, 5, 6};
    B.inputMatrix(Bnum);

    Matrix C(2,3);
    double Cnum[6] = {2, 4, 6, 1, 3, 5};
    C.inputMatrix(Cnum);

    Matrix CT = C.transpose();

    Matrix Bx3 = B.scalarMult(3.0);
    Matrix Bx3CT = Bx3.multiply(CT);
    Matrix D = Bx3CT.add(A);

    D.display();

    return 0;
}
