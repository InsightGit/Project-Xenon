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

        std::string GetJsonFileText(){
            std::ifstream jsonfile;
            WCHAR path[MAX_PATH];
            char *pathchar;
            SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path);
            wcstombs(pathchar,path,MAX_PATH);
            std::string textfilepath = *pathchar+"\AppData\Roaming\VersionDict.json";
            jsonfile.open("VersionDict.json");
            std::cout << "Open:" << jsonfile.is_open() << "\n";
            std::stringstream jsonfilebuffer;
            jsonfilebuffer << jsonfile.rdbuf();
            std::cout << jsonfilebuffer.str();
            return jsonfilebuffer.str();
        }


        const dict::VersionParserData& GetAppStatuses() const {
            return appstatuses_;
        }

        void SetAppStatuses(const dict::VersionParserData& appstatuses) {
            appstatuses_ = appstatuses;
        }

    private:
        int id_;

        dict::DictUpdater updater_;
        dict::VersionParserData appstatuses_;
    };
} /* namespace xenon */

#endif /* SCENE_H_ */
