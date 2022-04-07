#pragma once
#include <iostream>
#include <assert.h>
#include "../ActionManager/Action.h"

using namespace std;
using namespace ActionManager;

namespace DecsTree {
	class DTNode {
	public:
		DTNode* trueNode = nullptr;
		DTNode* falseNode = nullptr;

		Blackboard* blackboard;

		DTNode(Blackboard* i_blackboard) : blackboard(i_blackboard){};

		inline virtual bool makeDecision() = 0;
	};

	class ActionTreeNode : public DTNode {
	public:
		Action* action;

		ActionTreeNode(Action* i_action, Blackboard* i_blackboard) : 
			DTNode(i_blackboard), action(i_action) {};

		~ActionTreeNode() {
			delete action;
		}

		inline bool makeDecision() {
			action->execute();
			return true;
		};
	};

	class Decision {
	public:
		Blackboard* blackboard;

		Decision(Blackboard* i_blackboard) : blackboard(i_blackboard) {};
		virtual bool execute() = 0;
	};

	class DecisionTreeNode : public DTNode {
	public:
		Decision* decision;

		DecisionTreeNode(Blackboard* i_blackboard, Decision* i_decision) : 
			DTNode(i_blackboard), decision(i_decision) {};

		~DecisionTreeNode() {
			delete decision;
		}

		inline bool makeDecision() {
			return decision->execute();
		};
	};

	class HasTargetDecision : public Decision {
	public:
		HasTargetDecision(Blackboard* i_blackboard) :
			Decision(i_blackboard) {};
		
		inline bool execute() {
			if (blackboard->DT_Target != nullptr)
				return true;
			return false;
		};
	};

	class IsNearObstacleDecision : public Decision {
	public:
		Boid* myChar;

		IsNearObstacleDecision(Blackboard* i_blackboard, Boid* i_myChar) :
			Decision(i_blackboard), myChar(i_myChar) {};

		inline bool execute() {
			for (auto it = blackboard->allObstacles.begin(); it != blackboard->allObstacles.end(); ++it) {
				if (glm::distance((*it)->obstacleRB->position, myChar->boidRB->position) <= 70)
					return true;
			}
			return false;
		};
	};

	//class HasArrivedDecision : public Decision {
	//public:
	//	Boid* myChar;
	//	Boid* target;

	//	HasArrivedDecision(Blackboard* i_blackboard, Boid* i_myChar, Boid* i_target) : 
	//		Decision(i_blackboard), myChar(i_myChar), target(i_target) {};

	//	inline bool execute() {
	//		if (glm::distance(target->boidRB->position, myChar->boidRB->position) <= 0.01) {
	//			for (auto it = blackboard->allSeekers.begin(); it != blackboard->allSeekers.end(); ++it) {
	//				if (myChar == (*it)) {
	//					blackboard->allSeekers.erase(it);
	//					return true;
	//				}
	//			}
	//			// My Character Not Found in allseekers
	//			assert(false);
	//		}
	//		return false;
	//	};
	//};
}