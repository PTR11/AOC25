#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

long long makeMaxCombination(std::vector<int> &digits, int length)
{
    int taken, i = 0;
    int n = digits.size();
    int r = n - 1;
    long long joltage = 0;

    while (taken < length)
    {
        int remaining = length - taken - 1;
        int max = digits[i];
        int maxIndex = i;

        for (int j = i; j <= r + 1; ++j)
        {
            int remainingSlots = n - j - 1;
            if (digits[j] > max && remainingSlots >= remaining)
            {
                max = digits[j];
                maxIndex = j;
            }
        }
        joltage = joltage * 10 + max;
        i = maxIndex + 1;
        taken++;
    }
    return joltage;
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
    int lineCounter = 1;
    long long result = 0;
    while (std::getline(file, line))
    {
        long long maximum = 0;
        std::vector<int> digits;
        for (int i = 0; i < line.size(); ++i)
        {
            digits.push_back(line[i] - '0');
        }

        maximum = makeMaxCombination(digits, 12);
        result += maximum;
        lineCounter++;
    }
    file.close();

    std::cout << "Result:" << result << std::endl;
}