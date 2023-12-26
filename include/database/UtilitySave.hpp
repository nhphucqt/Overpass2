#ifndef UTILITY_SAVE_HPP
#define UTILITY_SAVE_HPP

#include <UserSession.hpp>
#include <PlayerNode.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <filesystem>

bool CreateDirectoryRecursive(const std::string &dirName, std::error_code &err);
void DeleteDirContent(const std::string& dirPath);
bool sortDir(const std::string& filenameA, const std::string& filenameB);

#endif