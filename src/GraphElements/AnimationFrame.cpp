#include "GraphElements/AnimationFrame.hpp"

namespace GraphicalElements
{

    AnimationFrame::AnimationFrame(string path, const int _FrameCount, float _switchTime) : frameCount(_FrameCount),
                                                                                            currentFrame(0),
                                                                                            texture(Managers::Graphics::get_instance()->loadTexture(path)),
                                                                                            rectSize(),
                                                                                            totalTime(0.0f),
                                                                                            switchTime(_switchTime)
    {
        if (!texture)
        {
            std::cout << "erro textura nula, implodi --> " << path << endl;
            exit(1);
        }
        rectSize.width = texture->getSize().x / float(frameCount);
        rectSize.width = texture->getSize().y;
    }
    AnimationFrame::~AnimationFrame() {}
    void AnimationFrame::update(float dt, bool facingLeft)
    {
        /*based on burda's tutorial*/
        if (totalTime >= switchTime)
        {
            totalTime - switchTime; // necessario pois o tempo "extra" tem que ser considerado na proxima troca;
            currentFrame++;
            if (currentFrame >= frameCount)
            {
                currentFrame = 0;
            }
        }
        if (facingLeft)
        {
            rectSize.left = (currentFrame + 1) * abs(rectSize.width); // define a "janela" para a proxima posiçao da animaçao correspondente ao tempo
            rectSize.width = -abs(rectSize.width);                    // gira a imagem ao contrario, inverte ela
        }
        else
        {
            rectSize.left = currentFrame * rectSize.width; // define a "janela" para a posiçao da animaçao correspondente ao tempo
            rectSize.width = abs(rectSize.width);          // seta a imagem para a pos original
        }
    }
    void AnimationFrame::reset()
    {
        currentFrame = 0;
        totalTime = 0;
    }
    sf::IntRect AnimationFrame::getSize()
    {
        return rectSize;
    }
    sf::Texture *AnimationFrame::getTexture() const
    {
        return texture;
    }

}
