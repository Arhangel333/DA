#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    string s;
    cin >> s;
    size_t n = s.size();
    
    vector<vector<int64_t> > poli_count(n);
    for (size_t i = 0; i < n; i++) {
        vector<int64_t> row(n, 0);
        poli_count[i] = row;
<<<<<<< HEAD
        poli_count[i][i] = 1;
    }

    for (size_t l = 1; l <= n; l++) {
        int i = 0, j;
        while(i + l < n) {  
            j = i + l;      
            if(s[i] == s[j]) {            
                poli_count[i][j] = poli_count[i + 1][j] + poli_count[i][j - 1] + 1;
            }
            else {                        
                poli_count[i][j] = poli_count[i + 1][j] + poli_count[i][j - 1] - poli_count[i + 1][j - 1];
            }
            i++;
            
=======
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (i == j) {
                poli_count[i][j] = 1;
            }
        }
    }

    for (size_t l = 1; l <= n; l++) {
        int i = 0;
        while(i + l < n) {        
            if(s[i] == s[i + l]) {            
                poli_count[i][i + l] = poli_count[i + 1][i + l] + poli_count[i][i + l - 1] + 1;
            }
            else {                        
                poli_count[i][i + l] = poli_count[i + 1][i + l] + poli_count[i][i + l - 1] - poli_count[i + 1][i + l - 1];
            }
            i++;
>>>>>>> 8d890ca5ca283e30814d936e28ecd649c5e3d7c2
        }
    }
    
    cout << poli_count[0][n - 1] << endl;

    return 0;
}
