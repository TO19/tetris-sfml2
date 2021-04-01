#ifndef TXTFILEMANAGER
#define TXTFILEMANAGER
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

class TxtFileManager
{
private:
    TxtFileManager();
    static TxtFileManager *_instance;

public:
    static void writeToFile(std::string, std::string);
    static std::list<std::pair<std::string, int>> readScoreboardFile();
    static TxtFileManager *GetInstance();
    virtual ~TxtFileManager();
    TxtFileManager(TxtFileManager const &) = delete;
    TxtFileManager &operator=(TxtFileManager const &) = delete;
};

#endif /* TXTFILEMANAGER */