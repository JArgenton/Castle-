
#include "Factories/FontsFactory.hpp"

namespace Factories
{
    namespace flyweight
    {

        FontsFactory::FontsFactory()
        {
        }

        FontsFactory::~FontsFactory()
        {
            for (auto &MapElement : FlyweightMap)
            {
                delete MapElement.second;
            }
        }

        sf::Font *FontsFactory::getResource(const std::string &filepath)
        {
            auto iterator = FlyweightMap.find(filepath);
            if (iterator != FlyweightMap.end())
            {
                return (iterator->second);
            }

            sf::Font *flyweight = new sf::Font;
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
