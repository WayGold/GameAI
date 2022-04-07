#pragma once
#include "DecisionTreeNode.h"

namespace DecsTree {
	class DecisionTree {
	public:
		DTNode* root;
		Boid* myChar;
		Blackboard* blackboard;

		DecisionTree(Blackboard* i_Blackboard, Boid* i_myChar) : 
			blackboard(i_Blackboard), myChar(i_myChar) {
			// Root - Is Character Seeking
			auto hasTarget = new HasTargetDecision(blackboard);
			auto isNearWall = new IsNearObstacleDecision(blackboard, myChar);
			auto pathFindAction = new PathFindDTAction(myChar, blackboard->DT_Target, "PathFind", blackboard, 0, 0, 0);
			auto wanderAction = new WanderAction(myChar, "wander", blackboard, 0, 0, 0);
			auto evadeAction = new EvadeObstacleAction(myChar, "evade", blackboard, 0, 0, 0);

			// Building the root node
			root = new DecisionTreeNode(blackboard, hasTarget);
			root->trueNode = new ActionTreeNode(pathFindAction, blackboard);
			root->falseNode = new DecisionTreeNode(blackboard, isNearWall);

			// Second Layer
			auto isNearWallNode = root->falseNode;
			isNearWallNode->trueNode = new ActionTreeNode(evadeAction, blackboard);
			isNearWallNode->falseNode = new ActionTreeNode(wanderAction, blackboard);
		};

		~DecisionTree() {
			delete root;
		}

		inline void execute() {
			auto working = root;
			while (working) {
				auto result = working->makeDecision();
				result ? working = working->trueNode : working = working->falseNode;
			}
		};
	};
}