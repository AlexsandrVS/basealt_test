#include "../shared_lib/fetch_and_save.h" // Путь к вашему заголовочному файлу
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> branches = {"sisyphus", "p10", "p9"};

    // Вызов функции из разделяемой библиотеки для загрузки данных по нескольким веткам
    fetchAndSaveMultiple(branches);

    return 0;
}
