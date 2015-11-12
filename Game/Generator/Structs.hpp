#ifndef NordicArts_Game_Generators_Structs_H
#define NordicArts_Game_Generators_Structs_H

namespace NordicArts {
    namespace Game {
        namespace Generators {
            struct Job {
                // Job Name
                std::string cJobName;
                std::string cParentJob;

                // Ages
                int iMinAge			= 0;
                int iMaxAge			= 0;

                // Distance
                int iMaxDistance	= 0;

                // Building Needed
                bool bHouseNeeded	= false;
                bool bShopNeeded	= false;
            };

            struct Person {
                // Name
                std::string cFirstName;
                std::string cLastName;

                // Age
                int iAge		= 0;
                int iMaxAge		= 0;

                // Sex
                bool bMale		= false;

                // Homeless
                bool bHomeless	= false;

                // Job
                Job sJob;
            };

            struct Family {
                // Name
                std::string cFamilyName;

                // Parents
                Person sDad;
                Person sMum;

                // Family details
				int iMales;
				int iFemales;
                int iFamilySize;

                // GrandParents
                std::vector<Person> vGrandParents;

                // Children
                std::vector<Person> vChildren;
            };

            struct Settlement {
                // Name
                std::string cName;

                // Size
                int iSize;
                int iHouses;
                int iShops;
                int iPeople;

                // Official in charge
                bool bMayorAppointed;

                // People
                std::vector<Person> vPeople;
            };

            struct NewJob {
                std::string cName;

                // Age Requirements
                int iMinAge;
                int iMaxAge;

                // Distance Requiremnts
                int iDistance;
                int iMaxDistane;

                // Building Requirements
                bool bShop;
                bool bHouse;

                // Parent Job
                NewJob *sParentJob;

                NewJob(std::string _cName, int _iMinAge = 0, int _iMaxAge = 0, int _iDistance = 0, int _iMaxDistance = 0, bool _bShop = false, bool _bHouse = false) :
                        cName(_cName), iMinAge(_iMinAge), iMaxAge(_iMaxAge), bShop(_bShop), bHouse(_bHouse) {
                    sParentJob = nullptr;
                }
            };

            struct NewPerson {
                // Name
                std::string cFirstName;
                std::string cLastName;

                // Parents
                NewPerson *sDad;
                NewPerson *sMum;

                // Family
                std::vector<NewPerson> vSiblings;
                std::vector<NewPerson> vChildren;

                // Job
                NewJob *sJob;

                NewPerson(std::string _cFirstName, std::string _cLastName) :
                        cFirstName(_cFirstName), cLastName(_cLastName) {
                    sDad = nullptr;
                    sMum = nullptr;
                    sJob = nullptr;
                }
            };

            struct NewFamily {
                // Name
                std::string cName;

                // Parents
                NewPerson *sDad;
                NewPerson *sMum;

                // Family details
                int iMales;
                int iFemales;
                int iSize;

                // GrandParents
                std::vector<NewPerson> vGrandParents;

                // Children
                std::vector<NewPerson> vChildren;

                NewFamily(std::string _cName, int _iMales = 0, int _iFemales = 0, int _iSize = 0) :
                        cName(_cName), iMales(_iMales), iFemales(_iFemales), iSize(_iSize) {
                    sDad = nullptr;
                    sMum = nullptr;
                }
            };

            struct NewSettlement {
                // Name
                std::string cName;

                // Size
                int iSize;
                int iHouses;
                int iShops;
                int iPeople;

                // Official in charge
                NewPerson *sLeader;

                // People
                std::vector<NewFamily> vFamilies;

                NewSettlement(std::string _cName, int _iSize = 0, int _iHouses = 0, int _iShops = 0, int _iPeople = 0) :
                        cName(_cName), iSize(_iSize), iHouses(_iHouses), iShops(_iShops), iPeople(_iPeople) {
                    sLeader = nullptr;
                }
            };
        };
    };
};

#endif
