#include <UtilitySave.hpp>

bool UtilitySave::CreateDirectoryRecursive(const std::string &dirName, std::error_code &err)
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

bool UtilitySave::sortDir(const std::string &filenameA, const std::string &filenameB)
{
    int a = std::stoi(filenameA.substr(1, 2));
    int b = std::stoi(filenameB.substr(1, 2));
    return (a < b);
}

void UtilitySave::DeleteDirContent(const std::string &dirPath)
{
    if (std::filesystem::exists(dirPath)) {
        for (const auto &entry : std::filesystem::directory_iterator(dirPath))
            std::filesystem::remove_all(entry.path());
        std::filesystem::remove(dirPath);
    } else {
        std::cerr << dirPath + "not found.\n";
    }
}