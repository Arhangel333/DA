#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


using namespace std; 
 
vector<int> BuildArr(const string &str) { 
    int n = str.size(); 
    vector<int> suff_arr(n);

    int max_sim = -1;
    for (int i = 0; i < n; ++i) {
        if (str[i] > max_sim) {
            max_sim = str[i];
        }
    }

    vector<int> count(max(max_sim + 1, n), 0); 
    for (int i = 0; i < n; ++i) {
        ++count[str[i]]; 
    }
    for (int i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1]; 
    }

    for (int i = n - 1; i >= 0; --i) {
        suff_arr[--count[str[i]]] = i; 
    }
    
    vector<int> class_eq(n);
    class_eq[suff_arr[0]] = 0; 
    int class_eq_count = 1; 
    for (int i = 1; i < n; ++i) { 
        if (str[suff_arr[i]] != str[suff_arr[i - 1]]) {
            ++class_eq_count; 
        }
        class_eq[suff_arr[i]] = class_eq_count - 1; 
    }
     
    vector<int> tmp_suff_arr(n), tmp_eq_class(n); 
    for (int len = 1; len < n; len *= 2) { 
        for (int i = 0; i < n; ++i) { 
            tmp_suff_arr[i] = suff_arr[i] - len; 
            if (tmp_suff_arr[i] < 0) {
                tmp_suff_arr[i] += n; 
            }
        }
         
        count.assign(class_eq_count, 0);  //0000000000000

        for (int i = 0; i < n; ++i) {
            ++count[class_eq[tmp_suff_arr[i]]];
        } 
        for (int i = 1; i < class_eq_count; ++i) {
            count[i] += count[i - 1]; 
        }
        for (int i = n - 1; i >= 0; --i) {
            suff_arr[--count[class_eq[tmp_suff_arr[i]]]] = tmp_suff_arr[i]; 
        }
         
        tmp_eq_class[suff_arr[0]] = 0; 
        class_eq_count = 1; 
        for (int i = 1; i < n; ++i) { 
            pair<int, int> now = {class_eq[suff_arr[i]], class_eq[(suff_arr[i] + len) % n]}; 
            pair<int, int> prev = {class_eq[suff_arr[i - 1]], class_eq[(suff_arr[i - 1] + len) % n]}; 
            if (now != prev) {
                ++class_eq_count; 
            }
            tmp_eq_class[suff_arr[i]] = class_eq_count - 1; 
        } 
        class_eq = tmp_eq_class; 
    } 

    vector<int> res(n - 1);
    for (int i = 1; i < n; ++i) {
        res[i - 1] = suff_arr[i];
    }
     
    return res;
} 

vector<int> Search(const string &text, const string &patt, const vector<int> &suffixArray) {
    vector<int> res;

    if (patt == "") {
        return res;
    }

    int n = text.size(), m = patt.size();
    int L = 0, R = n;

    while (L < R) {
        int M = (L + R) / 2;
        if (text.compare(suffixArray[M], m, patt) >= 0) {
            R = M;
        }
        else {
            L = M + 1;
        }
    }
    int first_inner = L;

    R = n;
    while (L < R) {
        int M = (L + R) / 2;
        if (text.compare(suffixArray[M], m, patt) > 0) {
            R = M;
        }
        else {
            L = M + 1;
        }
    }
    int last_inner = L;

    if (first_inner == last_inner) {
        return res;
    }

    res.resize(last_inner - first_inner);
    for (int i = first_inner, j = 0; i < last_inner; ++i) {
        res[j++] = suffixArray[i];
    }
    sort(res.begin(), res.end());
    
    return res;
}
