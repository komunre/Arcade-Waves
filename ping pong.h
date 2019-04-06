#ifndef PING_PONG_H_INCLUDED
#define PING_PONG_H_INCLUDED
#include "catch.h"
sf::Texture TplayerAndEnemy, Tball, TfieldBorder;
sf::Sprite playerAndEnemy, ball, fieldBorder;
sf::Text EnemyScore, PlayerScore;
int VarEnemyScore = 0;
int VarPlayerScore = 0;
int pp_fieldX = 600;
int pp_fieldY = 300;
int playerX = 500;
int playerY = pp_fieldY / 2;
int enemyX = 20;
int enemyY = pp_fieldY / 2;
float BallX;
float BallY;
float BallSpeed = 4;
float BallSpeedY = 0;
int Highscore[2] = {0, 0};
enum BallDirection {RIGHT, LEFT};
BallDirection CurrentBallDirection;
enum EnemyPlatformDirection {UP, DOWN, STOP};
EnemyPlatformDirection CurrentEnemyPlatformDirection;
enum PlayerPlatformDirection {up, down, stop};
PlayerPlatformDirection CurrentPlayerPlatformDirection;
sf::Clock LastPositionClock;

void pp_draw(){
    window.setActive(true);
    window.clear(sf::Color::Black);
    system("cls");
    cout << "BallX: " << BallX << " BallY: " << BallY << endl << " playerX: " << playerX << " playerY: " << playerY << endl << " enemyX: " << enemyX << " enemyY: " << enemyY << endl << "BallSpeedY: " << BallSpeedY << endl;
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
    window.setActive(false);
}
void moveboard(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playerY - 4 > 0){
        playerY -= 4;
        CurrentPlayerPlatformDirection = up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playerY + 4 < pp_fieldY - 64){
        playerY += 4;
        CurrentPlayerPlatformDirection = down;
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
        CurrentPlayerPlatformDirection = stop;
    }
    cout << CurrentPlayerPlatformDirection << endl;
}
void checkCollision(){
    BallX = ball.getPosition().x;
    BallY = ball.getPosition().y;
    if ((BallX < playerX + 32 && BallX >= playerX + 16) && (BallY - 8 < playerY + 64 && BallY + 8 >= playerY)){
        BallSpeed = -BallSpeed;
        if (Acceleration == 2){
            BallSpeed -= 0.3;
        }
        switch(CurrentPlayerPlatformDirection){
        case up:
            if (BallSpeedY <= 0){
                BallSpeedY = -3;
            }
            else{
                BallSpeedY = 0;
            }
            break;
        case down:
            if (BallSpeedY >= 0){
                BallSpeedY = 3;
            }
            else{
                BallSpeedY = 0;
            }
            break;
        case stop:
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
    else if ((BallX < enemyX + 32 && BallX >= enemyX) && (BallY - 8 < enemyY + 64 && BallY + 8 >= enemyY)){
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
        ball.setPosition(playerX - 40, playerY + 32);
        BallSpeed = 4;
        BallSpeedY = 0;
        VarEnemyScore++;
        EnemyScore.setString(to_string(VarEnemyScore));
    }
    else if (BallX < 0){
        ball.setPosition(enemyX + 40, enemyY + 32);
        BallSpeed = -4;
        BallSpeedY = 0;
        VarPlayerScore++;
        PlayerScore.setString(to_string(VarPlayerScore));
    }
    else if (BallY + 8 >= pp_fieldY - 16){
        BallSpeedY = -BallSpeedY;
    }
    else if (BallY - 8 <= 0){
        BallSpeedY = -BallSpeedY;
    }
    if (Highscore[0] < VarEnemyScore){
        Highscore[0] = VarEnemyScore;
    }
    if (Highscore[1] < VarPlayerScore){
        Highscore[1] = VarPlayerScore;
    }
}
void moveball(){
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
    checkCollision();
}
void moveEnemyBoard(){
    int LastEnemyY = enemyY;
    if (AIOrLM == 1){
    int CurrentBallPosition = ball.getPosition().y - 16;
        if (CurrentBallPosition > enemyY){
            enemyY += 3;
        }
        else if (CurrentBallPosition < enemyY){
            enemyY -= 3;
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
