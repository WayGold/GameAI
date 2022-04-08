#pragma once
#include "WorldStates.h"

namespace GOAP {
	class Goal {
	public:
		// Level of Importance
		int LOI;
		string name;
		
		// Required World States and Current World States
		vector<int> RWS;
		vector<int> CWS;

		Goal(int i_LOI, string i_name, vector<int> i_CWS, vector<int> i_RWS) :
			LOI(i_LOI), name(i_name), CWS(i_CWS), RWS(i_RWS){};

		virtual void update(vector<int> i_CWS) = 0;
	};

	class EscapeGoal : public Goal {
	public:
		EscapeGoal(int i_LOI, string i_name, vector<int> i_CWS, vector<int> i_RWS) :
			Goal(i_LOI, i_name, i_CWS, i_RWS) {};

		inline void update(vector<int> i_CWS) {
			CWS = i_CWS;
		};
	};

	class FleeGoal : public Goal {
	public:
		FleeGoal(int i_LOI, string i_name, vector<int> i_CWS, vector<int> i_RWS) :
			Goal(i_LOI, i_name, i_CWS, i_RWS) {};

		inline void update(vector<int> i_CWS) {
			CWS = i_CWS;
			// Check if spotted, if spotted raise LOI
			if (CWS.at(0)) {
				LOI = 3;
			}
			else {
				LOI = 1;
			}
		};
	};
}