/*
 * MenuItem.h
 *
 *  Created on: Apr 30, 2017
 *      Author: Bobby
 */

#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "clickablesprite.h"

namespace xenon {
    namespace gui {
        class MenuItem : public ClickableSprite {
        public:
            sf::Text title;
        };
    } /* namespace gui */
} /* namespace xenon */

#endif /* MENUITEM_H_ */
