#include "libs.hpp"

long long polifind(string s)
{
    size_t n = s.size();

    vector<vector<long long>> poli_count(n);
    for (size_t i = 0; i < n; i++)
    {
        vector<long long> row(n, 0);
        poli_count[i] = row;
        poli_count[i][i] = 1;
    }

    for (size_t l = 1; l <= n; l++)
    {
        int i = 0, j;
        while (i + l < n)
        {
            j = i + l;
            if (s[i] == s[j])
            {
                poli_count[i][j] = poli_count[i + 1][j] + poli_count[i][j - 1] + 1;
            }
            else
            {
                poli_count[i][j] = poli_count[i + 1][j] + poli_count[i][j - 1] - poli_count[i + 1][j - 1];
            }
            i++;
        }
    }

    return poli_count[0][n - 1];
}
