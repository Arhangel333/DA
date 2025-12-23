#include <iostream>
#include <vector>
#include <limits>
#include <iostream>

const long long inf = std::numeric_limits<long long>::max();

struct edge{
    edge(int a, int b, long long k): first(a), second(b), weight(k){};
    int first, second;
    long long weight;
};

void Printmatr(std::vector<std::vector<long long>>& res, int n);
std::vector<std::vector<long long>> findPath(std::vector<edge>& e, int n, int m);

std::vector<long long> BF(std::vector<edge>& e, int n);
void SetWeight(std::vector<edge>& e, std::vector<long long>& res, int m);
std::vector<long long> Dijkstr(std::vector<edge>& plusEdges, int n, int m, std::vector<edge>& e, int s);



std::vector<long long> BF(std::vector<edge>& e, int n){
    std::vector<long long> res(n+1, inf);
    res[0] = 0;
    long long a, b, w;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < e.size(); j++){
            a = e[j].first;
            b = e[j].second;
            w = e[j].weight;
            if(res[a] != inf && res[a] + w < res[b]){
                res[b] = res[a] + w;
            }
        }
    }

    for(int i = 0; i < e.size(); i++){
        a = e[i].first;
        b = e[i].second;
        w = e[i].weight;
        if(res[a] != inf && res[a] + w < res[b]){
            res.clear();
            break;
        }
    }
    return res;
}

void SetWeight(std::vector<edge>& e, std::vector<long long>& res, int m){
    e.erase(e.begin()+m, e.end());

    long long a, b;
    for(int i = 0; i < e.size(); i++){
        a = e[i].first;
        b = e[i].second;
        e[i].weight += res[a] - res[b];
    }
}


std::vector<long long> Dijkstr(std::vector<edge>& plusEdges, int n, int m, std::vector<edge>& e, int s){
    std::vector<std::pair<long long, bool>> cur(n, std::make_pair(inf, false));
    std::vector<long long> res(n, inf);
    cur[s].first = 0;
    res[s] = 0;

    long long w, wres;
    int a, b;
    long long weight;
    int idx;

    for(int i = 0; i < n; i++){
        idx = -1;
        w = inf;
        for(int j = 0; j < n; j++){
            if(!cur[j].second && cur[j].first < w){
                w = cur[j].first;
                wres = res[j];
                idx = j+1;
            }
        }

        if(idx == -1){
            break;
        }
        
        cur[idx-1].second = true;
        for(int k = 0; k < m; k++){
            a = plusEdges[k].first;
            if(a != idx){
                continue;
            }
            b = plusEdges[k].second;
            weight = plusEdges[k].weight;
            if(w + weight < cur[b-1].first){
                cur[b-1].first = w + weight;
                res[b-1] = wres + e[k].weight;
            }
        }
    }

    return res;
}

void Printmatr(std::vector<std::vector<long long>>& res, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(res[i][j] == inf){
                std::cout << "inf"; 
            }
            else{
                std::cout << res[i][j];
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<long long>> findPath(std::vector<edge>& e, int n, int m)
{
    std::vector<long long> resBF;
    std::vector<edge> plusEdges = e;

    for(int i = 1; i < n+1; i++){
        plusEdges.push_back(edge(0, i, 0));
    }

    resBF = BF(plusEdges, n);
    std::vector<std::vector<long long>> res;

    if(resBF.empty()){
        std::cout << "Negative cycle\n";
        return res;
    }

    SetWeight(plusEdges, resBF, m);

    for(int i = 0; i < n; i++){
        res.push_back(Dijkstr(plusEdges, n, m, e, i));
    }
    return res;
}

int main(){
    std::vector<edge> e;
    int n, m;
    int a, b;
    long long w;
    char x = 0, x1 = 0;
    
    std::cin >> n >> m;
    for(int i = 0; i < m; i++){
        std::cin >> a >> b >> w;
        e.push_back(edge(a, b, w));
    }
    std::vector<std::vector<long long>> res;
    res = findPath(e, n, m);
    if(!res.empty()){
        Printmatr(res, n);
    }
}  