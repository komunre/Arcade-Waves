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

#include <iostream>
#include "catch.h"
#include "obstructions.h"
#include "space invaders.h"
#include "doodle_jump.h"
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <thread>
#include <SFML/Audio.hpp>
#include <fstream>
#include "ping pong.h"
#include <direct.h>

using namespace std;

sf::Clock runProgramm;
sf::Time runtime;

string Key;
bool ActiveKey = false;
string Line;

void ErrorOfLoading(){
    cout << "Support: " << endl << "Mail: koliziy5@gmail.com" << endl << "Discord: https://discord.gg/aVsMeGk" << endl;
    cout << "Send a screenshot in a letter for support to get help" << endl;
    Sleep(5000);
    throw;
}
void GameExitFunction(){
    runtime = runProgramm.getElapsedTime();
    ofstream GameExit("highscores.txt", ios::app);
    GameExit << "Catch highscore: " << highscore << endl;
    GameExit << "Ping pong highscore: " << Highscore[0] << " : " << Highscore[1] << endl;
    GameExit << "User played: " << runtime.asSeconds() << endl << "Settings exit" << endl;
    GameExit.close();
}
void InvalidLicense(){
    cout << "Invalid license!" << endl;
    Sleep(2000);
}

int main()
{
    if (!calibri.loadFromFile("other/calibri.ttf")){
        ErrorOfLoading();
        throw;
    }
    if (!Tcell.loadFromFile("images/water.png")){
        ErrorOfLoading();
    }
    cell.setTexture(Tcell);
    cell.setScale(0.13, 0.13);
    if (!Tborder.loadFromFile("images/rock.png")){
        ErrorOfLoading();
    }
    border.setTexture(Tborder);
    border.setScale(0.12, 0.12);
    if (!Tplayer.loadFromFile("images/ship2.png")){
        ErrorOfLoading();
    }
    player.setTexture(Tplayer);
    player.setScale(1.3, 1.3);
    player.setOrigin(8, 8);
    windowEnemy.setOrigin(8, 8);
    if (!Tenemy.loadFromFile("images/EnemyShip.png")){
        ErrorOfLoading();
    }
    windowEnemy.setTexture(Tenemy);
    windowEnemy.setScale(1.3, 1.3);
    windowEnemy.setOrigin(5.5, 6);
    if (!Troad.loadFromFile("images/road.png")){
        ErrorOfLoading();
    }
    road.setTexture(Troad);
    if (!Tcar.loadFromFile("images/car3.png")){
        ErrorOfLoading();
    }
    car.setTexture(Tcar);
    if (!Tportal.loadFromFile("images/portal2.png")){runtime = runProgramm.getElapsedTime();
        ErrorOfLoading();
    }
    Sportal.setTexture(Tportal);
    Sportal.setScale(1.3, 1.3);
    if (!Thouse.loadFromFile("images/house.png")){
        ErrorOfLoading();
    }
    house.setTexture(Thouse);
    if (!Tobstruction.loadFromFile("images/barrel.png")){
        ErrorOfLoading();
    }
    obstruction.setTexture(Tobstruction);
    if (!TplayerAndEnemy.loadFromFile("images/ping pong.png")){
        ErrorOfLoading();
    }
    playerAndEnemy.setTexture(TplayerAndEnemy);
    if (!Tball.loadFromFile("images/ball.png")){
        ErrorOfLoading();
    }
    ball.setTexture(Tball);
    ball.setPosition(pp_fieldX / 2, pp_fieldY / 2);
    if (!TfieldBorder.loadFromFile("images/border.png")){
        ErrorOfLoading();
    }
    fieldBorder.setTexture(TfieldBorder);
    textscore.setFont(calibri);
    textscore.setCharacterSize(20);
    textscore.setFillColor(sf::Color::White);
    textscore.setString("Score: 0");
    obtextscore.setFont(calibri);
    obtextscore.setFillColor(sf::Color::Black);
    obtextscore.setCharacterSize(20);
    obtextscore.setString("Score: 0");
    if (!music.openFromFile("other/Executus - Start given.wav")){
        ofstream Error("Error_log.txt");
        if (Error.is_open()){
            Error << "Music \"Executus - Start Given.wav\" not loaded" << endl;
        }
        Error.close();
    }
    else{
        MusicLoaded = true;
        music.setVolume(20);
        music.setLoop(true);
        music.play();
    }
    EnemyScore.setString(to_string(VarEnemyScore));
    EnemyScore.setFont(calibri);
    EnemyScore.setCharacterSize(20);
    PlayerScore.setString(to_string(VarPlayerScore));
    PlayerScore.setFont(calibri);
    PlayerScore.setCharacterSize(20);
    runtime = runProgramm.getElapsedTime();
    ofstream log("highscores.txt");
    log << "launch time: " << runtime.asMilliseconds() << endl;
    log.close();
    srand(time(0));
    settings();
    if (enableportals == true){
                portal();
            }
    enemy one;
    one.SetBegin(x / 3, y / 4);
    one.appearance = 'W';
    RandPosition();
    window.setFramerateLimit(60);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear(sf::Color::White);
        if (game == 1){
                window.setActive(false);
                screen(one.coordx, one.coordy);
                moving();
                window.setActive(true);
            if (Exit == true){
                return 0;
            }
            teleportation(one);
            in_the_zone(one);
            one.AImove(x, y);
            screen(one.coordx, one.coordy);
            in_the_zone(one);
        }
        else if (game == 2){
                OB_Screen();
                AutoMove();
                GoDown();
                if (Exit == true){
                    GameExitFunction();
                    return 0;
                }
                Sleep(speed);
            }
            else if (game == 3){
                window.setActive(false);
                pp_draw();
                window.setActive(true);
                moveball();
                moveboard();
                if (Exit == true){
                    GameExitFunction();
                    return 0;
                }
                moveEnemyBoard();
            }
            window.display();
        }
    window.setActive(false);
    runtime = runProgramm.getElapsedTime();
    ofstream played("highscores.txt", ios::app);
    played << "Catch highscore: " << highscore << endl;
    played << "Ping pong highscore: " << Highscore[0] << " : " << Highscore[1] << endl;
    played << "User played: " << runtime.asSeconds() << endl << "Window closed" << endl;
    played.close();
    return 0;
}
