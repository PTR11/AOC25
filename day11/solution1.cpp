#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cctype>

class Graph
{
public:
    // adj lista: string csúcs -> szomszédok listája
    std::unordered_map<std::string, std::vector<std::string>> adj;

    // él hozzáadása
    void addEdge(const std::string &from, const std::string &to)
    {
        adj[from].push_back(to);
    }

    // DFS alapú útvonal-számlálás
    int countPaths(const std::string &start,
                   std::string endNode)
    {
        std::unordered_set<std::string> visited;
        return dfs(start, endNode, visited);
    }

private:
    int dfs(const std::string &current,
            std::string endNodes,
            std::unordered_set<std::string> &visited)
    {
        if (endNodes == current)
            return 1;

        visited.insert(current);
        int pathCount = 0;

        for (const auto &neighbor : adj[current])
        {
            if (!visited.count(neighbor))
            {
                pathCount += dfs(neighbor, endNodes, visited);
            }
        }
        visited.erase(current);
        return pathCount;
    }
};

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
    Graph g;

    long long result = 0;
    while (std::getline(file, line))
    {
        auto parts = split(line, ':');
        auto neighbors = split(parts[1].substr(1, parts[1].size() - 1), ' ');
        for (std::string neighbor : neighbors)
        {
            g.addEdge(parts[0], neighbor);
        }
    }

    int ways = g.countPaths("you", "out");
    std::cout << "Result:" << ways << std::endl;

    return 0;
}
