#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const double EPSILON = 1e-10; // Small value for numerical comparisons
const double INF = numeric_limits<double>::infinity();

// Struct to represent a linear programming problem in standard form
struct LinearProgrammingProblem {
    vector<vector<double>> A; // Coefficients of the constraints
    vector<double> b;         // Right-hand side of the constraints
    vector<double> c;         // Coefficients of the objective function
};

// Helper function to print a matrix
void printMatrix(const vector<vector<double>>& mat) {
    for (const auto& row : mat) {
        for (double elem : row) {
            cout << elem << "\t";
        }
        cout << endl;
    }
}

// Function to read a matrix from user input
vector<vector<double>> readMatrix(int rows, int cols) {
    vector<vector<double>> mat(rows, vector<double>(cols));
    cout << "Enter the matrix (" << rows << "x" << cols << "):" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> mat[i][j];
        }
    }
    return mat;
}

// Function to read a vector from user input
vector<double> readVector(int size) {
    vector<double> vec(size);
    cout << "Enter the vector (" << size << " elements):" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> vec[i];
    }
    return vec;
}

// Function to read a linear programming problem from user input
LinearProgrammingProblem readProblem() {
    LinearProgrammingProblem problem;
    int m, n;

    cout << "Enter the number of constraints (m): ";
    cin >> m;
    cout << "Enter the number of variables (n): ";
    cin >> n;

    cout << "Enter the coefficients of the constraints (A matrix):" << endl;
    problem.A = readMatrix(m, n);

    cout << "Enter the right-hand side of the constraints (b vector):" << endl;
    problem.b = readVector(m);

    cout << "Enter the coefficients of the objective function (c vector):" << endl;
    problem.c = readVector(n);

    return problem;
}

// Simplex method implementation
vector<double> simplex(const LinearProgrammingProblem& problem) {
    int m = problem.A.size();
    int n = problem.A[0].size();

    vector<vector<double>> tableau(m + 1, vector<double>(n + m + 1));

    // Construct initial tableau
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            tableau[i][j] = problem.A[i][j];
        }
        tableau[i][n + i] = 1;
        tableau[i][n + m] = problem.b[i];
    }
    for (int j = 0; j < n; ++j) {
        tableau[m][j] = -problem.c[j];
    }
    tableau[m][n + m] = 0;

    // Perform simplex iterations
    while (true) {
        int pivot_col = -1;
        for (int j = 0; j <= n + m; ++j) {
            if (tableau[m][j] < -EPSILON) {
                pivot_col = j;
                break;
            }
        }
        if (pivot_col == -1) break;

        int pivot_row = -1;
        double min_ratio = INF;
        for (int i = 0; i < m; ++i) {
            if (tableau[i][pivot_col] > EPSILON) {
                double ratio = tableau[i][n + m] / tableau[i][pivot_col];
                if (ratio < min_ratio) {
                    min_ratio = ratio;
                    pivot_row = i;
                }
            }
        }
        if (pivot_row == -1) {
            // Unbounded problem
            return vector<double>();
        }

        // Perform pivot operation
        double pivot_elem = tableau[pivot_row][pivot_col];
        for (int j = 0; j <= n + m; ++j) {
            tableau[pivot_row][j] /= pivot_elem;
        }
        for (int i = 0; i <= m; ++i) {
            if (i != pivot_row) {
                double multiplier = tableau[i][pivot_col];
                for (int j = 0; j <= n + m; ++j) {
                    tableau[i][j] -= multiplier * tableau[pivot_row][j];
                }
            }
        }
    }

    // Extract solution from tableau
    vector<double> solution(n, 0);
    for (int i = 0; i < m; ++i) {
        int var_index = -1;
        for (int j = 0; j < n; ++j) {
            if (abs(tableau[i][j] - 1) < EPSILON) {
                var_index = j;
                break;
            }
        }
        if (var_index != -1) {
            solution[var_index] = tableau[i][n + m];
        }
    }

    return solution;
}

int main() {
    // Read the linear programming problem from user input
    LinearProgrammingProblem problem = readProblem();

    // Solve the linear programming problem
    vector<double> solution = simplex(problem);

    // Print solution
    cout << "Optimal solution:" << endl;
    for (int i = 0; i < solution.size(); ++i) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }

    // Calculate and print the value of the objective function
    double objective_value = 0;
    for (int i = 0; i < solution.size(); ++i) {
        objective_value += solution[i] * problem.c[i];
    }
    cout << "Z = " << objective_value << endl;

    return 0;
}
