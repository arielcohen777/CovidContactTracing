#pragma once
#include<string>
#include<list>

typedef std::string String;

struct TreeNode
{
	String medicareID;
	int directContacts = 0;
	int totalCases = 1;
	TreeNode* parentPtr;
	std::list<TreeNode*> directContactsPtrList;

	TreeNode(const String&);
	TreeNode(TreeNode*, const String&);
};