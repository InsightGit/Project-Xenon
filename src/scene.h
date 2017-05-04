/*
 * Scene.h
 *
 *  Created on: Apr 21, 2017
 *      Author: Bobby
 */

#ifndef SCENE_H_
#define SCENE_H_
#include <tchar.h>
#include <Shlobj.h>
#include <windows.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>

#include "dictupdater.h"
#include "versionparser.h"

#include "mainscreen.h"


namespace xenon {
    namespace gui{
        class AppDrawer;
    }
    class Scene : sf::NonCopyable {
    public:
        Scene(int id);
        virtual ~Scene();

        int GetId() const {
            return id_;
        }

        void SetId(int id) {
            id_ = id;
        }


        bool Spawn();

        void EventUpdate(sf::Event *currentevent);
        void Draw(sf::RenderWindow *window);
    protected:
        gui::MainScreen *mainscreen;
        gui::AppDrawer *appdrawer;

        void Update(sf::RenderWindow *window);

        bool GetMainScreenSpawned() const {
            return mainscreenspawned_;
        }

        void SetMainScreenSpawned(bool mainscreennotspawned = false) {
            mainscreenspawned_ = mainscreennotspawned;
        }

        bool CheckForUpdates(){
            return updater_.CheckForUpdates();
        }

        std::string GetJsonFileText(){
            std::string path = getenv("APPDATA");
            path.append("/VersionDict.json");
            std::cout << "Path:" << path << "\n";
            std::ifstream jsonfile(path);
            std::stringstream jsonfilebuffer;
            jsonfilebuffer << jsonfile.rdbuf();
            std::cout << jsonfilebuffer.str() << "end\n";
            return jsonfilebuffer.str();
        }


        const dict::VersionParserData& GetAppStatuses() const {
            return appstatuses_;
        }

        void SetAppStatuses(const dict::VersionParserData& appstatuses) {
            appstatuses_ = appstatuses;
        }

        bool IsLostFocus() const {
            return lostfocus_;
        }

        void SetLostFocus(bool lostfocus = false) {
            lostfocus_ = lostfocus;
        }

        bool IsAppDrawerSpawned() const {
            return appdrawerspawned_;
        }

        void SetAppDrawerSpawned(bool appdrawerspawned = false) {
            appdrawerspawned_ = appdrawerspawned;
        }
    private:
        int id_;
        bool lostfocus_ = false;
        bool mainscreenspawned_ = false;
        bool appdrawerspawned_ = false;

        dict::DictUpdater updater_;
        dict::VersionParserData appstatuses_;
    };
} /* namespace xenon */

#endif /* SCENE_H_ */
