#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>

using namespace std;
namespace fs = filesystem;

void listFiles(const fs::path& path) {
    cout << "Listing files in: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename() << "\n";
    }
}

void createDirectory(const fs::path& path) {
    if (fs::create_directory(path)) {
        cout << "Directory created: " << path << "\n";
    } else {
        cout << "Failed to create directory or already exists: " << path << "\n";
    }
}

void copyFile(const fs::path& source, const fs::path& destination) {
    try {
        if (!fs::exists(source)) {
            cout << "Source file does not exist: " << source << "\n";
            return;
        }
        fs::copy(source, destination);
        cout << "File copied from " << source << " to " << destination << "\n";
    } catch (const fs::filesystem_error& e) {
        cout << "Error copying file: " << e.what() << "\n";
    }
}

void moveFile(const fs::path& source, const fs::path& destination) {
    try {
        if (!fs::exists(source)) {
            cout << "Source file does not exist: " << source << "\n";
            return;
        }
        fs::rename(source, destination);
        cout << "File moved from " << source << " to " << destination << "\n";
    } catch (const fs::filesystem_error& e) {
        cout << "Error moving file: " << e.what() << "\n";
    }
}

void changeDirectory(fs::path& currentPath, const fs::path& newPath) {
    fs::path targetPath = currentPath / newPath;
    if (fs::exists(targetPath) && fs::is_directory(targetPath)) {
        currentPath = fs::absolute(targetPath);
        cout << "Changed directory to: " << currentPath << "\n";
    } else {
        cout << "Directory does not exist: " << targetPath << "\n";
    }
}

void showHelp() {
    cout << "Available commands:\n";
    cout << "  ls                   : List files in the current directory.\n";
    cout << "  mkdir <name>        : Create a new directory with the specified name.\n";
    cout << "  cp <source> <destination> : Copy a file from source to destination.\n";
    cout << "  mv <source> <destination> : Move a file from source to destination.\n";
    cout << "  cd <directory>      : Change the current directory to the specified directory.\n";
    cout << "  exit                : Exit the program.\n";
}

int main() {
    string command;
    fs::path currentPath = fs::current_path();

    while (true) {
        cout << "\nCurrent directory: " << currentPath << "\n";
        cout << "Enter command (type 'help' for assistance): ";
        getline(cin, command);

        if (command == "exit") {
            break;
        } else if (command == "ls") {
            listFiles(currentPath);
        } else if (command == "help") {
            showHelp();
        } else if (command.substr(0, 6) == "mkdir ") {
            createDirectory(currentPath / command.substr(6));
        } else if (command.substr(0, 3) == "cp ") {
            istringstream iss(command.substr(3));
            string source, destination;
            iss >> source >> destination;
            if (iss && !destination.empty()) {
                copyFile(currentPath / source, currentPath / destination);
            } else {
                cout << "Usage: cp <source> <destination>\n";
            }
        } else if (command.substr(0, 3) == "mv ") {
            istringstream iss(command.substr(3));
            string source, destination;
            iss >> source >> destination;
            if (iss && !destination.empty()) {
                moveFile(currentPath / source, currentPath / destination);
            } else {
                cout << "Usage: mv <source> <destination>\n";
            }
        } else if (command.substr(0, 3) == "cd ") {
            changeDirectory(currentPath, command.substr(3));
        } else {
            cout << "Unknown command. Type 'help' for assistance.\n";
        }
    }
    return 0;
}
