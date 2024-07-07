#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <future>
#include <set>
#include <unordered_map>
#include <filesystem> // Для создания каталога

using json = nlohmann::json;
namespace fs = std::filesystem; // Пространство имен для работы с файловой системой

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
        // Создание каталога Answer
        fs::create_directory("Answer");

        // Загрузка данных
        json p10_data = load_json("p10.json");
        json sisyphus_data = load_json("sisyphus.json");

        // Получение списка уникальных архитектур
        std::set<std::string> architectures;
        for (const auto& pkg : p10_data["packages"]) {
            architectures.insert(pkg["arch"]);
        }
        for (const auto& pkg : sisyphus_data["packages"]) {
            architectures.insert(pkg["arch"]);
        }

        // Асинхронная обработка для каждой архитектуры
        std::vector<std::future<json>> futures;
        for (const auto& arch : architectures) {
            futures.push_back(std::async(std::launch::async, process_comparison, std::ref(p10_data), std::ref(sisyphus_data), arch));
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
            json result = compare_packages(p10_data, sisyphus_data, arch);
            std::ofstream file("Answer/" + arch + "_comparison_result.json");
            file << std::setw(4) << result << std::endl;
            std::cout << "Comparison result for arch " << arch << " saved to Answer/" << arch << "_comparison_result.json" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
