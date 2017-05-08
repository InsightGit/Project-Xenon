/*
 * Scene.cc
 *
 *  Created on: Apr 21, 2017
 *      Author: Bobby
 */

#include "scene.h"

#include "appdrawer.h"

namespace xenon {
    Scene::Scene(int id) {
        id_ = id;
    }

    Scene::~Scene() {
        delete mainscreen;
        delete appdrawer;
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

        if(IsAppDrawerSpawned()){
            appdrawer->EventUpdate(currentevent);
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
            //checks apps version scene
            xenon::dict::VersionParser parser(GetJsonFileText());
            SetAppStatuses(parser.ParseVersions());
            SetId(1);
        }else if(GetId()==1){
            //main screen scene
            if(!GetMainScreenSpawned()){
                mainscreen = new gui::MainScreen(GetAppStatuses());
                mainscreen->Spawn();
                SetMainScreenSpawned(true);
            }
            if(IsAppDrawerSpawned()){
                SetAppDrawerSpawned(false);
                delete appdrawer;
            }
            mainscreen->Draw(window);
        }else if(GetId()>=2 && GetId()<=4 && !IsAppDrawerSpawned()){
            if(GetId()==2){
                appdrawer = new gui::AppDrawer(GetAppStatuses(), xenon::dict::UpToDate,this);
            }else if(GetId()==3){
                appdrawer = new gui::AppDrawer(GetAppStatuses(), xenon::dict::NotUpToDate,this);
            }else if(GetId()==4){
                appdrawer = new gui::AppDrawer(GetAppStatuses(), xenon::dict::SecurityIssue,this);
            }

            appdrawer->Spawn();
            SetAppDrawerSpawned(true);
        }else if(GetId()>=2 && GetId()<=4){
            //show apps (2==uptodateapps,3==notuptodateapps,4==securityissueapps)
            appdrawer->Draw(window,IsLostFocus());
        }
    }
} /* namespace xenon */
