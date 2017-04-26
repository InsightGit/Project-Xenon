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
            xenon::dict::AppStatus GetChromeAppStatus(std::string latestversion){
                //detects chrome version number (only works if user has opened app)
                std::ifstream chromejsondatafile("%homepath%/AppData/Local/Google/Chrome/User Data/Local State");
                std::stringstream chromejsondatafilestream;
                chromejsondatafilestream << chromejsondatafile.rdbuf();
                Json::Value chromejsonroot(chromejsondatafilestream.str());
                int versionnumber =(chromejsonroot["variations_permanent_consistancy_country"][0].asCString())[0]*10; //?
                versionnumber = versionnumber + chromejsonroot["variations_permanent_consistancy_country"][0].asCString()[1];
                if(versionnumber >= std::stoi(latestversion)){
                    return xenon::dict::UpToDate;
                }else if(versionnumber <= 40){
                    return xenon::dict::SecurityIssue;
                }else{
                    return xenon::dict::NotUpToDate;
                }
            }

            std::string GetFirefoxProfileId(){
                //finds what is the firefox profile id of the user
                std::ifstream firefoxprofilefile("%appdata%/Mozilla/Firefox/profiles.ini");
                std::string linetext;
                unsigned int linenum = 0;
                std::string profileid;
                while(std::getline(firefoxprofilefile,linetext)){
                    if(linenum == 7){
                        for(unsigned int i = 0; linetext.size() > i;++i){
                            if(i>=15){
                                char *currentchar = &linetext[i];
                                profileid.append(currentchar);
                            }
                        }
                    }
                }
                return profileid;
            }

            xenon::dict::AppStatus GetFirefoxAppStatus(int latestversion){
                std::string profiletext = GetFirefoxProfileId();
                //Using Firefox profile id, look for version number
                std::ifstream firefoxcompatibiltyfile("%appdata%/Mozilla/Firefox/Profiles/"+profiletext+"/compatibility.ini");
                std::string linetext;
                unsigned int linenum = 0;
                std::string versionnumstring;
                while(std::getline(firefoxcompatibiltyfile,linetext)){
                    if(linenum == 2){
                        versionnumstring = linetext[13]+linetext[14];
                    }
                }
                int versionnum = std::stoi(versionnumstring);
                if(versionnum >= latestversion){
                    return xenon::dict::UpToDate;
                }else if(versionnum <= 43){
                    return xenon::dict::SecurityIssue;
                }else{
                    return xenon::dict::NotUpToDate;
                }
            }

            xenon::dict::AppData NameToAppData(const std::string appname){
                AppData appdatatoreturn;
                appdatatoreturn.appname = appname;
                if(appname=="Google Chrome"){
                    appdatatoreturn.appicon.create(ChromeIcon.width,ChromeIcon.height,ChromeIcon.pixel_data);
                }else if(appname=="Mozilla Firefox"){
                    appdatatoreturn.appicon.create(FirefoxIcon.width,FirefoxIcon.height,FirefoxIcon.pixel_data);
                }
                return appdatatoreturn;
            }
        }

        VersionParser::VersionParser(Json::Value *applicationproperties) {
            // TODO Auto-generated constructor stub
            appproperties=*applicationproperties;
        }

        VersionParser::~VersionParser() {
            // TODO Auto-generated destructor stub
        }

        AppStatus VersionParser::GetAppStatus(const std::string appname,const std::string applatestversion,const char *applocation){
            /*if(sizeof(size_t) == 4){
                //32 bit operations

            }else if(sizeof(size_t) == 8){
                //64 bit operations

            }*/
            if(appname == "Google Chrome"){
                if(FileExists(applocation)){
                    return internaldict::GetChromeAppStatus(applatestversion);
                }else{
                    return NonExistant;
                }
            }else if(appname == "Mozilla Firefox"){
                if(FileExists(applocation)){
                    return internaldict::GetFirefoxAppStatus(std::stoi(applatestversion));
                }else{
                    return NonExistant;
                }
            }
        }

        VersionParserData VersionParser::ParseVersions(){
            VersionParserData datatoreturn;
            for(int i = 0;appproperties["number"] > i;++i){
                AppStatus status = GetAppStatus(appproperties["list"][i]["name"].asString(),appproperties["list"][i]["latestversion"].asString(),appproperties["list"][i]["location"].asCString());
                AppData appdata = internaldict::NameToAppData(appproperties["list"][i]["name"].asString());

                if(status == UpToDate){
                    datatoreturn.appsuptodate.push_back(appdata);
                    datatoreturn.numberofappsuptodate++;
                }else if(status == NotUpToDate){
                    datatoreturn.appsnotuptodate.push_back(appdata);
                    datatoreturn.numberofappsnotuptodate++;
                }else if(status == SecurityIssue){
                    datatoreturn.appssecurityissues.push_back(appdata);
                    datatoreturn.numberofappssecurityissues++;
                }
            }
            return datatoreturn;
        }
    } /* namespace dict */
} /* namespace xenon */
