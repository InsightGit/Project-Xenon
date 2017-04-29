/*
 * MainScreen.cc
 *
 *  Created on: Apr 28, 2017
 *      Author: Bobby
 */

#include "MainScreen.h"

namespace xenon {
    namespace gui {
        MainScreen::MainScreen(xenon::dict::VersionParserData datatouse) {
            datatouse_ = datatouse;

            statusfont.loadFromFile("default.ttf");
            statustext.setFont(statusfont);
        }

        MainScreen::MainScreen(sf::Font statusfonttouse, xenon::dict::VersionParserData datatouse){
            datatouse_ = datatouse;

            statusfont = statusfonttouse;
            statustext.setFont(statusfont);
        }

        MainScreen::~MainScreen() {

        }

        void MainScreen::SpawnStatusArea(){
            if(GetWorstAppStatus() == xenon::dict::UpToDate){
                statussprite.spriteimage.create(MaterialCheckIcon.width,MaterialCheckIcon.height,MaterialCheckIcon.pixel_data);
                statussprite.spritetexture.loadFromImage(statussprite.spriteimage);
                statussprite.setTexture(statussprite.spritetexture);
                statussprite.setPosition(sf::Vector2f(470,240));
            }else if(GetWorstAppStatus() == xenon::dict::NotUpToDate){
                statussprite.spriteimage.create(MaterialWarningIcon.width,MaterialWarningIcon.height,MaterialWarningIcon.pixel_data);
                statussprite.spritetexture.loadFromImage(statussprite.spriteimage);
                statussprite.setTexture(statussprite.spritetexture);
                statussprite.setPosition(sf::Vector2f(470,240));
            }else if(GetWorstAppStatus() == xenon::dict::SecurityIssue){
                statussprite.spriteimage.create(MaterialErrorIcon.width,MaterialErrorIcon.height,MaterialErrorIcon.pixel_data);
                statussprite.spritetexture.loadFromImage(statussprite.spriteimage);
                statussprite.setTexture(statussprite.spritetexture);
                statussprite.setPosition(sf::Vector2f(470,240));
            }
        }

        void MainScreen::Spawn(){
            if(GetVersionData().totalnumberofapps > 0){
                divider.setFillColor(sf::Color::Black);
                divider.setPosition(sf::Vector2f(300,0));

                if(GetVersionData().numberofappsuptodate > 0){
                    uptodatebutton.spriteimage.create(UpToDateButton.width,UpToDateButton.height,UpToDateButton.pixel_data);
                    uptodatebutton.spritetexture.loadFromImage(uptodatebutton.spriteimage);
                    uptodatebutton.setTexture(uptodatebutton.spritetexture);
                    uptodatebutton.setPosition(sf::Vector2f(50,50));
                    SetWorstAppStatus(xenon::dict::UpToDate);
                }
                if(GetVersionData().numberofappsnotuptodate > 0){
                    notuptodatebutton.spriteimage.create(NotUpToDateButton.width,NotUpToDateButton.height,NotUpToDateButton.pixel_data);
                    notuptodatebutton.spritetexture.loadFromImage(notuptodatebutton.spriteimage);
                    notuptodatebutton.setTexture(notuptodatebutton.spritetexture);
                    notuptodatebutton.setPosition(sf::Vector2f(50,190));
                    SetWorstAppStatus(xenon::dict::NotUpToDate);
                }
                if(GetVersionData().numberofappssecurityissues > 0){
                    securityissuebutton.spriteimage.create(SecurityIssueButton.width,SecurityIssueButton.height,SecurityIssueButton.pixel_data);
                    securityissuebutton.spritetexture.loadFromImage(securityissuebutton.spriteimage);
                    securityissuebutton.setTexture(securityissuebutton.spritetexture);
                    securityissuebutton.setPosition(sf::Vector2f(50,320));
                    SetWorstAppStatus(xenon::dict::SecurityIssue);
                }

                SpawnStatusArea();
            }
        }
    } /* namespace gui */
} /* namespace xenon */
