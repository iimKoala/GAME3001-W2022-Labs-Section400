#pragma once
#ifndef __DECISION_TREE__
#define __DECISION_TREE__

#include "Agent.h"
#include "CloseCombatCondition.h"
#include "RangedCombatCondition.h"
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
	RangedCombatCondition* getRangedCombatNode() const;
	std::vector<TreeNode*>& getTree();

	void setAgent(Agent* agent);
	void setLOSNode(LOSCondition* node);
	void setRadiusNode(RadiusCondition* node);
	void setCloseCombatNode(CloseCombatCondition* node);
	void setRangedCombatNode(RangedCombatCondition* node);

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
	RangedCombatCondition* m_RangedCombatNode;

	// TreeNode List
	std::vector<TreeNode*> m_treeNodeList;
};

#endif /* defined (__DECISION_TREE__) */