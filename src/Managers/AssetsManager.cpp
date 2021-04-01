#include "AssetsManager.hh"

AssetsManager::AssetsManager()
{
}

std::map<std::string, sf::Texture *> AssetsManager::textures;
std::map<std::string, sf::Font *> AssetsManager::fonts;

// Get Texture by Name
sf::Texture *AssetsManager::getTexture(std::string name)
{
    if (textures.find(name) != textures.end())
    {
        // Log(true, false, name, "texture");
        return textures[name];
    }
    else
    {
        Log(false, false, name, "texture");
        return NULL;
    }
}

// Get Font by Name
sf::Font *AssetsManager::getFont(std::string name)
{
    if (fonts.find(name) != fonts.end())
    {
        // Log(true, false, name, "font"); TODO check if okay
        return fonts[name];
    }
    else
    {
        Log(false, false, name, "font");
        return NULL;
    }
}

sf::Texture *AssetsManager::loadTexture(std::string name, std::string path)
{
    sf::Texture *texture = new sf::Texture();

    if (texture->loadFromFile(path))
    {
        textures[name] = texture;
        Log(true, true, name, "texture");
        return textures[name];
    }
    else
    {
        delete texture;
        Log(false, true, name, "texture");
        return NULL;
    }
}

sf::Font *AssetsManager::loadFont(std::string name, std::string path)
{
    sf::Font *font = new sf::Font();

    if (font->loadFromFile(path))
    {
        fonts[name] = font;
        Log(true, true, name, "font");
        return fonts[name];
    }
    else
    {
        delete font;
        Log(false, true, name, "font");
        return NULL;
    }
}

AssetsManager::~AssetsManager()
{

    // Delete all of the textures
    sf::Texture *texture;
    std::map<std::string, sf::Texture *>::iterator iter = textures.begin();
    while (iter != textures.end())
    {
        texture = iter->second;
        delete texture;
        iter++;
    }
    // Delete all of the fonts
    sf::Font *font;
    std::map<std::string, sf::Font *>::iterator iterF = fonts.begin();
    while (iterF != fonts.end())
    {
        font = iterF->second;
        delete font;
        iterF++;
    }
}

void AssetsManager::Log(bool isSuccess, bool isLoad, std::string name, std::string type)
{
    std::string success = isSuccess ? "[INFO] Successfully " : "[ERROR] Failed to ";
    std::string getOrLoad = isLoad ? "load " : "get ";
    std::cout << success << getOrLoad << "> " << name << " < "
              << type << "." << std::endl;
}
