

void Level::clearState()
{
    pControl.reset();

    movingEntities.cleanList(); // Limpar a lista de entidades em movimento
    obstacles.cleanList();      // Limpar a lista de obstáculos

    levelEnded = false;
    player1Points = 0;
    player2Points = 0;

    // Resetar referências aos jogadores
    Player1 = nullptr;
    Player2 = nullptr;
}