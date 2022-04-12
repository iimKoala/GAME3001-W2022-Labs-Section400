#pragma once
#ifndef __DECISION_TREE__
#define __DECISION_TREE__

#include "Agent.h"
#include "CloseCombatCondition.h"
#include "LOSCondition.h"
#include "RadiusCondition.h"
#include "TreeNode.h"
#include "TreeNodeType.h"

class DecisionTree
{
public:
	// Constructor(s)
	DecisionTree();
	DecisionTree(Agent* agent);

	// Destructor
	~DecisionTree();

	// Getters and Setters (Accessors and Mutators)
	Agent* getAgent() const;
	LOSCondition* getLOSNode() const;
	RadiusCondition* getRadiusNode() const;
	CloseCombatCondition* getCloseCombatNode() const;

	void setAgent(Agent* agent);

	// Public Utility / Convenience Functions
	TreeNode* AddNode(TreeNode* parent, TreeNode* child_node, TreeNodeType type);
	void Display();
	void Update();
	void Clean();

	void MakeDecision(); // in-order traversal

private:
	// Private Data Members
	Agent* m_agent;
	LOSCondition* m_LOSNode;
	RadiusCondition* m_RadiusNode;
	CloseCombatCondition* m_CloseCombatNode;

	// TreeNode List
	std::vector<TreeNode*> m_treeNodeList;

	// Private Methods
	//void m_buildTree();
	
};

#endif /* defined (__DECISION_TREE__) */