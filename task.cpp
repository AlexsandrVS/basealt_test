#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>

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
json compare_packages(const json& branch1, const json& branch2) {
    std::vector<Package> packages1, packages2;

    // Загрузка пакетов из первой ветки
    for (const auto& pkg : branch1["packages"]) {
        Package package;
        package.name = pkg["name"];
        package.epoch = pkg["epoch"];
        package.version = pkg["version"];
        package.release = pkg["release"];
        package.arch = pkg["arch"];
        package.disttag = pkg["disttag"];
        package.buildtime = pkg["buildtime"];
        package.source = pkg["source"];
        packages1.push_back(package);
    }

    // Загрузка пакетов из второй ветки
    for (const auto& pkg : branch2["packages"]) {
        Package package;
        package.name = pkg["name"];
        package.epoch = pkg["epoch"];
        package.version = pkg["version"];
        package.release = pkg["release"];
        package.arch = pkg["arch"];
        package.disttag = pkg["disttag"];
        package.buildtime = pkg["buildtime"];
        package.source = pkg["source"];
        packages2.push_back(package);
    }

    // Сравнение пакетов и формирование результата
    std::vector<Package> only_in_first, only_in_second, higher_version_in_first;

    // Поиск пакетов, которые есть только в первой ветке
    for (const auto& pkg1 : packages1) {
        auto it = std::find_if(packages2.begin(), packages2.end(), [&](const Package& pkg2) {
            return pkg1.name == pkg2.name;
        });
        if (it == packages2.end()) {
            only_in_first.push_back(pkg1);
        } else {
            if (pkg1 > *it) {
                higher_version_in_first.push_back(pkg1);
            }
        }
    }

    // Поиск пакетов, которые есть только во второй ветке
    for (const auto& pkg2 : packages2) {
        auto it = std::find_if(packages1.begin(), packages1.end(), [&](const Package& pkg1) {
            return pkg2.name == pkg1.name;
        });
        if (it == packages1.end()) {
            only_in_second.push_back(pkg2);
        }
    }

    // Формирование JSON с результатами
    json result;
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

int main() {
    try {
        json p11_data = load_json("p11.json");
        json p10_data = load_json("p10.json");

        json comparison_result = compare_packages(p11_data, p10_data);

        std::ofstream file("comparison_result.json");
        file << std::setw(4) << comparison_result << std::endl;
        std::cout << "Comparison result saved to comparison_result.json" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
