#include <Game/Generator/People.hpp>
#include <Game/Generator/Jobs.hpp>

#include <NordicEngine/Utility/Maths.hpp>
#include <NordicEngine/ThirdParty/jsonxx/jsonxx.h>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            People::People(int iPeople, int iSeed) : m_iPeople(iPeople), m_iSeed(iSeed) {
            }

            People::~People() {
            }

            Person People::getPerson() {
                int iAge = NordicEngine::getRandom(0, 99, m_iSeed);
                Person sPerson;

                return sPerson;
            }

            std::vector<Person> People::getPeople() {
                std::vector<Person> vPeople;

                return vPeople;
            }

            void People::generate() {
                std::vector<std::string> vFirstNames;
                std::vector<std::string> vLastNames;

                NordicEngine::Files::TextFile::Reader oFile("GameFiles/Scripts/Names.json");
                jsonxx::Object oJSON;
                oJSON.parse(oFile.read());
                
                jsonxx:Array aNames = oJSON.get<jsonxx::Array>("Names");
                for (size_t i = 0; i != aNames.size(); i++) {
                    std::string cName = aNames.get<jsonxx::Object(i).get<jsonxx::String>("name");
                    if (
                }
            }
        };
    };
};
