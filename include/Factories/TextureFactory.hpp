#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

namespace flyweight
{
    class Flyweight // padrao de projeto Flyweight junto ao padrao de projeto Factory
    {
    private:
        std::unordered_map<std::string, sf::Texture *> FlyweightMap; // Map of textures

    public:
        Flyweight();
        ~Flyweight();
        sf::Texture *getResource(const std::string &filepath);
    };
}