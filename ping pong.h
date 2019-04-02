#ifndef PING_PONG_H_INCLUDED
#define PING_PONG_H_INCLUDED
#include "catch.h"
sf::Texture TplayerAndEnemy, Tball, TfieldBorder;
sf::Sprite playerAndEnemy, ball, fieldBorder;
int pp_fieldX = 600;
int pp_fieldY = 300;
int playerX = 500;
int playerY = pp_fieldY / 2;
int enemyX = 20;
int enemyY = pp_fieldY / 2;
float BallX;
float BallY;
float BallSpeed = 2;
enum BallDirection {RIGHT, LEFT};
BallDirection CurrentBallFirection;

void pp_draw(){
    window.setActive(true);
    window.clear(sf::Color::Black);
    system("cls");
    cout << "BallX: " << BallX << " BallY: " << BallY << endl << " playerX: " << playerX << " playerY: " << playerY << endl << " enemyX: " << enemyX << " enemyY: " << enemyY << endl;
    window.draw(fieldBorder);
    playerAndEnemy.setPosition(playerX, playerY);
    window.draw(playerAndEnemy);
    playerAndEnemy.setPosition(enemyX, enemyY);
    window.draw(playerAndEnemy);
    window.draw(ball);
    window.setActive(false);
}
void moveboard(){
    sf::Vector2i cursorpos = sf::Mouse::getPosition(window);
    if (cursorpos.y < 0){
        playerY = 0;
    }
    else if (cursorpos.y > pp_fieldY - 64){
        playerY = pp_fieldY - 64;
    }
    else{
        playerY = cursorpos.y;
    }
}
void moveball(){
    ball.move(BallSpeed, 0);
}
void moveEnemyBoard(){
    enemyY = ball.getPosition().y - 16;
}
void checkCollision(){
    BallX = ball.getPosition().x;
    BallY = ball.getPosition().y;
    if ((BallX < playerX + 16 && BallX >= playerX) && (BallY < playerY + 16 && BallY >= playerY)){
        BallSpeed -= BallSpeed * 2;
        BallSpeed -= 0.05;;
    }
    else if ((BallX < enemyX + 16 && BallX >= enemyX) && (BallY < enemyY + 16 && BallY >= enemyY)){
        BallSpeed += 0.05;
        BallSpeed = BallSpeed - BallSpeed * 2;
    }
    else if (BallX < 0 || BallX > pp_fieldX){
        BallX = pp_fieldX / 2;
        BallSpeed = 2;
    }
}

#endif // PING_PONG_H_INCLUDED
