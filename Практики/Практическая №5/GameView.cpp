#include "GameView.h"

GameView *NewGameView(const sf::Vector2i &windowSize)
{
    GameView *view = new GameView();
    view->window.create(sf::VideoMode(windowSize.x, windowSize.y), "Game");
    view->window.setFramerateLimit(60);
    view->windowSize = windowSize;
    view->camera.reset(sf::FloatRect(0, 0, float(windowSize.x), float(windowSize.y)));
    return view;
}

void EnterGameLoop(GameView &view, OnUpdate onUpdate, OnDraw onDraw, void *pData)
{
    while (view.window.isOpen())
    {
        sf::Event event;
        while (view.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                view.window.close();
        }

        float deltaSec = view.clock.restart().asSeconds();

        if (onUpdate)
        {
            onUpdate(pData, view, deltaSec);
        }

        view.window.clear();
        
        if (onDraw)
        {
            onDraw(pData, view);
        }

        view.window.display();
    }
}

void SetCameraCenter(GameView &view, const sf::Vector2f &center)
{
    view.camera.setCenter(center);
    view.window.setView(view.camera);
}

void DestroyGameView(GameView *&pView)
{
    if (pView)
    {
        pView->window.close();
        delete pView;
        pView = nullptr;
    }
}