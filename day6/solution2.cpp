#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

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
    std::vector<string> input;
    std::vector<string> symbols;

    long long result = 0;
    while (std::getline(file, line))
    {
        input.push_back(line);
    }

    auto asd = input[input.size() - 1].size();
    std::vector<long long> numbers;
    for (int i = input[input.size() - 1].size() - 1; i >= 0; i--)
    {
        std::string number;
        for (int j = 0; j < input.size() - 1; j++)
        {
            if (input[j][i] == ' ')
                continue;
            number += std::string(1, input[j][i]);
        }
        if (!number.empty())
            numbers.push_back(stoll(number));
        char op = input[input.size() - 1][i];
        if (op == '+')
        {
            result += std::accumulate(numbers.begin(), numbers.end(), 0LL);
            numbers.clear();
        }
        else if (op == '*')
        {
            result += std::accumulate(numbers.begin(), numbers.end(), 1LL, std::multiplies<long long>());
            numbers.clear();
        }
    }

    file.close();
    std::cout << "Result:" << result << std::endl;
}