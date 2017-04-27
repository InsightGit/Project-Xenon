/*
 * dictupdater.h
 *
 *  Created on: Apr 20, 2017
 *      Author: Bobby
 */

#ifndef DICTUPDATER_H_
#define DICTUPDATER_H_

#include <windows.h>

#include <string>
#include <fstream>
#include <sstream>

#include <SFML/Network.hpp>
//#include <json/value.h>
#include <rapidjson/Document.h>

namespace xenon {
    namespace dict {
        class DictUpdater {
        public:
            DictUpdater();
            virtual ~DictUpdater();

            bool CheckForUpdates();
        protected:
            sf::Socket::Status Connect(const std::string ipaddress){
                return connection_.connect(ipaddress,59000);
            }
            sf::Socket::Status SendPacket(sf::Packet *packettosend){
                return connection_.send(*packettosend);
            }
            sf::Socket::Status RecievePacket(sf::Packet *packettouse){
                return connection_.receive(*packettouse);
            }
            void Disconnect(){
                connection_.disconnect();
            }

            bool DoesFileExist() const {
                return fileexist_;
            }

            void SetFileExist(bool fileexists = false) {
                fileexist_ = fileexists;
            }

            void Update();
        private:
            sf::TcpSocket connection_;
            bool fileexist_ = false;
        };
    } /* namespace dict */
} /* namespace xenon */

#endif /* DICTUPDATER_H_ */
