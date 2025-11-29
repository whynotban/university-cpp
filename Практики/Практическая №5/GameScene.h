#pragma once
#include "TmxLevel.h"
#include <vector>

struct GameView;

struct GameScene
{
    TmxLevel level;
    TmxObject player;
    std::vector<TmxObject> enemies;
    std::vector<TmxObject> coins;
    std::vector<TmxObject> blocks;
    std::vector<TmxObject> secrets;
    std::vector<TmxObject> traps;

    std::vector<float> enemySpeeds;

    sf::Vector2f startPosition;
    sf::Vector2f velocity;
    float currentJumpSpeed;
    float currentMoveSpeed;
};

GameScene* NewGameScene();
void UpdateGameScene(void* pData, GameView& view, float deltaSec);
void DrawGameScene(void* pData, GameView& view);
void DestroyGameScene(GameScene*& pScene);