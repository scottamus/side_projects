//
//  main.cpp
//  WhiteboardQuestionRefresher
//
//  Created by Scott Loveless on 3/16/15.
//  Copyright (c) 2015 Scott Loveless. All rights reserved.
//

#include <iostream>
using namespace std;


typedef struct IntElement {
    struct IntElement *next;
    int data;
} IntElement;

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    void InsertInFront(int data);
    void InsertInBack(int data);
    void PrintOutInOrder();
    
protected:
    typedef struct Node {
        struct Node *next;
        int data;
    } Node;
    
    Node * head;
};

LinkedList::LinkedList()
{
    head = NULL;
    return;
}

LinkedList::~LinkedList()
{
    while (head)
    {
        Node *next = head->next;
        delete head;
        head = next;
    }
}

void LinkedList::InsertInFront(int data)
{
    Node *n = new Node;
    n->data = data;
    
    if (!head) // special case for empty list
    {
        head = n;
        return;
    }
    
    n->next = head;
    head = n;
    return;
}

void LinkedList::InsertInBack(int data)
{
    Node *n = new Node;
    n->data = data;
    
    if (!head) // special case for empty list
    {
        head = n;
        return;
    }
    
    Node *curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    // should be at the end now
    curr->next = n;
}

void LinkedList::PrintOutInOrder()
{
    while(head) {
        cout << head->data << " ";
        head = head->next ;
    }
    cout << endl;
}

void InsertInFront(IntElement **head, int data) // need to pass in pointer to head pointer!!
{
    IntElement *n = new IntElement;
    n->data = data;
    
    if (!*head) // special case for empty list
    {
        *head = n;
        return;
    }
    
    n->next = *head;
    *head = n;
    return;
}

void InsertInBack(IntElement **head, int data) // need to pass in pointer to head pointer!!
{
    IntElement *n = new IntElement;
    n->data = data;
    
    if (!*head) // special case for empty list
    {
        *head = n;
        return;
    }
    
    IntElement *curr = *head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    // should be at the end now
    curr->next = n;
    return;
}

void PrintOutInOrder(IntElement *head)
{
    while(head) {
        cout << head->data << " ";
        head = head->next ;
    }
    cout << endl;
}

bool deleteElement(IntElement **head, IntElement *deleteMe)
{
    IntElement *tmp = *head;
    
    if (deleteMe == *head) // special case for the head
    {
        *head = tmp->next;
        delete deleteMe;
        return true;
    }
    
    // iterate to the node before the one to delete
    while (tmp->next != deleteMe && tmp->next) {
        tmp = tmp->next;
    }
    
    // check for the last one (no match)
    if (tmp->next)
    {
        // delete it
        tmp->next = tmp->next->next;
        delete deleteMe;
        return true;
    }
    
    return false; // didn't find it
}

IntElement* FindElement(IntElement *head, int data)
{
    while (head && head->data != data) {
        head = head->next;
    }
    
    return head;
}

char firstNonrepeatedCharacter_Slow(const std::string &str)
{
    // sanity check
    if (str.empty())
        return NULL;
    
    int num = 0;
    for (int i=0; i<str.size(); i++) {
        char tmp = str[i];
        bool foundMatch = false;
        // compare against rest of string
        for (int j=(i + 1); j<str.size(); j++) {
            num++;
            if (str[i] == str[j])
                foundMatch = true;
        }
        // if no match here, this is the first non-repeated character
        if (!foundMatch)
        {
            cout << "number of comparisons: " << num << endl;
            return tmp;
        }
    }
    
    cout << "number of comparisons: " << num << endl;
    return NULL; // no non-repeated character
}

char firstNonrepeatedCharacter(const std::string &str)
{
    // sanity check
    if (str.empty())
        return NULL;
    
    int num = 0;
    // build up array, using char as index
    int *instances = new int[128];
    for (int i=0; i<str.size(); i++) {
        instances[(int)str[i]]++; // increment number of instances for THIS char.
        num++; // counter
    }
    cout << "number of comparisons: " << num << endl;
    
    for (int j=0; j<str.size(); j++) {
        if (instances[(int)str[j]] == 1)
            return str[j];
    }
    
    return NULL; // no non-repeated character
}

