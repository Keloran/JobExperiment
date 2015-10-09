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
            };

            class Jobs {
            // Variables
            public:
            protected:
            private:
                int m_iSeed;
                int m_iPeople;

                std::vector<Job> m_vJobs;

            // Methods
            public:
                Jobs(int iPeople, int iSeed);
                ~Jobs();

                Job getDefault();
                Job getJob(int iAge);

                std::vector<Job> getJobs();
        
                void generate();

            protected:
            private:

            };
        };
    };
};

#endif
