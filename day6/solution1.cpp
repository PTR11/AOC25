#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;
std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
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
    std::vector<std::vector<long long>> numbers;
    std::vector<string> symbols;

    long long result = 0;
    while (std::getline(file, line))
    {
        std::vector<std::string> parts = split(line, ' ');
        std::vector<long long> rowNumbers;
        if (!isdigit(parts[0][0]) && !parts[0].empty())
        {
            for (const auto &part : parts)
            {
                if (part.empty())
                    continue;
                symbols.push_back(part);
            }
        }
        else
        {
            for (const auto &part : parts)
            {
                if (part.empty())
                    continue;
                rowNumbers.push_back(stoll(part));
            }
            numbers.push_back(rowNumbers);
        }
    }

    for (int i = 0; i < symbols.size(); i++)
    {
        long long columnResult = (symbols[i] == "+") ? 0 : 1;

        if (symbols[i] == "+")
        {
            for (int j = 0; j < numbers.size(); j++)
            {
                columnResult += numbers[j][i];
            }
        }
        else if (symbols[i] == "*")
        {
            for (int j = 0; j < numbers.size(); j++)
            {
                columnResult *= numbers[j][i];
            }
        }
        result += columnResult;
    }

    file.close();
    std::cout << "Result:" << result << std::endl;
}