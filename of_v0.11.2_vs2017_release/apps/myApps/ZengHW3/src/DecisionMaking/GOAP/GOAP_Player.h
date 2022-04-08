#pragma once
#include "Goal.h"
#include "GOAP_Action.h"

namespace GOAP {
	class GOAP_Player {
	public:
		vector<Goal*> goals;
		vector<GOAP_Action*> actions;

		WorldStates* worldStates;
		Blackboard* blackboard;

		GOAP_Player(WorldStates* i_worldStates, Blackboard* i_Blackboard) :
			worldStates(i_worldStates), blackboard(i_Blackboard) {

			// Aux Vectors for World States Params
			int worldStateAux[] = { -1, -1, -1, -1 };
			vector<int> wsAuxVec = vector<int>(worldStateAux, worldStateAux + sizeof(worldStateAux) / sizeof(int));
			vector<int> swsAuxVec = wsAuxVec;
			vector<int> rwsAuxVec = wsAuxVec;

			// Create Escape Goal
			rwsAuxVec = wsAuxVec;
			rwsAuxVec.at(1) = 1;
			EscapeGoal* escGoal = new EscapeGoal(2, "Escape Room", worldStates->getWorldStates(), rwsAuxVec);

			// Create Evade Goal
			rwsAuxVec = wsAuxVec;
			rwsAuxVec.at(0) = 0;
			FleeGoal* fleeGoal = new FleeGoal(1, "Flee From Monster", worldStates->getWorldStates(), rwsAuxVec);

			goals.push_back(escGoal);
			goals.push_back(fleeGoal);

			// Create Actions
			PathFindDTAction* pathfindEscape = new PathFindDTAction(blackboard->myChar, blackboard->DT_Target,
				"Escape Room", blackboard, 0, 0, 0);
			EvadeTargetAction* evadeMonster = new EvadeTargetAction(blackboard->myChar, blackboard->monster, 
				"Evade Monster", blackboard, 0, 0, 0);
			MagicAction* magic = new MagicAction(blackboard->myChar, blackboard->monster, 
				"Magic Walls", blackboard, 0, 0, 0);

			// Set Escape Room Action
			swsAuxVec = wsAuxVec;
			rwsAuxVec = wsAuxVec;
			swsAuxVec.at(1) = 1;
			rwsAuxVec.at(2) = 1;
			GOAP_Action* escapeAction = new GOAP_Action(pathfindEscape, rwsAuxVec, swsAuxVec);

			// Reset Aux, Set Evade Action
			swsAuxVec = wsAuxVec;
			rwsAuxVec = wsAuxVec;
			swsAuxVec.at(0) = 0;
			rwsAuxVec.at(3) = 0;
			rwsAuxVec.at(0) = 1;
			GOAP_Action* evadeAction = new GOAP_Action(evadeMonster, rwsAuxVec, swsAuxVec);

			// Reset Aux, Set Magic Action
			swsAuxVec = wsAuxVec;
			rwsAuxVec = wsAuxVec;
			swsAuxVec.at(0) = 0;
			rwsAuxVec.at(3) = 1;
			rwsAuxVec.at(0) = 1;
			GOAP_Action* magicAction = new GOAP_Action(magic, rwsAuxVec, swsAuxVec);

			actions.push_back(escapeAction);
			actions.push_back(evadeAction);
			actions.push_back(magicAction);

		};

		~GOAP_Player() {

			for (int i = 0; i < goals.size(); i++) {
				delete goals.at(i);
			}

			for (int i = 0; i < actions.size(); i++) {
				delete actions.at(i);
			}
		};

		inline void run() {

			for (int i = 1; i < goals.size(); i++) {
				goals.at(i)->update(worldStates->getWorldStates());
			}

			// Get highest LOI goal
			int highest_LOI = goals[0]->LOI;
			int highest_LOI_Index = 0;

			for (int i = 1; i < goals.size(); i++) {
				if (goals.at(i)->LOI > highest_LOI) {
					highest_LOI = goals.at(i)->LOI;
					highest_LOI_Index = i;
				}
			}

			for (int i = 0; i < actions.size(); i++) {
				// If Satisfied World States Match With RWS of The Goal
				// And Action's RWS is Satified
				if (cmp_WS(actions.at(i)->SWS, goals.at(highest_LOI_Index)->RWS) &&
					cmp_WS(actions.at(i)->RWS, worldStates->getWorldStates())) {
					actions.at(i)->run();
				}
			}

		}

		inline bool cmp_WS(vector<int> i_vec1, vector<int> i_vec2) {
			for (int i = 0; i < i_vec1.size(); i++) {
				// Skip unimportant index
				if (i_vec1.at(i) == -1 || i_vec2.at(i) == -1)
					continue;
				if (i_vec1.at(i) != i_vec2.at(i))
					return false;
			}
			return true;
		};
	};
}