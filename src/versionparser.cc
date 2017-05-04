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
            /*xenon::dict::AppStatus GetChromeAppStatus(std::string latestversion){
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
                if(versionnum >= latestversion){
                    return xenon::dict::UpToDate;
                }else if(versionnum <= 43){
                    return xenon::dict::SecurityIssue;
                }else{
                    return xenon::dict::NotUpToDate;
                }
            }*/
            xenon::dict::AppData NameToAppData(const std::string appname, const std::string applocation){
                AppData appdatatoreturn;
                appdatatoreturn.appname = appname;
                appdatatoreturn.fullapplocation = applocation;
                if(appname=="Google Chrome"){
                    appdatatoreturn.appicon.create(ChromeIcon.width,ChromeIcon.height,ChromeIcon.pixel_data);
                }else if(appname=="Mozilla Firefox"){
                    appdatatoreturn.appicon.create(FirefoxIcon.width,FirefoxIcon.height,FirefoxIcon.pixel_data);
                }
                return appdatatoreturn;
            }
        }

        VersionParser::VersionParser(const std::string jsontext) {
            appproperties.Parse(jsontext.c_str());

            if(sizeof(size_t) == 4){
                is64bit_= false;
            }else if(sizeof(size_t) == 8){
                is64bit_= true;
            }
        }

        VersionParser::~VersionParser() {
            //
        }

        std::vector<std::string> VersionParser::GetPotentialProgramLocations(int *lengthoutput){
            // lists all possible locations for program file locations by searching all logical drives
            std::vector<std::string> potentialprogramlocations;
            DWORD size = MAX_PATH;
            char logicaldrivepaths[MAX_PATH] = {0};
            char *singledrivepath = logicaldrivepaths;

            GetLogicalDriveStrings(size,logicaldrivepaths);
            while(*singledrivepath){
                if(DirectoryExists(singledrivepath)){
                    std::string programfilespath = singledrivepath;
                    programfilespath.append("/Program Files/");
                    potentialprogramlocations.push_back(programfilespath);
                    *(lengthoutput)++;
                    if(is64bit_){
                        std::string programfilespath = singledrivepath;
                        programfilespath.append("/Program Files (x86)/");
                        potentialprogramlocations.push_back(programfilespath);
                        *(lengthoutput)++;
                    }
                }
                // increments string length to go to next drive
                singledrivepath += strlen(singledrivepath) + 1;
            }

            return potentialprogramlocations;
        }

        float GetFileVersion(const char *filepath){
            DWORD  versionhandle = 0;
            UINT   size      = 0;
            PBYTE *buffer  = NULL;
            DWORD  versize   = GetFileVersionInfoSize( filepath, &versionhandle);

            if (versize != NULL)
            {
                char *verdata = new char[versize];

                if (GetFileVersionInfo( filepath, versionhandle, versize, verdata))
                {
                    if (VerQueryValue(verdata,"\\",(VOID FAR* FAR*)&buffer,&size))
                    {
                        if (size)
                        {
                            VS_FIXEDFILEINFO *versioninfo = (VS_FIXEDFILEINFO *)buffer;
                            if (versioninfo->dwSignature == 0xfeef04bd)
                            {
                                //TODO: (Potential Bug) (Bobby if there is) Make it work on 64-bit hardware
                                float version = HIWORD(versioninfo->dwProductVersionMS);
                                version += float(LOWORD(versioninfo->dwProductVersionMS)*0.1);
                                delete[] verdata;
                                return version;
                            }
                        }
                    }
                }
                delete[] verdata;
            }
            return NULL;
        }

        AppStatus VersionParser::GetExistingAppStatus(const std::string appname, const float latestversion, const std::string fullapplocation){
            float versionnum = GetFileVersion(fullapplocation.c_str());
            if(versionnum>=latestversion){
                return UpToDate;
            }else if(appname=="Google Chrome"){
                if(versionnum <= 40){
                    return SecurityIssue;
                }
            }else if(appname=="Mozilla Firefox"){
                if(versionnum <= 43){
                    return SecurityIssue;
                }
            }else if(versionnum < latestversion){
                return NotUpToDate;
            }
        }

        FullAppStatus VersionParser::GetFullAppStatus(const std::string appname, const float latestversion, const std::string applocation){
            int lengthofpotentialprogramlocations = 0;
            std::vector<std::string> potentialprogramlocations = GetPotentialProgramLocations(&lengthofpotentialprogramlocations);
            bool foundprogram = false;
            std::string fullprogramlocation;
            for(int i = 0;lengthofpotentialprogramlocations > i;++i){
                if(FileExists(potentialprogramlocations[i]+applocation)){
                    foundprogram = true;
                    fullprogramlocation = potentialprogramlocations[i]+applocation;
                    break;
                }
            }
            FullAppStatus returnvalue;
            returnvalue.fullapplocation = fullprogramlocation;
            if(foundprogram){
                returnvalue.appstatus = GetExistingAppStatus(appname,latestversion,returnvalue.fullapplocation);
            }else{
                returnvalue.appstatus = NonExistant;
            }
            return returnvalue;
        }

        VersionParserData VersionParser::ParseVersions(){
            VersionParserData datatoreturn;
            for(int i = 0;std::stoi(appproperties["updateapps"]["number"].GetString()) > i;++i){
                FullAppStatus status = GetFullAppStatus(appproperties["updateapps"]["list"][i]["name"].GetString(),
                        appproperties["updateapps"]["list"][i]["latestversion"].GetFloat(),
                        appproperties["updateapps"]["list"][i]["applocation"].GetString());
                AppData appdata = internaldict::NameToAppData(appproperties["updateapps"]["list"][i]["name"].GetString(),status.fullapplocation);
                if(status.appstatus == UpToDate){
                    datatoreturn.appsuptodate.push_back(appdata);
                    datatoreturn.numberofappsuptodate++;
                    datatoreturn.totalnumberofapps++;
                }else if(status.appstatus == NotUpToDate){
                    datatoreturn.appsnotuptodate.push_back(appdata);
                    datatoreturn.numberofappsnotuptodate++;
                    datatoreturn.totalnumberofapps++;
                }else if(status.appstatus == SecurityIssue){
                    datatoreturn.appssecurityissues.push_back(appdata);
                    datatoreturn.numberofappssecurityissues++;
                    datatoreturn.totalnumberofapps++;
                }
            }
            return datatoreturn;
        }
    } /* namespace dict */
} /* namespace xenon */
