#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "controls.h"

void parseConfig(const std::string& filename) {
    std::ifstream configFile(filename);
    if (!configFile.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(configFile, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t delimiterPos = line.find("->");
        if (delimiterPos == std::string::npos) continue;
        char key = line[0];
        std::string action = line.substr(delimiterPos + 2);
        size_t firstNonSpace = action.find_first_not_of(" ");
        if (firstNonSpace != std::string::npos) {
            action = action.substr(firstNonSpace);
        }
        key = toupper(key);
        hotkeyActions[key] = action;
        std::cout << "Config is working at " << hotkeyActions[key] << " " << key << "\n";
    }
    configFile.close();
}