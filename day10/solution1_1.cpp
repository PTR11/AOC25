#include <bits/stdc++.h>
using namespace std;

// Gauss-elimination mod 2, returns basis solution + free variable mask.
struct LinearSystem
{
    int m, n;              // m variables (buttons), n equations (lights)
    vector<vector<int>> A; // n x m
    vector<int> b;         // n
    vector<int> where;     // which row each variable is leading in (-1 none)

    LinearSystem(int n_, int m_) : n(n_), m(m_), A(n_, vector<int>(m_, 0)), b(n_, 0), where(m_, -1) {}

    // Solve system Ax = b (mod 2). Returns all free variables' indices.
    vector<int> solve()
    {
        int row = 0;
        for (int col = 0; col < m && row < n; col++)
        {
            // Find pivot
            int sel = row;
            while (sel < n && A[sel][col] == 0)
                sel++;
            if (sel == n)
                continue;
            swap(A[sel], A[row]);
            swap(b[sel], b[row]);
            where[col] = row;

            // Eliminate
            for (int r = 0; r < n; r++)
            {
                if (r != row && A[r][col])
                {
                    for (int c = col; c < m; c++)
                        A[r][c] ^= A[row][c];
                    b[r] ^= b[row];
                }
            }
            row++;
        }
        // Check consistency
        for (int r = 0; r < n; r++)
        {
            bool allZero = true;
            for (int c = 0; c < m; c++)
                if (A[r][c])
                {
                    allZero = false;
                    break;
                }
            if (allZero && b[r])
            {
                // No solution, but puzzle text guarantees solution exists
            }
        }

        vector<int> freeVars;
        for (int i = 0; i < m; i++)
            if (where[i] == -1)
                freeVars.push_back(i);
        return freeVars;
    }

    // Given free variable assignment fvMask -> returns full x vector
    vector<int> getSolution(uint64_t fvMask, const vector<int> &freeVars)
    {
        vector<int> x(m, 0);

        // set free vars
        for (int i = 0; i < (int)freeVars.size(); i++)
        {
            if (fvMask & (1ULL << i))
                x[freeVars[i]] = 1;
        }

        // back substitute
        for (int v = 0; v < m; v++)
        {
            int r = where[v];
            if (r == -1)
                continue;
            int sum = b[r];
            for (int c = v + 1; c < m; c++)
                if (A[r][c] && x[c])
                    sum ^= 1;
            x[v] = sum;
        }
        return x;
    }
};

int main()
{
    const string FILENAME = "inputSolution.txt"; // <-- ITT ADD MEG A FÁJL NEVÉT

    ifstream fin(FILENAME);
    if (!fin)
    {
        cerr << "Nem sikerült megnyitni a fájlt: " << FILENAME << "\n";
        return 1;
    }

    string line;
    long long total = 0;

    while (true)
    {
        if (!getline(fin, line))
            break;
        if (line.find('[') == string::npos)
            continue;

        // ---- PARSE DIAGRAM ----
        int L = line.find('[');
        int R = line.find(']');
        string diag = line.substr(L + 1, R - L - 1);

        int N = diag.size(); // # of lights
        vector<int> target(N, 0);
        for (int i = 0; i < N; i++)
            target[i] = (diag[i] == '#');

        // ---- PARSE BUTTONS ----
        vector<vector<int>> buttons;
        int pos = R + 1;

        while (true)
        {
            int p1 = line.find('(', pos);
            if (p1 == string::npos)
                break;
            int p2 = line.find(')', p1);
            string inside = line.substr(p1 + 1, p2 - p1 - 1);
            if (inside.size() > 0)
            {
                vector<int> idx;
                string tmp;
                for (char c : inside)
                {
                    if (isdigit(c))
                        tmp += c;
                    else if (!tmp.empty())
                    {
                        idx.push_back(stoi(tmp));
                        tmp.clear();
                    }
                }
                if (!tmp.empty())
                    idx.push_back(stoi(tmp));
                buttons.push_back(idx);
            }
            pos = p2 + 1;
        }

        int M = buttons.size();

        LinearSystem ls(N, M);

        // Fill matrix A and b
        for (int r = 0; r < N; r++)
            ls.b[r] = target[r];

        for (int j = 0; j < M; j++)
        {
            for (int idx : buttons[j])
            {
                ls.A[idx][j] ^= 1;
            }
        }

        // Solve
        vector<int> freeVars = ls.solve();
        int F = freeVars.size();

        long long best = (1LL << 60);

        uint64_t limit = (F <= 20 ? (1ULL << F) : 0);

        if (F > 20)
        {
            cerr << "Too many free vars, unexpected in AoC input.\n";
            return 1;
        }

        for (uint64_t mask = 0; mask < limit; mask++)
        {
            vector<int> sol = ls.getSolution(mask, freeVars);
            int cost = 0;
            for (int x : sol)
                cost += x;
            best = min(best, (long long)cost);
        }

        total += best;
    }

    cout << total << "\n";
    return 0;
}
