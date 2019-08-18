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

#pragma once
#ifndef OBSTRUCTIONS_H_INCLUDED
#define OBSTRUCTIONS_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

sf::Texture Troad;
sf::Sprite road;
sf::Texture Tobstruction, Thouse, Tcar;
sf::Sprite obstruction, house, car;
sf::Text obtextscore;
const int OB_x = 4;
const int OB_y = 14;
int Auto = OB_x / 2;
int OB_Score = 0;
int ObstructionX, ObstructionY;
int numberOfAttempts = 0;
string obconsolescore;
void OB_Screen(){
    window.setActive(true);
    system("cls");
    int cols = 0;
    int rows = 0;
    cout << "Score: " << OB_Score << endl;
    while (rows != OB_y){
        cols = 0;
        while (cols != 20){
            cout << ' ';
            cols++;
        }
        cols = 0;
        while (cols != OB_x){
            if (cols == 0 || cols == OB_x - 1){
                house.setPosition(cols * 16, rows * 16);
                window.draw(house);
                ++cols;
            }
            else if (cols == Auto && rows == OB_y - 1){
                car.setPosition(cols * 16, rows * 16);
                road.setPosition(cols * 16, rows * 16);
                window.draw(road);
                window.draw(car);
                ++cols;
            }
            else if (cols == ObstructionX && rows == ObstructionY){
                obstruction.setPosition(cols * 16, rows * 16);
                road.setPosition(cols * 16, rows * 16);
                window.draw(road);
                window.draw(obstruction);
                ++cols;
            }
            else{
               road.setPosition(cols * 16, rows * 16);
               window.draw(road);
               ++cols;
            }
        }
        ++rows;
        cout << endl;
    }
    obtextscore.setPosition(0, 220);
    window.draw(obtextscore);
    cout << "ob_x: " << ObstructionX << " ob_y: " << ObstructionY << endl;
    cout << "a and d to move. t to see credits" << endl;
    window.setActive(false);
}
void RandPosition(){
    ObstructionX = 1 + (rand() % OB_x);
    ObstructionY = 0;
    if (ObstructionX >= OB_x - 1){
        RandPosition();
    }
}
void GoDown(){
    if (ObstructionY + 1 < OB_y){
        ObstructionY++;
    }
    else{
        RandPosition();
        OB_Score++;
        obconsolescore = "Score: " + to_string(OB_Score);
        obtextscore.setString(obconsolescore);
        return;
    }
    if (ObstructionY == OB_y - 1 && ObstructionX == Auto){
        numberOfAttempts++;
        ofstream ObScoreFile("highscores.txt", ios::app);
        ObScoreFile << "Attemp: " << numberOfAttempts << endl;
        ObScoreFile << "    Speed: " << speed << endl;
        ObScoreFile << "    " << obconsolescore << endl;
        ObScoreFile.close();
        OB_Score = 0;
        RandPosition();
        obconsolescore = "Score: " + to_string(OB_Score);
        obtextscore.setString(obconsolescore);
    }
}
void AutoMove(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Auto - 1 > 0){
            Auto--;
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Auto + 1 < OB_x - 1){
            Auto++;
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
        credits();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        ofstream SettindsScoreFile("highscores.txt", ios::app);
        SettindsScoreFile << "Attemp: " << numberOfAttempts << endl;
        SettindsScoreFile << "    Speed: " << speed << endl;
        SettindsScoreFile << "    " << obconsolescore << endl;
        SettindsScoreFile.close();
        OB_Score = 0;
        settings();
    }
}


#endif // OBSTRUCTIONS_H_INCLUDED
