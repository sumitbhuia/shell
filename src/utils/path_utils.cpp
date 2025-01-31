// Path-related utilities (e.g., PATH parsing)

#include "path_utils.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <filesystem>
#include <sstream>

std::vector<std::filesystem::path> parsePathEnv()
{
    std::vector<std::filesystem::path> directories;
    const char *pathEnv = getenv("PATH");
    if (!pathEnv)
        return directories;

    std::stringstream ss(pathEnv);
    std::string path;
    while (std::getline(ss, path, ':'))
    {
        directories.push_back(std::filesystem::path(path));
    }
    return directories;
}

bool isExternalCommand(const std::string &cmd)
{
    auto directories = parsePathEnv();
    for (const auto &dir : directories)
    {
        std::filesystem::path execPath = dir / cmd;
        if (std::filesystem::exists(execPath) && access(execPath.c_str(), X_OK) == 0)
        {
            return true; // Command exists and is executable
        }
    }
    return false;
}

std::string findExecutable(const std::string &cmd)
{
    auto directories = parsePathEnv();
    for (const auto &dir : directories)
    {
        std::filesystem::path execPath = dir / cmd;
        if (std::filesystem::exists(execPath) && access(execPath.c_str(), X_OK) == 0)
        {
            return execPath.string();
        }
    }
    return ""; // Command not found
}
