#include <Game/Generator/People.hpp>
#include <Game/Generator/Jobs.hpp>
#include <Game/Generator/Names.hpp>

#include <NordicEngine/Utility/Maths.hpp>
#include <NordicEngine/Files/Format/TextFile/Reader.hpp>
#include <NordicEngine/String/String.hpp>

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

            Person People::getPerson(std::string cLastName) {
                bool bMale = NordicEngine::getRandom(0, 1, m_iSeed);

                return getPerson(cLastName, (bool)bMale);
            }
            Person People::getPerson(std::string cLastName, bool bMale) {
                int iAge    = NordicEngine::getRandom(m_iMinAge, 99, m_iSeed);
                int iMaxAge;
                if (iAge == 99 || iAge == 98) {
                    iMaxAge = 99;
                } else {
                    iMaxAge = NordicEngine::getRandom((iAge + 1), 99, m_iSeed);
                }

                std::string cFirstName;
                Names oNames;
                if (bMale) {
                    cFirstName = oNames.getMaleName(m_iSeed);
                } else {
                    cFirstName = oNames.getFemaleName(m_iSeed);
                }

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

                Person sDad;
                Person sMum;
                std::vector<Person> vGrandParents;
                std::vector<Person> vChildren;
                
                for (size_t i = 0; i != vPeople.size(); i++) {
                    Person sPerson = vPeople.at(i);
                    
                    if (sPerson.bMale) {
                        if (sDad.cFirstName == "") {
                            sDad = sPerson;
                        } else {
                            if (sDad.iAge > sPerson.iAge) {
                                vChildren.push_back(sPerson);
                            } else {
                                vGrandParents.push_back(sDad);
                                sDad = sPerson;
                            }
                        }
                    } else {
                        if (sMum.cFirstName == "") {
                            sMum = sPerson;
                        } else {
                            if (sMum.iAge > sPerson.iAge) {
                                vChildren.push_back(sPerson);
                            } else {
                                vGrandParents.push_back(sMum);
                                sMum = sPerson;
                            }
                        }
                    }
                }

                sFamily.cLastName       = cLastName;
                sFamily.sDad            = sDad;
                sFamily.sMum            = sMum;
                sFamily.vGrandParents   = vGrandParents;
                sFamily.vChildren       = vChildren;

                return sFamily;
            }

            void People::generate() {
                Names oNames;

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

                    std::string cLastName = oNames.getLastName(m_iSeed);
                    cStatus = ("Generating the " + cLastName + " Family");
                    printIt(cStatus);

                    // Temp Family
                    std::vector<Person> vPeople;

                    for (int j = 0; j != iFamilySize; j++) {
                        setMinAge(0);
                        Person sPerson;

                        if (j == 0) { 
                            setMinAge(21); 
                            sPerson = getPerson(cLastName, true);
                        } else if (j == 1) {
                            sPerson = getPerson(cLastName, false);
                        } else {
                            sPerson = getPerson(cLastName);
                        }

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

                // People not in a family
                int iHomeless = (iTotalPeople - (m_sSettlement.iHouses - iHousesTaken));
                bool bHomeless = false;
                for (int i = 0; i != iTotalPeople; i++) {
                    int iRandLength = NordicEngine::getRandom(3, 6, m_iSeed);

                    bHomeless = false;
                    if (iHomeless >= 1) { bHomeless = true; }

                    std::string cLastName   = oNames.getLastName(m_iSeed);

                    setHomeless(bHomeless);
                    Person sPerson      = getPerson(cLastName);
                    iHomeless           = (iHomeless - 1);

                    m_vPeople.push_back(sPerson);
                }

                cStatus = "Generated Loners";
                printIt(cStatus);
            }
        };
    };
};
