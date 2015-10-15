#ifndef NordicArts_Game_Generators_Structs_H
#define NordicArts_Game_Generators_Structs_H

namespace NordicArts {
    namespace Game {
        namespace Generators {
            struct Job {
                int iMinAge;
                int iMaxAge;
                int iMaxDistance;
    
                std::string cJobName;
                std::string cParentJob;

                bool bHouseNeeded;
                bool bShopNeeded;
            };

            struct Person {
                int iAge;
                int iMaxAge;
                
                bool bMale;
                bool bHomeless;

                Job sJob;
                
                std::string cFirstName;
                std::string cLastName;
            };

            struct Family {
                std::string cLastName;
                
                Person sDad;
                Person sMum;
                
                std::vector<Person> vGrandParents;
                std::vector<Person> vChildren;
            };

            struct Settlement {
                std::string cName;
                
                int iSize;
                int iHouses;
                int iShops;
                int iPeople;

                bool bMayorAppointed; 

                std::vector<Person> vPeople;
            };
        };
    };
};

#endif
