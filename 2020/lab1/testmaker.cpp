#include <iostream>
#include <fstream>
#include <cstdlib> // для rand() и srand()
#include <ctime>   // для time()

// Функция для генерации случайного автомобильного номера
std::string generateLicensePlate() {
    char letter1 = 'A' + rand() % 26;
    char letter2 = 'A' + rand() % 26;
    char letter3 = 'A' + rand() % 26;
    int number = rand() % 1000; // случайное число от 0 до 999
    char buffer[10];
    sprintf(buffer, "%c %03d %c%c", letter1, number, letter2, letter3);
    return std::string(buffer);
}

// Функция для генерации случайной строки заданной длины
std::string generateRandomString(size_t length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return result;
}

int main(int argc, char* argv[]) {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    // Открываем файл для записи
    std::ofstream outFile("input.txt");
    if (!outFile) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    int numPairs = 20;
    if (argc > 1)
    {
        numPairs = atoi(argv[1]);
        //std::cout<<numPairs<<std::endl;
    }

    // Генерация и запись пар в файл
    for (int i = 0; i < numPairs; ++i) {
        std::string licensePlate = generateLicensePlate();
        size_t valueLength = rand() % 2048; // случайная длина от 0 до 2048 символов
        std::string value = generateRandomString(valueLength);

        outFile << licensePlate << '\t' << value << '\n';
    }

    // Закрываем файл
    outFile.close();

    //std::cout << "testmaker.cpp: Файл input.txt успешно создан!" << std::endl;

    return 0;
}