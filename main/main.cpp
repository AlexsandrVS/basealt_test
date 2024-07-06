/////////////////////////////////////////////////////////////////////////////
//* тестовое задание:

//* Eсть публичый REST API для нашей базы данных: https://rdb.altlinux.org/api/
//* У него есть метод /export/branch_binary_packages/{branch}
//* в качестве бранча можно использовать: sisyphus, p10, p9 и др..

//! Нужно сделать разделяемую библиотеку (собранную в соответствии с данными рекомендациями:
//* https://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html )
//* и CLI-утилиту к ней(использующую эту библиотеку), которая:
//* 1) получает списки бинарных пакетов 2-х веток. Например, sisyphus и p10.
//* 2) делает сравнение полученных списков пакетов и выводит JSON
//* (структуру нужно придумать), в котором будет отображено:
//* - все пакеты, которые есть в 1-й но нет во 2-й
//* - все пакеты, которые есть в 2-й но их нет в 1-й
//* - все пакеты, version-release которых больше в 1-й чем во 2-й

//* Это нужно сделать с каждой из поддерживаемых веткой архитектур (поле arch в ответе).
//* Процесс разработки нужно оформить в виде git репозитория с историей изменений с самого первого этапа 
//* (без переписывания коммитов) и выложить, например, на github.

//* В разработке можно использовать любые необходимые вам библиотеки, при
//* условии что эти библиотеки будут использоваться из репозитория ALT
//* Linux: https://packages.altlinux.org/ru/p10/

//* Утилита должна запускаться под операционной системой Linux (мы будем
//* проверять её сборку и работу на ALT Рабочая станция К 10.1), к ней
//* должно быть README на английском языке, содержащее инструкцию по
//* установке в систему (в соответствии со стандартом FHS) и запуску.
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <curl/curl.h> //? sudo dnf install libcurl-devel
#include <string>

// Callback функция для записи данных в std::string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc &e) {
        // Handle memory problem
        return 0;
    }
    return newLength;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://rdb.altlinux.org/api/export/branch_binary_packages/sisyphus";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
