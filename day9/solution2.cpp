#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
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

long long calculateArea(std::pair<long long, long long> p1, std::pair<long long, long long> p2)
{
    long long width = std::abs(p1.first - p2.first) + 1;
    long long height = std::abs(p1.second - p2.second) + 1;

    return width * height;
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
    std::vector<std::pair<long long, long long>> coordinates;

    long long result = 1;
    while (std::getline(file, line))
    {
        auto parts = split(line, ',');
        coordinates.push_back(make_pair(stoll(parts[0]), stoll(parts[1])));
    }

    std::vector<long long> areas;
    for (int i = 0; i < coordinates.size(); i++)
    {
        for (int j = i + 1; j < coordinates.size(); j++)
        {
            long long minX = std::min(coordinates[i].first, coordinates[j].first);
            long long maxX = std::max(coordinates[i].first, coordinates[j].first);
            long long minY = std::min(coordinates[i].second, coordinates[j].second);
            long long maxY = std::max(coordinates[i].second, coordinates[j].second);

            bool isValid = true;

            for (int k = 0; k < coordinates.size(); k++)
            {
                long long currentX = coordinates[k].first;
                long long currentY = coordinates[k].second;

                long long nextX = coordinates[(k + 1) % coordinates.size()].first;
                long long nextY = coordinates[(k + 1) % coordinates.size()].second;
                if (!(
                        minX >= max(currentX, nextX) ||
                        maxX <= min(currentX, nextX) ||
                        minY >= max(currentY, nextY) ||
                        maxY <= min(currentY, nextY)))
                {
                    isValid = false;
                    break;
                }
            }
            if (isValid)
            {
                long long area = calculateArea(coordinates[i], coordinates[j]);
                areas.push_back(area);
            }
        }
    }
    std::sort(areas.begin(), areas.end());

    std::cout << "Result:" << areas[areas.size() - 1] << std::endl;
}