/*
 * AppDrawer.h
 *
 *  Created on: Apr 30, 2017
 *      Author: Bobby
 */

#ifndef APPDRAWER_H_
#define APPDRAWER_H_

#include "menuitem.h"
#include "scene.h"

#include "Resources/uptodatebanner.h"
#include "Resources/uptodatebannermaterialback.h"

namespace xenon {
    namespace gui {
        class AppDrawer {
        public:
            AppDrawer(xenon::dict::VersionParserData versionparserdatatouse, xenon::dict::AppStatus appstatustoopen, xenon::Scene *currentscene);
            virtual ~AppDrawer();

            void Spawn();

            void Update(sf::RenderWindow *window, bool lostfocus);

            void Draw(sf::RenderWindow *window, bool lostfocus);
        protected:
            std::vector<xenon::gui::MenuItem> programicons;
            sf::View programsview = sf::View(sf::FloatRect(0,0,740,580));
            sf::Font font;
            xenon::gui::ClickableSprite banner;
            xenon::gui::ClickableSprite bannerbackarrow;

            xenon::dict::AppStatus GetAppStatus() const {
                return appstatus_;
            }

            const xenon::dict::VersionParserData& GetVersionParserData() const {
                return versionparserdata_;
            }

            unsigned int GetProgramIconLength() const {
                return programiconlength_;
            }

            void SetProgramiconlength(unsigned int programiconlength = 0) {
                programiconlength_ = programiconlength;
            }

            void GoBackToMainScreen(){
                currentscene_ = new Scene(1);
            }

        private:
            xenon::dict::VersionParserData versionparserdata_;
            xenon::dict::AppStatus appstatus_;
            xenon::Scene *currentscene_;
            unsigned int programiconlength_ = 0;
        };
    } /* namespace gui */
} /* namespace xenon */

#endif /* APPDRAWER_H_ */
