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
                int iSex	= NordicEngine::getRandom(0, 100, m_iSeed);
                bool bMale = false;
                if (iSex >= 51) { bMale = true; }

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
                cStatus += sPerson.sJob.cJobName;

                if (sPerson.sJob.cParentJob != "") {
                    cStatus += (" " + sPerson.sJob.cParentJob + ", ");
                } else {
					cStatus += ", ";
				}

				if (sPerson.iAge >= 2) {
	                cStatus += (NordicEngine::getString(sPerson.iAge) + " years old, ");
				} else {
					cStatus += (NordicEngine::getString(sPerson.iAge) + " year old, ");
				}

                cStatus += (sPerson.cFirstName + " ");
                cStatus += (sPerson.cLastName + ", ");
				if (sPerson.bMale) {
					cStatus += "Male, ";
				} else {
					cStatus += "Female, ";
				}

				printIt(cStatus);
            }

			void People::familyInfo(Family sFamily) {
				std::string cStatus = "Generated the ";
				cStatus += (sFamily.cFamilyName + " family, ");
				cStatus += (NordicEngine::getString(sFamily.iMales) + " males, ");
				cStatus += (NordicEngine::getString(sFamily.iFemales) + " females, ");
				cStatus += ("Dad " + sFamily.sDad.cFirstName + ", ");
				cStatus += ("Mum " + sFamily.sMum.cFirstName + ", ");

				int iChildren = sFamily.vChildren.size();
				if (iChildren >= 2) {
					cStatus += (NordicEngine::getString(iChildren) + " children, ");
				} else {
					cStatus += (NordicEngine::getString(iChildren) + " child, ");
				}

				int iGrandParents = sFamily.vGrandParents.size();
				if (iGrandParents >= 2) {
					cStatus += (NordicEngine::getString(iGrandParents) + " grandparents, ");
				} else {
					cStatus += (NordicEngine::getString(iGrandParents) + " grandparent, ");
				}

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

				int iMales 		= 0;
				int iFemales	= 0;
                
                for (size_t i = 0; i != vPeople.size(); i++) {
                    Person sPerson = vPeople.at(i);
                    if (sPerson.bMale) {
						iMales += 1;

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
						iFemales += 1;

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

                sFamily.cFamilyName     = cLastName;
                sFamily.sDad            = sDad;
                sFamily.sMum            = sMum;
                sFamily.vGrandParents   = vGrandParents;
                sFamily.vChildren       = vChildren;
				sFamily.iMales			= iMales;
				sFamily.iFemales		= iFemales;

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
					familyInfo(sFamily);

                    m_vFamilies.push_back(sFamily);

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
