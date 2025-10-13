#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <random>

// Ваша реализация Trie (без изменений)
class TTrie;
class TNode {
public:
    friend TTrie;
    TNode() : failLink(nullptr), exitLink(nullptr), leaf(false) {}
private:
    std::unordered_map<std::string, TNode*> chil;
    TNode* failLink;
    TNode* exitLink;
    bool leaf;
    size_t patSize;
    std::vector<size_t> pos;
};

class TTrie {
public:
    TTrie() : root(new TNode()) {}
    ~TTrie() { Destroy(root); }
    
    void AddPat(std::pair<std::vector<std::string>, size_t>& pat) {
        TNode* now = root;
        for (auto iter : pat.first) {
            if (now->chil.find(iter) == now->chil.end()) {
                now->chil.insert(std::make_pair(iter, new TNode()));
            }
            now = now->chil.find(iter)->second;
        }
        now->leaf = true;
        now->pos.push_back(pat.second);
        now->patSize = pat.first.size();
    }
    
    void failInit(size_t max) {
        root->failLink = root;
        for (auto iter : root->chil) {
            iter.second->failLink = root;
        }
        for (size_t i = 1; i < max; ++i) {
            for (auto iter : root->chil) {
                SetLinks(iter.second, i);
            }
        }
    }
    
    std::vector<std::pair<size_t, size_t>> search(std::vector<std::pair<std::string, std::pair<size_t, size_t>>>& text, size_t patCount, size_t patLen) {
        size_t textSize = text.size();
        std::vector<size_t> patInd(textSize, 0);
        TNode* now = root;
        TNode* link;
        std::vector<std::pair<size_t, size_t>> result;

        for (size_t i = 0; i < textSize; ++i) {
            auto findChild = now->chil.find(text[i].first);
            if (findChild != now->chil.end())
                now = findChild->second;
            else {
                now = now->failLink;
                findChild = now->chil.find(text[i].first);
                while (now != root && findChild == now->chil.end()) {
                    now = now->failLink;
                    findChild = now->chil.find(text[i].first);
                }
                if (findChild != now->chil.end()) {
                    now = findChild->second;
                }
            }
            if (now->leaf) {
                for (int p : now->pos) {
                    if ((int)i - (int)now->patSize - p + 2 >= 0) {
                        ++patInd[i - now->patSize - p + 2];
                    }
                }
            }
            if (now->exitLink) {
                link = now->exitLink;
                while (link) {
                    for (int p : link->pos) {
                        if ((int)i - (int)link->patSize - p + 2 >= 0) {
                            ++patInd[i - link->patSize - p + 2];
                        }
                    }
                    link = link->exitLink;
                }
            }
        }
        for (size_t i = 0; i < textSize - patLen + 1; ++i) {
            if (patInd[i] == patCount) {
                result.push_back(std::make_pair(text[i].second.first, text[i].second.second));
            }
        }
        return result;
    }

private:
    void Destroy(TNode* n) {
        for (auto iter : n->chil) {
            Destroy(iter.second);
        }
        delete n;
    }
    
    void SetLinks(TNode* n, size_t lvl) {
        if (lvl != 1) {
            for (auto iter : n->chil) {
                SetLinks(iter.second, lvl - 1);
            }
        }
        else {
            for (auto iter : n->chil) {
                Linking(n, iter.second, iter.first);
            }
        }
    }
    
    void Linking(TNode* parent, TNode* nd, std::string nodeSym) {
        TNode* link = parent->failLink;
        auto findChild = link->chil.find(nodeSym);
        while (link != root && findChild == link->chil.end()) {
            link = link->failLink;
            findChild = link->chil.find(nodeSym);
        }
        if (findChild == link->chil.end())
            nd->failLink = root;
        else {
            nd->failLink = findChild->second;
            link = nd->failLink;
            if (link->leaf)
                nd->exitLink = link;
            else if (link->exitLink)
                nd->exitLink = link->exitLink;
        }
    }
    TNode* root;
};

std::vector<std::pair<std::vector<std::string>, size_t>> split(std::stringstream& pattern, std::string joker, size_t& wordCount) {
    std::string word;
    std::vector<std::pair<std::vector<std::string>, size_t>> result;
    std::vector<std::string> pat;
    while (pattern >> word) {
        ++wordCount;
        if (word == joker) {
            if (!pat.empty()) {
                result.push_back(std::make_pair(pat, wordCount - pat.size()));
                pat.clear();
            }
        }
        else {
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });
            pat.push_back(word);
        }
    }
    if (word != joker) {
        result.push_back(std::make_pair(pat, wordCount - pat.size() + 1));
    }
    return result;
}

// Функция для генерации случайного текста
std::vector<std::string> generate_random_text(size_t word_count, size_t max_word_len) {
    std::vector<std::string> text;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> len_dist(1, max_word_len);
    std::uniform_int_distribution<> char_dist('a', 'z');
    
    for (size_t i = 0; i < word_count; ++i) {
        size_t len = len_dist(gen);
        std::string word;
        for (size_t j = 0; j < len; ++j) {
            word += static_cast<char>(char_dist(gen));
        }
        text.push_back(word);
    }
    
    return text;
}

// Функция для измерения времени поиска с помощью Trie
void benchmark_trie(const std::vector<std::string>& text, const std::vector<std::string>& pattern, size_t iterations) {
    TTrie tree;
    size_t patLen = pattern.size();
    size_t wordCount = 0;
    
    // Подготовка данных для Trie
    std::vector<std::pair<std::vector<std::string>, size_t>> pos;
    pos.emplace_back(pattern, 0);
    size_t max = pattern.size();
    
    for (auto& iter : pos) {
        tree.AddPat(iter);
    }
    tree.failInit(max);
    
    // Подготовка текста для Trie
    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> trie_text;
    for (size_t i = 0; i < text.size(); ++i) {
        trie_text.emplace_back(text[i], std::make_pair(1, i+1));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        auto result = tree.search(trie_text, 1, patLen);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    std::cout << "Trie search: " << duration << " ms" << std::endl;
}

// Функция для измерения времени поиска с помощью std::search
void benchmark_std_search(const std::vector<std::string>& text, const std::vector<std::string>& pattern, size_t iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        auto it = std::search(text.begin(), text.end(), pattern.begin(), pattern.end());
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    std::cout << "std::search: " << duration << " ms "<< std::endl;
}

int main(int argc, char* argv[]) {

    
    // Генерация тестовых данных
    size_t text_size = 100000;  // Размер текста (количество слов)
    const size_t pattern_size = 10;   // Размер шаблона
    const size_t max_word_len = 10;   // Максимальная длина слова
    const size_t iterations = 1;    // Количество итераций для бенчмарка

    if(argc > 1){
        text_size = atoi(argv[1]);
    } 

    auto text = generate_random_text(text_size, max_word_len);
    auto pattern = generate_random_text(pattern_size, max_word_len);
    
    std::cout << "Text size: " << text_size << " words" << std::endl;
    
    // Запуск бенчмарков
    benchmark_trie(text, pattern, iterations);
    benchmark_std_search(text, pattern, iterations);
    
    return 0;
}