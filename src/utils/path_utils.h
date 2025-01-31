// Declarations for path-related utilities

#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include <vector>
#include <filesystem>

std::vector<std::filesystem::path> parsePathEnv();
bool isExternalCommand(const std::string &cmd);
std::string findExecutable(const std::string &cmd);

#endif
