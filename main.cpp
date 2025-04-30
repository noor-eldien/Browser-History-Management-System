#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Node
{
public:
    string url;
    Node* next;
    Node* prev;
    Node() {} // default ctor
    Node(string URL) : url(URL), next(nullptr), prev(nullptr) {}
    ~Node(){}
};


class HistoryStack
{
public:
    HistoryStack() {}

    vector<string> commands;
    Node *nextPagesStack= nullptr; // top of the next pages stack
    Node *prevPagesStack= nullptr; // top of the previous pages stack
    void pushIntoPrevStack(string url) // this function is only used to fill the URLs Stack in the beginning of the process
    {
        Node *urlNode = new Node(url);

        urlNode->next = prevPagesStack;
        if (prevPagesStack != nullptr)
        {
            prevPagesStack->prev = urlNode;
        }
        prevPagesStack = urlNode;
    }
    void pushIntoPrevStack(Node *sendToPrev) // overridden function, will be used when choosing next / go forward
    {
        sendToPrev->next = prevPagesStack;
        if (prevPagesStack != nullptr)
        {
            prevPagesStack->prev = sendToPrev;
        }
        prevPagesStack = sendToPrev;
    }
    void pushIntoNextStack(Node *sendToNext) // will be used when choosing prev / go backward
    {
        sendToNext->next = nextPagesStack;
        if(nextPagesStack != nullptr)
        {
            nextPagesStack->prev = sendToNext;
        }
        nextPagesStack = sendToNext;
    }
    Node* popTopPrevStack() // to return the top of the PrevStack and return it
    {
        Node *tmp = prevPagesStack;
        if(prevPagesStack==nullptr)
        {
            return nullptr;
        }
        prevPagesStack = prevPagesStack->next;
        if(prevPagesStack!= nullptr)
        {
            prevPagesStack->prev = nullptr;
        }
        tmp->next = nullptr;
        return tmp;
    }
    Node* popTopNextStack() // to return the top of the nextStack and return it
    {
        if(nextPagesStack==nullptr)
        {
            return nullptr;
        }
        Node *tmp = nextPagesStack;
        nextPagesStack = nextPagesStack->next;
        if(nextPagesStack != nullptr)
        {
            nextPagesStack->prev = nullptr;
        }
        tmp->next = nullptr;
        return tmp;
    }

    // when choosing to go backward-> pop and show the top URL from the prevStack
    //                             -> push the popped URL into the nextStack
    void goToPrev()
    {
        // Move current page from prevStack to nextStack, so prevStack->next is "previous" page
        Node *current = popTopPrevStack();
        if(current!=nullptr)
        {
            pushIntoNextStack(current);
        }
    }

    // when choosing to go forward -> pop and show the top URL from the nextStack
    //                             -> push the popped URL into the prevStack
    void goToNext()
    {
        // Move current page from nextStack to prevStack
        Node *current = popTopNextStack();
        if(current!=nullptr)
        {
            pushIntoPrevStack(current);
        }
    }
    void operation() // responsible for managing the navigation operations based on the commands
    {
        cout << "The current page at initial state is:" << endl; // last URL / page that appear at the initial state
        if(prevPagesStack!= nullptr)
        {
            cout <<prevPagesStack->url <<endl <<endl;
        }

        for (int i = 0; i < commands.size(); ++i)
        {
            cout<< i+1<<":";
            if(commands[i] == "Backward")
            {
                cout<< "After choosing Backward: ";
                goToPrev();
            }
            else if (commands[i] == "Forward")
            {
                cout<< "After choosing Forward: ";
                goToNext();
            }
            currentState();
        }
    }
    void currentState() // will be used to return info about the current state after each operation done
    {
        if(prevPagesStack != nullptr)
        {
            cout << "The current page is:" << endl;
            cout << prevPagesStack->url << endl;
            // Next one is top of next stack, Previous one is prev of prevPagesStack
            if(nextPagesStack!= nullptr)
            {
                cout << "The Next one is:" << endl;
                cout << nextPagesStack->url << endl;
            }
            if(prevPagesStack->next != nullptr)
            {
                cout << "The Previous one is:" << endl;
                cout << prevPagesStack->next->url << endl;
            }
            cout << endl;
        }
        else
        {
            cout<<"you haven't visited any urls yet"<<endl;
        }
    }

};



int main()
{
    HistoryStack stack;
    ifstream infile("URLs.txt"); // opening the URLs file
    if (!infile)
    {
        cout << "Can't open file!" << endl;
        return 0;
    }
    int numberOfUrl; // reading the first line which is the number of URLs
    infile >> numberOfUrl;
    string dummy;
    getline(infile, dummy); // move to the next line after number

    string url;
    for (int i = 0; i < numberOfUrl; ++i) // reading URLs from file and pushing them in the stack of the URLs
    {
        getline(infile, url);
        stack.pushIntoPrevStack(url); // Filling the URLs Stack
    }

    string commandsLine; // taking the whole command line / last line in the file
    getline(infile, commandsLine);

    vector<string> commandsV; // storing commands in a vector -dynamic size- to be sent to the HistoryStack to manage operations
    string word;
    istringstream iss(commandsLine);
    while (iss >> word)
    {
        commandsV.push_back(word);
    }
    stack.commands = commandsV;
    infile.close();

    stack.operation();



}
