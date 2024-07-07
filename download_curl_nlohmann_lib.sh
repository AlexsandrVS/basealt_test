#!/bin/bash

# Проверка, запущен ли скрипт с правами root
# Checking if script is run as root
if [ "$(id -u)" != "0" ]; then
    echo "Этот скрипт требует привилегий root. Попытка перезапустить с sudo..."
    # This script requires root privileges. Attempting to rerun with sudo...
    sudo "$0" "$@"  # Перезапуск скрипта с sudo
    # Re-running the script with sudo
    exit $? 
fi

# Включение установки nlohmann/json.hpp
# Including nlohmann/json.hpp installation

# Предполагается, что nlohmann/json.hpp доступен в системных репозиториях
# Assuming nlohmann/json.hpp is available in system repositories

# Для дистрибутивов на основе Ubuntu и Debian
# For Ubuntu and Debian based distributions
if [ -f /etc/debian_version ] || [ -f /etc/lsb-release ]; then
    apt-get update
    apt-get install -y libcurl4-openssl-dev nlohmann-json3-dev
    echo "Библиотека libcurl и nlohmann/json.hpp успешно установлены для Debian/Ubuntu."
    # libcurl library and nlohmann/json.hpp successfully installed for Debian/Ubuntu based distributions.

# Для CentOS и Fedora
# For CentOS and Fedora
elif [ -f /etc/redhat-release ]; then
    yum install -y libcurl-devel nlohmann-json3-devel
    echo "Библиотека libcurl и nlohmann/json.hpp успешно установлены для CentOS/Fedora."
    # libcurl library and nlohmann/json.hpp successfully installed for CentOS/Fedora.

# Для openSUSE
# For openSUSE
elif [ -f /etc/SuSE-release ]; then
    zypper install -y libcurl-devel nlohmann-json3-devel
    echo "Библиотека libcurl и nlohmann/json.hpp успешно установлены для openSUSE."
    # libcurl library and nlohmann/json.hpp successfully installed for openSUSE.

# Для Alt Linux
# For Alt Linux
elif [ -f /etc/altlinux-release ]; then
    apt-get update
    apt-get install -y libcurl-devel nlohmann-json3-devel
    echo "Библиотека libcurl и nlohmann/json.hpp успешно установлены для Alt Linux."
    # libcurl library and nlohmann/json.hpp successfully installed for Alt Linux.

# Если дистрибутив не распознан, отображаем сообщение об ошибке
# If the distribution is not recognized, display an error message
else
    echo "Не удалось определить дистрибутив Linux для установки libcurl и nlohmann/json.hpp." >&2
    # Unable to determine Linux distribution for libcurl and nlohmann/json.hpp installation.
    exit 1
fi

echo -e "\nЗагрузка завершена успешно! / Downloading success!"
