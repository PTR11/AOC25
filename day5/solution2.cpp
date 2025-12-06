#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <chrono>

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
    std::ifstream file("inputTask.txt");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::pair<long long, long long>> intervals;

    long long result = 0;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        std::vector<std::string> parts = split(line, '-');
        if (parts.size() == 2)
        {
            long long start = stoll(parts[0]);
            long long end = stoll(parts[1]);
            intervals.push_back({start, end});
        }
    }

    // Sort intervals by start
    std::sort(intervals.begin(), intervals.end());

    // Merge intervals
    std::vector<std::pair<long long, long long>> merged;
    for (const auto &interval : intervals)
    {
        if (merged.empty() || merged.back().second < interval.first - 1)
        {
            merged.push_back(interval);
        }
        else
        {
            merged.back().second = std::max(merged.back().second, interval.second);
        }
    }

    for (const auto &interval : merged)
    {
        result += (interval.second - interval.first + 1);
    }

    file.close();
    std::cout << "Result:" << result << std::endl;
}