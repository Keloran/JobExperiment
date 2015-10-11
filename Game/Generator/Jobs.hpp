#ifndef NordicArts_Game_Generators_Jobs_H
#define NordicArts_Game_Generators_Jobs_H

#include <Game/Includes.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            struct Job {
                int iMinAge;
                int iMaxAge;
                int iMaxDistance;

                std::string cJobName;
                std::string cParentJob;

                bool bNeedsHouse;
                bool bNeedsShop;
            };

            class Jobs {
            // Variables
            public:
            protected:
            private:
                int m_iSeed;
                int m_iAge;

                std::vector<Job> m_vJobs;

            // Methods
            public:
                Jobs(int iPeople, int iSeed);
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
