#ifndef NordicArts_Game_Generator_Names_H
#define NordicArts_Game_Generator_Names_H

#include <Game/Includes.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            class Names {
            // Variables
            public:
            protected:
            private:

            // Methods
            public:
                Names();
                ~Names();
                
                std::string getLastName(int iSeed);
                std::string getMaleName(int iSeed);
                std::string getFemaleName(int iSeed);

            protected:
            private:

            };
        };
    };
};

#endif
