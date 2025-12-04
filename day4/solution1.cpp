#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;
std::vector<std::string> get3x3Matrix(const std::vector<std::vector<std::string>> &matrix, int x, int y)
{
    std::vector<std::string> result;
    int rows = matrix.size();
    int cols = matrix[0].size();
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (x + i >= 0 && x + i < rows && y + j >= 0 && y + j < cols)
            {
                result.push_back(matrix[x + i][y + j]);
            }
            else
            {
                result.push_back("."); // or any placeholder for out-of-bounds
            }
        }
    }
    return result;
}
int main()
{
    std::ifstream file("inputSolution.txt");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    std::string line;

    std::vector<std::vector<std::string>> matrix;

    int result = 0;
    while (std::getline(file, line))
    {
        std::vector<std::string> row = {};
        for (char c : line)
        {
            row.push_back(std::string(1, c));
        }
        if (row.size() > 0)
        {
            matrix.push_back(row);
        }
    }

    int rowIndex = 0;
    for (std::vector<std::string> row : matrix)
    {
        int colIndex = 0;
        for (std::string cell : row)
        {
            if (cell == "@")
            {
                // matrix[rowIndex][colIndex] = "C";
                auto neighbors = get3x3Matrix(matrix, rowIndex, colIndex);
                neighbors[4] = ".";
                int countPapers = std::count(neighbors.begin(), neighbors.end(), "@");
                if (countPapers < 4)
                {
                    result++;
                    std::cout << "x";
                }
                else
                {
                    std::cout << cell;
                }
                matrix[rowIndex][colIndex] = "@";
            }
            else
            {
                std::cout << cell;
            }
            colIndex++;
        }
        std::cout << std::endl;
        rowIndex++;
    }

    file.close();

    std::cout << "Result:" << result << std::endl;
}