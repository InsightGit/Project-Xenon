/*
 * MainScreen.cc
 *
 *  Created on: Apr 28, 2017
 *      Author: Bobby
 */

#include "mainscreen.h"

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

        /*MainScreen::~MainScreen() {

        }*/

        void MainScreen::SpawnStatusArea(){
            statustext.setCharacterSize(16);
            statustext.setPosition(sf::Vector2f(320,300));
            if(GetWorstAppStatus() == xenon::dict::UpToDate){
                statustext.setFillColor(sf::Color(76, 175, 80, 255));
                statussprite.spriteimage.create(MaterialCheckIcon.width,MaterialCheckIcon.height,MaterialCheckIcon.pixel_data);
                statustext.setString("All searched apps up to date!");
            }else if(GetWorstAppStatus() == xenon::dict::NotUpToDate){
                statustext.setFillColor(sf::Color(255, 235, 59, 255));
                statussprite.spriteimage.create(MaterialWarningIcon.width,MaterialWarningIcon.height,MaterialWarningIcon.pixel_data);
                statustext.setString("Some searched apps are not up to date.");
            }else if(GetWorstAppStatus() == xenon::dict::SecurityIssue){
                statustext.setFillColor(sf::Color(244, 67, 54, 255));
                statussprite.spriteimage.create(MaterialErrorIcon.width,MaterialErrorIcon.height,MaterialErrorIcon.pixel_data);
                statustext.setString("Some searched apps have known security issues!");
            }

            statussprite.spritetexture.loadFromImage(statussprite.spriteimage);
            statussprite.sprite.setTexture(statussprite.spritetexture);
            statussprite.sprite.setPosition(sf::Vector2f(statustext.getPosition().x-20,34));
        }

        void MainScreen::Spawn(){
            if(GetVersionData().totalnumberofapps > 0){
                divider.spriteimage.create(Divider.width,Divider.height,Divider.pixel_data);
                divider.spritetexture.loadFromImage(divider.spriteimage);
                divider.sprite.setTexture(divider.spritetexture);
                divider.sprite.setPosition(sf::Vector2f(300,0));

                if(GetVersionData().numberofappsuptodate > 0){
                    uptodatebutton.spriteimage.create(UpToDateButton.width,UpToDateButton.height,UpToDateButton.pixel_data);
                    uptodatebutton.spritetexture.loadFromImage(uptodatebutton.spriteimage);
                    uptodatebutton.sprite.setTexture(uptodatebutton.spritetexture);
                    uptodatebutton.sprite.setPosition(sf::Vector2f(0,50));
                    SetWorstAppStatus(xenon::dict::UpToDate);
                }
                if(GetVersionData().numberofappsnotuptodate > 0){
                    notuptodatebutton.spriteimage.create(NotUpToDateButton.width,NotUpToDateButton.height,NotUpToDateButton.pixel_data);
                    notuptodatebutton.spritetexture.loadFromImage(notuptodatebutton.spriteimage);
                    notuptodatebutton.sprite.setTexture(notuptodatebutton.spritetexture);
                    notuptodatebutton.sprite.setPosition(sf::Vector2f(0,190));
                    SetWorstAppStatus(xenon::dict::NotUpToDate);
                }
                if(GetVersionData().numberofappssecurityissues > 0){
                    securityissuebutton.spriteimage.create(SecurityIssueButton.width,SecurityIssueButton.height,SecurityIssueButton.pixel_data);
                    securityissuebutton.spritetexture.loadFromImage(securityissuebutton.spriteimage);
                    securityissuebutton.sprite.setTexture(securityissuebutton.spritetexture);
                    securityissuebutton.sprite.setPosition(sf::Vector2f(0,320));
                    SetWorstAppStatus(xenon::dict::SecurityIssue);
                }
                SpawnStatusArea();
            }
        }

        void MainScreen::Draw(sf::RenderWindow *window){
            //window->draw(divider.sprite);

            if(GetVersionData().numberofappsuptodate > 0){
                window->draw(uptodatebutton.sprite);
            }
            if(GetVersionData().numberofappsnotuptodate > 0){
                window->draw(notuptodatebutton.sprite);
            }
            if(GetVersionData().numberofappssecurityissues > 0){
                window->draw(securityissuebutton.sprite);
            }

            window->draw(statussprite.sprite);
            window->draw(statustext);
        }
    } /* namespace gui */
} /* namespace xenon */
