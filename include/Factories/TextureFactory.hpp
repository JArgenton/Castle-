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
        class TextureFactory // padrao de projeto TextureFactory junto ao padrao de projeto Factory
        {
        private:
            std::unordered_map<std::string, sf::Texture *> FlyweightMap; // Map of textures

        public:
            TextureFactory();
            ~TextureFactory();
            sf::Texture *getResource(const std::string &filepath);
        };
    }
} // namespace Factories
