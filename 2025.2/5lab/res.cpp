<<<<<<< HEAD
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

class SuffixArray {
private:
    string text;
    vector<int> suffixArray;

    void buildSuffixArray() {
        /* for (int i = 0; i < text.size(); ++i)
        {
            
        } */
        int n = text.size();
        suffixArray.resize(n);
        vector<int> rank(n), tempRank(n);
        
        for (int i = 0; i < n; i++) {
            suffixArray[i] = i;
            rank[i] = text[i];
        }
        
        for (int k = 1; k < n; k *= 2) {
            auto cmp = [&](int i, int j) {
                if (rank[i] != rank[j])
                    return rank[i] < rank[j];
                int ri = (i + k < n) ? rank[i + k] : -1;
                int rj = (j + k < n) ? rank[j + k] : -1;
                return ri < rj;
            };
            
            sort(suffixArray.begin(), suffixArray.end(), cmp);
            
            tempRank[suffixArray[0]] = 0;
            for (int i = 1; i < n; i++) {
                tempRank[suffixArray[i]] = tempRank[suffixArray[i - 1]] + 
                    (cmp(suffixArray[i - 1], suffixArray[i]) ? 1 : 0);
            }
            rank = tempRank;
        }
    }

public:



    SuffixArray(const string& str) : text(str) {
        buildSuffixArray();
        /* std::cout<<text<<std::endl<<text.size()<<" - "<<suffixArray.size()<<std::endl;
        for (int i = 0; i < suffixArray.size(); i++)
        {
            std::cout<<suffixArray[i]<<std::endl;
        } */
    }

    vector<int> search(const string& pattern) {
        vector<int> positions;
        
        int n = text.size();
        printf("Search: %d\n", n);
        int m = pattern.size();
        
        

        if (m == 0) return positions;
        
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            string suffix = text.substr(suffixArray[mid]);
            if (suffix.compare(0, m, pattern) >= 0) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        int start = left;
        
        left = start;
        right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            string suffix = text.substr(suffixArray[mid]);
            if (suffix.compare(0, m, pattern) <= 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        int end = right;
        
        if (start <= end) {
            for (int i = start; i <= end; i++) {
                positions.push_back(suffixArray[i] + 1);
            }
            sort(positions.begin(), positions.end());
        }
        
        return positions;
    }
};

string readLine1() {
    string line;
    char c;
    
    while (fgets(c, sizeof(c), stdin) && c != '\n') {
        line += c;
    }
    cout<<endl;
    return line;
}

string readLine() {
    string line;
    char* c;
    if(fgets(c, sizeof(c), stdin)){
        line(c*);
        return line;
    }else{
        return nullptr;
    } 
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string text, str;
    text = readLine();
    
    
    
    SuffixArray sa(text);
    
    string pattern;
    int patternNum = 1;
    
    while (1) {
        pattern = readLine();
        if (pattern.empty()){
            if(cin.eof()){
                break;
            }
            continue;
        }
        
        vector<int> positions = sa.search(pattern);
        
        cout << patternNum << ": ";
        for (size_t i = 0; i < positions.size(); i++) {
            if (i > 0) cout << ", ";
            cout << positions[i];
        }
        cout << "\n";
        
        patternNum++;
    }
    
    return 0;
=======
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

class SuffixArray {
private:
    string text;
    vector<int> suffixArray;

    void buildSuffixArray() {
        /* for (int i = 0; i < text.size(); ++i)
        {
            
        } */
        int n = text.size();
        suffixArray.resize(n);
        vector<int> rank(n), tempRank(n);
        
        for (int i = 0; i < n; i++) {
            suffixArray[i] = i;
            rank[i] = text[i];
        }
        
        for (int k = 1; k < n; k *= 2) {
            auto cmp = [&](int i, int j) {
                if (rank[i] != rank[j])
                    return rank[i] < rank[j];
                int ri = (i + k < n) ? rank[i + k] : -1;
                int rj = (j + k < n) ? rank[j + k] : -1;
                return ri < rj;
            };
            
            sort(suffixArray.begin(), suffixArray.end(), cmp);
            
            tempRank[suffixArray[0]] = 0;
            for (int i = 1; i < n; i++) {
                tempRank[suffixArray[i]] = tempRank[suffixArray[i - 1]] + 
                    (cmp(suffixArray[i - 1], suffixArray[i]) ? 1 : 0);
            }
            rank = tempRank;
        }
    }

public:



    SuffixArray(const string& str) : text(str) {
        buildSuffixArray();
        /* std::cout<<text<<std::endl<<text.size()<<" - "<<suffixArray.size()<<std::endl;
        for (int i = 0; i < suffixArray.size(); i++)
        {
            std::cout<<suffixArray[i]<<std::endl;
        } */
    }

    vector<int> search(const string& pattern) {
        vector<int> positions;
        
        int n = text.size();
        printf("Search: %d\n", n);
        int m = pattern.size();
        
        

        if (m == 0) return positions;
        
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            string suffix = text.substr(suffixArray[mid]);
            if (suffix.compare(0, m, pattern) >= 0) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        int start = left;
        
        left = start;
        right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            string suffix = text.substr(suffixArray[mid]);
            if (suffix.compare(0, m, pattern) <= 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        int end = right;
        
        if (start <= end) {
            for (int i = start; i <= end; i++) {
                positions.push_back(suffixArray[i] + 1);
            }
            sort(positions.begin(), positions.end());
        }
        
        return positions;
    }
};

string readLine1() {
    string line;
    char c;
    
    while (fgets(c, sizeof(c), stdin) && c != '\n') {
        line += c;
    }
    cout<<endl;
    return line;
}

string readLine() {
    string line;
    char* c;
    if(fgets(c, sizeof(c), stdin)){
        line(c*);
        return line;
    }else{
        return nullptr;
    } 
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string text, str;
    text = readLine();
    
    
    
    SuffixArray sa(text);
    
    string pattern;
    int patternNum = 1;
    
    while (1) {
        pattern = readLine();
        if (pattern.empty()){
            if(cin.eof()){
                break;
            }
            continue;
        }
        
        vector<int> positions = sa.search(pattern);
        
        cout << patternNum << ": ";
        for (size_t i = 0; i < positions.size(); i++) {
            if (i > 0) cout << ", ";
            cout << positions[i];
        }
        cout << "\n";
        
        patternNum++;
    }
    
    return 0;
>>>>>>> 017b9db (8 9 fiished)
}