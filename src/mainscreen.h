/*
 * MainScreen.h
 *
 *  Created on: Apr 28, 2017
 *      Author: Bobby
 */

#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_

#include "versionparser.h"
#include "clickablesprite.h"

#include "Resources/divider.h"

#include "Resources/materialcheckicon.h"
#include "Resources/materialwarningicon.h"
#include "Resources/materialerroricon.h"

#include "Resources/uptodatebutton.h"
#include "Resources/notuptodatebutton.h"
#include "Resources/securityissuebutton.h"

namespace xenon {
    namespace gui {
        /*struct MainScreenIsDrawing{
            bool uptodatebutton = false;
            bool notuptodatebutton = false;
            bool securityissue
        };*/
        class MainScreen {
        public:
            MainScreen(xenon::dict::VersionParserData datatouse);
            MainScreen(sf::Font statusfonttouse,xenon::dict::VersionParserData datatouse);
            //virtual ~MainScreen();

            void SpawnStatusArea();
            void Spawn();

            void Draw(sf::RenderWindow *window);

            bool IsUpToDateButtonClicked(sf::RenderWindow *window, bool lostfocus) { return uptodatebutton.IsClicked(window,lostfocus); }
            bool IsNotUpToDateButtonClicked(sf::RenderWindow *window, bool lostfocus) { return notuptodatebutton.IsClicked(window,lostfocus); }
            bool IsSecurityIssueButtonClicked(sf::RenderWindow *window, bool lostfocus) { return securityissuebutton.IsClicked(window,lostfocus); }
        protected:
            xenon::gui::ClickableSprite divider;

            xenon::gui::ClickableSprite statussprite;
            sf::Font statusfont;
            sf::Text statustext;

            xenon::gui::ClickableSprite uptodatebutton;
            xenon::gui::ClickableSprite notuptodatebutton;
            xenon::gui::ClickableSprite securityissuebutton;

            const xenon::dict::VersionParserData& GetVersionData() const {
                return datatouse_;
            }

            xenon::dict::AppStatus GetWorstAppStatus() const {
                return worstappstatus_;
            }

            void SetWorstAppStatus(xenon::dict::AppStatus worstappstatus) {
                worstappstatus_ = worstappstatus;
            }
        private:
            xenon::dict::VersionParserData datatouse_;
            xenon::dict::AppStatus worstappstatus_;
        };
    } /* namespace gui */
} /* namespace xenon */

#endif /* MAINSCREEN_H_ */
