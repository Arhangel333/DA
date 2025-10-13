#include <iostream>  // Для ввода-вывода
#include <string>    // Для работы со строками
#include <unordered_map>  // Для хранения детей узла в виде хеш-таблицы
#include <utility>   // Для std::pair
#include <vector>    // Для динамических массивов
#include <sstream>   // Для разбиения строк на токены
#include <algorithm> // Для transform и tolower

class TTrie;  // Предварительное объявление класса TTrie

class TNode
{
public:
    friend TTrie;  // Разрешаем TTrie доступ к приватным полям
    TNode() : failLink(nullptr), exitLink(nullptr), leaf(false) {}  // Конструктор, инициализирующий указатели и флаг

private:
    std::unordered_map<std::string, TNode *> chil;  // Дочерние узлы, ключ - символ, значение - узел
    TNode *failLink;  // Ссылка на узел, куда переходить при неудачном поиске
    TNode *exitLink;  // Ссылка на ближайший терминальный узел
    bool leaf;        // Флаг, является ли узел терминальным (концом шаблона)
    size_t patSize;   // Длина шаблона, заканчивающегося в этом узле
    std::vector<size_t> pos;  // Позиции в исходном шаблоне, где встречается этот паттерн
};

class TTrie
{
public:
    TTrie() : root(new TNode()) {}  // Конструктор, создающий корневой узел

    ~TTrie()  // Деструктор
    {
        Destroy(root);  // Рекурсивное удаление всех узлов
    }

    // Добавление шаблона в trie
    void AddPat(std::pair<std::vector<std::string>, size_t> &pat)
    {
        TNode *now = root;  // Начинаем с корня
        for (auto iter : pat.first)  // Для каждого символа в шаблоне
        {
            if (now->chil.find(iter) == now->chil.end())  // Если символ отсутствует среди детей
            {
                now->chil.insert(std::make_pair(iter, new TNode()));  // Создаем новый узел
            }
            now = now->chil.find(iter)->second;  // Переходим к дочернему узлу
        }
        now->leaf = true;  // Помечаем узел как терминальный
        now->pos.push_back(pat.second);  // Сохраняем позицию шаблона
        now->patSize = pat.first.size();  // Сохраняем длину шаблона
    }

    // Инициализация fail-ссылок для алгоритма Ахо-Корасик
    void failInit(size_t max)
    {
        root->failLink = root;  // fail-ссылка корня указывает на себя
        for (auto iter : root->chil)  // Для каждого ребенка корня
        {
            iter.second->failLink = root;  // fail-ссылка указывает на корень
        }
        for (size_t i = 1; i < max; ++i)  // Для каждого уровня глубины
        {
            for (auto iter : root->chil)  // Для каждого ребенка корня
            {
                SetLinks(iter.second, i);  // Устанавливаем ссылки для узлов на этом уровне
            }
        }
    }

    // Поиск шаблонов в тексте
    std::vector<std::pair<size_t, size_t>> search(std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &text, size_t patCount, size_t patLen)
    {
        size_t textSize = text.size();
        std::vector<size_t> patInd(textSize, 0);  // Вектор для подсчета совпадений
        TNode *now = root;  // Текущий узел
        TNode *link;        // Вспомогательный указатель для exit-ссылок
        std::vector<std::pair<size_t, size_t>> result;  // Результаты поиска

        for (size_t i = 0; i < textSize; ++i)  // Для каждого символа в тексте
        {
            auto findChild = now->chil.find(text[i].first);  // Ищем символ среди детей
            if (findChild != now->chil.end())  // Если нашли
                now = findChild->second;       // Переходим к ребенку
            else  // Если не нашли
            {
                now = now->failLink;  // Переходим по fail-ссылке
                findChild = now->chil.find(text[i].first);
                while (now != root && findChild == now->chil.end())  // Пока не корень и не нашли символ
                {
                    now = now->failLink;  // Продолжаем идти по fail-ссылкам
                    findChild = now->chil.find(text[i].first);
                }
                if (findChild != now->chil.end())  // Если нашли символ
                {
                    now = findChild->second;  // Переходим к ребенку
                }
            }
            if (now->leaf)  // Если текущий узел терминальный
            {
                for (int p : now->pos)  // Для каждой позиции шаблона
                {
                    if ((int)i - (int)now->patSize - p + 2 >= 0)  // Проверка границ
                    {
                        ++patInd[i - now->patSize - p + 2];  // Увеличиваем счетчик совпадений
                    }
                }
            }
            if (now->exitLink)  // Если есть exit-ссылка
            {
                link = now->exitLink;
                while (link)  // Пока есть exit-ссылки
                {
                    for (int p : link->pos)  // Для каждой позиции шаблона
                    {
                        if ((int)i - (int)link->patSize - p + 2 >= 0)
                        {
                            ++patInd[i - link->patSize - p + 2];  // Увеличиваем счетчик совпадений
                        }
                    }
                    link = link->exitLink;  // Переходим к следующей exit-ссылке
                }
            }
        }
        for (size_t i = 0; i < textSize - patLen + 1; ++i)  // Для каждой возможной стартовой позиции
        {
            if (patInd[i] == patCount)  // Если все подшаблоны совпали
            {
                result.push_back(std::make_pair(text[i].second.first, text[i].second.second));  // Добавляем позицию в результат
            }
        }

        return result;
    }

private:
    void Destroy(TNode *n)  // Рекурсивное удаление узлов
    {
        for (auto iter : n->chil)  // Для каждого ребенка
        {
            Destroy(iter.second);  // Удаляем рекурсивно
        }

        delete n;  // Удаляем текущий узел
    }

