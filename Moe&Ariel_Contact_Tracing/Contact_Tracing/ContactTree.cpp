#include "ContactTree.h"
#include <deque>
#include <iostream>

using namespace std;

TreeNode* ContactTree::RecursiveDestruct(TreeNode* treeNodePtr)
{
    if (treeNodePtr == nullptr)
        return nullptr;

    //before deleting the node, call this function for all its children
    for (std::list<TreeNode*>::iterator it = treeNodePtr->directContactsPtrList.begin(); it != treeNodePtr->directContactsPtrList.end(); ++it)
        *it = RecursiveDestruct(*it);

    //delete the node
    delete treeNodePtr;

    return nullptr;
}

ContactTree::ContactTree()
{
    this->rootPtr = nullptr;
}

ContactTree::~ContactTree()
{
    this->rootPtr = RecursiveDestruct(this->rootPtr);
}

bool ContactTree::IsEmpty()
{
    return this->size == 0;
}

int ContactTree::GetSize()
{
    return this->size;
}

void ContactTree::AddPatient0(const String& medId)
{
    //create a new node as the root of the contact tree
    this->rootPtr = new TreeNode(medId);
    this->size++;
}

void ContactTree::AddContact(const String& existingMedId, const String& newMedId)
{
    TreeNode* parentNodePtr = LookUpContact(existingMedId);

    if (parentNodePtr == nullptr) {
        cout << "Failed to add new contact. No contact with medicare ID " << existingMedId << " was found.\n";
        return;
    }

    //add the new node to the list of its parents direct contacts
    parentNodePtr->directContactsPtrList.push_back(new TreeNode(parentNodePtr, newMedId));
    //increment the number of direct contacts of the parent
    parentNodePtr->directContacts++;
    //starting with the parent node, go up the ancestoral line of the new node and increment the number of total cases
    while (parentNodePtr != nullptr)
    {
        parentNodePtr->totalCases++;
        parentNodePtr = parentNodePtr->parentPtr;
    }
    this->size++;
}

TreeNode* ContactTree::LookUpContact(const String& medID)
{
    if (this->IsEmpty()) {
        return nullptr;
    }

    //traverse the tree in BFS manner
    std::deque<TreeNode*> nodePtrQueue;
    //push the root of the tree at the back of the queue
    nodePtrQueue.push_back(this->rootPtr);
    //as long as the queue is not empty
    while (!nodePtrQueue.empty())
    {
        //if the node we are looking for is found at the front of the queue, return it
        if (nodePtrQueue.front()->medicareID == medID)
            return nodePtrQueue.front();

        //push all the children of the node at the front of the queue, to the back of the queue
        for (std::list<TreeNode*>::iterator it = nodePtrQueue.front()->directContactsPtrList.begin(); it != nodePtrQueue.front()->directContactsPtrList.end(); ++it)
            nodePtrQueue.push_back(*it);

        //discard the node at the front of the queue
        nodePtrQueue.pop_front();
    }
    return nullptr;
}

