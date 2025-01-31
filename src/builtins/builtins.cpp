#include "../utils/path_utils.h" 
#include "builtins.h"
#include <unordered_set>
#include <filesystem>
#include <sstream>
#include <iostream>
#include <cstdlib>


namespace fs = std::filesystem;

std::unordered_set<std::string> builtins = {"echo", "exit", "type" , "pwd" , "cd"};

std::string handleEcho(const std::string& args) {
    return args;
}

std::string handleExit(const std::string&) {
    exit(0);
}

std::string handleType(const std::string& args) {
    // Use parsePathEnv to get directories from PATH
    auto directories = parsePathEnv();

    // Check if the argument is a built-in command
    if (builtins.find(args) != builtins.end()) {
        return args + " is a shell builtin";
    }

    else{

        // Search for the command in each directory
        for (const auto& dir : directories) {
            fs::path p = dir / args;
            if (fs::exists(p)) {
                return args + " is " + p.string();
            }
        }

    }

    return args + ": not found";
}

std::string handlePWD(const std::string&) {
    return fs::current_path().string();
}

std::string handleCD(const std::string& args) {
    
    if (args.empty()) {
        return ""; 
    }

    if (args == "~" || args == "$HOME" || args == "~/" || args == "-") {
        fs::current_path(std::getenv("HOME")); // Change directory to home
        return "";
    }

    fs::path targetPath = fs::absolute(args); // Convert to absolute path
    if (fs::exists(targetPath) && fs::is_directory(targetPath)) {
        fs::current_path(targetPath); // Change directory
        return "";
    }

    return "cd: " + args + ": No such file or directory"; 
}

