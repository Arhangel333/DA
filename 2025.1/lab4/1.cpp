<<<<<<< HEAD
#include <vector>
#include <string>
#include <algorithm>
#include <map>

std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string> &strs)
{
    std::map<size_t, std::vector<std::string>> lengthGroups;
    for (const auto &str : strs)
    {
        lengthGroups[str.length()].push_back(str);
    }

    std::vector<std::vector<std::string>> result;

    for (auto &pair : lengthGroups)
    {
        size_t length = pair.first;
        std::vector<std::string> &words = pair.second;
        if (words.size() == 1)
        {
            result.push_back({words[0]});
            continue;
        }

        std::vector<bool> used(words.size(), false);

        for (size_t i = 0; i < words.size(); ++i)
        {
            if (used[i])
                continue;

            std::vector<std::string> group = {words[i]};
            used[i] = true;

            std::string sortedI = words[i];
            std::sort(sortedI.begin(), sortedI.end());

            for (size_t j = i + 1; j < words.size(); ++j)
            {
                if (used[j])
                    continue;

                std::string sortedJ = words[j];
                std::sort(sortedJ.begin(), sortedJ.end());

                if (sortedI == sortedJ)
                {
                    group.push_back(words[j]);
                    used[j] = true;
                }
            }

            result.push_back(group);
        }
    }

    return result;
=======
#include <vector>
#include <string>
#include <algorithm>
#include <map>

std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string> &strs)
{
    std::map<size_t, std::vector<std::string>> lengthGroups;
    for (const auto &str : strs)
    {
        lengthGroups[str.length()].push_back(str);
    }

    std::vector<std::vector<std::string>> result;

    for (auto &pair : lengthGroups)
    {
        size_t length = pair.first;
        std::vector<std::string> &words = pair.second;
        if (words.size() == 1)
        {
            result.push_back({words[0]});
            continue;
        }

        std::vector<bool> used(words.size(), false);

        for (size_t i = 0; i < words.size(); ++i)
        {
            if (used[i])
                continue;

            std::vector<std::string> group = {words[i]};
            used[i] = true;

            std::string sortedI = words[i];
            std::sort(sortedI.begin(), sortedI.end());

            for (size_t j = i + 1; j < words.size(); ++j)
            {
                if (used[j])
                    continue;

                std::string sortedJ = words[j];
                std::sort(sortedJ.begin(), sortedJ.end());

                if (sortedI == sortedJ)
                {
                    group.push_back(words[j]);
                    used[j] = true;
                }
            }

            result.push_back(group);
        }
    }

    return result;
>>>>>>> 017b9db (8 9 fiished)
}