bool reverseWordsInString(std::string &str)
{
    // sanity check
    if (str.empty())
        return false;
    
    char *reversed = new char[str.size()];
    
    int readPosition = str.size() - 1;
    int writePosition = 0;
    int wordEnd;
    int wordStart;
    
    while (readPosition >= 0)
    {
        if (str[readPosition] != ' ') // word character
        {
            // store end of word since reading backwards
            wordEnd = readPosition;
            
            // find next non-word character
            while (readPosition >= 0 && str[readPosition] != ' ')
                readPosition--;
            
            // now we're on next non-word character
            // get word start index
            wordStart = readPosition + 1;
            
            // copy word to reversed string
            while (wordStart <= wordEnd)
            {
                reversed[writePosition] = str[wordStart];
                writePosition++;
                wordStart++;
            }
            
            // readPosition is already on space, so no need to decrement here...
        }
        else // nonword character (space)
        {
            // write character and increment write position, then decrement read position
            reversed[writePosition] = str[readPosition];
            writePosition++;
            readPosition--;
        }
    }
    
    str = reversed;
    
    return true;
}

void reverseStringInPlace(std::string &str)
{
    // sanity check
    if (str.empty())
        return;
    
    char temp;
    int startIndex = 0;
    int endIndex = str.size() - 1;
    
    while (startIndex < endIndex)
    {
        temp = str[startIndex];
        str[startIndex] = str[endIndex];
        str[endIndex] = temp;
        
        // move indexes towards middle
        startIndex++;
        endIndex--;
    }
}

int main(int argc, const char * argv[]) {
    // class version, insert in back:
//    LinkedList *list = new LinkedList();
//    for (int i=1; i<=10; i++) {
//        list->InsertInBack(i);
//    }
//    list->PrintOutInOrder();
    
    // class version, insert in front:
//    LinkedList *list = new LinkedList();
//    for (int i=1; i<=10; i++) {
//        list->InsertInFront(i);
//    }
//    list->PrintOutInOrder();
    
    // struct version, insert in back:
//    IntElement *list;
//    for (int i=1; i<=10; i++) {
//        InsertInBack(&list, i);
//    }
//    PrintOutInOrder(list);
    
    // struct version, insert in front
//    IntElement *list;
//    for (int i=1; i<=10; i++) {
//        InsertInFront(&list, i);
//    }
//    PrintOutInOrder(list);

    // struct version, find element:
//    IntElement *list;
//    for (int i=1; i<=10; i++) {
//        InsertInBack(&list, i);
//    }
//    IntElement *null = FindElement(list, 45);
//    if (!null) cout << "it was null" << endl;
//    IntElement *found = FindElement(list, 7);
//    if (found) cout << "found data is: " << found->data << endl;
    
    // struct version, delete element:
//    IntElement *list;
//    for (int i=1; i<=10; i++) {
//        InsertInBack(&list, i);
//    }
//    cout << "starting list: ";
//    PrintOutInOrder(list);
//    IntElement *found = FindElement(list, 7); // change to 1, 10, 12, etc. to test different cases.
//    if (found) cout << "found data is: " << found->data << endl;
//    bool result = deleteElement(&list, found);
//    cout << "result is: " << result << endl;
//    cout << "current list: ";
//    PrintOutInOrder(list);
    
    // first non-repeating character in a string
//    string str = "the red fox jumped over the brown cow.";
//    
//    string str2 = "lorem ipsum dolor sit amet, consectetuer adipiscing elit. nam cursus. morbi ut mi. nullam enim leo, egestas id, condimentum at, laoreet mattis, massa. sed eleifend nonummy diam. praesent mauris ante, elementum et, bibendum at, posuere sit amet, nibh. duis tincidunt lectus quis dui viverra vestibulum. suspendisse vulputate aliquam dui. nulla elementum dui ut augue. aliquam vehicula mi at mauris. maecenas placerat, nisl at consequat rhoncus, sem nunc gravida justo, quis eleifend arcu velit quis lacus. morbi magna magna, tincidunt a, mattis non, imperdiet vitae, tellus. sed odio est, auctor ac, sollicitudin in, consequat vitae, orci. fusce id felis. vivamus sollicitudin";
//    char c = firstNonrepeatedCharacter_Slow(str2);
//    cout << "first non-repeated character is: " << c << endl;
//    cout << "next one: " << endl;
//    char d = firstNonrepeatedCharacter(str2);
//    cout << "first non-repeated character is: " << d << endl;
    
    // reverse words in a string
//    string str = "hello world.";
//    cout << "starting string: " << str << endl;
//    reverseWordsInString(str);
//    cout << "reversed: " << str << endl;
    
    // reverse string in place
    string str = "hello world.";
    cout << "starting string: " << str << endl;
    reverseStringInPlace(str);
    cout << "reversed: " << str << endl;
    
    return 0;
}





