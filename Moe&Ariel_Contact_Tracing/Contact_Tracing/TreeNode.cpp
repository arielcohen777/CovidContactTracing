#include "TreeNode.h"

TreeNode::TreeNode(const String& medId)
{
	this->medicareID = medId;
	this->parentPtr = nullptr;
}

TreeNode::TreeNode(TreeNode* parentPtr, const String& medId)
{
	this->medicareID = medId;
	this->parentPtr = parentPtr;
}
