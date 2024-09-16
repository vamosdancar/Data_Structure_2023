#include "TermsList.h"
#include <list>

// Constructor
TermsLIST::TermsLIST() : head(nullptr)
{

}

// Destructor
TermsLIST::~TermsLIST()
{
    TermsListNode* current = head;
    TermsListNode* next = nullptr;

    // Looping
    while (current != nullptr)
    {
        next = current->getNext();
        delete current;
        current = next;
    }
}

// Return the head of the list
TermsListNode* TermsLIST::getHead()
{
    return head;
}

// Insert a new node
void TermsLIST::insert(const string& name, int age, const string& date, char term)
{
    // Allocate memory
    TermsListNode* newNode = new TermsListNode(name, age, date, term);
    if (!newNode)
    {
        return; 
    }

    // check the list
    if (!head)
    {
        head = newNode;
    }

    // traverse to the end of the list
    else {
        TermsListNode* temp = head;
        while (temp->getNext()) {
            temp = temp->getNext();
        }
        temp->setNext(newNode);
    }
}

// Search
TermsListNode* TermsLIST::search(const string& name)
{
    TermsListNode* current = head;

    // Traverse the list
    while (current != nullptr)
    {
        if (current->getName() == name)
        {
            return current;  // Return the node.
        }
        current = current->getNext();
    }
    return nullptr;  // Return nullptr
}

// Delete node by name
void TermsLIST::deleteMember(const std::string& name)
{
    if (!head) return; // if list is empty

    // head node is the one to delete
    if (head->getName() == name)
    {
        TermsListNode* temp = head;
        head = head->getNext();  // Update the pointer
        delete temp;  // Deallocate
        return;
    }

    // traverse the list to find the node
    TermsListNode* current = head;
    while (current->getNext() && (current->getNext()->getName() != name))
    {
        current = current->getNext();
    }

    // If the node to be deleted
    if (current->getNext())
    {
        TermsListNode* temp = current->getNext();
        current->setNext(temp->getNext());  // Update the link
        delete temp;  // Deallocate
    }
}
