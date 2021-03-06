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

#ifndef CATCH_H_INCLUDED
#define CATCH_H_INCLUDED
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
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
sf::Music music;
sf::RenderWindow window(sf::VideoMode(800, 430), "Minigames!");
bool MusicLoaded = false;
int Boot = true;
int game;
bool done = false;
int speed;
const int x = 20;
const int y = 20;
bool enableportals;
bool Exit = false;
int coordinatesX, coordinatesY;
int score = 0;
char hero = 'g';
char Move;
int portalx[2];
int portaly[2];
int AIOrLM;
int Acceleration;
string consolescore;
int highscore = 0;
string Developers[17]{"Programmers:", "Komunre", " ", "Painters:", "Iskra", "Phinn.Human", " ", "Music:", "Executus https://soundcloud.com/execute-murlock", " ", "Testers:", "IllnfernoDashli", "Jlemijkon", "Yuzua", " ", "Special thanks:", "Jlemikon"};
void credits(){
    system("cls");
    int peoples = 0;
    for (int x = 0; x != 17; x++){
        Sleep(2000);
        cout << Developers[x] << endl;
    }
    Sleep(2000);
}
bool settings(){
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << (char)169 << " Proskuryakov N. V. 2018" << endl;
    cout << "         \"             \"" << endl
     << "mmmmm  mmm    m mm   mmm     mmmm   mmm   mmmmm   mmm    mmm" << endl
        << "# # #    #    #\"  #    #    #\" \"#  \"   #  # # #  #\"  #  #   \"" << endl
        << "# # #    #    #   #    #    #   #  m\"\"\"#  # # #  #\"\"\"\"   \"\"\"m" << endl
        << "# # #  mm#mm  #   #  mm#mm  \"#m\"#  \"mm\"#  # # #  \"#mm\"  \"mmm\"" << endl
         << "                             m  #" << endl
         << "                             \"\"\"\"" << endl;
    cout << "version: 1.1.5" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "|Support: ";
    for (int x = 10; x != 48; x ++){
        cout << ' ';
    }
    cout << '|' << endl;
    cout << "|Mail: koliziy5@gmail.com";
    for (int x = 25; x != 48; x ++){
        cout << ' ';
    }
    cout << '|' << endl;
    cout << "|Discord: https://discord.gg/aVsMeGk";
    for (int x = 36; x != 48; x ++){
        cout << ' ';
    }
    cout << '|' << endl;
    cout << "------------------------------------------------" << endl;
    if (Boot == false){
        cout << "Do you want to exit?" << endl << "y/n" << endl;
        char exit;
        cin >> exit;
        if (exit == 'y'){
                Exit = true;
                return true;
        }
        else if (exit != 'n'){
            settings();
            return false;
        }
    }
    if (MusicLoaded == true){
        cout << "What music would you like?" << endl << "1. Executus - Start Given" << endl << "2. Executus - Alarm" << endl << "3. Nothing" << endl;
        int SettingsMusic;
        cin >> SettingsMusic;
        if (SettingsMusic == 1){
            if (!music.openFromFile("other/Executus - Start given.wav")){
                MusicLoaded = false;
            }
            music.play();
        }
        else if (SettingsMusic == 2){
            if (!music.openFromFile("other/Executus - Alarm.wav")){
                ofstream MusicError("error_log.txt");
                if (MusicError.is_open()){
                    MusicError << "Music \"Executus - Alarm.wav\" not loaded" << endl;
                }
                MusicLoaded = false;
            }
            music.play();
        }
        else if (SettingsMusic == 3){

        }
        cout << "what to do with music?" << endl << "1. Play" << endl << "2. Stop" << endl << "3. Nothing" << endl;
        cin >> SettingsMusic;
        if (SettingsMusic == 1){
            music.play();
        }
        else if (SettingsMusic == 2){
            music.stop();
        }
    }
    cout << "What game would you like to play?" << endl << "1. Catch" << endl << "2. Obstructions" << endl << "3. Ping pong" << endl;
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
    }
    else if (game == 3){
        cout << "What would you like" << endl << "1. AI" << endl << "2. Local multiplayer" << endl;
        cin >> AIOrLM;
        if (AIOrLM != 1 && AIOrLM != 2){
            settings();
        }
        cout << "What would you like" << endl << "1. Disable acceleration" << endl << "2. Enable acceleration" << endl;
        cin >> Acceleration;
        if (Acceleration != 1 && Acceleration != 2){
            settings();
        }
    }
    else{
        settings();
    }
    Boot = false;
    return false;
}
void screen(int Coordx, int Coordy){ //������� ���� � g
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
        while (r != y){ //���� ���������� ����� �� ����� ��������� ������ ����
            c = 0;
        cout << r;
        while (c != x){ //���� ���������� �������� �� ����� ��������� ����� ����
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
    cout << "Enter a, w, s or d to move" << endl;
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
        if (score > highscore){
            highscore = score;
        }
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
