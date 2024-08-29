
#include "States/Jogo.hpp"

int main()

{
    time_t t;
    srand((unsigned)time(&t));

    States::Jogo j;
    j.exec();

    return 0;
}