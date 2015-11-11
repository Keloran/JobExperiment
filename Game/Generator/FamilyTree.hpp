#ifndef NordicArts_Game_Generators_FamilyTree_H
#define NordicArts_Game_Generators_FamilyTree_H

#include <Game/Includes.hpp>
#include <Game/Generator/Structs.hpp>

namespace NordicArts {
	namespace Game {
		namespace Generators {
			class FamilyTree {
			// Variables
			public:
			protected:
			private:
				int m_iSeed;
				int m_iFamilies;
				int m_iStartFamilies;
				int m_iGenerations;

			// Methods
			public:
				FamilyTree(int iStartFamilies, int iGenerations, int iSeed);
				~FamilyTree();

				void generate();

			protected:
			private:
			
			};
		};
	};
};

#endif
