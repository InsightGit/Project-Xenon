/*
 * dictupdater.cc
 *
 *  Created on: Apr 20, 2017
 *      Author: Bobby
 */

#include "dictupdater.h"

namespace xenon {
    namespace dict {
        DictUpdater::DictUpdater() {
            // TODO Auto-generated constructor stub
            DWORD fileattributes = GetFileAttributes("%appdata%/VersionDict.json");
            if(fileattributes != INVALID_FILE_ATTRIBUTES && !(fileattributes & FILE_ATTRIBUTE_DIRECTORY)){ //check if file exists and is not directory
                fileexist_ = true;
            }
        }

        DictUpdater::~DictUpdater() {
            // TODO Auto-generated destructor stub
        }

        void DictUpdater::Update(){
            sf::Packet packet;
            packet << std::string("requestingupdate");
            SendPacket(&packet);
            packet = sf::Packet();
            RecievePacket(&packet);
            std::string jsondata;
            packet >> jsondata;
            std::ofstream jsonfile("%appdata%/VersionDict.json", std::ios_base::app);
            jsonfile << jsondata;
            jsonfile.close();
        }

        bool DictUpdater::CheckForUpdates(){
            if(Connect("192.168.1.99") != sf::Socket::Done){
                return false;
            }
            sf::Packet packettouse;
            /*packettouse << std::string("versionnumrequest");
            if(SendPacket(&packettouse) != sf::Socket::Done){
                Disconnect();
                return false;
            }*/
            if(RecievePacket(&packettouse) != sf::Socket::Done){
                Disconnect();
                return false;
            }
            int majorversion = -1;
            int minorversion = -1;
            int patchversion = -1;
            if(packettouse >> majorversion >> minorversion >> patchversion){
                if(!(majorversion>= 0 && minorversion>=0 && patchversion>=0)){  //check if version numbers are not valid
                    Disconnect();
                    return false;
                }
            }else{
                Disconnect();
                return false;
            }

            if(DoesFileExist()){ //check if file exists and is not directory
                std::ifstream jsonfile("%appdata%/VersionDict.json");
                std::stringstream jsonfilebuffer;
                jsonfilebuffer << jsonfile.rdbuf();
                jsonfile.close();
                rapidjson::Document root;
                root.Parse(jsonfilebuffer.str().c_str());
                if(root["version"]["major"].GetInt() < majorversion){
                    Update();
                }else if(root["version"]["minor"].GetInt() < minorversion){
                    Update();
                }else if(root["version"]["patch"].GetInt() < patchversion){
                    Update();
                }else{
                    return false;
                }
            }else{
                Update();
            }
            return true;
        }
    } /* namespace dict */
} /* namespace xeon */
