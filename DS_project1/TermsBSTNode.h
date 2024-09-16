#pragma once
#include <string>
#include <vector>

// in a Binary Search Tree for terms
class TermsBSTNode
{
private:
    TermsBSTNode* left;  // left child node
    TermsBSTNode* right;  // right child node

    char termType; 
    std::string memberName;  // Name of the member
    int memberAge;  // Age of the member
    std::string memberDate;  // Date associated
    std::string expirationDate;  // Expiration date

    int memberCount;  // Count of members

public:
    // constructor
    TermsBSTNode() : left(nullptr), right(nullptr), termType('\0'), memberAge(0), memberCount(0) {}

    // Destructor
    ~TermsBSTNode() {}

    // Getters and setters
    TermsBSTNode* getLeft() { return left; }
    TermsBSTNode* getRight() { return right; }

    void setLeft(TermsBSTNode* l) { left = l; }
    void setRight(TermsBSTNode* r) { right = r; }
    void setTermType(char t) { termType = t; }
    void setMemberCount(int ct) { memberCount = ct; }

    char getTermType() const { return termType; }
    int getMemberCount() const { return memberCount; }


    // increment and decrement the member count
    void increaseMemberCount() { memberCount++; }
    void decreaseMemberCount() { memberCount--; }

    // Additional getters and setters
    std::string& getMemberName() { return memberName; }
    void setMemberName(const std::string& name) { memberName = name; }
    int getMemberAge() { return memberAge; }
    void setMemberAge(int age) { memberAge = age; }
    const std::string& getExpirationDate() const { return expirationDate; }
    void setExpirationDate(const std::string& expDate) { expirationDate = expDate; }
    std::string& getMemberDate() { return memberDate; }
    void setMemberDate(const std::string& date) { memberDate = date; }
};
