#include "MemberQueue.h"
#include <fstream>

#define MAX_SIZE 100

using namespace std;

MemberQueue::MemberQueue() // Default constructor initializes

{
	frontIndex = 0;
	rearIndex = -1;
	size = 0;
}

MemberQueue::~MemberQueue() // Destructor

{ 
	
}

bool MemberQueue::empty() // Returns true if the queue is empty
{
	return size == 0;
}

bool MemberQueue::full() // Returns true if the queue is full
{
	return size == MAX_SIZE;
}

// Inserts a new node
void MemberQueue::push(MemberQueueNode newNode)
{
    if (full())
    {
        throw std::runtime_error("Queue is full.");
    }
    rearIndex = (rearIndex + 1) % MAX_SIZE;  // queue indexing
    data[rearIndex] = newNode;               // Store
    size++;                                  // Increment
}

// Removes and returns the node at the front of the queue
MemberQueueNode MemberQueue::pop()
{
    MemberQueueNode ret = data[frontIndex];  // front node
    frontIndex = (frontIndex + 1) % MAX_SIZE; // Circular queue
    size--;                                   // Decrement the size
    return ret;                               // front node
}


// Returns the node at the front of the queue
MemberQueueNode MemberQueue::front()
{
    return data[frontIndex];
}

