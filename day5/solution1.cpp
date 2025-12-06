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
    std::vector<std::pair<long long, long long>> intervals;

    int result = 0;
    while (std::getline(file, line))
    {
        std::vector<std::string> parts = split(line, '-');
        if (line.empty())
            continue;
        if (parts.size() == 2)
        {
            long long start = stoll(parts[0]);
            long long end = stoll(parts[1]);
            intervals.push_back({start, end});
        }
        else
        {
            long long current = stoll(parts[0]);
            bool found = std::any_of(intervals.begin(), intervals.end(), [current](const std::pair<long long, long long> &interval)
                                     { return current >= interval.first && current <= interval.second; });
            result += found ? 1 : 0;
        }
    }

    file.close();
    std::cout << "Result:" << result << std::endl;
}