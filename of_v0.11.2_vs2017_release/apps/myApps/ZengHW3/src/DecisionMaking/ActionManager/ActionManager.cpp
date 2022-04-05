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
	
}
