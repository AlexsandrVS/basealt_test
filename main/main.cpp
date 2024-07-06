#include "../shared_lib/fetch_and_save.h"

int main() {
    std::vector<std::string> branches = {"sisyphus", "p11", "p10", "p9"};

    // Вызов функции из разделяемой библиотеки для загрузки данных по нескольким веткам
    fetchAndSaveMultiple(branches);

    return 0;
}
