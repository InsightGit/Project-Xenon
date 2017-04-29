/*
 * Scene.cc
 *
 *  Created on: Apr 21, 2017
 *      Author: Bobby
 */

#include "scene.h"

namespace xenon {
    Scene::Scene(int id) {
        // TODO Auto-generated constructor stub
        id_ = id;
    }

    Scene::~Scene() {
        // TODO Auto-generated destructor stub
    }

    bool Scene::Spawn(){
        return true;
    }

    void Scene::Update(sf::Event *currentevent){
        //ONLY for event updating
        if(currentevent->type == sf::Event::LostFocus){
            SetLostFocus(true);
        }else if(currentevent->type == sf::Event::GainedFocus){
            SetLostFocus(false);
        }
    }

    void Scene::Draw(sf::RenderWindow *window){
        //checks apps versions
        if(GetId()==0){
            xenon::dict::VersionParser parser(GetJsonFileText());
            SetAppStatuses(parser.ParseVersions());
            SetId(1);
        }else if(GetId()==1){
            //
        }
    }
} /* namespace xenon */
