/*
 * AppDrawer.cc
 *
 *  Created on: Apr 30, 2017
 *      Author: Bobby
 */

#include "appdrawer.h"

namespace xenon {
    namespace gui {
        AppDrawer::AppDrawer(xenon::dict::VersionParserData versionparserdatatouse, xenon::dict::AppStatus appstatustoopen, xenon::Scene *currentscene) {
            versionparserdata_ = versionparserdatatouse;
            appstatus_ = appstatustoopen;
            currentscene_ = currentscene;
            font.loadFromFile("default.ttf");
        }

        AppDrawer::~AppDrawer() {
            // TODO Auto-generated destructor stub
        }

        void AppDrawer::Spawn(){
            if(GetAppStatus()==xenon::dict::UpToDate){
                sf::Vector2i placementvector = sf::Vector2i(1,1);
                for(int i = 0;GetVersionParserData().numberofappsuptodate > i;++i){
                    //generates app icons for uptodate category
                    xenon::gui::MenuItem menuItem;
                    menuItem.spritetexture.loadFromImage(GetVersionParserData().appsnotuptodate[i].appicon);
                    menuItem.sprite.setTexture(menuItem.spritetexture);

                    menuItem.title.setFont(font);
                    menuItem.title.setString(GetVersionParserData().appsnotuptodate[i].appname);
                    menuItem.title.setFillColor(sf::Color::Black);
                    menuItem.title.setCharacterSize(12);

                    menuItem.sprite.setPosition(placementvector.x*150,placementvector.x*150);
                    menuItem.title.setPosition(menuItem.sprite.getPosition().x,menuItem.sprite.getPosition().y+138);
                    placementvector.x++;
                    if(placementvector.x >= 4){
                        placementvector.x = 1;
                        placementvector.y++;
                    }
                    programicons.push_back(menuItem);
                }
                //handle banner
                banner.spriteimage.create(UpToDateBanner.width,UpToDateBanner.height,UpToDateBanner.pixel_data);
                banner.spritetexture.loadFromImage(banner.spriteimage);
                banner.sprite.setTexture(banner.spritetexture);
                banner.sprite.setPosition(sf::Vector2f(0,0));
                bannerbackarrow.spriteimage.create(UpToDateBannerMaterialBack.width,UpToDateBannerMaterialBack.height);
                bannerbackarrow.spritetexture.loadFromImage(bannerbackarrow.spriteimage);
                bannerbackarrow.sprite.setTexture(bannerbackarrow.spritetexture);
                bannerbackarrow.sprite.setPosition(sf::Vector2f(640,0));
            }
        }

        void AppDrawer::Update(sf::RenderWindow *window, bool lostfocus){
            if(bannerbackarrow.IsClicked(window,lostfocus)){
                GoBackToMainScreen();
            }
        }

        void AppDrawer::Draw(sf::RenderWindow *window, bool lostfocus){
            Update(window,lostfocus);

            for(int i = 0; GetProgramIconLength() > i; ++i){
                window->draw(programicons[i].sprite);
            }
            window->draw(banner.sprite);
            window->draw(bannerbackarrow.sprite);
        }
    } /* namespace gui */
} /* namespace xenon */
