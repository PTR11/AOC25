#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
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

struct Machine
{
    std::string currentState;
    int goal;
    std::vector<int> buttons;
    std::vector<int> joltageRequirements;

    Machine(int result, std::vector<int> schematics, std::vector<int> joltages)
    {
        goal = result;
        buttons = schematics;
        joltageRequirements = joltages;
    }

    void switchLight(int index)
    {
        if (currentState[index] == '#')
        {
            currentState[index] = '.';
        }
        else
        {
            currentState[index] = '#';
        }
    }

    void toggleLights(std::vector<int> buttons)
    {
        for (int button : buttons)
        {
            switchLight(button);
        }
    }
};

int solve_bfs(int goal, const vector<int> &buttons)
{
    queue<pair<int, int>> q;
    unordered_set<int> vis;

    q.push({0, 0});
    vis.insert(0);

    while (!q.empty())
    {
        auto [curr, steps] = q.front();
        q.pop();

        if (curr == goal)
        {
            return steps;
        }

        for (int b : buttons)
        {
            int nxt = curr ^ b;
            if (vis.find(nxt) == vis.end())
            {
                vis.insert(nxt);
                q.push({nxt, steps + 1});
            }
        }
    }

    return 0; // ha nincs megoldás
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
    std::vector<Machine> machines;

    long long result = 0;
    while (std::getline(file, line))
    {
        auto parts = split(line, ' ');
        std::string lightIndicators = parts[0].substr(1, parts[0].size() - 2);
        int goal = 0;
        for (int i = 0; i < lightIndicators.size(); i++)
        {
            if (lightIndicators[i] == '#')
            {
                goal |= 1 << i;
            }
        }

        auto joltages = split(parts[parts.size() - 1].substr(1, parts[parts.size() - 1].size() - 2), ',');
        std::vector<int> joltagesInt;
        std::transform(joltages.begin(), joltages.end(), std::back_inserter(joltagesInt), [](const std::string &joltage)
                       { return std::stoi(joltage); });

        std::vector<int> buttons;
        for (int i = 1; i < parts.size() - 1; i++)
        {
            int b = 0;
            auto schemaParts = split(parts[i].substr(1, parts[i].size() - 1), ',');
            for (std::string part : schemaParts)
            {
                int converted = stoi(part);
                b |= 1 << converted;
            }
            buttons.push_back(b);
        }
        machines.push_back(Machine(goal, buttons, joltagesInt));
    }

    for (Machine machine : machines)
    {
        result += solve_bfs(machine.goal, machine.buttons);
    }

    std::cout << "Result:" << result << std::endl;
}