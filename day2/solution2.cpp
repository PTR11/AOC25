#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
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

bool isRepeatedPattern(const std::string &number, int len)
{
    for (size_t i = len; i < number.size(); ++i)
    {
        if (number[i] != number[i % len])
            return false;
    }
    return true;
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
    long long result = 0;

    while (std::getline(file, line))
    {
        std::vector<string> intervals = split(line, ',');
        for (string interval : intervals)
        {
            std::vector<string> limits = split(interval, '-');
            long long lowerLimit = stoll(limits.at(0));
            long long upperLimit = stoll(limits.at(1));
            for (long long i = lowerLimit; i <= upperLimit; i++)
            {
                auto number = to_string(i);
                for (size_t len = 1; len <= number.size() / 2; ++len)
                {
                    if (number.size() % len != 0)
                        continue;
                    if (isRepeatedPattern(number, len))
                    {
                        result += i;
                        break;
                    }
                }
            }
        }
    }
    file.close();
    std::cout << "Result:" << result << std::endl;
}