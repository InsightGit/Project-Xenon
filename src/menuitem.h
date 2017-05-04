/*
 * MenuItem.h
 *
 *  Created on: Apr 30, 2017
 *      Author: Bobby
 */

#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "clickablesprite.h"

#include "versionparser.h"

namespace xenon {
    namespace gui {
        class MenuItem : public ClickableSprite {
        public:
            sf::Text title;

            MenuItem(xenon::dict::AppData associatedfullappdatatouse){
                associatedfullappdata_ = associatedfullappdatatouse;
            }

            std::string GetAppLocation(){
                return associatedfullappdata_.fullapplocation;
            }
        private:
            xenon::dict::AppData associatedfullappdata_;
        };
    } /* namespace gui */
} /* namespace xenon */

#endif /* MENUITEM_H_ */
