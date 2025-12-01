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
    int code = 50;
    int result = 0;
    int lineCounter = 1;

    while (std::getline(file, line))
    {
        auto direction = line.at(0);
        int number = stoi(line.substr(1, line.size())) % 100;

        if (direction == 'L')
        {
            if ((code - number) < 0)
            {
                code = 100 - abs(code - number);
            }
            else
            {
                code = code - number;
            }
        }
        else if (direction == 'R')
        {
            if ((code + number) > 99)
            {
                code = code + number - 100;
            }
            else
            {
                code = code + number;
            }
        }

        if (code == 0)
        {
            result++;
        }
        lineCounter++;
    }
    file.close();

    std::cout << "Result:" << result << std::endl;
}