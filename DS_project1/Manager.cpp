#include "Manager.h"
#include <string.h>
#include <ctime>
#include <vector>

Manager::Manager() : age(0), term('\0') // constructor
{

}

Manager::~Manager() //destructor
{

}

void Manager::run(const char* command) //run function
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");

    if (!fcmd)  // Check the command file is success fully opened
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    char cmd[20];

    while (fcmd >> cmd)
    {
        if (strcmp(cmd, "LOAD") == 0) //check the LOAD command
        {
            LOAD("data.txt");
        }

        else if (strcmp(cmd, "ADD") == 0) //check the ADD command
        {
            // Declare variables
            string name, date, tempAge;
            char term = '\0';
            int age;

            bool isValid = true;  // To check validity


            fcmd >> ws;  //Skip a blank


            // Check the name
            if (!getline(fcmd, name, ' ') || name.empty()) 
            {
                isValid = false;
            }


            // Check the name is digit
            bool isAllDigit = true;
            for (char c : name)
            {
                if (!isdigit(c))
                {
                    isAllDigit = false;
                    break;
                }
            }

            if (isAllDigit)  // check the name is all digits
            {
                isValid = false;

            }

            fcmd >> ws;   //Skip a blank


            // Extract age information
            if (!getline(fcmd, tempAge, ' '))
            {
                isValid = false;
            }

            isAllDigit = true;
            for (char c : tempAge)
            {
                if (!isdigit(c))
                {
                    isAllDigit = false;

                    break;
                }
            }

            if (!isAllDigit) // Check the age is all digits
            {
                isValid = false;

            }
            age = stoi(tempAge);  // Change the string to integer


            fcmd >> ws;  //Skip a blank

            if (!(fcmd >> date))
            {
                isValid = false;
            }

            if (date.size() != 10 || date[4] != '-' || date[7] != '-') // check the date format
            {
                isValid = false;
            }

            fcmd >> ws; //Skip a blank

            if (fcmd.peek() == '\n' || fcmd.peek() == EOF) {
                term = '\0';  // Error of term
            }
            else {
                term = fcmd.get();
            }

            // check the term value
            if ((term != 'A' && term != 'B' && term != 'C' && term != 'D') || (fcmd.peek() != ' ' && fcmd.peek() != '\n' && fcmd.peek() != EOF))
            {
                
                isValid = false;
            }


            if (term != '\0' && (fcmd.peek() != EOF && fcmd.peek() != '\n' && fcmd.peek() != ' ')) {
                
                isValid = false;
            }

            // no additional characters
            while (fcmd.peek() == ' ')
            {
                
                fcmd.get();
            }

            if (isValid)  // Call ADD function
            {
                ADD(name, age, date, term);
            }

            else  // PrintErrorCode
            {
                PrintErrorCode(200);
                std::string remainderOfLine;
                getline(fcmd, remainderOfLine); 
                // Read and ignore the line
            }

            if (fcmd.peek() == '\n' || fcmd.eof()) {
                fcmd.get();  // Move to next line
            }


        }

        else if (strcmp(cmd, "QPOP") == 0)
        {
            QPOP();    // Check the QPOP command
        }

        else if (strcmp(cmd, "SEARCH") == 0) 
        {
            // Check the SEARCH command
            std::string name;
            fcmd >> name; // Read the name from file
            SEARCH(name);
        }

        else if (strcmp(cmd, "PRINT") == 0)
        {
        // Check the PRINT command
            char pri[10];
            fcmd >> pri;
            PRINT(pri);
        }

        else if (strcmp(cmd, "DELETE") == 0)
        {
        // Check the DELETE command
            string type, value;
            fcmd >> type >> value; // Read the type from file
            DELETE(type, value);
        }

        else if (strcmp(cmd, "EXIT") == 0)
        {
        // Check the EXIT command
            PrintSuccess("EXIT");
            fcmd.close(); // Close the cmd file
            flog.close(); // Close the log file

            exit(0); // Terminate program
        }
        else
        {
            PrintErrorCode(1000);  // unknown command
        }
    }
}


void Manager::PrintSuccess(const char* cmd) //To print a Success message
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}

void Manager::PrintErrorCode(int num) //To print an Error code message
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}


// LOAD
void Manager::LOAD(const char* filename)
{
    ifstream fin(filename);

    if (!fin.is_open())  // Check the file open

    {
        PrintErrorCode(100);
        return;
    }

    flog << "========= LOAD =========" << endl;

    bool isFullErrorPrinted = false;  // Add this flag to check if the error has been printed


      // Read information
    while (fin >> name >> age >> date >> term)
    {
        MemberQueueNode newNode(name, age, date, term);
        if (!Queue.full())  // Check the Queue
        {
            Queue.push(newNode);
            flog << name << "/" << age << "/" << date << "/" << term << endl;
        }
        else  // If Queue is full
        {
            if (!isFullErrorPrinted)  // Check the flag
            {
                flog << "========================" << endl;  // Close the previous block
                PrintErrorCode(100);  // error code
                isFullErrorPrinted = true;  // Set the flag to true
            }
            break;
        }

    }

    if (!Queue.full() && !isFullErrorPrinted)     
        // If no error occurred during LOAD, end the log block
    {
        flog << "========================" << endl;
    }

    fin.close(); //close
}



