#include "GraphElements/Text.hpp"

using namespace Managers;

#define TEXT_SIZE 24

namespace GraphicalElements
{

    Managers::Graphics *Text::pGraphicM = Managers::Graphics::get_instance();

    Text::Text(TupleF position, string info, const char *path) : info(info)
    {
        text.setString(info);

        text.setFont(*pGraphicM->loadFont(path));

        text.setCharacterSize(TEXT_SIZE);

        setTextAlignment(TextAlignment::left);

        text.setPosition(sf::Vector2f(position.x, position.y));

        text.setFillColor(sf::Color::White);
    }

    Text::~Text() {}

    void Text::setTextInfo(std::string info)
    {
        this->info = info;
        text.setString(this->info);
    }

    void Text::setPosition(TupleF position)
    {
        text.setPosition(sf::Vector2f(position.x, position.y));
    }

    void Text::setTextColor(const unsigned int R, const unsigned int G, const unsigned int B)
    {
        text.setFillColor(sf::Color(R, G, B));
    }

    void Text::setFontSize(const unsigned int size)
    {
        text.setCharacterSize(size);
    }

    void Text::setTextAlignment(TextAlignment option)
    {
        switch (option)
        {
        case TextAlignment::left:
            text.setOrigin(0, 0);
            break;
        case TextAlignment::center:
            text.setOrigin(getSize().x / 2, getSize().y);
            break;
        case TextAlignment::right:
            text.setOrigin(getSize().x, 0);
            break;
        default:
            text.setOrigin(getSize().x / 2, getSize().y);
            break;
        }
    }

    TupleF Text::getSize() const
    {
        sf::FloatRect textRect = text.getLocalBounds();
        return TupleF(textRect.width, textRect.height);
    }

    void Text::render()
    {
        pGraphicM->render(&text);
    }

    std::string Text::getInfo() const
    {
        return info;
    }

    TupleF Text::getPosition() const
    {
        return TupleF(text.getPosition().x, text.getPosition().y);
    }

} // namespace GraphicalElements