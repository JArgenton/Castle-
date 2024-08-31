#include "Managers/GraphicManager.hpp"

namespace GraphicalElements
{
    class AnimationFrame
    {
    private:
        const int frameCount;   // quantidade de frames que serao passados, constante.
        int currentFrame;       // frame da ultima atualizaçao
        sf::Texture *texture;   // conjunto de frames salvos em uma textura
        sf::IntRect rectSize;   // objeto com metodos para controlar area, utilizado para definir as partes da textura que representam cada frame
        float totalTime;        // timer para controlar passagem do tempo
        const float switchTime; // tempo para trocar de frame
    public:
        AnimationFrame(string path, const int _FrameCount, float _switchTime);
        ~AnimationFrame();
        void update(float dt, bool facingLeft);
        void reset();
        sf::IntRect getSize();
        sf::Texture *getTexture() const;
    };

}
