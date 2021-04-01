#ifndef TEXTUREMANAGER_HH
#define TEXTUREMANAGER_HH

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class AssetsManager
{
private:
    static std::map<std::string, sf::Texture *> textures;
    static std::map<std::string, sf::Font *> fonts;
    static void Log(bool isSuccess, bool isLoad, std::string name, std::string type);
    AssetsManager();

public:
    ~AssetsManager();
    static sf::Texture *getTexture(std::string name);
    static sf::Font *getFont(std::string name);
    static sf::Texture *loadTexture(std::string name, std::string path);
    static sf::Font *loadFont(std::string name, std::string path);
};

#endif
