/*
 * AppDrawer.h
 *
 *  Created on: Apr 30, 2017
 *      Author: Bobby
 */

#ifndef APPDRAWER_H_
#define APPDRAWER_H_


#include "menuitem.h"

#include "versionparser.h"

#include "scene.h"

#include "Resources/materialbackarrow.h"

#include "Resources/uptodatebanner.h"
#include "Resources/notuptodatebanner.h"
#include "Resources/securityissuebanner.h"

namespace xenon {
    namespace gui {
        class AppDrawer {
        public:
            AppDrawer(xenon::dict::VersionParserData versionparserdatatouse, xenon::dict::AppStatus appstatustoopen, xenon::Scene *currentscene);
            virtual ~AppDrawer();

            void Spawn();

            void EventUpdate(sf::Event *currentevent);

            void Draw(sf::RenderWindow *window, bool lostfocus);
        protected:
            std::vector<xenon::gui::MenuItem> programicons;
            sf::View programsview = sf::View(sf::FloatRect(0,0,740,580));
            sf::Font font;
            sf::Clock limitclicks;
            xenon::gui::ClickableSprite banner;
            xenon::gui::ClickableSprite bannerbackarrow;

            void SpawnGenericProgramIcon(xenon::gui::MenuItem *menuitemtouse, sf::Vector2i *placementvector);
            void UpToDateSpawn();
            void NotUpToDateSpawn();
            void SecurityIssueSpawn();

            void Update(sf::RenderWindow *window, bool lostfocus);

            void ExecuteExternalApplication(const TCHAR *appname);

            xenon::dict::AppStatus GetAppStatus() const {
                return appstatus_;
            }

            const xenon::dict::VersionParserData& GetVersionParserData() const {
                return versionparserdata_;
            }

            unsigned int GetProgramIconLength() const {
                return programiconlength_;
            }

            void SetProgramIconLength(unsigned int programiconlength = 0) {
                programiconlength_ = programiconlength;
            }

            void GoBackToMainScreen(){
                currentscene_->SetId(1);
            }

            bool IsLimitClicksSet() const {
                return limitclicksset_;
            }

            void SetLimitClicksSet(bool limitclicksset = false) {
                limitclicksset_ = limitclicksset;
            }

            float GetBottomScrollLimit() const {
                return bottomscrolllimit_;
            }

            void SetBottomScrollLimit(float bottomscrolllimit) {
                bottomscrolllimit_ = bottomscrolllimit;
            }

            float GetTopScrollLimit() const {
                return topscrolllimit_;
            }

            void SetTopScrollLimit(float topscrolllimit) {
                topscrolllimit_ = topscrolllimit;
            }

        private:
            xenon::dict::VersionParserData versionparserdata_;
            xenon::dict::AppStatus appstatus_;
            xenon::Scene *currentscene_;
            unsigned int programiconlength_ = 0;
            float topscrolllimit_;
            float bottomscrolllimit_;
            bool limitclicksset_ = false;
        };
    } /* namespace gui */
} /* namespace xenon */

#endif /* APPDRAWER_H_ */
