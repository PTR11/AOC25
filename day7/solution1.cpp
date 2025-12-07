#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;
int main()
{
    std::ifstream file("inputSolution.txt");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    std::string line;
    std::unordered_set<int> tachionBeamsX;
    int startXIndex = -1;

    long long result = 0;
    while (std::getline(file, line))
    {
        if (startXIndex == -1)
        {
            startXIndex = line.find_first_not_of('.');
            tachionBeamsX.insert(startXIndex);
        }
        else
        {
            for (int i = 0; i < line.size(); i++)
            {
                auto beam = tachionBeamsX.find(i);
                if (line[i] == '^' && beam != tachionBeamsX.end())
                {
                    result++;
                    tachionBeamsX.erase(i);
                    if (i > 0)
                        tachionBeamsX.insert(i - 1);
                    if (i < line.size() - 1)
                        tachionBeamsX.insert(i + 1);
                }
            }
        }
    }

    file.close();
    std::cout << "Result:" << result << std::endl;
}