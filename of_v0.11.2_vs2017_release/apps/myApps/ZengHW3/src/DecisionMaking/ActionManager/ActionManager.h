#pragma once
#include "Action.h"
#include <queue>
#include <vector>

using namespace std;

namespace ActionManager {

	class priorityComp {
	public:
		inline bool operator()(Action* a, Action* b) const {
			if (a->priority != b->priority) {
				return a->priority > b->priority;
			}
			return a->queueTime < b->queueTime;
		}
	};

	class ActionManager {
	public:
		priority_queue<Action*, vector<Action*>, priorityComp> pendingQueue;
		priority_queue<Action*, vector<Action*>, priorityComp> activeQueue;

		ActionManager();

		bool scheduleAction(Action* i_action);
		void execute();
	};
}