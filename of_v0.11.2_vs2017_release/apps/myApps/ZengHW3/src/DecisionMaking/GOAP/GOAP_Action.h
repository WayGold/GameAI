#pragma once
#include "../ActionManager/Action.h"

using namespace ActionManager;

namespace GOAP {
	class GOAP_Action {
	public:
		Action* action;
		// Required World States and Satisfy World States
		vector<int> RWS;
		vector<int> SWS;

		GOAP_Action(Action* i_action, vector<int> i_RWS, vector<int> i_SWS) : 
			action(i_action), RWS(i_RWS), SWS(i_SWS) {};

		~GOAP_Action() {
			delete action;
		};

		inline void run() {
			action->execute();
		};
	};
}
