
#include "States/Game.hpp"

int main()
{
    time_t t;
    srand((unsigned)time(&t));

    States::Game j;
    j.exec();

    return 0;
}