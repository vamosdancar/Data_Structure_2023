#pragma once
#include "MemberQueueNode.h"

class MemberQueue
{
private:
    MemberQueueNode data[100]; // Array to store

    int frontIndex;            //pointing to the front of the queue
    int rearIndex;             // pointing to the rear of the queue
    int size;                  // Number of elements

public:
    // constructor
    MemberQueue();

    // Destructor
    ~MemberQueue();

    // Check the queue 
    bool empty();

    // Check the queue
    bool full();

    // Insert a node
    void push(MemberQueueNode node);

    // Remove and return the node
    MemberQueueNode pop();

    // Return the node
    MemberQueueNode front();
};
