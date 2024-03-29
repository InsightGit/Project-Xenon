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
                }else if(appname=="Evernote"){
                    appdatatoreturn.appicon.create(EvernoteIcon.width,EvernoteIcon.height,EvernoteIcon.pixel_data);
                }else if(appname=="Google Drive"){
                    appdatatoreturn.appicon.create(GoogleDriveIcon.width,GoogleDriveIcon.height,GoogleDriveIcon.pixel_data);
                }else if(appname=="LibreOffice"){
                    appdatatoreturn.appicon.create(LibreOfficeIcon.width,LibreOfficeIcon.height,LibreOfficeIcon.pixel_data);
                }else if(appname=="Skype"){
                    appdatatoreturn.appicon.create(SkypeIcon.width,SkypeIcon.height,SkypeIcon.pixel_data);
                }else if(appname=="VLC"){
                    appdatatoreturn.appicon.create(VLCIcon.width,VLCIcon.height,VLCIcon.pixel_data);
                }else if(appname=="GIMP"){
                    appdatatoreturn.appicon.create(GIMPIcon.width,GIMPIcon.height,GIMPIcon.pixel_data);
                }else if(appname=="uTorrent"){
                    appdatatoreturn.appicon.create(uTorrentIcon.width,uTorrentIcon.height,uTorrentIcon.pixel_data);
                }else if(appname=="F.lux"){
                    appdatatoreturn.appicon.create(FluxIcon.width,FluxIcon.height,FluxIcon.pixel_data);
                }else if(appname=="Spotify"){
                    appdatatoreturn.appicon.create(SpotifyIcon.width,SpotifyIcon.height,SpotifyIcon.pixel_data);
                }else if(appname=="7-Zip"){
                    appdatatoreturn.appicon.create(SevenZipIcon.width,SevenZipIcon.height,SevenZipIcon.pixel_data);
                }else if(appname=="iTunes"){
                    appdatatoreturn.appicon.create(iTunesIcon.width,iTunesIcon.height,iTunesIcon.pixel_data);
                }else if(appname=="Notepad++"){
                    appdatatoreturn.appicon.create(NotepadPlusPlusIcon.width,NotepadPlusPlusIcon.height,NotepadPlusPlusIcon.pixel_data);
                }else if(appname=="Thunderbird"){
                    appdatatoreturn.appicon.create(ThunderbirdIcon.width,ThunderbirdIcon.height,ThunderbirdIcon.pixel_data);
                }else if(appname=="Opera"){
                    appdatatoreturn.appicon.create(OperaIcon.width,OperaIcon.height,OperaIcon.pixel_data);
                }else if(appname=="CCleaner"){
                    appdatatoreturn.appicon.create(CCleanerIcon.width,CCleanerIcon.height,CCleanerIcon.pixel_data);
                }
                return appdatatoreturn;
            }
        }

        VersionParser::VersionParser(const std::string jsontext) {
            appproperties.Parse(jsontext.c_str());

            /*if(sizeof(size_t) == 4){
                is64bit_= false;
            }else if(sizeof(size_t) == 8){
                is64bit_= true;
            }*/

            is64bit_= true;
        }
        VersionParser::~VersionParser(){}

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
                    *lengthoutput++;
                    std::string programfilesx86path = singledrivepath;
                    programfilesx86path.append("/Program Files (x86)/");
                    potentialprogramlocations.push_back(programfilesx86path);
                    *lengthoutput++;
                }
                // increments string length to go to next drive
                singledrivepath += strlen(singledrivepath) + 1;
            }

            return potentialprogramlocations;
        }

        float VersionParser::GetFileVersion(const char *filepath){
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
                                float major = (versioninfo->dwProductVersionMS >> 16) & 0xffff;
                                float minor = (versioninfo->dwProductVersionMS >>  0) & 0xffff;
                                float revision = (versioninfo->dwProductVersionLS >> 16) & 0xffff;

                                float version = major+(minor*0.1)+(revision*0.0001);

                                delete[] verdata;
                                return version;
                            }
                        }
                    }
                }
            }
            return NULL;
        }

        AppStatus VersionParser::GetExistingAppStatus(const std::string appname, const float latestversion,
                                                      const float latestversion2, const std::string fullapplocation){
            char *fullapplocationchar = new char[fullapplocation.length()+1];
            std::strcpy(fullapplocationchar,fullapplocation.c_str());
            float versionnum = GetFileVersion(fullapplocationchar);
            if(versionnum>=latestversion || versionnum>=latestversion2){
                return UpToDate;
            }else if(versionnum < latestversion){
                if(appname=="Google Chrome"){
                    if(versionnum <= 40){
                        return SecurityIssue;
                    }
                }else if(appname=="Mozilla Firefox"){
                    if(versionnum <= 43){
                        return SecurityIssue;
                    }
                }else if(appname=="Evernote"){
                    if(versionnum <= 4.6001){
                        return SecurityIssue;
                    }
                }else if(appname=="LibreOffice"){
                    if(versionnum <= 5.2005){
                        return SecurityIssue;
                    }
                }else if(appname=="Skype"){
                    if(versionnum <= 5.9){
                        return SecurityIssue;
                    }
                }else if(appname=="VLC"){
                    if(versionnum <= 2.2003){
                        return SecurityIssue;
                    }
                }else if(appname=="GIMP"){
                    if(versionnum <= 2.8016){
                        return SecurityIssue;
                    }
                }else if(appname=="uTorrent"){
                    if(versionnum <= 1.8003){
                        return SecurityIssue;
                    }
                }else if(appname=="F.lux"){
                    if(versionnum <= 3.10){
                        return SecurityIssue;
                    }
                }else if(appname=="Spotify"){
                    if(versionnum <= 0.8002){
                        return SecurityIssue;
                    }
                }else if(appname=="7-Zip"){
                    if(versionnum <= 16.0){
                        return SecurityIssue;
                    }
                }else if(appname=="iTunes"){
                    if(versionnum < 12.6){
                        return SecurityIssue;
                    }
                }else if(appname=="Notepad++"){
                    if(versionnum < 7.3003){
                        return SecurityIssue;
                    }
                }else if(appname=="Thunderbird"){
                    if(versionnum < 45.0){
                        return SecurityIssue;
                    }
                }else if(appname=="Opera"){
                    if(versionnum < 36.0){
                        return SecurityIssue;
                    }
                }else if(appname=="CCleaner"){
                    if(versionnum < 5.0002){
                        return SecurityIssue;
                    }
                }
                return NotUpToDate;
            }
        }

        FullAppStatus VersionParser::GetFullAppStatus(const std::string appname, const float latestversion,
                                                      const std::string applocation,const std::vector<std::string> alternateapplocations,
                                                      const float latestversion2){
            int lengthofpotentialprogramlocations = 0;
            std::vector<std::string> potentialprogramlocations = GetPotentialProgramLocations(&lengthofpotentialprogramlocations);
            bool foundprogram = false;
            std::string fullprogramlocation;
            for(int i = 0;potentialprogramlocations.size() > i;++i){
                if(FileExists(std::string(potentialprogramlocations[i]+applocation).c_str())){
                    foundprogram = true;
                    fullprogramlocation = potentialprogramlocations[i]+applocation;
                }else if(alternateapplocations.size()!=0){
                    for(int iterator2 = 0; alternateapplocations.size() > iterator2;++iterator2){
                        if(FileExists(std::string(potentialprogramlocations[i]+alternateapplocations[iterator2]).c_str())){
                            foundprogram = true;
                            fullprogramlocation = potentialprogramlocations[i]+alternateapplocations[iterator2];
                        }
                    }
                }
                if(foundprogram){
                    break;
                }
            }
            FullAppStatus returnvalue;
            returnvalue.fullapplocation = fullprogramlocation;
            if(foundprogram){
                returnvalue.appstatus = GetExistingAppStatus(appname,latestversion,latestversion2,returnvalue.fullapplocation);
            }else{
                returnvalue.appstatus = NonExistant;
            }
            return returnvalue;
        }

        VersionParserData VersionParser::ParseVersions(){
            VersionParserData datatoreturn;
            for(int i = 0;appproperties["updateapps"]["number"].GetInt() > i;++i){
                FullAppStatus status;
                if(appproperties["updateapps"]["list"][i].HasMember("alternateapplocations")){
                    std::vector<std::string> potentialapplocations;
                    for(int iterator2 = 0;appproperties["updateapps"]["list"][i]["aallength"].GetInt() > iterator2; ++iterator2){
                        potentialapplocations.push_back(appproperties["updateapps"]["list"]
                                                       [i]["alternateapplocations"][iterator2].GetString());
                    }
                    status = GetFullAppStatus(appproperties["updateapps"]["list"][i]["name"].GetString(),
                            appproperties["updateapps"]["list"][i]["latestversion"].GetFloat(),
                            appproperties["updateapps"]["list"][i]["applocation"].GetString(),potentialapplocations,
                            appproperties["updateapps"]["list"][i]["latestversion2"].GetFloat());
                }else{
                    status = GetFullAppStatus(appproperties["updateapps"]["list"][i]["name"].GetString(),
                            appproperties["updateapps"]["list"][i]["latestversion"].GetFloat(),
                            appproperties["updateapps"]["list"][i]["applocation"].GetString());
                }
                if(status.appstatus==NonExistant && appproperties["updateapps"]["list"][i].HasMember("homepathlocation")){
                    status.fullapplocation = "C:";
                    status.fullapplocation.append(getenv("HOMEPATH"));
                    status.fullapplocation.append(appproperties["updateapps"]["list"][i]["homepathlocation"].GetString());
                    if(FileExists(status.fullapplocation.c_str())){
                        if(appproperties["updateapps"]["list"][i].HasMember("latestversion2")){
                            status.appstatus = GetExistingAppStatus(appproperties["updateapps"]["list"][i]["name"].GetString(),
                                                                   appproperties["updateapps"]["list"][i]["latestversion"].GetFloat(),
                                                                   appproperties["updateapps"]["list"][i]["latestversion2"].GetFloat(),
                                                                   status.fullapplocation);
                        }else{
                            status.appstatus = GetExistingAppStatus(appproperties["updateapps"]["list"][i]["name"].GetString(),
                                                                   appproperties["updateapps"]["list"][i]["latestversion"].GetFloat(),
                                                                   99999,
                                                                   status.fullapplocation);
                        }
                    }
                }
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
