#ifndef TTRIE
#define TTRIE

#include <memory>
#include <string>
#include <iostream>
#include <queue>
#include <new>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <ctime>

const unsigned short MAX_WORD = 17;
#define T unsigned long long
#define S std::string
#define Pair std::pair

const S TERML = "$";

class TNode
{
private:
    std::unordered_map<S, TNode *> children;
    TNode *fail;
    TNode *exit;
    Pair<T, T> *lengt;

    void Destroy();
    TNode *CreateChild(const S sim);

public:
    TNode()
    {
        lengt = nullptr;
        exit = nullptr;
        fail = nullptr;
    }
    void notTerml(T numStr, T len)
    {
        if (this->children.find(TERML) == this->children.end())
        {
            Pair<S, TNode *> tmpPair = std::make_pair(TERML, new TNode);
            Pair<T, T> *tmpPairInt = new Pair<T, T>;
            *tmpPairInt = std::make_pair(numStr, len);
            tmpPair.second->lengt = tmpPairInt;
            this->children.insert(tmpPair);
        }
    }
    ~TNode(){};
    friend class TTrie;
};

void TNode::Destroy()
{
    if (!this->children.empty())
    {
        for (std::unordered_map<S, TNode *>::iterator it = this->children.begin(); it != this->children.end(); ++it)
        {
            if (it->second != nullptr)
            {
                it->second->Destroy();
                delete it->second;
            }
        }
        this->children.clear();
    }
    delete this->lengt;
    this->lengt = nullptr;
    this->fail = nullptr;
    this->exit = nullptr;
}

TNode *TNode::CreateChild(const S sim)
{
    auto tmpPair = std::make_pair(sim, new TNode);
    this->children.insert(tmpPair); 
    return tmpPair.second;
}

class TTrie
{
public:
    TTrie()
    {
        this->root = new TNode;
        it = this->root;
    }
    void Create(const S &symb);
    void Itfind(const std::vector<Pair<T int, T int>> &vec, const S &symb);
    void Linking();
    void ItReset();
    ~TTrie()
    {
        this->root->Destroy();
        this->it = nullptr;
        delete this->root;
    };

    TNode *ItGet()
    {
        return this->it;
    }

private:
    TNode *root;
    TNode *it;
    bool Do(const S &symb);
    void GetRes(const std::vector<Pair<T int, T int>> &vec, std::unordered_map<S, TNode *>::iterator &it);
};

void TTrie::ItReset()
{
    it = this->root;
}

