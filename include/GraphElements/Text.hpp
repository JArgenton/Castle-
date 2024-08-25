#pragma once

#include "Managers/GraphicManager.hpp"

#include <SFML/Graphics.hpp>
#include <string>

#define FONT_PATH "assets/Viking.ttf"

namespace GraphicalElements
{

    enum TextAlignment
    {
        left,
        center,
        right
    };

    class Text
    {
    private:
        std::string info;

        sf::Text text;

        static Managers::Graphics *pGraphicM;

    public:
        Text(TupleF = TupleF(0, 0), string info = "", const char *path = FONT_PATH);

        ~Text();

        void setTextInfo(std::string info);

        void setPosition(TupleF position);

        void setTextColor(const unsigned int R, const unsigned int G, const unsigned int B);

        void setFontSize(const unsigned int size);

        void setTextAlignment(TextAlignment option);

        TupleF getSize() const;

        void render();

        string getInfo() const;

        TupleF getPosition() const;
    };

} // namespace GraphicalElements