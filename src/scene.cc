/*
 * Scene.cc
 *
 *  Created on: Apr 21, 2017
 *      Author: Bobby
 */

#include "scene.h"

namespace xenon {
    Scene::Scene(int id) {
        id_ = id;
    }

    Scene::~Scene() {
        delete mainscreen;
    }

    bool Scene::Spawn(){
        return true;
    }

    void Scene::EventUpdate(sf::Event *currentevent){
        //ONLY for event updating
        if(currentevent->type == sf::Event::LostFocus){
            SetLostFocus(true);
        }else if(currentevent->type == sf::Event::GainedFocus){
            SetLostFocus(false);
        }
    }

    void Scene::Update(sf::RenderWindow *window){
        if(GetId()==1){
            if(mainscreen->IsUpToDateButtonClicked(window,IsLostFocus())){
                SetId(2);
            }else if(mainscreen->IsNotUpToDateButtonClicked(window,IsLostFocus())){
                SetId(3);
            }else if(mainscreen->IsSecurityIssueButtonClicked(window,IsLostFocus())){
                SetId(4);
            }
        }
    }

    void Scene::Draw(sf::RenderWindow *window){
        Update(window);
        if(GetId()==0){
            //checks apps versions
            xenon::dict::VersionParser parser(GetJsonFileText());
            SetAppStatuses(parser.ParseVersions());
            SetId(1);
        }else if(GetId()==1){
            if(!GetMainScreenSpawned()){
                mainscreen = new gui::MainScreen(GetAppStatuses());
                mainscreen->Spawn();
                SetMainScreenSpawned(true);
            }
            mainscreen->Draw(window);
        }else if(GetId()==2){
            //
        }
    }
} /* namespace xenon */
