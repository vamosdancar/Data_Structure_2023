#pragma once
#include "TermsListNode.h"
#include <list>

using namespace std;

// linked list of terms
class TermsLIST
{
private:
    TermsListNode* head;  // Pointer to the head node
    std::list<TermsListNode*> termsList;  // List

public:
    // constructor
    TermsLIST();

    // Destructor
    ~TermsLIST();

    // Getter
    TermsListNode* getHead();

    //insert a new node into the list
    void insert(const string& name, int age, const string& date, char term);

    // Method to search
    TermsListNode* search(const string& name);

    // Method to delete
    void deleteMember(const std::string& name);

    // Method to decrease the member count
    void decreaseCountBy(int count) {
        for (auto iter = termsList.begin(); iter != termsList.end();) {
            if ((*iter)->getMembersCount() > 0) {
                (*iter)->decreaseMembersCount(count);
                if ((*iter)->getMembersCount() <= 0) {
                    //delete the node
                    delete* iter;  // Free node memory
                    iter = termsList.erase(iter);  // Remove the node
                }
                else {
                    ++iter;
                }
            }
            else {
                ++iter;
            }
        }
    }
};
