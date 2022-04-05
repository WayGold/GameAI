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
			auto isSeekDecs = new IsSeekingDecision(blackboard, myChar);
			root = new DecisionTreeNode(blackboard, isSeekDecs);

		};

		void execute();
	};
}