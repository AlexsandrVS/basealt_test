# Script to install curl library for various Linux distributions

if [ "$(id -u)" != "0" ]; then
    echo "This script requires root privileges. Attempting to rerun with sudo..."
    sudo "$0" "$@"  # Re-running the script with sudo
    exit $? 
fi

# For Ubuntu and Debian based distributions
if [ -f /etc/debian_version ] || [ -f /etc/lsb-release ]; then
    apt-get update
    apt-get install -y libcurl4-openssl-dev
    echo "libcurl library successfully installed for Debian/Ubuntu based distributions."

# For CentOS and Fedora
elif [ -f /etc/redhat-release ]; then
    yum install -y libcurl-devel
    echo "libcurl library successfully installed for CentOS/Fedora."

# For openSUSE
elif [ -f /etc/SuSE-release ]; then
    zypper install -y libcurl-devel
    echo "libcurl library successfully installed for openSUSE."

# For Alt Linux
elif [ -f /etc/altlinux-release ]; then
    apt-get update
    apt-get install -y libcurl-devel
    echo "libcurl library successfully installed for Alt Linux."

# If the distribution is not recognized, display an error message
else
    echo "Unable to determine Linux distribution for libcurl installation." >&2
    exit 1
fi

echo "**************"
echo "* Completed! *"
echo "**************"
