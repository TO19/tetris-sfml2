#include "TxtFileManager.hh"

TxtFileManager::TxtFileManager(){};
TxtFileManager::~TxtFileManager(){};
TxtFileManager *TxtFileManager::_instance = 0;

TxtFileManager *TxtFileManager::GetInstance()
{
    if (_instance == 0)
    {
        _instance = new TxtFileManager();
    }

    return _instance;
}

void TxtFileManager::writeToFile(std::string fileName, std::string stringToWrite)
{
    std::ofstream file(fileName, std::ios_base::app | std::ios_base::out);
    file << std::endl
         << stringToWrite << std::endl;
}

std::list<std::pair<std::string, int>> TxtFileManager::readScoreboardFile()
{
    std::list<std::pair<std::string, int>> list;
    std::ifstream file;
    file.open("./Assets/score.txt");

    while (!file.eof())
    {
        std::string name;
        int score;
        file >> name >> score;

        if (name != "" && std::to_string(score) != "") { // Last score was being printed twice for some reasons
            list.push_back({name, score});
        }
    }

    file.close();

    list.sort([](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return a.second > b.second;
    });

    return list;
}
