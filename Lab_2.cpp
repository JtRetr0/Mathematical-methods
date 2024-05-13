#include <iostream>
#include <vector>

class SimplexMethod {
private:
    static void Swap(std::vector<std::vector<double>>& table, int i, int j) {
        std::vector<double> temp = table[i];
        table[i] = table[j];
        table[j] = temp;
    }

    static void PrintTable(const std::vector<std::vector<double>>& table) {
        for (const auto& row : table) {
            for (double val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    static int FindPivotColumn(const std::vector<std::vector<double>>& table) {
        int n = table[0].size() - 1;
        int pivotColumn = 0;
        for (int j = 1; j < n; j++) {
            if (table[table.size() - 1][j] < table[table.size() - 1][pivotColumn]) {
                pivotColumn = j;
            }
        }
        return pivotColumn;
    }

    static int FindPivotRow(const std::vector<std::vector<double>>& table, int pivotColumn) {
        int m = table.size() - 1;
        int pivotRow = -1;
        double minRatio = std::numeric_limits<double>::max();
        for (int i = 0; i < m; i++) {
            if (table[i][pivotColumn] > 0) {
                double ratio = table[i][table[0].size() - 1] / table[i][pivotColumn];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    pivotRow = i;
                }
            }
        }
        return pivotRow;
    }

public:
    static void Solve(std::vector<std::vector<double>>& table) {
        int m = table.size() - 1;
        int n = table[0].size() - 1;

        PrintTable(table);

        while (true) {
            int pivotColumn = FindPivotColumn(table);
            if (table[m][pivotColumn] >= 0) {
                break;
            }

            int pivotRow = FindPivotRow(table, pivotColumn);
            if (pivotRow == -1) {
                std::cout << "The task is unlimited:" << std::endl;
                return;
            }

            double pivot = table[pivotRow][pivotColumn];
            for (int j = 0; j <= n; j++) {
                table[pivotRow][j] /= pivot;
            }
            for (int i = 0; i <= m; i++) {
                if (i != pivotRow) {
                    double factor = table[i][pivotColumn];
                    for (int j = 0; j <= n; j++) {
                        table[i][j] -= factor * table[pivotRow][j];
                    }
                }
            }
            PrintTable(table);
        }
        std::cout << "The maximum value of the function: " << table[m][n] << std::endl;
        std::cout << "Values of variables at which the maximum value is reached:" << std::endl;
        for (int i = 0; i < m; i++) {
            if (table[i][0] < n) {
                std::cout << "x" << static_cast<int>(table[i][0] + 1) << ": " << table[i][n] << std::endl;
            }
        }
    }
};

int main()
 {
    std::vector<std::vector<double>> table = {
        {2, 6, 1, 0, 0, 24},
        {5, 4, 0, 1, 0, 31},
        {2, 3, 0, 0, 1, 18},
        {-12, -16, 0, 0, 0, 0}
    };
    SimplexMethod::Solve(table);
    return 0;
}
