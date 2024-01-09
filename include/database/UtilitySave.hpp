#ifndef UTILITY_SAVE_HPP
#define UTILITY_SAVE_HPP

#include <UserSession.hpp>
#include <PlayerNode.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <filesystem>

class UtilitySave {
public:
    static bool CreateDirectoryRecursive(const std::string &dirName, std::error_code &err);
    static void DeleteDirContent(const std::string& dirPath);
    static bool sortDir(const std::string& filenameA, const std::string& filenameB);
};

#endif