    // Установка fail-ссылок для узлов на заданном уровне
    void SetLinks(TNode *n, size_t lvl)
    {
        if (lvl != 1)  // Если не достигли нужного уровня
        {
            for (auto iter : n->chil)  // Для каждого ребенка
            {
                SetLinks(iter.second, lvl - 1);  // Рекурсивно вызываем для следующего уровня
            }
        }
        else  // Если достигли нужного уровня
        {
            for (auto iter : n->chil)  // Для каждого ребенка
            {
                Linking(n, iter.second, iter.first);  // Устанавливаем ссылки
            }
        }
    }

    // Установка fail-ссылки для конкретного узла
    void Linking(TNode *parent, TNode *nd, std::string nodeSym)
    {
        TNode *link = parent->failLink;  // Начинаем с fail-ссылки родителя
        auto findChild = link->chil.find(nodeSym);  // Ищем символ среди детей
        while (link != root && findChild == link->chil.end())  // Пока не корень и не нашли символ
        {
            link = link->failLink;  // Идем по fail-ссылке
            findChild = link->chil.find(nodeSym);
        }
        if (findChild == link->chil.end())  // Если не нашли символ
            nd->failLink = root;  // fail-ссылка указывает на корень
        else
        {
            nd->failLink = findChild->second;  // fail-ссылка указывает на найденный узел
            link = nd->failLink;
            if (link->leaf)  // Если найденный узел терминальный
                nd->exitLink = link;  // Устанавливаем exit-ссылку
            else if (link->exitLink)  // Если у найденного узла есть exit-ссылка
                nd->exitLink = link->exitLink;  // Наследуем ее
        }
    }
    TNode *root;  // Корень trie
};

// Разбиение шаблона с джокерами на подшаблоны
std::vector<std::pair<std::vector<std::string>, size_t>> split(std::stringstream &pattern, std::string joker, size_t &wordCount)
{
    std::string word;
    std::vector<std::pair<std::vector<std::string>, size_t>> result;
    std::vector<std::string> pat;
    while (pattern >> word)  // Читаем слово из шаблона
    {
        ++wordCount;  // Увеличиваем счетчик слов
        if (word == joker)  // Если встретили джокер
        {
            if (!pat.empty())  // Если текущий подшаблон не пуст
            {
                result.push_back(std::make_pair(pat, wordCount - pat.size()));  // Добавляем подшаблон в результат
                pat.clear();  // Очищаем текущий подшаблон
            }
        }
        else  // Если не джокер
        {
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                           { return std::tolower(c); });  // Приводим к нижнему регистру
            pat.push_back(word);  // Добавляем слово в подшаблон
        }
    }
    if (word != joker)  // Если последнее слово не джокер
    {
        result.push_back(std::make_pair(pat, wordCount - pat.size() + 1));  // Добавляем последний подшаблон
    }
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);  // Ускоряем ввод-вывод
    std::cin.tie(nullptr);

    TTrie tree;  // Создаем trie
    std::string str;
    getline(std::cin, str);  // Читаем шаблон
    std::stringstream pattern(str);
    size_t patLen = 0;
    auto pos = split(pattern, "?", patLen);  // Разбиваем шаблон на подшаблоны
    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> text;
    size_t max = 0;
    size_t patCount = 0;
    for (auto iter : pos)  // Для каждого подшаблона
    {
        if (iter.first.size() > max)  // Находим максимальную длину подшаблона
        {
            max = iter.first.size();
        }
        tree.AddPat(iter);  // Добавляем подшаблон в trie
        ++patCount;  // Увеличиваем счетчик подшаблонов
    }

    tree.failInit(max);  // Инициализируем fail-ссылки

    size_t line = 0;
    while (getline(std::cin, str))  // Читаем текст построчно
    {
        line++;
        size_t position = 0;
        if (str.empty())
            continue;
        std::stringstream part(str);
        while (part >> str)  // Читаем слова из строки
        {
            ++position;
            std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
                           { return std::tolower(c); });  // Приводим к нижнему регистру
            text.push_back(std::make_pair(str, std::make_pair(line, position)));  // Сохраняем слово с его позицией
        }
    }

    if (text.size() >= patLen)  // Если текст не короче шаблона
    {
        auto result = tree.search(text, patCount, patLen);  // Ищем шаблоны

        for (auto iter : result)  // Выводим результаты
        {
            std::cout << iter.first << ", " << iter.second << '\n';
        }
    }

    return 0;
}