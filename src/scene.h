/*
 * Scene.h
 *
 *  Created on: Apr 21, 2017
 *      Author: Bobby
 */

#ifndef SCENE_H_
#define SCENE_H_
#include <tchar.h>

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
        Json::Value jsonroot;

        void SetId(int id) {
            id_ = id;
        }

        bool CheckForUpdates(){
            return updater_.CheckForUpdates();
        }

        std::string GetJsonFileText(){
            std::stringstream jsonfilebuffer;
            jsonfilebuffer << jsonfile_.rdbuf();
            jsonfile_.close();
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

        std::ifstream jsonfile_ = std::ifstream("%appdata%/VersionDict.json");
        dict::DictUpdater updater_;
        dict::VersionParserData appstatuses_;
    };
} /* namespace xenon */

#endif /* SCENE_H_ */
