#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate the least squares approximation for polynomial data
void leastSquaresPolynomial(double x[], double y[], int n, int m, double coeff[]) {
    double X[2 * m + 1];
    for (int i = 0; i < 2 * m + 1; i++) {
        X[i] = 0;
        for (int j = 0; j < n; j++) {
            X[i] += pow(x[j], i);
        }
    }

    double B[m + 1][m + 2], a[m + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            B[i][j] = X[i + j];
        }
    }

    double Y[m + 1];
    for (int i = 0; i <= m; i++) {
        Y[i] = 0;
        for (int j = 0; j < n; j++) {
            Y[i] += pow(x[j], i) * y[j];
        }
    }

    for (int i = 0; i <= m; i++) {
        B[i][m + 1] = Y[i];
    }

    m += 1;
    for (int i = 0; i < m; i++) {
        for (int k = i + 1; k < m; k++) {
            if (B[i][i] < B[k][i]) {
                for (int j = 0; j <= m; j++) {
                    double temp = B[i][j];
                    B[i][j] = B[k][j];
                    B[k][j] = temp;
                }
            }
        }
    }

    for (int i = 0; i < m - 1; i++) {
        for (int k = i + 1; k < m; k++) {
            double t = B[k][i] / B[i][i];
            for (int j = 0; j <= m; j++) {
                B[k][j] -= t * B[i][j];
            }
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        a[i] = B[i][m];
        for (int j = 0; j < m; j++) {
            if (j != i) {
                a[i] -= B[i][j] * a[j];
            }
        }
        a[i] /= B[i][i];
    }

    for (int i = 0; i < m; i++) {
        coeff[i] = a[i];
    }
}

int main() {
    int n, m;
    cout << "Enter the number of data points: ";
    cin >> n;
    double x[n], y[n];
    cout << "Enter the data points (x and y):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    cout << "Enter the degree of the polynomial: ";
    cin >> m;
    double coeff[m + 1];
    leastSquaresPolynomial(x, y, n, m, coeff);

    cout << "The least squares approximation polynomial is: y = ";
    for (int i = 0; i <= m; i++) {
        cout << coeff[i] << "x^" << i;
        if (i != m) {
            cout << " + ";
        }
    }
    cout << endl;

    return 0;
}

