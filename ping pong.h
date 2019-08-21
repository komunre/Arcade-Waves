/* Copyright (C) 2019  Proskuryakov N. V.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#ifndef PING_PONG_H_INCLUDED
#define PING_PONG_H_INCLUDED
#include "catch.h"
sf::Texture TplayerAndEnemy, Tball, TfieldBorder;
sf::Sprite playerAndEnemy, ball, fieldBorder;
sf::Text EnemyScore, PlayerScore;
int VarEnemyScore = 0;
int VarPlayerScore = 0;
const int pp_fieldX = 600;
const int pp_fieldY = 300;
const int playerX = 500;
int playerY = pp_fieldY / 2;
const int enemyX = 38;
float enemyY = pp_fieldY / 2;
float BallX;
float BallY;
float LastBallX;
float BallSpeed = 4;
float BallSpeedY = 0;
int Highscore[2] = {0, 0};
enum BallDirection {RIGHT, LEFT};
BallDirection CurrentBallDirection;
enum RacketDirection {UP, DOWN, STOP};
RacketDirection CurrentEnemyPlatformDirection;
RacketDirection CurrentPlayerPlatformDirection;
sf::Clock LastPositionClock;

void pp_draw(){
    window.setActive(true);
    window.clear(sf::Color::Black);
    system("cls");
    window.draw(fieldBorder);
    playerAndEnemy.setPosition(playerX, playerY);
    window.draw(playerAndEnemy);
    playerAndEnemy.setPosition(enemyX, enemyY);
    window.draw(playerAndEnemy);
    window.draw(ball);
    EnemyScore.setPosition(150, 100);
    window.draw(EnemyScore);
    PlayerScore.setPosition(400, 100);
    window.draw(PlayerScore);
    ball.setPosition(BallX, BallY);
    window.draw(ball);
    window.setActive(false);
}
void moveboard(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playerY - 4 > 0){
        playerY -= 4;
        CurrentPlayerPlatformDirection = UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playerY + 4 < pp_fieldY - 64){
        playerY += 4;
        CurrentPlayerPlatformDirection = DOWN;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        BallX = pp_fieldX / 2;
        BallY = pp_fieldY / 2;
        BallSpeed = 2;
        BallSpeedY = 0;
        if (Highscore[0] < VarEnemyScore){
            Highscore[0] = VarEnemyScore;
        }
        if (Highscore[1] < VarPlayerScore){
            Highscore[1] = VarPlayerScore;
        }
        VarEnemyScore = 0;
        VarPlayerScore = 0;
        settings();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
        credits();
    }
    else{
        CurrentPlayerPlatformDirection = STOP;
    }
}
void checkCollision(){
    BallX = ball.getPosition().x;
    BallY = ball.getPosition().y;
    if ((BallX < playerX + 32 && (LastBallX > playerX + 32 || BallX >= playerX + 16)) && (BallY < playerY + 64 && BallY + 16 >= playerY)){
        if (BallY < playerY + 64 && BallY > playerY + 58){
            BallSpeedY = 5;
        }
        else if (BallY + 16 < playerY + 6 && BallY + 16 > playerY){
            BallSpeedY = -5;
        }
        else{
            BallX = playerX;
            BallSpeed = -BallSpeed;
            if (Acceleration == 2){
                BallSpeed -= 0.3;
            }
            switch(CurrentPlayerPlatformDirection){
            case UP:
                if (BallSpeedY <= 0){
                    BallSpeedY = -3;
                }
                else{
                    BallSpeedY = 0;
                }
                break;
            case DOWN:
                if (BallSpeedY >= 0){
                BallSpeedY = 3;
                }
                else{
                    BallSpeedY = 0;
                }
                break;
            case STOP:
                if (BallY < playerY + 16 && BallY > playerY){
                    if (BallSpeedY <= 0){
                        BallSpeedY = -3;
                    }
                    else{
                        BallSpeedY = 0;
                    }
                }
                else if (BallY < playerY + 64 && BallY > playerY + 32){
                    if (BallSpeedY >= 0){
                        BallSpeedY = 3;
                    }
                    else{
                        BallSpeedY = 0;
                    }
                }
            }
            CurrentBallDirection = LEFT;
        }
    }
    else if ((BallX >= enemyX && (LastBallX < enemyX || BallX < enemyX + 40)) && (BallY < enemyY + 64 && BallY + 16 >= enemyY)){
        BallX = enemyX + 42;
        BallSpeed = -BallSpeed;
        if (Acceleration == 2){
            BallSpeed += 0.3;
        }
        switch(CurrentEnemyPlatformDirection){
        case UP:
            if (BallSpeedY <= 0){
                BallSpeedY = -3;
            }
            else{
                BallSpeedY = 0;
            }
            break;
        case DOWN:
            if (BallSpeedY >= 0){
                BallSpeedY = 3;
            }
            else{
                BallSpeedY = 0;
            }
        case STOP:
            if (BallY < enemyY + 16 && BallY > enemyY){
                BallSpeedY = -3;
            }
            else if (BallY < enemyY + 64 && BallY > enemyY + 32){
                BallSpeedY = 3;
            }
        }
        CurrentBallDirection = RIGHT;
    }
    else if (BallX > pp_fieldX){
        BallY = playerY + 32;
        BallX = playerX - 40;
        ball.setPosition(playerX - 40, playerY + 32);
        BallSpeed = 4;
        BallSpeedY = 0;
        VarEnemyScore++;
        EnemyScore.setString(to_string(VarEnemyScore));
    }
    else if (BallX < 0){
        BallX = enemyX + 40;
        ball.setPosition(enemyX + 40, enemyY + 32);
        BallSpeed = -4;
        BallSpeedY = 0;
        VarPlayerScore++;
        PlayerScore.setString(to_string(VarPlayerScore));
    }
    else if (BallY + 16 >= pp_fieldY){
        BallSpeedY = -3;
    }
    else if (BallY <= 0){
        BallSpeedY = 3;
    }
    if (Highscore[0] < VarEnemyScore){
        Highscore[0] = VarEnemyScore;
    }
    if (Highscore[1] < VarPlayerScore){
        Highscore[1] = VarPlayerScore;
    }
}
void moveball(){
    LastBallX = BallX;
    ball.move(BallSpeed, BallSpeedY);
    BallX = ball.getPosition().x;
    BallY = ball.getPosition().y;
    if (BallY < 0){
        BallY = 0;
        ball.setPosition(BallX, BallY);
    }
    else if (BallY > pp_fieldY - 8){
        BallY = pp_fieldY - 8;
        ball.setPosition(BallX, BallY);
    }
    else{
        BallY = playerY + 32;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            switch(CurrentPlayerPlatformDirection){
            case UP:
                BallSpeedY = -3;
                break;
            case DOWN:
                BallSpeedY = 3;
                break;
            case STOP:
                BallSpeedY = 0;
                break;
            }
        }
    }
    checkCollision();
}
void moveEnemyBoard(){
    int LastEnemyY = enemyY;
    if (AIOrLM == 1){
    int CurrentBallPosition = ball.getPosition().y - 16;
        if (CurrentBallPosition > enemyY){
            enemyY += 2.5;
        }
        else if (CurrentBallPosition < enemyY){
            enemyY -= 2.5;
        }
    }
    if (AIOrLM == 2){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            enemyY -= 4;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            enemyY += 4;
        }
    }
    if (enemyY > pp_fieldY - 64){
        enemyY = pp_fieldY - 64;
    }
    else if (enemyY < 0){
        enemyY = 0;
    }
    if (enemyY < LastEnemyY){
        CurrentEnemyPlatformDirection = UP;
    }
    else if (enemyY > LastEnemyY){
        CurrentEnemyPlatformDirection = DOWN;
    }
    else{
        CurrentEnemyPlatformDirection = STOP;
    }
}

#endif // PING_PONG_H_INCLUDED
