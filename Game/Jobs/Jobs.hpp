#ifndef NordicArts_Game_Jobs_H
#define NordicArts_Game_Jobs_H

#include <Game/Includes.hpp>

namespace NordicArts {
    namespace Game {
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

            std::vector<Job> m_vJobs;

        // Methods
        public:
            Jobs(int iSeed);
            ~Jobs();

            Job getJob(int iAge);

        protected:
        private:
            void parseJobs();
        };
    };
};

#endif
