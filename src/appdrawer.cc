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

            menuitemtouse->sprite.setPosition(placementvector->x*150,placementvector->y*150);
            menuitemtouse->title.setPosition(menuitemtouse->sprite.getPosition().x, menuitemtouse->sprite.getPosition().y+138);
            placementvector->x++;
            if(placementvector->x >= 5){
                placementvector->x = 0;
                placementvector->y++;
            }
        }

        void AppDrawer::UpToDateSpawn(){
            sf::Vector2i placementvector = sf::Vector2i(0,1);
            for(int i = 0;GetVersionParserData().numberofappsuptodate > i;++i){
                xenon::gui::MenuItem menuitem = xenon::gui::MenuItem(GetVersionParserData().appsuptodate[i]);
                //menuitem.spriteimage.copy(GetVersionParserData().appsuptodate[i].appicon,0,0);
                /*menuitem.spriteimage = GetVersionParserData().appsuptodate[i].appicon;
                menuitem.spritetexture.loadFromImage(menuitem.spriteimage);*/

                menuitem.title.setString(GetVersionParserData().appsuptodate[i].appname);
                SpawnGenericProgramIcon(&menuitem,&placementvector);
                programicons.push_back(menuitem);

                programicons[i].spriteimage = GetVersionParserData().appsuptodate[i].appicon;
                programicons[i].spritetexture.loadFromImage(programicons[i].spriteimage);
                programicons[i].sprite.setTexture(programicons[i].spritetexture);

                SetProgramIconLength(GetProgramIconLength()+1);

                if(i==0){
                    SetTopScrollLimit(programicons[i].title.getPosition().y-100);
                }else if(i==GetVersionParserData().numberofappsuptodate-1){
                    SetBottomScrollLimit(programicons[i].title.getPosition().y+100);
                }
            }
            //handle banner image loading
            banner.spriteimage.create(UpToDateBanner.width,UpToDateBanner.height,UpToDateBanner.pixel_data);

            //bannerbackarrow.spriteimage.create(UpToDateBannerMaterialBack.width,UpToDateBannerMaterialBack.height);
        }

        void AppDrawer::NotUpToDateSpawn(){
            sf::Vector2i placementvector = sf::Vector2i(0,1);
            for(int i = 0;GetVersionParserData().numberofappsnotuptodate > i;++i){
                xenon::gui::MenuItem menuitem = xenon::gui::MenuItem(GetVersionParserData().appsnotuptodate[i]);;

                menuitem.title.setString(GetVersionParserData().appsnotuptodate[i].appname);
                SpawnGenericProgramIcon(&menuitem,&placementvector);
                programicons.push_back(menuitem);

                programicons[i].spriteimage = GetVersionParserData().appsnotuptodate[i].appicon;
                programicons[i].spritetexture.loadFromImage(programicons[i].spriteimage);
                programicons[i].sprite.setTexture(programicons[i].spritetexture);

                SetProgramIconLength(GetProgramIconLength()+1);

                if(i==0){
                    SetTopScrollLimit(programicons[i].sprite.getPosition().y+100);
                }else if(i==GetVersionParserData().numberofappsnotuptodate-1){
                    SetBottomScrollLimit(programicons[i].sprite.getPosition().y+100);
                }
            }
            //handle banner image loading
            banner.spriteimage.create(NotUpToDateBanner.width,NotUpToDateBanner.height,NotUpToDateBanner.pixel_data);

            //bannerbackarrow.spriteimage.create(NotUpToDateBannerMaterialBack.width,NotUpToDateBannerMaterialBack.height);
        }

        void AppDrawer::SecurityIssueSpawn(){
            sf::Vector2i placementvector = sf::Vector2i(0,1);
            for(int i = 0;GetVersionParserData().numberofappssecurityissues > i;++i){
                xenon::gui::MenuItem menuitem = xenon::gui::MenuItem(GetVersionParserData().appssecurityissues[i]);

                menuitem.title.setString(GetVersionParserData().appssecurityissues[i].appname);
                SpawnGenericProgramIcon(&menuitem,&placementvector);
                programicons.push_back(menuitem);
                programicons[i].spriteimage = GetVersionParserData().appssecurityissues[i].appicon;
                programicons[i].spritetexture.loadFromImage(programicons[i].spriteimage);
                programicons[i].sprite.setTexture(programicons[i].spritetexture);

                SetProgramIconLength(GetProgramIconLength()+1);

                if(i==0){
                    SetTopScrollLimit(programicons[i].sprite.getPosition().y+100);
                }else if(i==GetVersionParserData().numberofappssecurityissues-1){
                    SetBottomScrollLimit(programicons[i].sprite.getPosition().y+100);
                }
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

        void AppDrawer::ExecuteExternalApplication(const TCHAR *appname){
           // additional information
            // additional information
            STARTUPINFO startupinfo;
            PROCESS_INFORMATION processinfo;

            // set the size of the structures
            ZeroMemory( &startupinfo, sizeof(startupinfo) );
            startupinfo.cb = sizeof(startupinfo);
            ZeroMemory( &processinfo, sizeof(processinfo) );

           // start the program up
           CreateProcess( appname,   // the path
             NULL,        // Command line
             NULL,           // Process handle not inheritable
             NULL,           // Thread handle not inheritable
             FALSE,          // Set handle inheritance to FALSE
             0,              // No creation flags
             NULL,           // Use parent's environment block
             NULL,           // Use parent's starting directory
             &startupinfo,            // Pointer to STARTUPINFO structure
             &processinfo             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
             );
             // Close process and thread handles.
             CloseHandle( processinfo.hProcess );
             CloseHandle( processinfo.hThread );
        }

        void AppDrawer::EventUpdate(sf::Event *currentevent){
            if(currentevent->type == sf::Event::MouseWheelScrolled){
                if(currentevent->mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
                    float viewymovement = currentevent->mouseWheelScroll.delta*-20;
                    if(GetTopScrollLimit() < viewymovement+programsview.getCenter().y && GetBottomScrollLimit() > viewymovement+programsview.getCenter().y){
                        programsview.move(sf::Vector2f(0,viewymovement));
                    }
                }
            }
        }

        void AppDrawer::Update(sf::RenderWindow *window, bool lostfocus){
            if(bannerbackarrow.IsClicked(window,lostfocus)){
                GoBackToMainScreen();
            }
            for(int i = 0; GetProgramIconLength() > i; ++i){
                if(programicons[i].IsClicked(window,lostfocus,true,programsview) && !IsLimitClicksSet()){
                    ExecuteExternalApplication(programicons[i].GetAppLocation().c_str());
                    limitclicks.restart();
                    SetLimitClicksSet(true);
                }else if(limitclicks.getElapsedTime().asSeconds() >= 1){
                    SetLimitClicksSet(false);
                }
                programicons[i].spritetexture.loadFromImage(programicons[i].spriteimage);
                programicons[i].sprite.setTexture(programicons[i].spritetexture);
            }
        }

        void AppDrawer::Draw(sf::RenderWindow *window, bool lostfocus){
            Update(window,lostfocus);

            window->setView(programsview);

            for(int i = 0; programicons.size() > i; ++i){
                window->draw(programicons[i].sprite);
                window->draw(programicons[i].title);
            }

            window->setView(window->getDefaultView());

            window->draw(banner.sprite);
            window->draw(bannerbackarrow.sprite);
        }
    } /* namespace gui */
} /* namespace xenon */
