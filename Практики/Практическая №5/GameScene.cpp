#include "GameScene.h"
#include "GameView.h"
#include <iostream>

GameScene* NewGameScene()
{
    GameScene* scene = new GameScene();

    scene->level.LoadFromFile("res/platformer.tmx");

    scene->player = scene->level.GetFirstObject("player");
    scene->coins = scene->level.GetAllObjects("coin");
    scene->enemies = scene->level.GetAllObjects("enemy");
    scene->blocks = scene->level.GetAllObjects("block");
    scene->secrets = scene->level.GetAllObjects("secret");
    scene->traps = scene->level.GetAllObjects("trap");

    for (size_t i = 0; i < scene->enemies.size(); ++i) {
        scene->enemySpeeds.push_back(100.f);
    }

    scene->startPosition = scene->player.sprite.getPosition();
    scene->velocity = { 0.f, 0.f };
    scene->currentJumpSpeed = 350.f;
    scene->currentMoveSpeed = 200.f;

    return scene;
}

void UpdateGameScene(void* pData, GameView& view, float deltaSec)
{
    if (deltaSec > 0.05f) deltaSec = 0.05f;

    GameScene* pLogic = (GameScene*)pData;

    float gravity = 1000.f;

    pLogic->velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        pLogic->velocity.x = -pLogic->currentMoveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        pLogic->velocity.x = pLogic->currentMoveSpeed;

    sf::Vector2f movementX;
    movementX.x = pLogic->velocity.x * deltaSec;
    movementX.y = 0.f;

    pLogic->player.sprite.move(movementX);

    sf::FloatRect playerRect = pLogic->player.sprite.getGlobalBounds();
    for (const auto& block : pLogic->blocks) {
        if (playerRect.intersects(block.rect)) {
            pLogic->player.sprite.move(-movementX);
            break;
        }
    }

    pLogic->velocity.y += gravity * deltaSec;

    sf::Vector2f movementY;
    movementY.x = 0.f;
    movementY.y = pLogic->velocity.y * deltaSec;

    pLogic->player.sprite.move(movementY);

    bool onGround = false;
    playerRect = pLogic->player.sprite.getGlobalBounds();

    for (const auto& block : pLogic->blocks) {
        if (playerRect.intersects(block.rect)) {
            pLogic->player.sprite.move(-movementY);

            if (pLogic->velocity.y > 0) {
                onGround = true;
                pLogic->velocity.y = 0;
            }
            else {
                pLogic->velocity.y = 0;
            }
            break;
        }
    }

    if (onGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        pLogic->velocity.y = -pLogic->currentJumpSpeed;
    }

    for (size_t i = 0; i < pLogic->enemies.size(); ++i) {
        float enemyMove = pLogic->enemySpeeds[i] * deltaSec;
        pLogic->enemies[i].sprite.move(enemyMove, 0);

        sf::FloatRect enemyRect = pLogic->enemies[i].sprite.getGlobalBounds();
        bool hitWall = false;

        for (const auto& block : pLogic->blocks) {
            if (enemyRect.intersects(block.rect)) {
                hitWall = true;
                break;
            }
        }

        if (hitWall) {
            pLogic->enemies[i].sprite.move(-enemyMove, 0);
            pLogic->enemySpeeds[i] = -pLogic->enemySpeeds[i];
        }
    }

    for (auto it = pLogic->coins.begin(); it != pLogic->coins.end();) {
        if (pLogic->player.sprite.getGlobalBounds().intersects(it->sprite.getGlobalBounds())) {
            it = pLogic->coins.erase(it);
        }
        else {
            ++it;
        }
    }

    bool secretFound = false;
    for (const auto& secret : pLogic->secrets) {
        sf::FloatRect secretBounds = secret.sprite.getGlobalBounds();
        if (secretBounds.width == 0) secretBounds = secret.rect;

        if (pLogic->player.sprite.getGlobalBounds().intersects(secretBounds)) {
            secretFound = true;
            break;
        }
    }

    if (secretFound) {
        pLogic->currentJumpSpeed = 550.f;
        pLogic->currentMoveSpeed = 300.f;
        pLogic->secrets.clear();
    }

    for (const auto& enemy : pLogic->enemies) {
        if (pLogic->player.sprite.getGlobalBounds().intersects(enemy.sprite.getGlobalBounds())) {
            pLogic->player.sprite.setPosition(pLogic->startPosition);
            pLogic->velocity = { 0.f, 0.f };
            pLogic->currentJumpSpeed = 350.f;
            pLogic->currentMoveSpeed = 200.f;
            pLogic->secrets = pLogic->level.GetAllObjects("secret");
        }
    }

    for (const auto& trap : pLogic->traps) {
        sf::FloatRect trapBounds = trap.sprite.getGlobalBounds();
        if (trapBounds.width == 0) trapBounds = trap.rect;

        if (pLogic->player.sprite.getGlobalBounds().intersects(trapBounds)) {
            pLogic->player.sprite.setPosition(pLogic->startPosition);
            pLogic->velocity = { 0.f, 0.f };
            pLogic->currentJumpSpeed = 350.f;
            pLogic->currentMoveSpeed = 200.f;
            pLogic->secrets = pLogic->level.GetAllObjects("secret");
        }
    }

    SetCameraCenter(view, pLogic->player.sprite.getPosition());
}

void DrawGameScene(void* pData, GameView& view)
{
    GameScene* pLogic = (GameScene*)pData;

    pLogic->level.Draw(view.window);

    for (const auto& coin : pLogic->coins)
    {
        view.window.draw(coin.sprite);
    }

    for (const auto& secret : pLogic->secrets)
    {
        view.window.draw(secret.sprite);
    }

    for (const auto& enemy : pLogic->enemies)
    {
        view.window.draw(enemy.sprite);
    }

    for (const auto& trap : pLogic->traps)
    {
        view.window.draw(trap.sprite);
    }

    view.window.draw(pLogic->player.sprite);
}

void DestroyGameScene(GameScene*& pScene)
{
    if (pScene)
    {
        delete pScene;
        pScene = nullptr;
    }
}