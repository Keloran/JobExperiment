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

            Family People::makeFamily(std::string cLastName, std::vector<Person> vPeople) {
                Family sFamily;

                bool bGrandParent   = false;
                bool bChild         = false;
                bool bMum           = false;
                bool bDad           = false;
                bool bAdded         = false;
                
                sFamily.cLastName = cLastName;

                for (size_t i = 0; i != vPeople.size(); i++) {
                    bGrandParent    = false;
                    bChild          = false;
                    bAdded          = false;

                    if (sFamily.sDad.cFirstName != "") { bDad = true; }
                    if (sFamily.sMum.cFirstName != "") { bMum = true; }
                    if (vPeople.at(i).iAge >= 60) { bGrandParent = true; }
                    if (vPeople.at(i).iAge <= 21) { bChild = true; }

                    std::string cInfo = "Person is ";
                    cInfo += ("Male: " + NordicEngine::getString(vPeople.at(i).bMale));
                    cInfo += (", Aged: " + NordicEngine::getString(vPeople.at(i).iAge));
                    printIt(cInfo);

                    // Add Parents
                    if (vPeople.at(i).bMale) {
                        if (!bDad) {
                            sFamily.sDad    = vPeople.at(i);
                            bAdded          = true;
                            bDad            = true;
                        }
                    } else {
                        if (!bMum) {
                            sFamily.sMum    = vPeople.at(i);
                            bAdded          = true;
                            bMum            = true;
                        }
                    }

                    // Add others
                    if (!bAdded) { 
                        if (bGrandParent) { sFamily.vGrandParents.push_back(vPeople.at(i)); }
                        if (bChild) { sFamily.vChildren.push_back(vPeople.at(i)); }
                    }
                }

                return sFamily;
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

                    // Temp Family
                    std::vector<Person> vPeople;

                    for (int j = 0; j != iFamilySize; j++) {
                        setMinAge(0);
                        if (j == 0) { setMinAge(21); } // need at least 1 adult 

                        Person sPerson      = getPerson(cLastName, oMarkov.generateWord());
                        m_vPeople.push_back(sPerson);
                        vPeople.push_back(sPerson);
                    }

                    // Actual Family
                    Family sFamily = makeFamily(cLastName, vPeople);
                    printIt(sFamily.sMum.cFirstName);
                    printIt(sFamily.sDad.cFirstName);

                    m_vFamilies.push_back(sFamily);
                    cStatus = ("Generated the " + cLastName + " Family");
                    printIt(cStatus);

                    iTotalPeople = (iTotalPeople - iFamilySize);
                    if (iTotalPeople <= 0) { break; };
                }

                cStatus = "Generated Families";
                printIt(cStatus);

                cStatus = "Generating Loners";
                printIt(cStatus);

                printIt(m_vFamilies.size());
                for (size_t i = 0; i != m_vFamilies.size(); i++) {
                    printIt(m_vFamilies.at(i).vGrandParents.size());
                    printIt(m_vFamilies.at(i).vChildren.size());
                    printIt(m_vFamilies.at(i).sDad.cFirstName);
                    printIt(m_vFamilies.at(i).sMum.cFirstName);
                }

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
