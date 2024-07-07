#!/bin/bash

# Checking if script is run as root
if [ "$(id -u)" != "0" ]; then
    echo "This script requires root privileges. Attempting to rerun with sudo..."
    sudo "$0" "$@"  # Re-running the script with sudo
    exit $? 
fi

# Including nlohmann/json.hpp installation
# Assuming nlohmann/json.hpp is available in system repositories

# For Ubuntu and Debian based distributions
if [ -f /etc/debian_version ] || [ -f /etc/lsb-release ]; then
    apt-get update
    apt-get install -y libcurl4-openssl-dev nlohmann-json3-dev
    echo "libcurl library and nlohmann/json.hpp successfully installed for Debian/Ubuntu based distributions."

# For CentOS and Fedora
elif [ -f /etc/redhat-release ]; then
    yum install -y libcurl-devel nlohmann-json3-devel
    echo "libcurl library and nlohmann/json.hpp successfully installed for CentOS/Fedora."

# For openSUSE
elif [ -f /etc/SuSE-release ]; then
    zypper install -y libcurl-devel nlohmann-json3-devel
    echo "libcurl library and nlohmann/json.hpp successfully installed for openSUSE."

# For Alt Linux
elif [ -f /etc/altlinux-release ]; then
    apt-get update
    apt-get install -y libcurl-devel nlohmann-json3-devel
    echo "libcurl library and nlohmann/json.hpp successfully installed for Alt Linux."

# If the distribution is not recognized, display an error message
else
    echo "Unable to determine Linux distribution for libcurl and nlohmann/json.hpp installation." >&2
    exit 1
fi

echo -e "\n Downloading success!"