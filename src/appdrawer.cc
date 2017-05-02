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

        void AppDrawer::SpawnGenericProgramIcon(xenon::gui::MenuItem *menuitemtouse, sf::Vector2i *placementvector){
            //generates app icon template along with title template without the actual icon data or title strin

            menuitemtouse->title.setFont(font);
            menuitemtouse->title.setFillColor(sf::Color::Black);
            menuitemtouse->title.setCharacterSize(12);

            menuitemtouse->sprite.setPosition(placementvector->x*150,placementvector->x*150);
            menuitemtouse->title.setPosition(menuitemtouse->sprite.getPosition().x, menuitemtouse->sprite.getPosition().y+138);
            placementvector->x++;
            if(placementvector->x >= 4){
                placementvector->x = 1;
                placementvector->y++;
            }
        }

        void AppDrawer::UpToDateSpawn(){
            sf::Vector2i placementvector = sf::Vector2i(1,1);
            for(int i = 1;GetVersionParserData().numberofappsuptodate > i;++i){
                xenon::gui::MenuItem menuitem;
                //menuitem.spriteimage.copy(GetVersionParserData().appsuptodate[i].appicon,0,0);
                /*menuitem.spriteimage = GetVersionParserData().appsuptodate[i].appicon;
                menuitem.spritetexture.loadFromImage(menuitem.spriteimage);*/

                menuitem.title.setString(GetVersionParserData().appsuptodate[i].appname);
                SpawnGenericProgramIcon(&menuitem,&placementvector);
                programicons.push_back(menuitem);
                programicons[i-1].spriteimage = GetVersionParserData().appsuptodate[i].appicon;
                programicons[i-1].spritetexture.loadFromImage(programicons[i-1].spriteimage);
                programicons[i-1].sprite.setTexture(programicons[i-1].spritetexture);

                SetProgramIconLength(GetProgramIconLength()+1);
            }
            //handle banner image loading
            banner.spriteimage.create(UpToDateBanner.width,UpToDateBanner.height,UpToDateBanner.pixel_data);

            //bannerbackarrow.spriteimage.create(UpToDateBannerMaterialBack.width,UpToDateBannerMaterialBack.height);
        }

        void AppDrawer::NotUpToDateSpawn(){
            sf::Vector2i placementvector = sf::Vector2i(1,1);
            for(int i = 1;GetVersionParserData().numberofappsnotuptodate > i;++i){
                xenon::gui::MenuItem menuitem;

                menuitem.title.setString(GetVersionParserData().appsnotuptodate[i].appname);
                SpawnGenericProgramIcon(&menuitem,&placementvector);
                programicons.push_back(menuitem);

                programicons[i-1].spriteimage = GetVersionParserData().appsuptodate[i].appicon;
                programicons[i-1].spritetexture.loadFromImage(programicons[i-1].spriteimage);
                programicons[i-1].sprite.setTexture(programicons[i-1].spritetexture);

                SetProgramIconLength(GetProgramIconLength()+1);
            }
            //handle banner image loading
            banner.spriteimage.create(NotUpToDateBanner.width,NotUpToDateBanner.height,NotUpToDateBanner.pixel_data);

            //bannerbackarrow.spriteimage.create(NotUpToDateBannerMaterialBack.width,NotUpToDateBannerMaterialBack.height);
        }

        void AppDrawer::SecurityIssueSpawn(){
            sf::Vector2i placementvector = sf::Vector2i(1,1);
            for(int i = 1;GetVersionParserData().numberofappssecurityissues > i;++i){
                xenon::gui::MenuItem menuitem;

                menuitem.title.setString(GetVersionParserData().appssecurityissues[i].appname);
                SpawnGenericProgramIcon(&menuitem,&placementvector);
                programicons.push_back(menuitem);

                programicons[i-1].spriteimage = GetVersionParserData().appsuptodate[i].appicon;
                programicons[i-1].spritetexture.loadFromImage(programicons[i-1].spriteimage);
                programicons[i-1].sprite.setTexture(programicons[i-1].spritetexture);

                SetProgramIconLength(GetProgramIconLength()+1);
            }
            //handle banner image loading
            banner.spriteimage.create(SecurityIssueBanner.width,SecurityIssueBanner.height,SecurityIssueBanner.pixel_data);

            //bannerbackarrow.spriteimage.create(SecurityIssueBannerMaterialBack.width,SecurityIssueBannerMaterialBack.height,SecurityIssueBannerMaterialBack.pixel_data);
        }

        void AppDrawer::Spawn(){
            if(GetAppStatus()==xenon::dict::UpToDate){
                UpToDateSpawn();
            }else if(GetAppStatus()==xenon::dict::NotUpToDate){
                NotUpToDateSpawn();
            }else if(GetAppStatus()==xenon::dict::SecurityIssue){
                SecurityIssueSpawn();
            }

            banner.spritetexture.loadFromImage(banner.spriteimage);
            banner.sprite.setTexture(banner.spritetexture);
            banner.sprite.setPosition(sf::Vector2f(0,0));

            bannerbackarrow.spriteimage.create(MaterialBackArrow.width, MaterialBackArrow.height, MaterialBackArrow.pixel_data);
            bannerbackarrow.spritetexture.loadFromImage(bannerbackarrow.spriteimage);
            bannerbackarrow.sprite.setTexture(bannerbackarrow.spritetexture);
            bannerbackarrow.sprite.setPosition(sf::Vector2f(640,0));
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
                window->draw(programicons[i].title);
            }
            window->draw(banner.sprite);
            window->draw(bannerbackarrow.sprite);
        }
    } /* namespace gui */
} /* namespace xenon */
