#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Graph {
public:
    std::unordered_map<std::string, std::vector<std::string>> adj;

    void addEdge(const std::string &from, const std::string &to) {
        adj[from].push_back(to);
    }

    long long countPathsWithFFTandDAC(const std::string &start, const std::string &end) {
        std::unordered_map<std::string, std::unordered_map<int, long long>> memo;
        return dfs(start, end, false, false, memo);
    }

private:
    // bitmask: 1 = fft meglét, 2 = dac meglét
    long long dfs(const std::string &start, const std::string &end, bool hasFFT, bool hasDAC,
                  std::unordered_map<std::string, std::unordered_map<int, long long>> &memo) {
        int state = (hasFFT ? 1 : 0) | (hasDAC ? 2 : 0);
        if (memo[start].count(state)) return memo[start][state];

        if (start == end) {
            return (hasFFT && hasDAC) ? 1 : 0;
        }

        if (start == "fft") hasFFT = true;
        if (start == "dac") hasDAC = true;

        long long total = 0;
        for (const auto &neighbor : adj[start]) {
            total += dfs(neighbor, end, hasFFT, hasDAC, memo);
        }

        return memo[start][state] = total;
    }
};

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) tokens.push_back(token);
    return tokens;
}

int main() {
    std::ifstream file("inputSolution.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    Graph g;
    std::string line;
    while (std::getline(file, line)) {
        auto parts = split(line, ':');
        auto neighbors = split(parts[1].substr(1), ' ');
        for (const auto &neighbor : neighbors) {
            g.addEdge(parts[0], neighbor);
        }
    }

    long long result = g.countPathsWithFFTandDAC("svr", "out");
    std::cout << "Result: " << result << std::endl;
    return 0;
}
