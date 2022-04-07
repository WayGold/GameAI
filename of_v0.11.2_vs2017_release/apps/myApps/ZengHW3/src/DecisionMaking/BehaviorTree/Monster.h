#pragma once
#include "Task.h"

namespace BehaviorTreeSpace {
	// Monster Behavior Tree
	class Monster {
	public:
		Blackboard* blackboard;
		Boid* monster;
		Boid* myChar;

		// Scripted Pathfind locations for Monster
		Boid* top;
		Boid* bottom;
		Boid* left;
		Boid* right;

		Task* root;

		Monster(Blackboard* i_Blackboard, Boid* i_myChar, Boid* i_monster,
				Boid* i_top, Boid* i_bottom, Boid* i_left, Boid* i_right) :
			blackboard(i_Blackboard), monster(i_monster), myChar(i_myChar),
			top(i_top), bottom(i_bottom), left(i_left), right(i_right) {

			// 1st Layer - Selector
			root = new Selector();

			// 2nd Layer
			UntilFailDecorator* child_left = new UntilFailDecorator();
			RandomSelector* child_right = new RandomSelector();
			root->children.push_back(child_left);
			root->children.push_back(child_right);

			// 3rd Layer - Decorator side
			Sequencer* seq = new Sequencer();
			child_left->children.push_back(seq);

			// 3rd Layer - Pathfinders to circle around obstacle
			PathFindAction* toTopAction = new PathFindAction(monster, top, "to top", blackboard, 0, 0, 0);
			PathFindAction* toBottomAction = new PathFindAction(monster, bottom, "to bottom", blackboard, 0, 0, 0);
			PathFindAction* toLeftAction = new PathFindAction(monster, left, "to left", blackboard, 0, 0, 0);
			PathFindAction* toRightAction = new PathFindAction(monster, right, "to right", blackboard, 0, 0, 0);

			// Add to RandSel
			child_right->children.push_back(new PathFindTask(toTopAction));
			child_right->children.push_back(new PathFindTask(toBottomAction));
			child_right->children.push_back(new PathFindTask(toLeftAction));
			child_right->children.push_back(new PathFindTask(toRightAction));


			// 4th Layer - If myChar is visible, path find to myChar
			// Is Visible
			IsVisibleTask* isVisible = new IsVisibleTask(blackboard, monster, myChar);
			seq->children.push_back(isVisible);

			// To My Char
			PathFindBTAction* toMyChar = new PathFindBTAction(monster, nullptr, "to my char", blackboard, 0, 0, 0);
			PathFindTask* toMyCharTask = new PathFindTask(toMyChar);
			seq->children.push_back(toMyCharTask);
		}

		~Monster() {
			delete root;
		}

		inline void update() {
			root->run();
		}
	};
}