void TTrie::Create(const S &symb)
{

    std::unordered_map<S, TNode *>::iterator itt;

    if (this->it->children.empty())
    { // если узел пуст то добавить входящие символы дочерними
        this->it = it->CreateChild(symb);
    }
    else
    {
        itt = this->it->children.find(symb);
        if (itt != this->it->children.end())
        {
            it = itt->second;
            //переставляем итератор
        }
        else
        {
            this->it = it->CreateChild(symb); // иначе добавляем ребенка и переводим итератор
        }
    }
}
bool TTrie::Do(const S &symb)
{
    std::unordered_map<S, TNode *>::iterator itt;
    if (!this->it->children.empty())
    {                                        // если дети есть
        itt = this->it->children.find(symb); //ищем строку которую передали в функцию
        if (itt != this->it->children.end())
        { // если находим передвигаемся на нее
            it = itt->second;
        }
        else
        { // если нет строки, то передвигаем итератор на fail
            while (itt == this->it->children.end() && it != this->root)
            { // проходим по всем fail в итоге 2 варианта
                it = it->fail;
                itt = this->it->children.find(symb);
            }
            if (itt != this->it->children.end())
            {                     // 1) находим символ
                it = itt->second; // передвигаем итератор
            }
            else if (it == this->root)
            {                                        // 2) дошли до корня
                itt = this->it->children.find(symb); // ищем в нем символ
                if (itt != this->it->children.end())
                {                     //если нашли символ
                    it = itt->second; // передвигаем итератор
                }
            }
        }
    }
    else
    {
        if (it->fail)
        {
            it = it->fail;
        } // если fail нулевой, то это либо корень либо терминатор
    }
    if (it == this->root)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void TTrie::GetRes(const std::vector<Pair<T int, T int>> &vec, std::unordered_map<S, TNode *>::iterator &it)
{
    auto it1 = this->it;
    while (it1)
    {
        it = it1->children.find(TERML);
        if (it == it1->children.end())
        { //если на последней букве и она не терминал
            it1 = it1->exit;
            continue;
        }
        auto ptrVec = vec.end();
        --ptrVec;
        T patternlenght = it->second->lengt->second;
        while (ptrVec->second < patternlenght)
        { //пока колич слов в строке которую взяли меньше длины паттерна
            patternlenght -= ptrVec->second;
            ptrVec--; //итератор назад
        }
        auto WordNumb = ptrVec->second;
        WordNumb -= patternlenght - 1;
        printf("%llu,%llu,%llu\n", ptrVec->first, WordNumb, it->second->lengt->first);
        it1 = it1->exit;
    }
}

void TTrie::Itfind(const std::vector<Pair<T int, T int>> &vec, const S &symb)
{
    std::unordered_map<S, TNode *>::iterator it;
    if (Do(symb))
    { // если Do true то it != root
        this->GetRes(vec, it);
    }
}

void TTrie::Linking()
{
    TNode *tmpNode = root;
    std::queue<TNode *> queue;
    for (auto it = this->root->children.begin(); it != this->root->children.end(); it++)
    {
        queue.push(it->second);
        it->second->fail = root;
    }
    while (!queue.empty())
    {
        tmpNode = queue.front();
        queue.pop();
        std::unordered_map<S, TNode *>::iterator it; // итератор для unordered_map
        for (it = tmpNode->children.begin(); it != tmpNode->children.end(); ++it)
        {
            TNode *child = it->second;
            TNode *parentFail = tmpNode->fail;
            S childsymbols = it->first;
            queue.push(child);
            while (true)
            {
                if (childsymbols != TERML)
                {
                    std::unordered_map<S, TNode *>::iterator existingNode = parentFail->children.find(childsymbols); //есть ли символ ребенка в родительском fail
                    if (existingNode != parentFail->children.end())
                    { //если есть
                        if (existingNode->second != child)
                        {                                       //и узел не тот же
                            child->fail = existingNode->second; //делаем fail на него
                            if (existingNode->second->children.find(TERML) != existingNode->second->children.end())
                            {                                       //проверяем символ на конец слова
                                child->exit = existingNode->second; //если да, делаем ссылку выхода на него
                            }
                            else
                            {
                                if (existingNode->second->exit)
                                {                                             //проверяем есть ли у него ссылка на конец слова
                                    child->exit = existingNode->second->exit; //ссылаемся на нее если есть
                                }
                            }
                        }
                        else
                        { //если это тот же самый узел делаем ссылку неудач на корень
                            child->fail = root;
                        }
                        break;
                    }
                }
                else
                {
                    break;
                }
                if (parentFail == root)
                {                       //если fail родителя был на корень
                    child->fail = root; //перенаправляем fail ребенка на корень
                    break;
                }
                else
                { //иначе переходим по fail родителя и ищем символ ребенка
                    parentFail = parentFail->fail;
                }
            }
        }
    }
}
#endif

int main()
{
    char buffer[MAX_WORD];
    bool sp = false;
    T l = 1;
    T numStr = 0;
    TTrie trie;
    unsigned short i = 0;

    char c = tolower(getchar());
    memset(buffer, 0, MAX_WORD);
    while (c > 0)
    {
        while (c == '\t' || c == ' ')
        {
            sp = true;
            c = tolower(getchar());
        }
        i = 0;
        while (c >= 'a' && c <= 'z')
        { //считываем слово
            sp = false;
            buffer[i] = c;
            ++i;
            c = tolower(getchar());
        }
        if (c == '\t' || c == ' ')
        {
            sp = true;
            if (buffer[0] != '\0')
            {
                trie.Create(buffer);
            }
            ++l;
            memset(buffer, 0, MAX_WORD);
        }
        else if (c == '\n')
        {
            if (buffer[0] != '\0')
            {
                trie.Create(buffer);
            }
            ++numStr;
            if (sp)
            {
                --l;
            }
            trie.ItGet()->notTerml(numStr, l);
            memset(buffer, 0, MAX_WORD);
            trie.ItReset();
            l = 1;
            c = tolower(getchar());
            if (c == '\n')
            {
                trie.ItReset();
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            std::cerr << "ERROR: incorrect puttern.\n";
            return 0;
        }
        c = tolower(getchar());
    }

    trie.Linking();

    std::vector<Pair<T int, T int>> vec;
    Pair<T int, T int> PairStr;
    PairStr = std::make_pair<T int, T int>(1, 0);
    vec.push_back(PairStr);
    c = tolower(getchar());

    while (c > 0)
    {
        while (c == '\t' || c == ' ')
        {
            sp = true;
            c = tolower(getchar());
        }
        i = 0;
        while (c >= 'a' && c <= 'z')
        {
            sp = false;
            buffer[i] = c;
            ++i;
            c = tolower(getchar());
        }
        if (c == '\t' || c == ' ')
        {
            sp = true;
            if (buffer[0] != '\0')
            {
                ++vec.back().second;
                trie.Itfind(vec, buffer); //поиск
                memset(buffer, 0, MAX_WORD);
            }
        }
        else if (c == '\n')
        {
            if (buffer[0] != '\0')
            {
                if (!sp)
                {
                    ++vec.back().second;
                }
                trie.Itfind(vec, buffer);
                memset(buffer, 0, MAX_WORD);
            }
            ++PairStr.first;
            vec.push_back(PairStr);
        }
        else
        {
            std::cerr << "ERROR: incorrect input.\n";
            return 0;
        }
        c = tolower(getchar());
    }
    return 0;
}