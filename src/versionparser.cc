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
                std::string path = "C:";
                path.append(getenv("HOMEPATH"));
                path.append("/AppData/Local/Google/Chrome/User Data/Local State");
                std::cout << path << "\n";
                std::ifstream chromejsondatafile(path);
                std::stringstream chromejsondatafilestream;
                rapidjson::Document chromejsonroot;
                chromejsondatafilestream << chromejsondatafile.rdbuf();
                chromejsonroot.Parse(chromejsondatafilestream.str().c_str());
                //assert(chromejsonroot["variations_permanent_consistency_country"].HasMember());
                std::string wholeversionnumber = chromejsonroot["variations_permanent_consistency_country"][0].GetString();
                int versionnumber = wholeversionnumber[0];
                versionnumber=versionnumber*10;
                versionnumber = versionnumber + wholeversionnumber[1];
                std::cout << "Chrome Version Num:" << chromejsonroot["variations_permanent_consistency_country"][0].GetString() << "\n";
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
                std::string path = getenv("APPDATA");
                path.append("/Mozilla/Firefox/profiles.ini");
                std::cout << path << "\n";
                std::ifstream firefoxprofilefile(path);
                std::string linetext;
                unsigned int linenum = 0;
                std::string profileid;
                while(std::getline(firefoxprofilefile,linetext)){
                    if(linenum == 6){
                        for(int iterator = 0; linetext.size() > iterator;++iterator){
                            if(iterator>=14 && profileid.length()<16){
                                char *currentchar = &linetext[iterator];
                                profileid.append(currentchar);
                            }
                        }
                    }
                    linenum++;
                }
                std::cout << "profileid:" << profileid << "\n";
                return profileid;
            }

            xenon::dict::AppStatus GetFirefoxAppStatus(int latestversion){
                std::string profiletext = GetFirefoxProfileId();
                //Using Firefox profile id, look for version number
                std::string path = getenv("APPDATA");
                path.append("/Mozilla/Firefox/Profiles/");
                path.append(profiletext);
                path.append("/compatibility.ini");
                std::cout << path << "\n";
                std::ifstream firefoxcompatibiltyfile(path);
                std::string linetext;
                unsigned int linenum = 0;
                int versionnum;
                while(std::getline(firefoxcompatibiltyfile,linetext)){

                    if(linenum == 1){
                        versionnum = int(linetext[13])+2;
                    }
                    linenum++;
                }
                std::cout << "Firefox Version Num:" << std::to_string(versionnum) << "\n";
                assert(false);
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

        VersionParser::VersionParser(const std::string jsontext) {
            // TODO Auto-generated constructor stub
            appproperties.Parse(jsontext.c_str());
        }

        VersionParser::~VersionParser() {
            // TODO Auto-generated destructor stub
        }

        AppStatus VersionParser::GetAppStatus(const std::string appname,const std::string applatestversion){
            /*if(sizeof(size_t) == 4){
                //32 bit operations

            }else if(sizeof(size_t) == 8){
                //64 bit operations

            }*/
            if(appname == "Google Chrome"){
                std::string path = "C:";
                path.append(getenv("HOMEPATH"));
                path.append("/AppData/Local/Google/Chrome/User Data/Local State");
                std::cout << path << "\n";
                if(FileExists(path.c_str())){
                    return internaldict::GetChromeAppStatus(applatestversion);
                }else{
                    return NonExistant;
                }
            }else if(appname == "Mozilla Firefox"){
                std::string path = getenv("APPDATA");
                path.append("/Mozilla/Firefox/profiles.ini");
                std::cout << path << "\n";
                if(FileExists(path.c_str())){
                    return internaldict::GetFirefoxAppStatus(std::stoi(applatestversion));
                }else{
                    return NonExistant;
                }
            }
        }

        VersionParserData VersionParser::ParseVersions(){
            VersionParserData datatoreturn;
            assert(appproperties.HasMember("updateapps"));
            for(int i = 0;std::stoi(appproperties["updateapps"]["number"].GetString()) > i;++i){
                AppStatus status = GetAppStatus(appproperties["updateapps"]["list"][i]["name"].GetString(),appproperties["updateapps"]["list"][i]["latestversion"].GetString());
                AppData appdata = internaldict::NameToAppData(appproperties["updateapps"]["list"][i]["name"].GetString());

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
