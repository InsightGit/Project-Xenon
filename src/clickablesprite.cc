/*
 * clickablesprite.cc
 *
 *  Created on: Apr 28, 2017
 *      Author: Bobby
 */

#include "clickablesprite.h"

namespace xenon {
    namespace gui {
        bool ClickableSprite::IsClicked(sf::RenderWindow *window,bool lostfocus,sf::Mouse::Button buttonpressed){
            if(sf::Mouse::isButtonPressed(buttonpressed) && !lostfocus){
                if(sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window)))){
                    return true;
                }
            }
            return false;
        }
    } /* namespace gui */
} /* namespace xenon */
