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

    void Scene::Draw(sf::RenderWindow *window){
        //checks apps versions
        if(GetId()==0){
            Json::Value jsonroot = Json::Value(GetJsonFileText());
            xenon::dict::VersionParser parser(&(jsonroot["apps"]));
            SetAppStatuses(parser.ParseVersions());
            SetId(1);
        }else if(GetId()==1){
            //
        }
    }
} /* namespace xenon */
