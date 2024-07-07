#include "fetch_and_save.h"
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <vector>
#include <future>

// Callback function to write data into std::string
// Callback функция для записи данных в std::string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc &e) {
        // Handle memory problem
        // Обработка проблемы с памятью
        return 0;
    }
    return newLength;
}

// Function to fetch data from URL and save as JSON file
// Функция для загрузки данных по URL и сохранения в файле JSON
void fetchAndSave(const std::string& branch) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + branch;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::ofstream outFile(branch + ".json");
            if (outFile.is_open()) {
                outFile << readBuffer;
                outFile.close();
                std::cout << "Data saved to " << branch << ".json" << std::endl;
            } else {
                std::cerr << "Unable to open file " << branch << ".json" << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

// Function to fetch and save multiple branches asynchronously
// Функция для асинхронной загрузки и сохранения нескольких веток
void fetchAndSaveMultiple(const std::vector<std::string>& branches) {
    std::vector<std::future<void>> futures;
    
    for (const std::string& branch : branches) {
        futures.push_back(std::async(std::launch::async, fetchAndSave, branch));
    }

    // Wait for all async tasks to complete
    // Ожидание завершения всех асинхронных задач
    for (auto& future : futures) {
        future.get();
    }
}
