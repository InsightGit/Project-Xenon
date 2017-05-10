//============================================================================
// Name        : Project.cpp
// Author      : Bobby Youstra
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
//prevents multiple compilation errors
#define __USE_MINGW_ANSI_STDIO 00


#include <iostream>

#include "scene.h"

#include "Resources/background.h"
#include "Resources/xenonicon.h"

void DrawScene(sf::RenderWindow *windowtouse, xenon::Scene *currentscene, sf::Sprite *backgroundsprite){
    windowtouse->clear(sf::Color(245, 245, 245, 255));
    //windowtouse->draw(*backgroundsprite);
    currentscene->Draw(windowtouse);
    windowtouse->display();
}

void WindowLoop(sf::RenderWindow *windowtouse, xenon::Scene *currentscene, sf::Sprite *backgroundsprite){
    DrawScene(windowtouse,currentscene,backgroundsprite);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(740,580),"Project Xenon");
    window.setIcon(XenonIcon.width,XenonIcon.height,XenonIcon.pixel_data);
    sf::Image backgroundimage;
    sf::Texture backgroundtexture;
    sf::Sprite backgroundsprite;

    //gets rid of windows command prompt window with application
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );

    xenon::Scene currentscene(0);

    backgroundimage.create(BackgroundImage.width,BackgroundImage.height,BackgroundImage.pixel_data);
    backgroundtexture.loadFromImage(backgroundimage);
    backgroundsprite.setTexture(backgroundtexture);
    backgroundsprite.setPosition(sf::Vector2f(0,0));

    while(window.isOpen()){
        sf::Event sfmlevent;
        while(window.pollEvent(sfmlevent)){
            currentscene.EventUpdate(&sfmlevent);
            if(sfmlevent.type == sf::Event::Closed){
                window.close();
            }
        }
        WindowLoop(&window,&currentscene,&backgroundsprite);
    }
	return 0;
}
