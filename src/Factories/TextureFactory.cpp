#include "Factories/TextureFactory.hpp"

namespace flyweight
{

    Flyweight::Flyweight()
    {
    }

    Flyweight::~Flyweight()
    {
        for (auto &MapElement : FlyweightMap)
        {
            delete MapElement.second;
        }
    }

    sf::Texture *Flyweight::getResource(const std::string &filepath)
    {
        auto iterator = FlyweightMap.find(filepath);
        if (iterator != FlyweightMap.end())
        {
            return (iterator->second);
        }

        sf::Texture *flyweight = new sf::Texture;
        if (!flyweight->loadFromFile(filepath))
        {
            delete flyweight;
            printf("erro carregando textura");

            exit(1);
        }
        FlyweightMap.insert(std::make_pair(filepath, flyweight));
        return flyweight;
    }
}