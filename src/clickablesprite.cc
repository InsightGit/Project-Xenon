/*
 * clickablesprite.cc
 *
 *  Created on: Apr 28, 2017
 *      Author: Bobby
 */

#include "clickablesprite.h"

namespace xenon {
    namespace gui {
        bool ClickableSprite::IsClicked(sf::RenderWindow *window, bool lostfocus, bool usingcustomview, sf::View viewtouse,
                                        sf::Mouse::Button buttonpressed){
            if(!usingcustomview){
                viewtouse = window->getDefaultView();
            }
            if(sf::Mouse::isButtonPressed(buttonpressed) && !lostfocus){
                if(sprite.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window),viewtouse))){
                    return true;
                }
            }
            return false;
        }
    } /* namespace gui */
} /* namespace xenon */
