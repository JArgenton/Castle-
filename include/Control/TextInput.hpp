#pragma once

#include "Control/Observer.hpp"

namespace Control
{

    // Inspirado na aplicação do monitor Burda

    class TextInput : public Observer
    {
    private:
        std::string text;

    public:
        TextInput();

        ~TextInput();

        void notifyPressed(std::string key);

        void notifyReleased(std::string key);

        std::string getString() const;

        void reset();
    };

} // namespace Control