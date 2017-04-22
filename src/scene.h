/*
 * Scene.h
 *
 *  Created on: Apr 21, 2017
 *      Author: Bobby
 */

#ifndef SCENE_H_
#define SCENE_H_
#include <SFML/Graphics.hpp>

#include "dictupdater.h"

namespace xenon {
    class Scene : sf::NonCopyable {
    public:
        Scene(int id);
        virtual ~Scene();

        int GetId() const {
            return id_;
        }
        bool Spawn();

        void Draw(sf::RenderWindow *window);
    protected:
        void SetId(int id) {
            id_ = id;
        }

        bool CheckForUpdates(){
            return updater_.CheckForUpdates();
        }
    private:
        int id_;

        xenon::dict::DictUpdater updater_;
    };
} /* namespace xenon */

#endif /* SCENE_H_ */
