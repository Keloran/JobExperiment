#include <Game/Generator/FamilyTree.hpp>

#include <Game/Generator/Family.hpp>

namespace NordicArts {
	namespace Game {
		namespace Generators {
			FamilyTree::FamilyTree(int iStartFamilies, int iGenerations, int iSeed) : m_iStartFamilies(iStartFamilies), m_iGenerations(iGenerations), m_iSeed(iSeed) {
			}

			FamilyTree::~FamilyTree() {
			}

			void FamilyTree::generate() {
				std::vector<Family> vStartFamilies;

				for (int i = 0; i != m_iStartFamilies; i++) {
					Family oFamily;
					oFamily.generate(m_iSeed);

					vStartFamilies.push_back(oFamily);
				}
			}
		};
	};
};
