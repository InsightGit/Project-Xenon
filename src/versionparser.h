/*
 * versionparser.h
 *
 *  Created on: Apr 24, 2017
 *      Author: Bobby
 */

#ifndef VERSIONPARSER_H_
#define VERSIONPARSER_H_
#include <windows.h>

#include <json/value.h>

namespace xenon {
    namespace dict {
        namespace internaldict{
            static xenon::dict::AppStatus GetChromeAppStatus(std::string location, std::string latestversion);
        }
        enum AppStatus{
            SecurityIssue,
            NotUpToDate,
            UpToDate,
            NonExistant
        };
        class VersionParser {
        public:
            VersionParser(Json::Value *applicationproperties);
            virtual ~VersionParser();

            AppStatus GetAppStatus();
        protected:
            Json::Value appproperties;

            bool FileExists(LPCTSTR filepath){
                DWORD fileattribs = GetFileAttributes(filepath);

                return (fileattribs != INVALID_FILE_ATTRIBUTES && !(fileattribs & FILE_ATTRIBUTE_DIRECTORY));
            }
        };
    } /* namespace dict */
} /* namespace xenon */

#endif /* VERSIONPARSER_H_ */
