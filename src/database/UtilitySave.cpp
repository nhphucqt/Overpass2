#include <UtilitySave.hpp>

bool CreateDirectoryRecursive(const std::string &dirName, std::error_code &err)
{
    err.clear();
    if (!std::filesystem::create_directories(dirName, err))
    {
        if (std::filesystem::exists(dirName))
        {
            // The folder already exists:
            err.clear();
            return true;
        }
        return false;
    }
    return true;
}

bool sortDir(const std::string &filenameA, const std::string &filenameB)
{
    int a = std::stoi(filenameA.substr(1, 2));
    int b = std::stoi(filenameB.substr(1, 2));
    return (a < b);
}

void DeleteDirContent(const std::string &dirPath)
{
    for (const auto &entry : std::filesystem::directory_iterator(dirPath))
    {
        std::filesystem::remove_all(entry.path());
    }
}