#include <Game/Generator/Jobs.hpp>

#include <NordicEngine/String/String.hpp>
#include <NordicEngine/Utility/Maths.hpp>
#include <NordicEngine/NordicEngine/Files/Format/TextFile/Reader.hpp>
#include <NordicEngine/NordicEngine/ThirdParty/jsonxx/jsonxx.h>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            Jobs::Jobs(int iPeople, int iSeed) : m_iPeople(iPeople), m_iSeed(iSeed) {
            }
    
            Jobs::~Jobs() {
            }

            Job Jobs::getDefault() {
                Job sJob;
                sJob.iMinAge        = 0;
                sJob.iMaxAge        = 99;
                sJob.iMaxDistance   = 0;
                sJob.cParentJob     = "";
                sJob.cJobName       = "Unemployed";
        
                return sJob;
            }

            std::vector<Job> Jobs::getJobs() {
                std::vector<Job> vJobs;
                for (int i = 0; i < m_iPeople; i++) {
                    int iAge = NordicEngine::getRandom(0, 99, m_iSeed);
                    vJobs.push_back(getJob(iAge));
                }

                return vJobs;
            }

            Job Jobs::getJob(int iAge) {
                std::vector<Job> vJobs;
                for (size_t i = 0; i != m_vJobs.size(); i++) {
                    if (m_vJobs.at(i).iMaxAge < iAge) { continue; }
                    if (m_vJobs.at(i).iMinAge > iAge) { continue; }
    
                    vJobs.push_back(m_vJobs.at(i));
                }

                // Get jobs from subset
                unsigned int iRand = NordicEngine::getRandom(0, vJobs.size(), m_iSeed);
                for (size_t i = 0; i != vJobs.size(); i++) {
                    if (i == iRand) {
                        return vJobs.at(i);
                    }
                }

                return getDefault();
            }

            void Jobs::generate() {
                // Parse the JSON
                NordicEngine::Files::TextFile::Reader oFile("GameFiles/Scripts/Jobs.json");
                jsonxx::Object oJSON;
                oJSON.parse(oFile.read());

                jsonxx::Array aJobs = oJSON.get<jsonxx::Array>("Jobs");
    
                for (size_t i = 0; i != aJobs.size(); i++) {
                    Job sJob;
    
                    sJob.iMaxAge        = aJobs.get<jsonxx::Object>(i).get<jsonxx::Number>("maxAge");
                    sJob.iMinAge        = aJobs.get<jsonxx::Object>(i).get<jsonxx::Number>("minAge");
                    sJob.iMaxDistance   = aJobs.get<jsonxx::Object>(i).get<jsonxx::Number>("maxDistance");
                    sJob.cParentJob     = aJobs.get<jsonxx::Object>(i).get<jsonxx::String>("parentJob");
                    sJob.cJobName       = aJobs.get<jsonxx::Object>(i).get<jsonxx::String>("name");

                    m_vJobs.push_back(sJob);
                }
            }
        };
    };
};
