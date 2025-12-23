/* Представим, что мы хотим разработать систему саджестов -
 * системы, которая поможет дополнять запросы пользователей.
 * На каждый введенный префикс система должна выдать наиболее
 * 3 близких к поисковому слову товары (расположены в лексиграфически.)
 *
 *
 * Ввод:
 * products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
 * Вывод: [
 *          ["mobile","moneypot","monitor"], // для "m"
 *          ["mobile","moneypot","monitor"], // для "mo"
 *          ["mouse","mousepad"],            // для "mou"
 *          ["mouse","mousepad"],            // для "mous"
 *          ["mouse","mousepad"]             // для "mouse"
 *        ]
 */
vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
    sort(products.begin(), products.end());
    vector<vector<string>> result;
    
    int left = 0, right = products.size() - 1;
    
    for (int i = 0; i < searchWord.length(); i++) {
        char c = searchWord[i];
        
        while (left <= right && 
               (products[left].length() <= i || products[left][i] < c)) {
            left++;
        }
        
        while (left <= right && 
               (products[right].length() <= i || products[right][i] > c)) {
            right--;
        }
        
        vector<string> suggestions;
        int count = min(3, right - left + 1);
        
        for (int j = 0; j < count; j++) {
            suggestions.push_back(products[left + j]);
        }
        
        result.push_back(suggestions);
    }
    
    return result;
}