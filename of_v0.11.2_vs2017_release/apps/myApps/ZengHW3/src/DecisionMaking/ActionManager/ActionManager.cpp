#include "ActionManager.h"

ActionManager::ActionManager::ActionManager()
{

}

bool ActionManager::ActionManager::scheduleAction(Action* i_action)
{
	pendingQueue.push(i_action);
	return false;
}

void ActionManager::ActionManager::execute()
{
	float currentTime = ofGetLastFrameTime();
	float priorityCutoff = activeQueue.top()->priority;

	priority_queue<Action*, vector<Action*>, priorityComp> queueCopy = pendingQueue;
	priority_queue<Action*, vector<Action*>, priorityComp> activeCopy = activeQueue;

	// Remove Expired Action
	

	// Check for adding action to active
	if (activeCopy.size() == 0) {

	}

	// Remove or run active actions
	activeCopy = activeQueue;
	priority_queue<Action*, vector<Action*>, priorityComp> newActive;

	while (activeCopy.size() > 0) {
		auto working = activeCopy.top();
		if (!working->isCompleted()) {
			newActive.push(working);
			working->execute();
		}
	}
	// Update Active Queue
	activeQueue = newActive;
}
