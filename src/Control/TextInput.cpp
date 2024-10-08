#include "Control/TextInput.hpp"

#include <iostream>

namespace Control
/*CODIGO INSPIRADO NA IMPLEMENTAÇAO DO MONITOR BURDA*/
{

    TextInput::TextInput() : Observer() {}

    TextInput::~TextInput() {}

    void TextInput::notifyPressed(std::string key)
    {
        if (key == "Enter" ||
            key == "Right" ||
            key == "Left" ||
            key == "Up" ||
            key == "Down" ||
            key == "Escape" ||
            key == "Control" ||
            key == "Shift" ||
            key == "RControl" ||
            key == "RShift" ||
            key == "Tab" ||
            key == "Unknown")
        {
            return;
        }

        if (key == "BackSpace")
        {
            if (text.size() > 0)
                text.pop_back();
        }

        else if (key == "Space")
        {
            text += " ";
        }

        else
        {
            text += key;
        }
    }

    void TextInput::notifyReleased(std::string key) {}

    std::string TextInput::getString() const
    {
        return text;
    }

    void TextInput::reset()
    {
        text = "";
    }

} // namespace Control