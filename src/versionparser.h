/*
 * versionparser.h
 *
 *  Created on: Apr 24, 2017
 *      Author: Bobby
 */

#define __USE_MINGW_ANSI_STDIO 0

#ifndef VERSIONPARSER_H_
#define VERSIONPARSER_H_
#include <windows.h>

#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>

#include <rapidjson/Document.h>

#include <SFML/Graphics.hpp>

//including resource files
#include "Resources/chromeicon.h"
#include "Resources/firefoxicon.h"

namespace xenon {
    namespace dict {
        enum AppStatus{
            SecurityIssue,
            NotUpToDate,
            UpToDate,
            NonExistant
        };

        struct AppData{
            sf::Image appicon;
            std::string appname;
        };

        namespace internaldict{
            static xenon::dict::AppStatus GetChromeAppStatus(const std::string latestversion);
            static std::string GetFirefoxProfileId();
            static xenon::dict::AppStatus GetFirefoxAppStatus(const std::string latestversion);
            static xenon::dict::AppData NameToAppData(const std::string name);
        }

        struct VersionParserData{
            int totalnumberofapps = 0;

            std::vector<AppData> appsnotuptodate;
            int numberofappsnotuptodate = 0;
            std::vector<AppData> appssecurityissues;
            int numberofappssecurityissues = 0;
            std::vector<AppData> appsuptodate;
            int numberofappsuptodate = 0;
        };

        class VersionParser {
        public:
            VersionParser(const std::string jsontext);
            virtual ~VersionParser();

            VersionParserData ParseVersions();
        protected:
            rapidjson::Document appproperties;

            AppStatus GetAppStatus(const std::string appname,const std::string applatestversion);
            bool FileExists(std::string filepath){
                std::ifstream filetoverify(filepath);

                return filetoverify.good();
            }
        };
    } /* namespace dict */
} /* namespace xenon */

#endif /* VERSIONPARSER_H_ */
