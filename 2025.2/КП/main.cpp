#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


vector<int> lcs_length(const vector<string>& a, const vector<string>& b) {
    int m = a.size();
    int n = b.size();
    
    
    vector<vector<int>> dp(2, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        int current = i % 2;      
        int previous = 1 - current; 
        
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                
                dp[current][j] = dp[previous][j - 1] + 1;
            } else {
                
                dp[current][j] = max(dp[previous][j], dp[current][j - 1]);
            }
        }
    }
    
    
    return dp[m % 2];
}


void hirschberg(const vector<string>& a, const vector<string>& b,
                int a_start, int a_end, int b_start, int b_end,
                vector<string>& result) {
    
    int m = a_end - a_start;  
    int n = b_end - b_start;  
    
    if (m == 0 || n == 0) {
        return;
    }
    
    
    if (m == 1) {
        for (int j = b_start; j < b_end; j++) {
            if (a[a_start] == b[j]) {
                result.push_back(a[a_start]);
                return;
            }
        }
        return;
    }

    if (n == 1) {
        for (int j = a_start; j < a_end; j++) {
            if (b[b_start] == a[j]) {
                result.push_back(b[b_start]);
                return;
            }
        }
        return;
    }
    
    
    int mid_a = a_start + m / 2;
    
    
    vector<string> left_a(a.begin() + a_start, a.begin() + mid_a);
    vector<string> segment_b(b.begin() + b_start, b.begin() + b_end);

    vector<int> l1 = lcs_length(left_a, segment_b);
    
    vector<string> right_a(a.begin() + mid_a, a.begin() + a_end);
    vector<string> reversed_b(b.begin() + b_start, b.begin() + b_end);
    
    reverse(right_a.begin(), right_a.end());
    reverse(reversed_b.begin(), reversed_b.end());
    
    vector<int> l2 = lcs_length(right_a, reversed_b);
    reverse(l2.begin(), l2.end());  
    
    int max_val = -1;
    int split_b = b_start;
    
    for (int j = 0; j <= n; j++) {
        

        int left_part = l1[j];    // LCS(левая_A, B[b_start..b_start+k])
        int right_part = l2[j];   // LCS(правая_A, B[b_start+k..b_end])
        int total = left_part + right_part;

        if (total > max_val) {
            max_val = total;
            split_b = b_start + j;
        }
    }   
    
    
    hirschberg(a, b, a_start, mid_a, b_start, split_b, result);
    hirschberg(a, b, mid_a, a_end, split_b, b_end, result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    
    string line1, line2;
    getline(cin, line1);
    getline(cin, line2);
    
    
    vector<string> words1, words2;
    
    stringstream ss1(line1);
    string word;
    while (ss1 >> word) {
        words2.push_back(word);
    }
    
    stringstream ss2(line2);
    while (ss2 >> word) {
        words1.push_back(word);
    }
    
    
    vector<string> lcs;
    hirschberg(words1, words2, 0, words1.size(), 0, words2.size(), lcs);
    
    
    cout << lcs.size() << "\n";
    for (size_t i = 0; i < lcs.size(); i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << lcs[i];
    }
    cout << "\n";
    
    return 0;
}