<<<<<<< HEAD
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

void printAnagrams(const std::vector<std::vector<std::string>>& anagrams) {
    for (const auto& group : anagrams) {
        std::cout << "[";
        for (size_t i = 0; i < group.size(); ++i) {
            std::cout << group[i];
            if (i != group.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
}

// Функция для группировки анаграмм из входного вектора строк
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string> &strs)
{
    // 1. Создаем map для группировки слов по их длине
    // Ключ: длина слова (size_t)
    // Значение: вектор слов этой длины
    std::map<size_t, std::vector<std::string>> lengthGroups;

    // 2. Заполняем lengthGroups, распределяя слова по их длинам
    for (const auto &str : strs)
    {
        lengthGroups[str.length()].push_back(str);
    }

    // 3. Вектор для хранения результата (групп анаграмм)
    std::vector<std::vector<std::string>> result;

    // 4. Обрабатываем каждую группу слов одинаковой длины
    for (auto &pair : lengthGroups)
    {
        size_t length = pair.first;            // Длина слов в текущей группе
        std::vector<std::string> &words = pair.second;  // Ссылка на вектор слов

        // 5. Если в группе только одно слово, сразу добавляем его в результат
        if (words.size() == 1)
        {
            result.push_back({words[0]});
            continue;
        }

        // 6. Вектор для отметки уже обработанных слов (чтобы избежать дублирования)
        std::vector<bool> used(words.size(), false);

        // 7. Проверяем все слова в текущей группе на анаграммы
        for (size_t i = 0; i < words.size(); ++i)
        {
            // Пропускаем уже обработанные слова
            if (used[i])
                continue;

            // 8. Создаем новую группу анаграмм, начиная с текущего слова
            std::vector<std::string> group = {words[i]};
            used[i] = true;  // Помечаем слово как обработанное

            // 9. Сортируем буквы текущего слова для сравнения с другими
            std::string sortedI = words[i];
            std::sort(sortedI.begin(), sortedI.end());

            // 10. Ищем анаграммы среди оставшихся слов
            for (size_t j = i + 1; j < words.size(); ++j)
            {
                // Пропускаем уже обработанные слова
                if (used[j])
                    continue;

                // 11. Сортируем буквы слова для сравнения
                std::string sortedJ = words[j];
                std::sort(sortedJ.begin(), sortedJ.end());

                // 12. Если слова являются анаграммами (после сортировки одинаковы)
                if (sortedI == sortedJ)
                {
                    group.push_back(words[j]);  // Добавляем в группу
                    used[j] = true;           // Помечаем как обработанное
                }
            }

            // 13. Добавляем найденную группу анаграмм в результат
            result.push_back(group);
        }
    }

    // 14. Возвращаем результат - вектор групп анаграмм
    return result;
}

int main(){

    std::vector<std::string> strs = {"cat", "car", "rac", "tca", "dcm", "mcd", "ghdf", "fdgh", "tyru", "r", "o"};

     printAnagrams(groupAnagrams(strs));
     std::cout<<"\n";
     printf("hi""\n" "lol");

=======
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

void printAnagrams(const std::vector<std::vector<std::string>>& anagrams) {
    for (const auto& group : anagrams) {
        std::cout << "[";
        for (size_t i = 0; i < group.size(); ++i) {
            std::cout << group[i];
            if (i != group.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
}

// Функция для группировки анаграмм из входного вектора строк
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string> &strs)
{
    // 1. Создаем map для группировки слов по их длине
    // Ключ: длина слова (size_t)
    // Значение: вектор слов этой длины
    std::map<size_t, std::vector<std::string>> lengthGroups;

    // 2. Заполняем lengthGroups, распределяя слова по их длинам
    for (const auto &str : strs)
    {
        lengthGroups[str.length()].push_back(str);
    }

    // 3. Вектор для хранения результата (групп анаграмм)
    std::vector<std::vector<std::string>> result;

    // 4. Обрабатываем каждую группу слов одинаковой длины
    for (auto &pair : lengthGroups)
    {
        size_t length = pair.first;            // Длина слов в текущей группе
        std::vector<std::string> &words = pair.second;  // Ссылка на вектор слов

        // 5. Если в группе только одно слово, сразу добавляем его в результат
        if (words.size() == 1)
        {
            result.push_back({words[0]});
            continue;
        }

        // 6. Вектор для отметки уже обработанных слов (чтобы избежать дублирования)
        std::vector<bool> used(words.size(), false);

        // 7. Проверяем все слова в текущей группе на анаграммы
        for (size_t i = 0; i < words.size(); ++i)
        {
            // Пропускаем уже обработанные слова
            if (used[i])
                continue;

            // 8. Создаем новую группу анаграмм, начиная с текущего слова
            std::vector<std::string> group = {words[i]};
            used[i] = true;  // Помечаем слово как обработанное

            // 9. Сортируем буквы текущего слова для сравнения с другими
            std::string sortedI = words[i];
            std::sort(sortedI.begin(), sortedI.end());

            // 10. Ищем анаграммы среди оставшихся слов
            for (size_t j = i + 1; j < words.size(); ++j)
            {
                // Пропускаем уже обработанные слова
                if (used[j])
                    continue;

                // 11. Сортируем буквы слова для сравнения
                std::string sortedJ = words[j];
                std::sort(sortedJ.begin(), sortedJ.end());

                // 12. Если слова являются анаграммами (после сортировки одинаковы)
                if (sortedI == sortedJ)
                {
                    group.push_back(words[j]);  // Добавляем в группу
                    used[j] = true;           // Помечаем как обработанное
                }
            }

            // 13. Добавляем найденную группу анаграмм в результат
            result.push_back(group);
        }
    }

    // 14. Возвращаем результат - вектор групп анаграмм
    return result;
}

int main(){

    std::vector<std::string> strs = {"cat", "car", "rac", "tca", "dcm", "mcd", "ghdf", "fdgh", "tyru", "r", "o"};

     printAnagrams(groupAnagrams(strs));
     std::cout<<"\n";
     printf("hi""\n" "lol");

>>>>>>> 017b9db (8 9 fiished)
}