// ADD
void Manager::ADD(const string& name, int age, const string& date, char term)
{
    if (Queue.full())     // Check the Queue
    {
        PrintErrorCode(200);  // PrintErrorCode
        return;
    }

    MemberQueueNode newNode(name, age, date, term);
    Queue.push(newNode);

    // Log the file
    flog << "======== ADD ========" << endl;
    flog << name << "/" << age << "/" << date << "/" << term << endl;
    flog << "=====================" << endl;
}





// QPOP
void Manager::QPOP()
{
    if (Queue.empty())   // Check the Queue
    {
        PrintErrorCode(300);  // PrintErrorCode
        return;
    }

    // Remove members
    while (!Queue.empty())
    {
        MemberQueueNode node = Queue.pop();

        // Add the data to Terms_BST
        tBST.insert(node.getName(), node.getAge(), node.getDate(), node.getTerms());

        // Add the data to Name_BST
        nBST.insert(node.getName(), node.getAge(), node.getDate(), node.getTerms());

        // Add the data to tList
        tList.insert(node.getName(), node.getAge(), node.getDate(), node.getTerms());
    }

    PrintSuccess("QPOP");  // Log the success of QPOP
}



// SEARCH
std::string tt(const std::string& startDate, char term) {

    int monthsToAdd = 0;
    // Define months based on term
    switch (term) {
    case 'A':
        monthsToAdd = 6;
        break;
    case 'B':
        monthsToAdd = 12;
        break;
    case 'C':
        monthsToAdd = 24;
        break;
    case 'D':
        monthsToAdd = 36;
        break;
    default:
        throw std::invalid_argument("Invalid term.");
    }

    // Convert string to struct tm
    std::tm timeStruct = {};
    strptime(startDate.c_str(), "%Y-%m-%d", &timeStruct); 

    // Handle the overflow
    int yearsToAdd = timeStruct.tm_mon / 12;
    timeStruct.tm_mon = timeStruct.tm_mon % 12;
    timeStruct.tm_mon += monthsToAdd;

    // Convert the string format
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeStruct);

    return std::string(buffer);
}


// SEARCH
void Manager::SEARCH(const std::string& name) {

    NameBSTNode* result = nBST.search(name);

    if (result != nullptr) {
        // Calculate the expiration
        std::string expirationDate;
        try {
            expirationDate = tt(result->getDate(), result->getTerm());
        }
        catch (const std::invalid_argument& e) {
            //log an error.
            PrintErrorCode(400);
            return;
        }

        flog << "======== SEARCH ========" << endl;
        flog << result->getName() << "/"
            << result->getAge() << "/"
            << result->getDate() << "/"
            << expirationDate << std::endl; 
        flog << "=======================" << std::endl;
           // Log the member's details
    }
    else {
        PrintErrorCode(400);
    }
}

void Manager::printTermsAndMembers(char term) {
    flog << "Terms_BST " << term << std::endl;
    nBST.printMembersByTerm(flog, term); //print the Terms_BST
}


// PRINT
void Manager::PRINT(const std::string& arg) {
  
    if (arg == "NAME")
    {

        if (nBST.isEmpty())
        {
            PrintErrorCode(500);  // Error code for no data.
            return;
        }

        else {
            flog << "===== PRINT =====" << std::endl;
            nBST.print(flog);
            flog << "===============" << std::endl;
        }

    }

    else if (arg == "A" || arg == "B" || arg == "C" || arg == "D") {

        // Check if the data exists in the BST.
        if (tBST.isEmpty(arg[0])) {
            PrintErrorCode(500);  // Error code for no data.
            return;
        }

        flog << "===== PRINT =====" << std::endl;
        flog << "Terms_BST " << arg << std::endl;
        tBST.inOrderTraversal(tBST.getRoot(), flog, arg[0]);
        flog << "===============" << std::endl;
    }
    else {
        PrintErrorCode(500);  // Error code for invalid argument.
    }
}




void Manager::DELETE(const std::string& type, const std::string& value) {

    if (type == "DATE") {
        std::string expirationDate = value;

        // Remove all nodes
        int count = tBST.deleteBeforeDate(expirationDate);

        if (count > 0) {
            // Decrease member count
            tList.decreaseCountBy(count);

            // Delete the member's node
            nBST.deleteMembersBeforeDate(expirationDate);

            PrintSuccess("DELETE");  // Success message.
        }
        else {
            PrintErrorCode(600); // PrintErrorCode
        }
    }

    else if (type == "NAME")
    {
        std::string name = value;

        // Delete the node from the Name_BST.
        bool isDeletedFromNameBST = nBST.deleteByName(name);

        // Also delete node from the Terms_BST and Terms_List.
        bool isDeletedFromTermsBST = tBST.deleteMember(name);
        tList.deleteMember(name);

    }
    else {
        PrintErrorCode(600); // PrintErrorCode
    }

}


