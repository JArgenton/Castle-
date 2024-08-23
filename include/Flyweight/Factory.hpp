#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using namespace std;
namespace flyweight
{
    template <typename Resource>
    class Flyweight
    {
    private:
        unordered_map<string, Resource *> FlyweightMap; // Mapa de texturas (ED2), carregar, organizar as texturas utilizadas

    public:
        Flyweight();
        ~Flyweight();
        Resource *getResource(const string &filepath);
    };

    template <typename Resource>
    Flyweight<Resource>::Flyweight()
    {
    }
    template <typename Resource>
    Flyweight<Resource>::~Flyweight()
    {
        for (auto &MapElement : FlyweightMap)
        {
            delete MapElement.second;
        }
    }

    template <typename Resource>
    Resource *Flyweight<Resource>::getResource(const string &filepath)
    {
        auto iterator = FlyweightMap.find(filepath);
        if (iterator != FlyweightMap.end())
        {
            return (iterator->second);
        }

        Resource *flyweight = new Resource;
        // verifica se o filepath corresponde a uma fonte, caso nao encontre-a, delete o obj e sai do programa (erro)
        if (!flyweight->loadFromFile(filepath))
        {
            delete flyweight;
            std::cout << "ERROR LOADING FILE" << filepath << std::endl;
            exit(1);
        }
        FlyweightMap.insert(std::make_pair(filepath, flyweight));
        return flyweight;
    }

}