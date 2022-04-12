#include "DecisionTree.h"

#include <iostream>

#include "ActionNode.h"
#include "AttackAction.h"
#include "MoveToLOSAction.h"
#include "MoveToPlayerAction.h"
#include "PatrolAction.h"

DecisionTree::DecisionTree()
{
	//m_buildTree();
}

DecisionTree::DecisionTree(Agent* agent)
{
	m_agent = agent;
	//m_buildTree();
}

DecisionTree::~DecisionTree()
= default;

Agent* DecisionTree::getAgent() const
{
	return m_agent;
}

LOSCondition* DecisionTree::getLOSNode() const
{
	return m_LOSNode;
}

RadiusCondition* DecisionTree::getRadiusNode() const
{
	return m_RadiusNode;
}

CloseCombatCondition* DecisionTree::getCloseCombatNode() const
{
	return m_CloseCombatNode;
}

RangedCombatCondition* DecisionTree::getRangedCombatNode() const
{
	return m_RangedCombatNode;
}

void DecisionTree::setRangedCombatNode(RangedCombatCondition* node)
{
	m_RangedCombatNode = node;
}

std::vector<TreeNode*>& DecisionTree::getTree()
{
	return m_treeNodeList;
}

void DecisionTree::setLOSNode(LOSCondition* node)
{
	m_LOSNode = node;
}

void DecisionTree::setRadiusNode(RadiusCondition* node)
{
	m_RadiusNode = node;
}

void DecisionTree::setCloseCombatNode(CloseCombatCondition* node)
{
	m_CloseCombatNode = node;
}

void DecisionTree::setAgent(Agent* agent)
{
	m_agent = agent;
}

TreeNode* DecisionTree::AddNode(TreeNode* parent, TreeNode* child_node, const TreeNodeType type)
{
	switch(type)
	{
	case LEFT_TREE_NODE:
		parent->m_pLeft = child_node;
		break;
	case RIGHT_TREE_NODE:
		parent->m_pRight = child_node;
		break;
	}
	child_node->m_pParent = parent;
	return child_node;
}

void DecisionTree::Display()
{
	for (auto node : m_treeNodeList)
	{
		std::cout << node->m_name << std::endl;
	}
}

void DecisionTree::Update()
{
	// Do something in the play Scene
}

void DecisionTree::Clean()
{
	for (auto node : m_treeNodeList)
	{
		delete node;
		node = nullptr;
	}
	m_treeNodeList.clear();
	m_treeNodeList.shrink_to_fit();

	m_LOSNode = nullptr;
	m_RadiusNode = nullptr;
	m_CloseCombatNode = nullptr;
}

// Traverse the Tree "in-order"
void DecisionTree::MakeDecision()
{
	auto currentNode = m_treeNodeList[0]; // root node
	while(!currentNode->m_isLeaf)
	{
		currentNode = dynamic_cast<ConditionNode*>(currentNode)->Condition() ?
			(currentNode->m_pRight) :
			(currentNode->m_pLeft);
	}
	dynamic_cast<ActionNode*>(currentNode)->Action();
}

//void DecisionTree::m_buildTree()
//{
//	//CONDITIONS
//	
//	// create and add the root node
//	m_LOSNode = new LOSCondition();
//	m_treeNodeList.push_back(m_LOSNode);
//
//	m_RadiusNode = new RadiusCondition();
//	AddNode(m_LOSNode, m_RadiusNode, LEFT_TREE_NODE);
//	m_treeNodeList.push_back(m_RadiusNode);
//
//	m_CloseCombatNode = new CloseCombatCondition();
//	AddNode(m_LOSNode, m_CloseCombatNode, RIGHT_TREE_NODE);
//	m_treeNodeList.push_back(m_CloseCombatNode);
//
//	// ACTIONS
//
//	TreeNode* patrolNode = AddNode(m_RadiusNode, new PatrolAction(), LEFT_TREE_NODE);
//	dynamic_cast<ActionNode*>(patrolNode)->setAgent(m_agent);
//	m_treeNodeList.push_back(patrolNode);
//
//	TreeNode* moveToLOSNode = AddNode(m_RadiusNode, new MoveToLOSAction(), RIGHT_TREE_NODE);
//	dynamic_cast<ActionNode*>(moveToLOSNode)->setAgent(m_agent);
//	m_treeNodeList.push_back(moveToLOSNode);
//
//	TreeNode* moveToPlayerNode = AddNode(m_CloseCombatNode, new MoveToPlayerAction(), LEFT_TREE_NODE);
//	dynamic_cast<ActionNode*>(moveToPlayerNode)->setAgent(m_agent);
//	m_treeNodeList.push_back(moveToPlayerNode);
//
//	TreeNode* attackNode = AddNode(m_CloseCombatNode, new AttackAction(), RIGHT_TREE_NODE);
//	dynamic_cast<ActionNode*>(attackNode)->setAgent(m_agent);
//	m_treeNodeList.push_back(attackNode);
//}
