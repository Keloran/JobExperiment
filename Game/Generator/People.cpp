#include <Game/Generator/People.hpp>

#include <NordicEngine/Utility/Maths.hpp>
#include <NordicEngine/Files/Format/TextFile/Reader.hpp>
#include <NordicEngine/Utility/Markov.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            People::People(int iPeople, int iHouses, int iSeed) : m_iPeople(iPeople), m_iHouses(iHouses), m_iSeed(iSeed) {
            }

            People::~People() {
            }

            Person People::getPerson(std::string cLastName, std::string cFirstName) {
                int iAge    = NordicEngine::getRandom(0, 99, m_iSeed);
                int iMaxAge;
                if (iAge == 99 || iAge == 98) {
                    iMaxAge = 99;
                } else {
                    iMaxAge = NordicEngine::getRandom((iAge + 1), 99, m_iSeed);
                }
                int iSex    = NordicEngine::getRandom(0, 1, m_iSeed);

                bool bMale = false;
                if (iSex == 1) { bMale = true; }

                Person sPerson;

                sPerson.cFirstName  = cFirstName;
                sPerson.cLastName   = cLastName;
                sPerson.iAge        = iAge;
                sPerson.iMaxAge     = iMaxAge;
                sPerson.bMale       = bMale;

                Jobs oJob(iAge, m_iSeed);
                oJob.generate();

                sPerson.sJob    = oJob.getJob();

                return sPerson;
            }

            std::vector<Person> People::getPeople() {
                generate();

                return m_vPeople;
            }

            void People::generate() {
                NordicEngine::Markov oMarkov;
                oMarkov.setNamesList("GameFiles/Proc/Names/names-list");

                // Generate the list of chances
                oMarkov.generate();

                // create familys
                int iFamilys    = NordicEngine::getRandom(m_iPeople, m_iHouses, m_iSeed);
                int iFamilySize = NordicEngine::getRandom(m_iPeople, iFamilys, m_iSeed);
                for (int i = 0; i != iFamilys; i++) {
                    std::string cLastName = oMarkov.generateWord(m_iSeed);

                    for (int j = 0; j != iFamilySize; j++) {
                        Person sPerson      = getPerson(cLastName, oMarkov.generateWord());
                        m_vPeople.push_back(sPerson);
                    }
                }

                // People not in a family
                int iRemainder = (m_iPeople - (iFamilySize + iFamilys));
                for (int i = 0; i != iRemainder; i++) {
                    Person sPerson      = getPerson(oMarkov.generateWord(), oMarkov.generateWord());

                    printIt(sPerson.cFirstName + " " + sPerson.cLastName);
                    printIt(sPerson.sJob.cJobName + " " + sPerson.sJob.cParentJob);

                    m_vPeople.push_back(sPerson);
                }
            }
        };
    };
};
