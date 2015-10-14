#include <Game/Generator/People.hpp>
#include <Game/Generator/Jobs.hpp>

#include <NordicEngine/Utility/Maths.hpp>
#include <NordicEngine/Files/Format/TextFile/Reader.hpp>
#include <NordicEngine/Utility/Markov.hpp>
#include <NordicEngine/String/String.hpp>
#include <NordicEngine/Utility/NameGen.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            People::People(Settlement sSettlement, int iSeed) : m_sSettlement(sSettlement), m_iSeed(iSeed) {
            }

            People::~People() {
            }

            void People::setHomeless(bool bHomeless) {
                m_bHomeless = bHomeless;
            }
            void People::setMinAge(int iMinAge) {
                m_iMinAge = iMinAge;
            }

            Person People::getPerson(std::string cLastName, std::string cFirstName) {
                int iAge    = NordicEngine::getRandom(m_iMinAge, 99, m_iSeed);
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
                sPerson.bHomeless   = m_bHomeless;

                Jobs oJob(m_sSettlement, sPerson, m_iSeed);
                oJob.generate();

                sPerson.sJob    = oJob.getJob();
                if (sPerson.sJob.cJobName == "Mayor") { m_sSettlement.bMayorAppointed = true; }

                personInfo(sPerson);
                return sPerson;
            }

            void People::personInfo(Person sPerson) {
                std::string cStatus = "Generated ";
                cStatus += (sPerson.sJob.cJobName + " ");

                if (sPerson.sJob.cParentJob != "") {
                    cStatus += (sPerson.sJob.cParentJob + " ");
                }

                cStatus += (NordicEngine::getString(sPerson.iAge) + "year old ");

                cStatus += (sPerson.cFirstName + " ");
                cStatus += (sPerson.cLastName + " ");

                printIt(cStatus);
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

                // Generate last name
                NordicEngine::NameGen oNameGen(m_iSeed);
                oNameGen.generateLists();

                std::string cStatus = "Generating Families";

                printIt(cStatus);

                // create familys
                int iFamilySize     = 2;
                int iTotalPeople    = m_sSettlement.iPeople;
                int iFamilys        = NordicEngine::getRandom((int)(m_sSettlement.iPeople / m_sSettlement.iHouses), (m_sSettlement.iPeople - m_sSettlement.iHouses), m_iSeed);
                int iHousesTaken    = iFamilys;
                for (int i = 0; i != iFamilys; i++) {
                    int iRandLength = NordicEngine::getRandom(3, 6, m_iSeed);
                    iFamilySize = NordicEngine::getRandom(2, (int)(m_sSettlement.iPeople / iFamilys), m_iSeed);

                    std::string cLastName = oNameGen.generateName(iRandLength);
                    cStatus = ("Generating the " + cLastName + " Family");
                    printIt(cStatus);

                    for (int j = 0; j != iFamilySize; j++) {
                        setMinAge(0);
                        if (j == 0) { setMinAge(21); } // need at least 1 adult 

                        Person sPerson      = getPerson(cLastName, oMarkov.generateWord());
                        m_vPeople.push_back(sPerson);
                    }
                    cStatus = ("Generated the " + cLastName + " Family");
                    printIt(cStatus);

                    iTotalPeople = (iTotalPeople - iFamilySize);
                    if (iTotalPeople <= 0) { break; };
                }

                cStatus = "Generated Families";
                printIt(cStatus);

                cStatus = "Generating Loners";
                printIt(cStatus);

                // People not in a family
                int iHomeless = (iTotalPeople - (m_sSettlement.iHouses - iHousesTaken));
                bool bHomeless = false;
                for (int i = 0; i != iTotalPeople; i++) {
                    int iRandLength = NordicEngine::getRandom(3, 6, m_iSeed);

                    bHomeless = false;
                    if (iHomeless >= 1) { bHomeless = true; }

                    std::string cLastName   = oNameGen.generateName(iRandLength);
                    std::string cFirstName  = oMarkov.generateWord();

                    setHomeless(bHomeless);
                    Person sPerson      = getPerson(cLastName, cFirstName);
                    iHomeless           = (iHomeless - 1);

                    m_vPeople.push_back(sPerson);
                }

                cStatus = "Generated Loners";
                printIt(cStatus);
            }
        };
    };
};
