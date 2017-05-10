/*
 * versionparser.h
 *
 *  Created on: Apr 24, 2017
 *      Author: Bobby
 */

#ifndef VERSIONPARSER_H_
#define VERSIONPARSER_H_

#define __USE_MINGW_ANSI_STDIO 0

#include <stdlib.h>
#include <windows.h>

#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>

#include <rapidjson/Document.h>

#include <SFML/Graphics.hpp>

//including resource files
#include "Resources/chromeicon.h"
#include "Resources/firefoxicon.h"
#include "Resources/evernoteicon.h"
#include "Resources/googledriveicon.h"
#include "Resources/libreofficeicon.h"
#include "Resources/skypeicon.h"
#include "Resources/vlcicon.h"
#include "Resources/gimpicon.h"
#include "Resources/utorrenticon.h"
#include "Resources/f.luxicon.h"
#include "Resources/spotifyicon.h"
#include "Resources/7zipicon.h"
#include "Resources/itunesicon.h"
#include "Resources/notepad++icon.h"
#include "Resources/thunderbirdicon.h"
#include "Resources/operaicon.h"
#include "Resources/ccleanericon.h"

namespace xenon {
    namespace dict {
        enum AppStatus{
            SecurityIssue,  //this enum does not contain all info; check FullAppStatus
            NotUpToDate,
            UpToDate,
            NonExistant
        };

        struct FullAppStatus{
            AppStatus appstatus;
            std::string fullapplocation;
        };

        struct AppData{
            sf::Image appicon;
            std::string appname;
            std::string fullapplocation;
        };

        namespace internaldict{
            /*static xenon::dict::AppStatus GetChromeAppStatus(const std::string latestversion);
            static std::string GetFirefoxProfileId();
            static xenon::dict::AppStatus GetFirefoxAppStatus(const std::string latestversion);*/
            static xenon::dict::AppData NameToAppData(const std::string appname, const std::string applocation);
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

            std::vector<std::string> GetPotentialProgramLocations(int *lengthoutput);
            // applocation refers to a relative path started in program files directory
            float GetFileVersion(const char *filepath);
            AppStatus GetExistingAppStatus(const std::string appname, const float latestversion,
                                                                      const float latestversion2, const std::string fullapplocation);

            FullAppStatus GetFullAppStatus(const std::string appname, const float latestversion,
                                           const std::string applocation,
                                           const std::vector<std::string> alternateapplocations = std::vector<std::string>(),
                                           const float latestversion2 = 9999999);

            bool FileOrDirectoryExists(const char *filepath){
                DWORD attributes = GetFileAttributes(filepath);

                return (attributes != INVALID_FILE_ATTRIBUTES);
            }

            bool FileExists(const char *filepath){
                DWORD attributes = GetFileAttributes(filepath);

                return (attributes != INVALID_FILE_ATTRIBUTES &&
                       !(attributes & FILE_ATTRIBUTE_DIRECTORY));
            }

            bool DirectoryExists(const char *filepath){
                DWORD attributes = GetFileAttributes(filepath);

                return (attributes != INVALID_FILE_ATTRIBUTES &&
                       (attributes & FILE_ATTRIBUTE_DIRECTORY));
            }

            bool Is64Bit() const {
                 return is64bit_;
             }
        private:
            bool is64bit_ = false;
        };
    } /* namespace dict */
} /* namespace xenon */

#endif /* VERSIONPARSER_H_ */
