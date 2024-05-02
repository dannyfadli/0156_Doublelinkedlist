#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int noMhs;
    string name;
    Node* next;
    Node* prev;
};

Node* START = NULL;

void addNode()
{
    Node* newNode = new Node();     //step 1:create a new node
    cout << "\nEnter the roll number of the student: ";
    cin >> newNode->noMhs;          //Assign Value to the data field of the new node
    cout << "\nEnter the name of the student: ";
    cin >> newNode->name;           //Assign value to the data field of the new node

    //Insert the new node in the list
    if (START == NULL || newNode->noMhs <= START->noMhs)    //Step 2: insert  the new node

    {
        if (START != NULL && newNode->noMhs == START->noMhs)
        {
            cout << "\033[31mDuplicate roll number not allowed\033[0m" << endl;
            return;
        }
        //if The list is empty, make the new node the start
        newNode->prev = START;          //Step 3 make the new node point the first node
        if (START != NULL)
        {
            START->prev = newNode;      //step 4 make the first Node point to the new node
        }
        newNode->prev = NULL;           //step 5: make the new node point to NULL
        START = newNode;                //Step 6: make the new node the first node
    }
    else
    {
        //insert the new node in the middle or at the end
        Node* current = START;          //step 1.a:Start from the first node
        Node* previous = NULL;          //step 1.b:previous node is NULL initialy

        while (current != NULL && current->noMhs < newNode->noMhs) //step 1C : trever
        {
            previous = current;         //Step 1.d : move the previous to the current node
            current = current->next;    //step 1. e: move the current ti the next mode

        }
        newNode->next = current;        //step 4 make the  next field of the new code point
        newNode->prev = previous;       //step 5: mske the previoud field of the new node ponit

        if (current != NULL)
        {
            current->prev = newNode;    //Step 6: make  the next  field  of the current node
        }
        if (previous != NULL)
        {
            previous->next = newNode;   //step 7:make the next field of the previous node
        }
        else
        {
            //If previous is still NULL, it means newNOde is now the first node
            START = newNode;
        }
    }

}

bool search(int rollNO, Node** previous, Node** current)
{
    *previous = NULL;
    *current = START;
    while (*current != NULL && (*current)->noMhs != rollNO)
    {
        *previous = *current;
        *current = (*current)->next;
    }
    return (*current != NULL);
}

void deleteNode()
{
    Node* previous, *current;    //
    int rollNo;

    cout << "\nEnter the roll number of the student whose record is to be deleted: ";
    cin >> rollNo;              //step 3: get the roll number to deleted

    if (START == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }

    current = START;            //step 1: start from the first node
    previous = NULL;

    // Locate the node to be deleted
    while (current != NULL && current->noMhs != rollNo)
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        cout << "\033[31mThe record with roll number " << rollNo << "not found\033[0m" << endl;
        return;
    }
    // Node to be deleted is that first node
    if (current == START)
    {
        START = START->next;    //step dua update start pointer
        if (START != NULL)
        {
            START->prev = NULL;
        }
    }
    else
    {
        //node to be deleted is not the first node
        previous->next = current->next;
        if (current->next != NULL)
        {
            //if there's a successo, update its prev pointer
            current->next->prev = previous;

        }
    }
    //Release the memory of the node marked as current
    delete current;
    cout << "\x1b[32mRecord with roll number " << rollNo << " deleted\x1b[0m" << endl;
}

bool listEmpty()
{
    return (START == NULL);
}

void travesrse()
{
    if (listEmpty())
        cout << "\nList is empty" << endl;
    else
    {
        cout << "\nRecords in ascending order of roll number are: " << endl;
        Node *currentNode = START;     //step 1
        while (currentNode != NULL)
            currentNode = currentNode->next;

        while (currentNode != NULL)
        {
            cout << currentNode->noMhs << " " << currentNode->name << endl;
            currentNode = currentNode->prev;
        }
    }

}

void revtraverse()
{
    if (listEmpty())
        cout << "\nLisst is empty" << endl;
    else
    {
        cout << "\nRecords in decending order of roll number are: " << endl;
        Node* currentNode = START;
        while (currentNode->next != NULL)
            currentNode = currentNode->next;

        while (currentNode != NULL)
        {
            cout << currentNode->noMhs << " " << currentNode->name << endl;
            currentNode = currentNode->prev;
        }
    }
}

void searchData()
{
    if (listEmpty() == true)
    {
        cout << "\nList is empty" << endl;
    }
    Node* prev, * curr;
    prev = curr = NULL;
    cout << "\nEnter the roll number of the student whose record you want to search: ";
    int num;
    cin >> num;
    if (search(num, &prev, &curr) == false)
        cout << "\nRecord not found" << endl;
    else
    {
        cout << "\nRecord found" << endl;
        cout << "\nRoll number: " << curr->noMhs << endl;
        cout << "\nName: " << curr->name << endl;
    }
}




int main()
{
    while (true)
    {
        try 
        {
            cout << "\nMenu" << endl;
            cout << "1. add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all records in the ascending order of roll numbers" << endl;
            cout << "4. View all records in the descending order of roll numbers" << endl;
            cout << "5. Search for a records in the list" << endl;
            cout << "6. Exit" << endl;
            cout << "\nEnter your choice (1-6): ";
            char ch;
            cin >> ch;

            switch (ch)
            {
                case '1':
                    addNode();
                    break;
                case '2':
                    deleteNode();
                     break;
                case '3':
                    travesrse();
                    break;
                case '4':
                    revtraverse();
                    break;
                case '5':
                    searchData();
                    break;
                case '6':
                    return 0;
                default:
                    cout << "\nInvalid option" << endl;
                    break;
            }

        }
        catch (exception& e)
        {
            cout << "Check for the values entered." << endl;
        }
    }

}

