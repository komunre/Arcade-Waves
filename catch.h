#ifndef CATCH_H_INCLUDED
#define CATCH_H_INCLUDED
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h> //Для использования _getch() которая ждёт символ и сразу передаёт его без enter
#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
using namespace std;
sf::Texture Tplayer;
sf::Texture Tenemy;
sf::Texture Tcell;
sf::Texture Tborder;
sf::Texture Tportal;
sf::Font calibri;
sf::Text textscore;
sf::Sprite cell;
sf::Sprite border;
sf::Sprite player;
sf::Sprite windowEnemy;
sf::Sprite Sportal;
sf::RenderWindow window(sf::VideoMode(600, 430), "Minigames!");
int Boot = true;
int game;
bool done = false;
int speed;
int x = 20;
int y = 20;
bool enableportals;
bool Exit = false;
int coordinatesX, coordinatesY;
int score = 0;
char hero = 'g';
char Move;
int portalx[2];
int portaly[2];
string consolescore;
int highscore = 0;
string Developers[16]{"Programmers:", "Komunre", " ", "Painters:", "Iskra", "Phinn.Human", " ", "Music:", "Executus", " ", "Testers:", "IllnfernoDashli", "Jlemijkon", " ", "Special thanks:", "Jlemikon"};
void credits(){
    system("cls");
    int peoples = 0;
    for (int x = 0; x != 16; x++){
        Sleep(2000);
        cout << Developers[x] << endl;
    }
    Sleep(2000);
}
bool settings(){
    system("cls");
    cout << "version: 1.0.2" << endl;
    cout << "Support: " << endl << "Mail: koliziy5@gmail.com" << endl << "Discord: https://discord.gg/aVsMeGk" << endl;
    if (Boot == false){
        cout << "Do you want to exit?" << endl << "y/n" << endl;
        char exit;
        cin >> exit;
        if (exit == 'y'){
                Exit = true;
                return true;
        }
    }
    cout << "What game would you like to play?" << endl << "1. Catch" << endl << "2. Obstructions" << endl;
    cin >> game;
    if (game == 1){
        coordinatesX = x / 2;
        coordinatesY = x / 2;
        cout << "Do you want to enable portals?" << endl << "y/n" << endl;
        char yn;
        cin >> yn;
        if (yn == 'y'){
            enableportals = true;
        }
        else{
            enableportals = false;
        }
    }
    else if (game == 2){
        cout << "Enter speed of a game (how much sleep in milliseconds): ";
        cin >> speed;
        window.setActive(false);
    }
    else if (game == 3){
        window.setActive(false);
    }
    else if (game == 4){
        window.setActive(false);
    }
    else{
        settings();
    }
    Boot = false;
    return false;
}
void screen(int Coordx, int Coordy){ //Выводит поле с g
    window.setActive(true);
    int c = 0;
    int r = 0;
            sf::Event event2;
        while (window.pollEvent(event2)){
            if(event2.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        while (r != y){ //Пока количество строк не будет равняться ширине поля
            c = 0;
        cout << r;
        while (c != x){ //Пока количество символов не будет равняться длине поля
                cout << c;
            if (r == 0 || r == y - 1 || c == 0 || c == x - 1){
                border.setPosition(c * x, r * y);
                window.draw(border);
                ++c;
            }
            else if ((c != coordinatesX || r != coordinatesY) && (c != Coordx || r != Coordy) && (c != portalx[0] || r != portaly[0]) && (c != portalx[1] || r != portaly[1])){
                cell.setPosition(c * x, r * y);
                window.draw(cell);
                ++c;
            }
            else if (c == coordinatesX && r == coordinatesY){
                player.setPosition((c * x) + 8, (r * y) + 8);
                cell.setPosition(c* x, r * y);
                window.draw(cell);
                window.draw(player);
                ++c;
            }
            else if ((c != portalx[0] || r != portaly[0]) && (c != portalx[1] || r != portaly[1])){
                    windowEnemy.setPosition((c * x) + 5.5, (r * y) + 6);
                    cell.setPosition(c * x, r * y);
                    window.draw(cell);
                    window.draw(windowEnemy);
                    ++c;
            }
            else{
                Sportal.setPosition(c * x, r * y);
                cell.setPosition(c * x, r * y);
                window.draw(cell);
                window.draw(Sportal);
                ++c;
            }
        }
        ++r;
        cout << endl;
    }
    done = true;
    textscore.setPosition(0, 400);
    window.draw(textscore);
    cout << "Enter a, w, s or d to move" << endl << "g is you. You need to catch W. @ is portals" << endl;
    window.display();
    window.setActive(false);
    }
void moving(){
    Sleep(100);
    window.setActive(true);
    sf::Event moveEvent;
    while(window.pollEvent(moveEvent)){
        if (moveEvent.type == sf::Event::Closed){
            window.close();
            return;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && coordinatesX - 1 != 0){
        --coordinatesX;
        player.setRotation(-90);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && coordinatesX + 1 != x - 1){
        ++coordinatesX;
        player.setRotation(90);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && coordinatesY - 1 != 0){
        --coordinatesY;
        player.setRotation(0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && coordinatesY + 1 != y - 1){
        ++coordinatesY;
        player.setRotation(180);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        if (score > highscore){
            highscore = score;
        }
        score = 0;
        settings();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
        credits();
    }
    else{
        moving();
        return;
    }
    window.setActive(false);
}
class wall{
public:
    int coordx[2];
    int coordy;
};
class enemy{
private:
    string name;
public:
    void AImove(int x, int y){
        int direction = rand() % 4;
        if (direction == 1 && coordx + 1 <= x - 2){
            ++coordx;
            windowEnemy.setRotation(90);
        }
        else if (direction == 2 && coordx - 1 != 0){
            --coordx;
            windowEnemy.setRotation(-90);
        }
        else if (direction == 3 && coordy + 1 != y - 1){
            ++coordy;
            windowEnemy.setRotation(180);
        }
        else if (coordy - 1 != 0){
            --coordy;
            windowEnemy.setRotation(0);
        }
        else{
            AImove(x, y);
        }
    }
    void SetBegin(int x, int y){
        coordx = x;
        coordy = y;
    }
    int coordx;
    int coordy;
    char appearance;
};
void randxy (int& randx, int& randy){
    randx = rand() % (x - 2);
    randy = rand() % (y - 2);
    if (randx <= 0 || randy <= 0){
        randxy(randx, randy);
    }
}
void portal (){
    randxy(portalx[0], portaly[0]);
    randxy(portalx[1], portaly[1]);
    if (portalx[0] == portalx[1] && portaly[0] == portaly[1]){
        portal();cout << consolescore;
    }
}
void in_the_zone(enemy& one){
    if (coordinatesX == one.coordx && coordinatesY == one.coordy){
        ++score;
        consolescore = "Score: " + to_string(score);
        textscore.setString(consolescore);
        randxy(one.coordx, one.coordy);
        if (enableportals == true){
            portal();
        }
    }
}
void teleportation(enemy& one){
    if (coordinatesX == portalx[0] && coordinatesY == portaly[0]){
        coordinatesX = portalx[1];
        coordinatesY = portaly[1];
    }
    else if (coordinatesX == portalx[1] && coordinatesY == portaly[1]){
        coordinatesX = portalx[0];
        coordinatesY = portaly[0];
    }
    else if (one.coordx == portalx[0] && one.coordy == portaly[0]){
        one.coordx = portalx[1];
        one.coordy = portaly[1];
    }
    else if (one.coordx == portalx[1] && one.coordy == portaly[1]){
        one.coordx = portalx[0];
        one.coordy = portaly[0];
    }
}

#endif // CATCH_H_INCLUDED
