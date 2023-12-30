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
        std::filesystem::remove_all(entry.path());
    std::filesystem::remove(dirPath);
}

std::vector<std::string> getSortedFileNames(const std::string& filepath)
{
    std::vector<std::string> loadFiles;
	for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(filepath))
	{
		std::string dir = dirEntry.path().filename();
		if (dir != "player.dat" && dir != "lane.txt")
			loadFiles.push_back(dir);
	}
	std::sort(loadFiles.begin(), loadFiles.end(), sortDir);
    return loadFiles;
}