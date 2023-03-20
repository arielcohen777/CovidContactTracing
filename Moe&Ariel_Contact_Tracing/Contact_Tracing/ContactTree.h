#pragma once

#include"TreeNode.h"

class ContactTree
{
private:
	int size = 0;
	TreeNode* rootPtr;
	TreeNode* RecursiveDestruct(TreeNode*);
public:
	ContactTree();
	~ContactTree();
	bool IsEmpty();
	int GetSize();
	void AddPatient0(const String&);
	void AddContact(const String&, const String&);
	TreeNode* LookUpContact(const String&);
	void DeleteContact(const String&);
	void DisplayContact(const String&);
	void DisplayContact(TreeNode*);
	void TraceSource(const String&);
	void PrintContactCases(const String&);
	void PrintContactTree();
	void PrintHierarchicalTree();
};

