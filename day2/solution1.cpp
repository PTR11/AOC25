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
                string number = to_string(i);
                string firstPart = number.substr(0, number.length() / 2);
                string secondPart = number.substr(number.length() / 2, number.length());
                if (firstPart == secondPart)
                {
                    result += i;
                }
            }
        }
    }
    file.close();

    std::cout << "Result:" << result << std::endl;
}