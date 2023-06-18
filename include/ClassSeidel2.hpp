#include <iostream>
#include <vector>
#include <cmath>

using namespace std;



class GaussSeidel {
private:
    vector<vector<double>> A;
    vector<double> b;
    vector<double> x0;

public:
    GaussSeidel() {}

    void solve() {
        int n;
        cout<<"=================================bienvenido al metodo Gauss Sediel================================="<<endl;
        cout<<"Ingrese la Dimension del sistema de ecuaciones: ";
        cin >> n;

        A = createMatrix(n);
        b = vector<double>(n, 0.0);
        x0 = vector<double>(n, 0.0);

        for (int i = 0; i < n; i++) {
            b[i] = A[i][n];
        }

        // Reordenar la matriz A y el vector b por la determinante dominante
        for (int i = 0; i < n; i++) {
            double maxElem = abs(A[i][i]);
            int maxRow = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(A[j][i]) > maxElem) {
                    maxElem = abs(A[j][i]);
                    maxRow = j;
                }
            }
            // Intercambiar filas
            if (maxRow != i) {
                for (int k = i; k <= n; k++) {
                    swap(A[i][k], A[maxRow][k]);
                }
            }
        }

        double epsilon = 0.0000000000001;
        int maxIter = 400;

        cout << "Estimacion inicial: ";
        for (double val : x0) {
            cout << val << " ";
        }
        cout << endl;

        vector<double> solution = gaussSeidel(A, b, x0, epsilon, maxIter);

        cout << "La solucion del sistema es: ";
        for (double val : solution) {
            cout << val << " ";
        }
        cout << endl;
    }


    void printIteration(int iteration, const vector<double>& x) {
        cout << "Iteracion " << iteration << ": ";
        for (double val : x) {
            cout << val << " ";
        }
        cout << endl;
    }

    vector<vector<double>> createMatrix(int n) {
        vector<vector<double>> matrix(n, vector<double>(n + 1, 0.0));
        cout << "Ingresa los coeficientes de la matriz A y el vector b:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << "A[" << i << "][" << j << "]: ";
                cin >> matrix[i][j];
            }
            cout << "b[" << i << "]: ";
            cin >> matrix[i][n];
        }
        return matrix;
    }

    vector<double> gaussSeidel(vector<vector<double>>& A, vector<double>& b, vector<double>& x0, double epsilon, int maxIter) {
        int n = A.size();
        vector<double> x = x0;
        int iterCount = 0;
        while (iterCount < maxIter) {
            vector<double> xNew = x;
            for (int i = 0; i < n; i++) {
                double sum1 = 0.0;
                double sum2 = 0.0;
                for (int j = 0; j < i; j++) {
                    sum1 += A[i][j] * xNew[j];
                }
                for (int j = i + 1; j < n; j++) {
                    sum2 += A[i][j] * x[j];
                }
                xNew[i] = (b[i] - sum1 - sum2) / A[i][i];
            }
            cout<<"----------------------------------------------------------"<<endl;
            cout.precision(12);
            printIteration(iterCount + 1, xNew);
            bool convergence = true;
            for (int i = 0; i < n; i++) {
                if (abs(xNew[i] - x[i]) >= epsilon) {
                    convergence = false;
                    break;
                }
            }
            if (convergence) {
                cout << "Convergencia alcanzada en la iteracion " << iterCount + 1 << endl;
                return xNew;
            }
            x = xNew;
            iterCount++;
        }
        cout << "No se alcanzo la convergencia en " << maxIter << " iteraciones" << endl;
        return x;
    }
};

