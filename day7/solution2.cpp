#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct PairHasher
{
    size_t operator()(const std::pair<int, int> &p) const
    {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

long long tachionCounter(std::vector<string> &input, int i, int j, std::unordered_map<std::pair<int, int>, long long, PairHasher> &memory)
{
    if (i == input.size() - 1)
        return 1;

    auto key = std::make_pair(i, j);
    if (memory.count(key))
        return memory[key];

    if (input[i][j] == '.' || input[i][j] == 'S')
    {
        memory[key] = tachionCounter(input, i + 1, j, memory);
        return memory[key];
    }

    if (input[i][j] == '^')
    {
        long long result = 0;
        if (j > 0)
            result += tachionCounter(input, i + 1, j - 1, memory);
        if (j < input[i].size() - 1)
            result += tachionCounter(input, i + 1, j + 1, memory);
        memory[key] = result;
        return result;
    }
    return 0;
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
    int startXIndex = -1;

    while (std::getline(file, line))
    {
        input.push_back(line);
        if (startXIndex == -1)
        {
            startXIndex = line.find_first_not_of('.');
        }
    }

    long long result = 0;

    std::unordered_map<std::pair<int, int>, long long, PairHasher> memory;
    result = tachionCounter(input, 0, startXIndex, memory);

    file.close();
    std::cout << "Result:" << result << std::endl;
}