void ContactTree::DeleteContact(const String& medId)
{
    TreeNode* nodePtr = LookUpContact(medId);
    if (nodePtr == nullptr) {
        cout << "Failed to delete contact. No contact with medicare ID " << medId << " was found.\n";
        return;
    }

    //if the contact is found at the root of the tree
    if (nodePtr->parentPtr == nullptr) { 
        //recursively delete all nodes and return
        this->rootPtr = RecursiveDestruct(this->rootPtr);
        this->size = 0;
        return;
    }

    TreeNode* parentPtr = nodePtr->parentPtr;
    //find and erase the node from the list of contacts of its parent
    for (std::list<TreeNode*>::iterator it = parentPtr->directContactsPtrList.begin(); it != parentPtr->directContactsPtrList.end(); ++it)
        if ((*it)->medicareID == medId) {
            parentPtr->directContactsPtrList.erase(it);
            break;
        }

    //decrement the number of direct contacts of the parent
    parentPtr->directContacts--;

    //starting with the parent node, go up the ancestoral line of the node and decrese the number of total cases
    while (parentPtr != nullptr)
    {
        parentPtr->totalCases -= nodePtr->totalCases;
        parentPtr = parentPtr->parentPtr;
    }

    //decrese the size of the tree by the number of total cases of the deleting node
    this->size -= nodePtr->totalCases;

    //now, we can recursively destruct the node.
    //nodePtr = RecursiveDestruct(nodePtr);

    //or alternartively:

    //destruct the subtreee in a BFS manner
    std::deque<TreeNode*> nodePtrQueue;
    nodePtrQueue.push_back(nodePtr);
    while (!nodePtrQueue.empty())
    {
        //push all the children of the current node at the back of the queue
        for (std::list<TreeNode*>::iterator it = nodePtrQueue.front()->directContactsPtrList.begin(); it != nodePtrQueue.front()->directContactsPtrList.end(); ++it)
           nodePtrQueue.push_back(*it);

        //delete the front node
        delete nodePtrQueue.front();
        //discard the pointer to that node from the queue
        nodePtrQueue.pop_front();
    }
}

void ContactTree::DisplayContact(const String& medId)
{
    TreeNode* nodePtr = LookUpContact(medId);
    if (nodePtr == nullptr) {
        cout << "Failed to display contact info. No contact with medicare ID " << medId << " was found.\n";
        return;
    }
    DisplayContact(nodePtr);
}

void ContactTree::DisplayContact(TreeNode* nodePtr)
{
    cout << "\nContact_info:";
    cout << "\n\tMedicare Id:\t" << nodePtr->medicareID;
    cout << "\n\tNumber of direct contacts:\t" << nodePtr->directContacts;
    cout << "\n\tNumber of total contacts:\t" << nodePtr->totalCases << endl;
}

void ContactTree::TraceSource(const String& medId)
{
    cout << "Tracing source for patient with Medicare ID: " << medId << endl;
    TreeNode* nodePtr = LookUpContact(medId);
    if (nodePtr == nullptr) {
        cout << "No contact with medicare ID " << medId << " was found.\n";
        return;
    }

    if (nodePtr->parentPtr == nullptr) {
        cout << "Patient was found at the root of the contact tree. This patient, is patient0.\n";
        return;
    }

    //starting with the parent of the node we found, go up the ancestoral line and print contact informations
    TreeNode* parentPtr = nodePtr->parentPtr;
    while (parentPtr != nullptr) {
        DisplayContact(parentPtr);
        parentPtr = parentPtr->parentPtr;
    }
}

void ContactTree::PrintContactCases(const String& medId)
{
    cout << "Direct contacts of patient with Medicare ID:" << medId << endl;
    TreeNode* nodePtr = LookUpContact(medId);
    if (nodePtr == nullptr) {
        cout << "No contact with medicare ID " << medId << " was found.\n";
        return;
    }

    //iterate through the direct contacts of the node and print informations
    for (std::list<TreeNode*>::iterator it = nodePtr->directContactsPtrList.begin(); it != nodePtr->directContactsPtrList.end(); ++it)
        DisplayContact(*it);
}

void ContactTree::PrintContactTree()
{
    if (this->IsEmpty()) {
        cout << "Tree is empty.\n";
        return;
    }

    cout << "\n--------Contact_Tree----------\n";

    //starting with the root of the tree, traverse the tree in BFS manner and display node's info
    std::deque<TreeNode*> nodePtrQueue;
    nodePtrQueue.push_back(this->rootPtr);
    while (!nodePtrQueue.empty())
    {
        for (std::list<TreeNode*>::iterator it = nodePtrQueue.front()->directContactsPtrList.begin(); it != nodePtrQueue.front()->directContactsPtrList.end(); ++it)
            nodePtrQueue.push_back(*it);
        DisplayContact(nodePtrQueue.front());
        nodePtrQueue.pop_front();
    }
    cout << "\n------------------------------\n";

}

void ContactTree::PrintHierarchicalTree()
{
}
