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

long long distanceBetweenPoints(const std::tuple<int, int, int> &a, const std::tuple<int, int, int> &b)
{
    long long dx = std::pow(std::get<0>(a) - std::get<0>(b), 2);
    long long dy = std::pow(std::get<1>(a) - std::get<1>(b), 2);
    long long dz = std::pow(std::get<2>(a) - std::get<2>(b), 2);
    return std::sqrt(dx + dy + dz);
}
void mergeCircuits(std::vector<std::vector<std::tuple<int, int, int>>> &circuits)
{
    bool merged = true;
    while (merged)
    {
        merged = false;
        for (size_t i = 0; i < circuits.size(); ++i)
        {
            for (size_t j = i + 1; j < circuits.size(); ++j)
            {
                bool share = false;
                for (const auto &p1 : circuits[i])
                {
                    if (std::find(circuits[j].begin(), circuits[j].end(), p1) != circuits[j].end())
                    {
                        share = true;
                        break;
                    }
                }
                if (share)
                {

                    circuits[i].insert(circuits[i].end(), circuits[j].begin(), circuits[j].end());

                    std::sort(circuits[i].begin(), circuits[i].end());
                    circuits[i].erase(std::unique(circuits[i].begin(), circuits[i].end()), circuits[i].end());

                    circuits.erase(circuits.begin() + j);
                    merged = true;
                    break;
                }
            }
            if (merged)
                break;
        }
    }
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
    std::vector<std::tuple<int, int, int>> junctionsBoxes;

    long long result = 1;
    while (std::getline(file, line))
    {
        auto parts = split(line, ',');
        if (parts.size() == 3)
        {
            int x = std::stoi(parts[0]);
            int y = std::stoi(parts[1]);
            int z = std::stoi(parts[2]);
            junctionsBoxes.push_back(std::make_tuple(x, y, z));
        }
    }

    std::vector<std::tuple<int, std::tuple<int, int, int>, std::tuple<int, int, int>>> distancePairs;
    for (int i = 0; i < junctionsBoxes.size(); ++i)
    {
        for (int j = i + 1; j < junctionsBoxes.size(); ++j)
        {
            long long dist = distanceBetweenPoints(junctionsBoxes[i], junctionsBoxes[j]);
            distancePairs.push_back(std::make_tuple(dist, junctionsBoxes[i], junctionsBoxes[j]));
        }
    }

    std::sort(distancePairs.begin(), distancePairs.end());

    std::vector<std::vector<std::tuple<int, int, int>>> circuits;
    for (int i = 0; i < 1000; ++i)
    {
        auto pair = std::make_pair(std::get<1>(distancePairs[i]), std::get<2>(distancePairs[i]));
        // Find connection between already existing circuits
        bool findCircuit = false;
        for (auto &circuit : circuits)
        {
            if (std::find(circuit.begin(), circuit.end(), pair.first) != circuit.end() ||
                std::find(circuit.begin(), circuit.end(), pair.second) != circuit.end())
            {
                if (std::find(circuit.begin(), circuit.end(), pair.first) == circuit.end())
                {
                    circuit.push_back(pair.first);
                }
                if (std::find(circuit.begin(), circuit.end(), pair.second) == circuit.end())
                {
                    circuit.push_back(pair.second);
                }
                findCircuit = true;
            }
            if (findCircuit)
                break;
        }
        if (!findCircuit)
        {
            circuits.push_back({pair.first, pair.second});
        }
    }

    mergeCircuits(circuits);
    std::vector<int> circuitsSize;
    // Get size of the circuits
    for (auto circuit : circuits)
    {
        circuitsSize.push_back(circuit.size());
    }
    std::sort(circuitsSize.begin(), circuitsSize.end(), std::greater<int>());
    for (int i = 0; i < 3; i++)
    {
        result *= circuitsSize[i];
    }
    std::cout << "Result:" << result << std::endl;
}