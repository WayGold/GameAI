#pragma once
#include <vector>
#include <stdlib.h> 
#include <time.h>
#include"Intersection.h"
#include "../Blackboard/Blackboard.h"
#include "../ActionManager/Action.h"

using namespace std;
using namespace BlackBoard;
using namespace ActionManager;

namespace BehaviorTreeSpace {
	class Task {
	public:
		vector<Task*> children;
		Task* runningChild = nullptr;

		virtual bool run() = 0;
	};

	class Selector : public Task {
	public:
		Selector() {};

		inline bool run() {
			if (runningChild)
				return runningChild->run();

			for (auto itr = children.begin(); itr != children.end(); ++itr) {
				if ((*itr)->run())
					return true;
			}
			return false;
		};
	};

	class Sequencer : public Task {
	public:
		Sequencer() {};

		inline bool run() {
			if (runningChild)
				return runningChild->run();

			for (auto itr = children.begin(); itr != children.end(); ++itr) {
				if (!(*itr)->run())
					return false;;
			}
			return true;
		};
	};

	class RandomSelector : public Task {
	public:
		RandomSelector() {};

		inline bool run() {
			if (runningChild)
				return runningChild->run();

			vector<Task*> children_copy = children;
			srand(time(NULL));

			while (children_copy.size() != 0) {
				int index = rand() % (children.size() - 1);
				if (children.at(index)->run())
					return true;
				else {
					children.erase(children.begin() + index);
				}
			}
			return false;
		};
	};

	class UntilFailDecorator : public Task {
	public:
		UntilFailDecorator() {};

		inline bool run() {
			if (runningChild) {
				if (!runningChild->run()) {
					runningChild = nullptr;
					return false;
				}
				return true;
			}
				
			// Only One Child Allowed
			if (children[0]->run()) {
				runningChild = children[0];
				return true;
			}
			else {
				return false;
			}

		};
	};

	class PathFindTask : public Task {
	public:
		Action* action;

		PathFindTask(Action* i_action) : action(i_action) {};
		~PathFindTask() {
			delete action;
		}
		
		inline bool run() {
			action->execute();
			return true;
		};
	};

	class IsVisibleTask : public Task {
	public:
		Blackboard* blackboard;
		Boid* monster;
		Boid* myChar;

		IsVisibleTask(Blackboard* i_blackboard, Boid* i_monster, Boid* i_myChar) : 
			blackboard(i_blackboard), monster(i_monster), myChar(i_myChar) {};

		inline bool run() {
			myChar = blackboard->myChar;
			if (myChar == nullptr)
				return false;

			auto monsterPos = monster->boidRB->position;
			auto charPos = myChar->boidRB->position;
			bool isBlocked = false;

			// Go through all Obstacles to see whether myChar is blocked out
			for (auto itr = blackboard->allObstacles.begin(); itr != blackboard->allObstacles.end(); ++itr) {
				// Check against 1st diagonal
				auto diagonal_a1 = (*itr)->top_left;
				auto diagonal_a2 = (*itr)->bottom_right;
				isBlocked = Intersect::doIntersect(monsterPos, charPos, diagonal_a1, diagonal_a2);

				// Check against 2nd diagonal
				auto diagonal_b1 = (*itr)->top_right;
				auto diagonal_b2 = (*itr)->bottom_left;
				isBlocked = Intersect::doIntersect(monsterPos, charPos, diagonal_b1, diagonal_b2);
				if (isBlocked)
					return false;
			}

			return true;
		};
	};
}