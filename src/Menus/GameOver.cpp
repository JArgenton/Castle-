#include "Menus/GameOver.hpp"

#define BACKGROUND_PATH "assets/BackGrounds/GameOver.jpeg"
#define LEADERBOARD_PATH "saves/LeaderSave.txt"

#include <fstream>
#include <map>

namespace Menus
{

    GameOver::GameOver(States::StateMachine *pSM, States::Level *plvl) : Menu(),
                                                                         State(pSM, States::stateID::GAMEOVER),
                                                                         title(TupleF(0, 0), "GAME OVER"),
                                                                         name(TupleF(0, 0), ""),
                                                                         nameLabel(TupleF(0, 0), "Name:"),
                                                                         input(),
                                                                         points(),
                                                                         pointsToIncrement(0),
                                                                         plvl(plvl)
    {
        Managers::Graphics *GM = Managers::Graphics::get_instance();

        GraphicalElements::Button *bt = NULL;

        bt = new GraphicalElements::Button(TupleF(GM->getWindowSize().x / 2.0f - 200, GM->getWindowSize().y - 100), "PLAY AGAIN");
        bt->select(true);
        vectorOfButtons.push_back(bt);

        bt = new GraphicalElements::Button(TupleF(GM->getWindowSize().x / 2.0f + 200, GM->getWindowSize().y - 100), "MAIN MENU");
        vectorOfButtons.push_back(bt);

        selected = 0;
        max = 1;

        title.setPosition(TupleF(GM->getWindowSize().x / 2.0f, GM->getWindowSize().y / 2 - 200));
        title.setFontSize(100);
        title.setTextAlignment(GraphicalElements::TextAlignment::center);
        title.setTextColor(177.6, 168.2, 144.3);

        points.setPosition(TupleF(GM->getWindowSize().x / 2.0f - 100, GM->getWindowSize().y / 2));
        points.setFontSize(40);
        points.setTextColor(177.6, 168.2, 144.3);
        points.setTextAlignment(GraphicalElements::TextAlignment::center);

        nameLabel.setPosition(TupleF(GM->getWindowSize().x / 2.0f - 200, GM->getWindowSize().y / 2 + 100));
        nameLabel.setFontSize(40);
        nameLabel.setTextColor(177.6, 168.2, 144.3);
        nameLabel.setTextAlignment(GraphicalElements::TextAlignment::center);

        name.setPosition(TupleF(GM->getWindowSize().x / 2.0f + nameLabel.getSize().x - 200, GM->getWindowSize().y / 2 + 100 - nameLabel.getSize().y));
        name.setFontSize(40);
        name.setTextColor(177.6, 168.2, 144.3);
        name.setTextAlignment(GraphicalElements::TextAlignment::center);
    }

    GameOver::~GameOver() {}

    void GameOver::update(float dt)
    {
        name.setTextInfo(input.getString());
        if (pointsToIncrement < plvl->getPlayerPoints())
            pointsToIncrement += 10;
        points.setTextInfo("Points: " + std::to_string(plvl->getPlayerPoints()));
    }

    /* Menu operation to render all it's objects. */
    void GameOver::render()
    {
        updateView();
        back.render();
        for (it = vectorOfButtons.begin(); it != vectorOfButtons.end(); ++it)
            (*it)->render();

        title.render();
        points.render();
        name.render();
        nameLabel.render();
    }

    void GameOver::exec()
    {
        if (active)
        {
            active = false;
            switch (selected)
            {
            case 0:
                changeState(States::stateID::FASE);
                break;
            case 1:
                changeState(States::stateID::MAINMENU);
                break;
            default:
                break;
            }

            writeIntoFile();
        }
    }

    void GameOver::resetState()
    {
        for (it = vectorOfButtons.begin(); it != vectorOfButtons.end(); ++it)
            (*it)->select(false);
        selected = 0;
        vectorOfButtons[selected]->select(true);
        active = true;
        input.reset();
    }

    void GameOver::writeIntoFile()
    {
        int playerPoints = plvl->getPlayerPoints();

        /* ================================= Reading File ================================= */
        std::ifstream readFile;

        readFile.open(LEADERBOARD_PATH, std::ios::in);

        std::multimap<int, std::string> pointsAndNamesMap;

        if (readFile)
        {

            int points;
            std::string name;
            std::string pointsString;

            for (int i = 0; i < 10; i++)
            {
                std::getline(readFile, pointsString);
                std::getline(readFile, name);
                if (pointsString.length() > 0)
                    pointsAndNamesMap.insert(std::pair<int, std::string>(std::stoi(pointsString), name));
            }

            readFile.close();
        }

        /* ================================= Writing File ================================= */
        if (playerPoints != 0 && input.getString().length() > 1)
            pointsAndNamesMap.insert(std::pair<int, std::string>(playerPoints, input.getString()));

        std::ofstream writeFile;

        writeFile.open(LEADERBOARD_PATH, std::ios::out | std::ios::trunc);

        if (!writeFile)
        {
            std::cout << "ERROR writing to file on GameOver" << std::endl;
            exit(1);
        }

        while (pointsAndNamesMap.size() > 10)
            pointsAndNamesMap.erase(pointsAndNamesMap.begin());

        for (auto itr = pointsAndNamesMap.rbegin(); itr != pointsAndNamesMap.rend(); ++itr)
        {
            writeFile << (*itr).first << std::endl;
            writeFile << (*itr).second << std::endl;
        }

        writeFile.close();
    }

}