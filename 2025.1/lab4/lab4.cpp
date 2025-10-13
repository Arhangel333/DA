#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>

class TTrie;

class TNode
{
public:
    friend TTrie;
    TNode() : failLink(nullptr), exitLink(nullptr), leaf(false) {}

private:
    std::unordered_map<std::string, TNode *> chil; // children
    TNode *failLink;
    TNode *exitLink;
    bool leaf;
    size_t patSize;
    std::vector<size_t> pos;
};

class TTrie
{
public:
    TTrie() : root(new TNode()) {}

    ~TTrie()
    {
        Destroy(root);
    }

    void AddPat(std::pair<std::vector<std::string>, size_t> &pat)
    {
        TNode *now = root;
        for (auto iter : pat.first)
        {
            if (now->chil.find(iter) == now->chil.end())
            {
                now->chil.insert(std::make_pair(iter, new TNode()));
            }
            now = now->chil.find(iter)->second;
        }
        now->leaf = true;
        now->pos.push_back(pat.second);
        now->patSize = pat.first.size();
    }

    void failInit(size_t max)
    {
        root->failLink = root;
        for (auto iter : root->chil)
        {
            iter.second->failLink = root;
        }
        for (size_t i = 1; i < max; ++i)
        {
            for (auto iter : root->chil)
            {
                SetLinks(iter.second, i);
            }
        }
    }

    std::vector<std::pair<size_t, size_t>> search(std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &text, size_t patCount, size_t patLen)
    {
        size_t textSize = text.size();
        std::vector<size_t> patInd(textSize, 0);
        TNode *now = root;
        TNode *link;
        std::vector<std::pair<size_t, size_t>> result;

        for (size_t i = 0; i < textSize; ++i)
        {
            auto findChild = now->chil.find(text[i].first);
            if (findChild != now->chil.end())
                now = findChild->second;
            else
            {
                now = now->failLink;
                findChild = now->chil.find(text[i].first);
                while (now != root && findChild == now->chil.end())
                {
                    now = now->failLink;
                    findChild = now->chil.find(text[i].first);
                }
                if (findChild != now->chil.end())
                {
                    now = findChild->second;
                }
            }
            if (now->leaf)
            {
                for (int p : now->pos)
                {
                    if ((int)i - (int)now->patSize - p + 2 >= 0)
                    {
                        ++patInd[i - now->patSize - p + 2];
                    }
                }
            }
            if (now->exitLink)
            {
                link = now->exitLink;
                while (link)
                {
                    for (int p : link->pos)
                    {
                        if ((int)i - (int)link->patSize - p + 2 >= 0)
                        {
                            ++patInd[i - link->patSize - p + 2];
                        }
                    }
                    link = link->exitLink;
                }
            }
        }
        for (size_t i = 0; i < textSize - patLen + 1; ++i)
        {
            if (patInd[i] == patCount)
            {
                result.push_back(std::make_pair(text[i].second.first, text[i].second.second));
            }
        }

        return result;
    }

private:
    void Destroy(TNode *n)
    {
        for (auto iter : n->chil)
        {
            Destroy(iter.second);
        }

        delete n;
    }

    void SetLinks(TNode *n, size_t lvl)
    {
        if (lvl != 1)
        {
            for (auto iter : n->chil)
            {
                SetLinks(iter.second, lvl - 1);
            }
        }
        else
        {
            for (auto iter : n->chil)
            {
                Linking(n, iter.second, iter.first);
            }
        }
    }

    void Linking(TNode *parent, TNode *nd, std::string nodeSym)
    {
        TNode *link = parent->failLink;
        auto findChild = link->chil.find(nodeSym);
        while (link != root && findChild == link->chil.end())
        {
            link = link->failLink;
            findChild = link->chil.find(nodeSym);
        }
        if (findChild == link->chil.end())
            nd->failLink = root;
        else
        {
            nd->failLink = findChild->second;
            link = nd->failLink;
            if (link->leaf)
                nd->exitLink = link;
            else if (link->exitLink)
                nd->exitLink = link->exitLink;
        }
    }
    TNode *root;
};

std::vector<std::pair<std::vector<std::string>, size_t>> split(std::stringstream &pattern, std::string joker, size_t &wordCount) // разбиение паттернов с джокером на подпаттерны
{
    std::string word;
    std::vector<std::pair<std::vector<std::string>, size_t>> result;
    std::vector<std::string> pat;
    while (pattern >> word)
    {
        ++wordCount;
        if (word == joker)
        {
            if (!pat.empty())
            {
                result.push_back(std::make_pair(pat, wordCount - pat.size()));
                pat.clear();
            }
        }
        else
        {
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                           { return std::tolower(c); });
            pat.push_back(word);
        }
    }
    if (word != joker)
    {
        result.push_back(std::make_pair(pat, wordCount - pat.size() + 1));
    }
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TTrie tree;
    std::string str;
    getline(std::cin, str);
    std::stringstream pattern(str);
    size_t patLen = 0;
    auto pos = split(pattern, "?", patLen);
    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> text;
    size_t max = 0;
    size_t patCount = 0;
    for (auto iter : pos)
    {
        if (iter.first.size() > max)
        {
            max = iter.first.size();
        }
        tree.AddPat(iter);
        ++patCount;
    }

    tree.failInit(max);

    size_t line = 0;
    while (getline(std::cin, str))
    {
        line++;
        size_t position = 0;
        if (str.empty())
            continue;
        std::stringstream part(str);
        while (part >> str)
        {
            ++position;
            std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
                           { return std::tolower(c); });
            text.push_back(std::make_pair(str, std::make_pair(line, position)));
        }
    }

    if (text.size() >= patLen)
    {
        auto result = tree.search(text, patCount, patLen);

        for (auto iter : result)
        {
            std::cout << iter.first << ", " << iter.second << '\n';
        }
    }

    return 0;
}
