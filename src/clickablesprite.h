/*
 * clickablesprite.h
 *
 *  Created on: Apr 28, 2017
 *      Author: Bobby
 */

#ifndef CLICKABLESPRITE_H_
#define CLICKABLESPRITE_H_


#include <SFML/Graphics.hpp>

namespace xenon {
    namespace gui {
        class ClickableSprite{
        public:
           sf::Texture spritetexture;
           sf::Image spriteimage;
           sf::Sprite sprite;

           bool IsClicked(sf::RenderWindow *window,bool lostfocus,sf::Mouse::Button buttonpressed = sf::Mouse::Left);
        };
    } /* namespace gui */
} /* namespace xenon */

#endif /* CLICKABLESPRITE_H_ */
