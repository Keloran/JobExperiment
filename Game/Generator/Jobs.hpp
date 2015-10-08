#ifndef NordicArts_Game_Generators_Jobs_H
#define NordicArts_Game_Generators_Jobs_H

#include <Game/Includes.hpp>
#include <Game/Generator/Generator.hpp>

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

            class Jobs : public Generator {
            // Variables
            public:
            protected:
            private:
                int m_iSeed;

                std::vector<Job> m_vJobs;

            // Methods
            public:
                Jobs();
                ~Jobs();

                Job getDefault();
                Job getJob(int iAge);
        
                void generate();

            protected:
            private:

            };
        };
    };
};

#endif
