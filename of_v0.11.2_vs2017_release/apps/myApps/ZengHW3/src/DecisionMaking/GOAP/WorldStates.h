#pragma once
#include "../Blackboard/Blackboard.h"
#include "../BehaviorTree/Intersection.h"
#include "../BehaviorTree/Task.h"

namespace GOAP {
	class WorldStates {
	public:
		// -1 not important, 0 false, 1 true
		int isSpotted;
		int hasArrived;
		int hasExit;
		int isFarEnough;

		WorldStates(BlackBoard::Blackboard* i_blackboard) {
			isSpotted = -1;
			hasArrived = -1;
			hasExit = -1;
			isFarEnough = -1;

			update(i_blackboard);
		};

		void update(BlackBoard::Blackboard* i_blackboard) {
			// Create isVisble task to check whether visible
			BehaviorTreeSpace::IsVisibleTask* isVisible = new BehaviorTreeSpace::IsVisibleTask(i_blackboard, 
				i_blackboard->monster, i_blackboard->myChar);

			if (isVisible->run())
				isSpotted = 1;
			else {
				isSpotted = 0;
			}

			// Deallocate
			delete isVisible;

			// Check whether exit exist
			if (i_blackboard->DT_Target)
				hasExit = 1;
			else {
				hasExit = 0;
			}

			// Check Whether myChar Has Arrived at the Exit Only if Exit exists
			if (hasExit == 1 && i_blackboard->myChar) {
				if (glm::distance(i_blackboard->DT_Target->boidRB->position, i_blackboard->myChar->boidRB->position) <= 0.01) {
					hasArrived = 1;
				}
				else {
					hasArrived = 0;
				}
			}
			else {
				hasArrived = 0;
			}
			
			if (i_blackboard->monster && i_blackboard->myChar) {
				// Check Whether myChar - Monster > 200 distance
				if (glm::distance(i_blackboard->monster->boidRB->position, i_blackboard->myChar->boidRB->position) > 200) {
					isFarEnough = 1;
				}
				else {
					isFarEnough = 0;
				}
			}
		};

		vector<int> getWorldStates() {
			vector<int> result;
			result.push_back(isSpotted);
			result.push_back(hasArrived);
			result.push_back(hasExit);
			result.push_back(isFarEnough);
			return result;
		}
	};
}