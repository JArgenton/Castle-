#include "Factories/TextureFactory.hpp"

namespace Factories
{
    namespace flyweight
    {

        TextureFactory::TextureFactory()
        {
        }

        TextureFactory::~TextureFactory()
        {
            for (auto &MapElement : FlyweightMap)
            {
                delete MapElement.second;
            }
        }

        sf::Texture *TextureFactory::getResource(const std::string &filepath)
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
} // namespace Factories
