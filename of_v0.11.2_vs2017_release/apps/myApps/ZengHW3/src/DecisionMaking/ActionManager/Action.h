#pragma once
#include <string>
#include "../Blackboard/Blackboard.h"

using namespace std;
using namespace BlackBoard;

namespace ActionManager {
	class Action {
	public:
		string name;
		Blackboard* blackboard;

		float priority;
		float queueTime;
		float expiryTime;

		Action(string i_name, Blackboard* i_bb, float i_priority, float i_queueTime, float i_expiryTime) :
			name(i_name), blackboard(i_bb), priority(i_priority), queueTime(i_queueTime), expiryTime(i_expiryTime) {};

		bool virtual  canInterrupt() = 0;
		bool virtual  canDoBoth(Action* i_action) = 0;
		bool virtual  isCompleted() = 0;

		void virtual  execute() = 0;
	};

	class WanderAction : public Action {
	public:
		Boid* myChar;
		bool isComplete = false;

		WanderAction(Boid* i_boid, string i_name, Blackboard* i_bb, float i_priority, float i_queueTime, float i_expiryTime)
			: Action(i_name, i_bb, i_priority, i_queueTime, i_expiryTime), myChar(i_boid) {};

		bool canInterrupt() { return true; };
		bool canDoBoth(Action* i_action) { return false; };
		bool isCompleted() { return isComplete; };

		void execute() {
			blackboard->allWanderers.push_back(myChar);
		};
	};

	class EvadeObstacleAction : public Action {
	public:
		Boid* myChar;
		bool isComplete = false;

		EvadeObstacleAction(Boid* i_boid, string i_name, Blackboard* i_bb, float i_priority, float i_queueTime, float i_expiryTime)
			: Action(i_name, i_bb, i_priority, i_queueTime, i_expiryTime), myChar(i_boid) {};

		inline bool canInterrupt() { return true; };
		inline bool canDoBoth(Action* i_action) { return false; };
		inline bool isCompleted() { return isComplete; };

		inline void execute() {
			auto deltaTime = ofGetLastFrameTime();

			blackboard->dynamicEvade->characterRB = myChar->boidRB;
			glm::vec2 accumAccel = glm::vec2(0, 0);

			// Calculate an accumulated steering from all obstacles
			for (auto itr = blackboard->allObstacles.begin(); itr != blackboard->allObstacles.end(); itr++) {
				blackboard->dynamicEvade->targetRB = (*itr)->obstacleRB;
				accumAccel += blackboard->dynamicEvade->getSteering().linearAccel;
			}

			// Look at travel direction
			blackboard->dynamicLWYG->characterRB = myChar->boidRB;

			// Set steering
			DynamicSteeringOutput steeringOutput;
			steeringOutput.linearAccel = accumAccel;
			steeringOutput.rotAccel = blackboard->dynamicLWYG->getSteering().rotAccel;

			myChar->boidRB->update(steeringOutput, blackboard->maxSpeed, blackboard->maxRotation, deltaTime);
		};
	};

	class PathFindAction : public Action {
	public:
		Boid* pathFinder;
		Boid* seekTarget;
		std::vector<Vertex*> path;
		bool isComplete = false;

		PathFindAction(Boid* i_boid, Boid* i_seekTarget, string i_name, Blackboard* i_bb, float i_priority, float i_queueTime, float i_expiryTime)
			: Action(i_name, i_bb, i_priority, i_queueTime, i_expiryTime), pathFinder(i_boid), seekTarget(i_seekTarget) {};

		inline bool canInterrupt() { return false; };
		inline bool canDoBoth(Action* i_action) { return false; };
		inline bool isCompleted() { return isComplete; };

		inline void execute() {
			auto deltaTime = ofGetLastFrameTime();

			if (pathFinder && seekTarget) {

				if (path.size() == 0) {
					path = Pathfinding::getPath(pathFinder->boidRB, seekTarget->boidRB, blackboard->tileGraph);
					// Remove Src
					path.erase(path.begin());
				}
				else {
					// Check pathfinder arrival at current path destination, pop from path if arrive
					Vertex* dst = (*path.begin());
					// Pop from front
					if (Pathfinding::has_arrive(pathFinder->boidRB, dst, blackboard->tileGraph)) {
						path.erase(path.begin());
						if (path.size() == 0)
							isComplete = true;
					}
				}

				RigidBody* explicitRB = new RigidBody();

				if (path.size() != 0)
					explicitRB->position = blackboard->tileGraph->localized(glm::vec2((*path.begin())->row, (*path.begin())->col));
				else {
					explicitRB->position = seekTarget->boidRB->position;
				}

				blackboard->dynamicEvade->characterRB = pathFinder->boidRB;
				glm::vec2 accumAccel = glm::vec2(0, 0);

				// Delegate to Arrive
				blackboard->dynamicSeek->characterRB = pathFinder->boidRB;
				blackboard->dynamicSeek->targetRB = explicitRB;

				accumAccel += blackboard->dynamicSeek->getSteering().linearAccel;

				// Calculate an accumulated steering from all obstacles
				for (auto itr = blackboard->allObstacles.begin(); itr != blackboard->allObstacles.end(); itr++) {
					blackboard->dynamicEvade->targetRB = (*itr)->obstacleRB;
					accumAccel += blackboard->dynamicEvade->getSteering().linearAccel;
				}

				// Look at travel direction
				blackboard->dynamicLWYG->characterRB = pathFinder->boidRB;

				// Set steering
				DynamicSteeringOutput steeringOutput;
				steeringOutput.linearAccel = accumAccel;
				steeringOutput.rotAccel = blackboard->dynamicLWYG->getSteering().rotAccel;

				// Update pathFinder
				pathFinder->boidRB->update(steeringOutput, blackboard->maxSpeed, blackboard->maxRotation, deltaTime);

				delete explicitRB;
			}
		};
	};
}