#include <Game/Generator/Names.hpp>

#include <NordicEngine/Files/Format/TextFile/Reader.hpp>
#include <NordicEngine/Utility/Maths.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            Names::Names() {
            }

            Names::~Names() {
            }

            std::string Names::getLastName(int iSeed) {
                NordicEngine::Files::TextFile::Reader oReader("GameFiles/Proc/Names/lastNames");
                oReader.readFile();
                std::vector<std::string> vNames = oReader.getContent();

                int iName = NordicEngine::getRandom(0, vNames.size(), iSeed);
                return vNames.at(iName);
            }

            std::string Names::getMaleName(int iSeed) {
                NordicEngine::Files::TextFile::Reader oReader("GameFiles/Proc/Names/maleNames");
                oReader.readFile();
                std::vector<std::string> vNames = oReader.getContent();
            
                int iName = NordicEngine::getRandom(0, vNames.size(), iSeed);
                return vNames.at(iName);
            }

            std::string Names::getFemaleName(int iSeed) {
                NordicEngine::Files::TextFile::Reader oReader("GameFiles/Proc/Names/femaleNames");
                oReader.readFile();
                std::vector<std::string> vNames = oReader.getContent();
                
                int iName = NordicEngine::getRandom(0, vNames.size(), iSeed);
                return vNames.at(iName);
            }
        };
    };
};
