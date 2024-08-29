#include "Menus/LeaderBoard.hpp"
#include <fstream>

#define FONT_PATH "assets/Viking.ttf"
#define BG_PATH "assets/BackGrounds/leaderBG.jpeg"
#define LEADERBOARD_SAVES "assets/Saves/LeaderSave.txt"

namespace Menus
{
    LeaderBoard::LeaderBoard(States::StateMachine *pStateMachine) : Menu(),
                                                                    State(pStateMachine, States::stateID::LEARDERBOARD)
    {
        Managers::Graphics *GM = Managers::Graphics::get_instance();
        GraphicalElements::Button *bt = NULL;

        bt = new GraphicalElements::Button(TupleF(GM->getWindowSize().x / 2.0f, GM->getWindowSize().y - 150), "RETURN");
        bt->select(true);
        vectorOfButtons.push_back(bt);

        max = 0;
    }

    LeaderBoard::~LeaderBoard()
    {
    }

    void LeaderBoard::update(float dt)
    {
        active = true;
    }

    void LeaderBoard::render()
    {
        updateView();
        back.render();
        for (it = vectorOfButtons.begin(); it != vectorOfButtons.end(); ++it)
            (*it)->render();

        for (iter = TotalPoints.begin(); iter != TotalPoints.end(); ++iter)
            (*iter)->render();
    }

    void LeaderBoard::resetState()
    {
        vectorOfButtons[0]->select(true);
        for (iter = TotalPoints.begin(); iter != TotalPoints.end(); ++iter)
            delete (*iter);
        TotalPoints.clear();
        build();
    }
    void LeaderBoard::execute()
    {
        if (active)
        {
            active = false;
            changeState(States::stateID::MAINMENU);
        }
    }
    void LeaderBoard::build()
    {
        std::ifstream file;

        // abre em modo binario e apenas lê o arquivo incapaz de editar
        file.open(LEADERBOARD_SAVES, std::ios::binary | std::ios::in);

        // abre ou cria o arquivo, apaga arquivo original para garantir que inicie vazio
        if (!file)
        {
            std::ofstream writeFile(LEADERBOARD_SAVES, std::ios::out | std::ios::trunc);
            writeFile.close();
        }

        int points;
        std::string name;
        std::string text;
        std::string pointsString;

        GraphicalElements::Text *txt;

        for (int i = 0; i < 10; i++)
        {
            std::string name;
            std::string pointsString;

            std::getline(file, pointsString);
            std::getline(file, name);

            // Criar textString com formatação
            std::string textString = std::to_string(i + 1) + " - " + name + " ";

            if (!pointsString.empty())
            {
                // Converter pointsString para inteiro
                int points = std::stoi(pointsString);

                // Formatar a string com valores separados por magnitude
                std::string formattedPointsString;
                for (int magnitude : {1000000, 100000, 10000, 1000, 100, 10, 1})
                {
                    formattedPointsString += std::to_string(points / magnitude);
                    points %= magnitude;
                }

                pointsString = formattedPointsString;
            }

            while (text.length() + pointsString.length() < 50)
            {
                text += "_";
            }

            txt = new GraphicalElements::Text(TupleF(Managers::Graphics::get_instance()->getWindowSize().x / 2.0f, 100 + 40 * i), text + pointsString, FONT_PATH);
            txt->setFontSize(48);
            txt->setTextAlignment(GraphicalElements::TextAlignment::center);
            txt->setTextColor(177.6, 168.2, 144.3);
            TotalPoints.push_back(txt);
        }
        file.close();
    }

} // namespace Menus
