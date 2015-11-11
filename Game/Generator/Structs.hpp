#ifndef NordicArts_Game_Generators_Structs_H
#define NordicArts_Game_Generators_Structs_H

namespace NordicArts {
    namespace Game {
        namespace Generators {
            struct Job {
                int iMinAge			= 0;
                int iMaxAge			= 0;
                int iMaxDistance	= 0;
    
                std::string cJobName;
                std::string cParentJob;

                bool bHouseNeeded	= false;
                bool bShopNeeded	= false;
            };

            struct Person {
                int iAge		= 0;
                int iMaxAge		= 0;
                
                bool bMale		= false;
                bool bHomeless	= false;

                Job sJob;
                
                std::string cFirstName;
                std::string cLastName;
            };

            struct Family {
                std::string cFamilyName;
                
                Person sDad;
                Person sMum;

				int iMales		= 0;
				int iFemales	= 0;
                
                std::vector<Person> vGrandParents;
                std::vector<Person> vChildren;
            };

            struct Settlement {
                std::string cName;
                
                int iSize		= 0;
                int iHouses		= 0;
                int iShops		= 0;
                int iPeople		= 0;

                bool bMayorAppointed	 = false; 

                std::vector<Person> vPeople;
            };
        };
    };
};

#endif
