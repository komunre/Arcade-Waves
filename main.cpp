#include <iostream>
#include "catch.h"
#include "obstructions.h"
#include "space invaders.h"
#include "doodle_jump.h"
#include <windows.h>
#include <ctime>
#include <conio.h> //Для использования _getch() которая ждёт символ и сразу передаёт его без enter
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <thread>
#include <SFML/Audio.hpp>
#include <fstream>
#include "ping pong.h"

using namespace std;

void ErrorOfLoading(){
    cout << "Support: " << endl << "Mail: koliziy5@gmail.com" << endl << "Discord: komunre#2298" << endl;
    cout << "Send a screenshot in a letter for support to get help" << endl;
    Sleep(5000);
    throw;
}
int main()
{
    sf::Clock runProgramm;
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
    if (!Tportal.loadFromFile("images/portal2.png")){
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
    ball.setOrigin(16, 16);
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
    sf::Music music;
    if (!music.openFromFile("other/Executus - Start given.wav")){
        ErrorOfLoading();
        throw;
    }
    music.setVolume(30);
    music.setLoop(true);
    music.play();
    sf::Time runtime = runProgramm.getElapsedTime();
    ofstream log("highscores.txt");
    log << "launch time: " << runtime.asMilliseconds() << endl;
    log.close();
    srand(time(0));
    if (settings() == true){
        return 0;
    }
    if (enableportals == true){
                portal();
            }
    enemy one;
    one.SetBegin(x / 3, y / 4);
    one.appearance = 'W';
    RandPosition();
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
                window.setActive(true);
                window.setActive(false);
                moving();
                window.setActive(true);
            if (Exit == true){
                runtime = runProgramm.getElapsedTime();
                ofstream Game1Exit("highscores.txt", ios::app);
                Game1Exit << "Catch highscore: " << highscore << endl;
                Game1Exit << "User played: " << runtime.asSeconds() << endl << "Settings exit" << endl;
                Game1Exit.close();
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
                    runtime = runProgramm.getElapsedTime();
                    ofstream Game2Exit("highscores.txt", ios::app);
                    Game2Exit << "Catch highscore: " << highscore << endl;
                    Game2Exit << "User played: " << runtime.asSeconds() << endl << "Settings exit" << endl;
                    Game2Exit.close();
                    return 0;
                }
                Sleep(speed);
            }
            else if (game == 3){
                window.setActive(false);
                pp_draw();
                window.setActive(true);
                moveboard();
                moveball();
                checkCollision();
                moveEnemyBoard();
            }
            else if (game == 4){
                window.setActive(false);
                draw();
                window.setActive(true);
                GoRight();
            }
            window.display();
        }
    window.setActive(false);
    runtime = runProgramm.getElapsedTime();
    ofstream played("highscores.txt", ios::app);
    played << "Catch highscore: " << highscore << endl;
    played << "User played: " << runtime.asSeconds() << endl << "Window closed" << endl;
    played.close();
    return 0;
}
