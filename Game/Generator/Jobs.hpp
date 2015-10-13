#ifndef NordicArts_Game_Generators_Jobs_H
#define NordicArts_Game_Generators_Jobs_H

#include <Game/Includes.hpp>
#include <Game/Generator/Structs.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            class Jobs {
            // Variables
            public:
            protected:
            private:
                int m_iSeed;

                std::vector<Job> m_vJobs;

                Settlement  m_sSettlement;
                Person      m_sPerson;

            // Methods
            public:
                Jobs(Settlement sSettlement, Person sPerson, int iSeed);
                ~Jobs();

                Job getDefault();
                Job getJob();
        
                void generate();

            protected:
            private:

            };
        };
    };
};

#endif
