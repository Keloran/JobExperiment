#ifndef NordicArts_Game_Generators_People_H
#define NordicArts_Game_Generators_People_H

#include <Game/Includes.hpp>

#include <NordicEngine/Utility/Maths.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            struct Person {
                // Person Details
                int iAge;
                int iMaxAge;

                // Linkers
                int iBornSettlement;
                int iParent;
                int iJob;

                // Male or Female
                bool bMale;
                
                // Name
                std::string cFirstName;
                std::string cLastName;                
            };

            class People {
            // Variables
            public:
            protected:
            private:

            // Methods
            public:
                People();
                ~People();

            protected:
            private:

            };
        };
    };
};

#endif
