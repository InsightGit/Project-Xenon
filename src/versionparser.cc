/*
 * versionparser.cc
 *
 *  Created on: Apr 24, 2017
 *      Author: Bobby
 */

#include "versionparser.h"

namespace xenon {
    namespace dict {
        namespace internaldict{
            xenon::dict::AppStatus GetChromeAppStatus(std::string location, std::string latestversion){
                std::ifstream chromejsondatafile(location);
                std::stringstream chromejsondatafilestream;
                chromejsondatafilestream << chromejsondatafile.rdbuf();
                Json::Value chromejsonroot(chromejsondatafilestream.str());
                int versionnumber =(*(chromejsonroot["variations_permanent_consistancy_country"][0].asCString())[0])*10; //?
                versionnumber = versionnumber + *(chromejsonroot["variations_permanent_consistancy_country"][0].asCString())[1];
                if(versionnumber >= 58){
                    return xenon::dict::UpToDate;
                }else{
                    return xenon::dict::NotUpToDate;
                }
            }
        }

        VersionParser::VersionParser(Json::Value *applicationproperties) {
            // TODO Auto-generated constructor stub
            appproperties=*applicationproperties;
        }

        VersionParser::~VersionParser() {
            // TODO Auto-generated destructor stub
        }

        AppStatus VersionParser::GetAppStatus(){
            /*if(sizeof(size_t) == 4){
                //32 bit operations

            }else if(sizeof(size_t) == 8){
                //64 bit operations

            }*/
            if(appproperties["name"].asString() == "Chrome"){
                if(FileExists(appproperties["location"].asCString())){
                    return internaldict::GetChromeAppStatus(appproperties["location"].asString(),appproperties["latestversion"].asString());
                }else{
                    return NonExistant;
                }
            }
        }
    } /* namespace dict */
} /* namespace xenon */
