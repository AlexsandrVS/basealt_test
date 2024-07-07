### Installing and Running the Repository

#### Prerequisites
- **Git**: Ensure that Git is installed on your system. You can download it from [git-scm.com](https://git-scm.com/downloads) and follow the installation instructions for your operating system.

#### Cloning the Repository
1. Open your terminal or command prompt.
2. Clone the repository from GitHub:

   ```
   git clone https://github.com/AlexsandrVS/basealt_test.git
   ```

#### Navigating to the Repository Directory
1. Navigate to the cloned repository directory:

   ```
   cd basealt_test
   ```

#### Building and Running the Project
1. Make the `run.sh` script executable:

   ```
   chmod +x run.sh
   ```

3. Run the script to build and execute the project:

   ```
   ./run.sh
   ```
   Ensure that the `run.sh` script correctly performs the necessary operations for your project.

### Usage Instructions
- Follow the on-screen instructions to select branches and perform package comparisons.
- Comparison results will be saved in JSON files in the `Answer/` directory.

### Troubleshooting
- If you encounter build or execution errors, ensure that all dependencies (e.g., `libcurl` and `nlohmann/json.hpp`) are installed and accessible.
- Check for specific build instructions or requirements in the repository's documentation.

---

This guide will help you install the repository, make the `run.sh` script executable, and run the project to compare packages between different distribution branches. If you have any further questions or issues, feel free to ask for assistance!
