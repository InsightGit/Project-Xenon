//============================================================================
// Name        : Project.cpp
// Author      : Bobby Youstra
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "scene.h"

void DrawScene(sf::RenderWindow *windowtouse, xenon::Scene *currentscene){
    windowtouse->clear();
    currentscene->Draw(windowtouse);
    windowtouse->display();
}

void WindowLoop(sf::RenderWindow *windowtouse, xenon::Scene *currentscene){
    DrawScene(windowtouse,currentscene);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(640,480),"Project Xenon");
    xenon::Scene currentscene(0);
    while(window.isOpen()){
        sf::Event sfmlevent;
        while(window.pollEvent(sfmlevent)){
            if(sfmlevent.type == sf::Event::Closed){
                window.close();
            }
        }
        WindowLoop(&window,&currentscene);
    }
	return 0;
}
