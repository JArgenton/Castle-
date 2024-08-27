#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include "Factories/EntityFactory.hpp"

namespace Factories
{
    namespace flyweight
    {
        class FontsFactory // padrao de projeto Flyweight junto ao padrao de projeto Factory
        {
        private:
            std::unordered_map<std::string, sf::Font *> FlyweightMap; // Map of textures

        public:
            FontsFactory();
            ~FontsFactory();
            sf::Font *getResource(const std::string &filepath);
        };
    }
} // namespace Factories
