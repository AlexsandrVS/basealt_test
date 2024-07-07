#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <future>
#include <set>
#include <unordered_map>
#include <dlfcn.h> // Для работы с динамическими библиотеками
#include "../build/shared_lib/fetch_and_save.h"

using json = nlohmann::json;

// Структура для представления пакета
struct Package {
    std::string name;
    int epoch;
    std::string version;
    std::string release;
    std::string arch;
    std::string disttag;
    int buildtime;
    std::string source;
};

// Оператор для сравнения пакетов по версии и релизу
bool operator>(const Package& lhs, const Package& rhs) {
    return (lhs.version > rhs.version) || (lhs.version == rhs.version && lhs.release > rhs.release);
}

// Функция для загрузки JSON из файла
json load_json(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    json data;
    file >> data;
    return data;
}

// Функция для выполнения сравнения пакетов из двух веток
json compare_packages(const json& branch1, const json& branch2, const std::string& arch) {
    std::unordered_map<std::string, Package> packages1_map, packages2_map;

    // Заполнение unordered_map для первой ветки
    for (const auto& pkg : branch1["packages"]) {
        if (pkg["arch"] == arch) {
            Package package;
            package.name = pkg["name"];
            package.epoch = pkg["epoch"];
            package.version = pkg["version"];
            package.release = pkg["release"];
            package.arch = pkg["arch"];
            package.disttag = pkg["disttag"];
            package.buildtime = pkg["buildtime"];
            package.source = pkg["source"];
            packages1_map[package.name] = package;
        }
    }

    // Заполнение unordered_map для второй ветки
    for (const auto& pkg : branch2["packages"]) {
        if (pkg["arch"] == arch) {
            Package package;
            package.name = pkg["name"];
            package.epoch = pkg["epoch"];
            package.version = pkg["version"];
            package.release = pkg["release"];
            package.arch = pkg["arch"];
            package.disttag = pkg["disttag"];
            package.buildtime = pkg["buildtime"];
            package.source = pkg["source"];
            packages2_map[package.name] = package;
        }
    }

    // Сравнение пакетов и формирование результата
    std::vector<Package> only_in_first, only_in_second, higher_version_in_first;

    // Поиск пакетов, которые есть только в первой ветке
    for (const auto& pair : packages1_map) {
        const auto& pkg1 = pair.second;
        auto it = packages2_map.find(pkg1.name);
        if (it == packages2_map.end()) {
            only_in_first.push_back(pkg1);
        } else {
            const auto& pkg2 = it->second;
            if (pkg1 > pkg2) {
                higher_version_in_first.push_back(pkg1);
            }
        }
    }

    // Поиск пакетов, которые есть только во второй ветке
    for (const auto& pair : packages2_map) {
        const auto& pkg2 = pair.second;
        auto it = packages1_map.find(pkg2.name);
        if (it == packages1_map.end()) {
            only_in_second.push_back(pkg2);
        }
    }

    // Формирование JSON с результатами
    json result;
    result["arch"] = arch;
    result["packages_only_in_first"] = json::array();
    for (const auto& pkg : only_in_first) {
        result["packages_only_in_first"].push_back({
            {"name", pkg.name},
            {"epoch", pkg.epoch},
            {"version", pkg.version},
            {"release", pkg.release},
            {"arch", pkg.arch},
            {"disttag", pkg.disttag},
            {"buildtime", pkg.buildtime},
            {"source", pkg.source}
        });
    }

    result["packages_only_in_second"] = json::array();
    for (const auto& pkg : only_in_second) {
        result["packages_only_in_second"].push_back({
            {"name", pkg.name},
            {"epoch", pkg.epoch},
            {"version", pkg.version},
            {"release", pkg.release},
            {"arch", pkg.arch},
            {"disttag", pkg.disttag},
            {"buildtime", pkg.buildtime},
            {"source", pkg.source}
        });
    }

    result["packages_higher_version_in_first"] = json::array();
    for (const auto& pkg : higher_version_in_first) {
        result["packages_higher_version_in_first"].push_back({
            {"name", pkg.name},
            {"epoch", pkg.epoch},
            {"version", pkg.version},
            {"release", pkg.release},
            {"arch", pkg.arch},
            {"disttag", pkg.disttag},
            {"buildtime", pkg.buildtime},
            {"source", pkg.source}
        });
    }

    return result;
}

// Функция для асинхронной обработки
json process_comparison(const json& branch1_data, const json& branch2_data, const std::string& arch) {
    return compare_packages(branch1_data, branch2_data, arch);
}

int main() {
    try {
        // Множество для хранения уже выбранных веток
        std::set<std::string> selected_branches;
        std::vector<json> branch_data;

        std::vector<std::string> branches = {"p9", "p10", "p11", "sisyphus"};
        std::vector<std::string> branch_choices;

        std::cout << "Select \n";

        while (selected_branches.size() < 2) {
            std::string choice;
            std::cout << "Выберите ветку (1. p9, 2. p10, 3. p11, 4. sisyphus): ";
            std::cin >> choice;

            int index = std::stoi(choice) - 1; // Индекс ветки в векторе branches

            // Проверяем корректность введенного номера
            if (index >= 0 && index < branches.size()) {
                std::string branch_name = branches[index];

                // Проверяем, что ветка еще не была выбрана
                if (selected_branches.count(branch_name) == 0) {
                    selected_branches.insert(branch_name);
                    branch_choices.push_back(branch_name);
                } else {
                    std::cout << "Эта ветка уже выбрана. Выберите другую ветку.\n";
                }
            } else {
                std::cout << "Некорректный выбор. Пожалуйста, выберите номер ветки от 1 до 4.\n";
            }
        }

        std::cout << "Выбранные ветки:\n";
        for (const auto& branch : branch_choices) {
            std::cout << branch << "\n";
        }

        // Загрузка выбранных веток через функцию из динамической библиотеки
        fetchAndSaveMultiple(branch_choices);

        // Загрузка данных из выбранных веток в вектор branch_data
        for (const auto& branch : branch_choices) {
            branch_data.push_back(load_json(branch + ".json"));
        }

        // Получение списка уникальных архитектур
        std::set<std::string> architectures;
        for (const auto& branch : branch_data) {
            for (const auto& pkg : branch["packages"]) {
                architectures.insert(pkg["arch"]);
            }
        }

        // Асинхронная обработка для каждой архитектуры
        std::vector<std::future<json>> futures;
        for (const auto& arch : architectures) {
            futures.push_back(std::async(std::launch::async, process_comparison, std::ref(branch_data[0]), std::ref(branch_data[1]), arch));
        }

        // Объединение результатов
        json final_result = json::array();
        for (auto& future : futures) {
            final_result.push_back(future.get());
        }

        // Сохранение итогового результата в файл
        std::ofstream final_file("Answer/final_comparison_result.json");
        final_file << std::setw(4) << final_result << std::endl;
        std::cout << "Final comparison result saved to Answer/final_comparison_result.json" << std::endl;

        // Сохранение отдельных файлов
        for (const auto& arch : architectures) {
            json result = compare_packages(branch_data[0], branch_data[1], arch);
            std::ofstream file("Answer/" + arch + "_comparison_result.json");
            file << std::setw(4) << result << std::endl;
            std::cout << "Comparison result for arch " << arch << " saved to Answer/" << arch << "_comparison_result.json" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
