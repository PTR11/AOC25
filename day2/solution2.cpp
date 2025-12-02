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

std::vector<std::string> splitIntoParts(const std::string &str, int x)
{
    std::vector<std::string> parts;
    size_t position = 0;
    while (position < str.size())
    {
        parts.push_back(str.substr(position, x));
        position += x;
    }
    return parts;
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
                string tmp = "";
                bool findInvalid = false;
                for (char c : number)
                {
                    tmp += c;
                    if (tmp.size() == number.size())
                    {
                        break;
                    }
                    std::vector<std::string> parts = splitIntoParts(number, tmp.size());
                    bool allEqual = std::all_of(parts.begin(), parts.end(), [&](const std::string &part)
                                                { return part == parts[0]; });
                    if (allEqual)
                    {
                        result += i;
                        findInvalid = true;
                        break;
                    }
                }
                if (findInvalid)
                {
                    continue;
                }
            }
        }
    }
    file.close();

    std::cout << "Result:" << result << std::endl;
}