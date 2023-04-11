#ifndef BinomialHeap
#define BinomialHeap

#include <iostream>
#include "CircularDynamicArray.cpp"
using namespace std;

template <typename keytype>
class BHeap
{
public:
    struct Node
    {
        keytype key;
        CircularDynamicArray<Node *> childList;

        Node(keytype key)
        {
            this->key = key;
        }

        int order()
        {
            return childList.length();
        }
    };

    CircularDynamicArray<Node *> rootList;
    Node *minElement;

    // Default Constructor
    BHeap(){

    };

    // Special Constructor
    BHeap(keytype k[], int s)
    {
        for (int i = 0; i < s; i++)
        {
            insert(k[i]);
        }
    };

    // Destructor
    ~BHeap()
    {
        while (rootList.length() != 0)
        {
            rootList.delFront();
        }
    };

    // Copy Constructor
    BHeap(const BHeap &other)
    {
        for (int i = 0; i < other.rootList.length(); i++)
        {
            Node *newNode = new Node(other.rootList[i]->key);
            buildHeapCopySpecial(newNode, other.rootList[i]);
            rootList.addEnd(newNode);
        }
        findMin();
    };

    // Copy Assignment Operator
    BHeap &operator=(const BHeap &other)
    {
        if (this != &other)
        {
            while (rootList.length() > 0)
            {
                rootList.delFront();
            }
            for (int i = 0; i < other.rootList.length(); i++)
            {
                Node *newNode = new Node(other.rootList[i]->key);
                buildHeapCopySpecial(newNode, other.rootList[i]);
                rootList.addEnd(newNode);
            }
            findMin();
        }
        return *this;
    };

    // Show minimum. Make no changes.
    keytype peekKey()
    {
        return minElement->key;
    };

    // Show minimum. Then remove it.
    keytype extractMin()
    {
        keytype deletedElementKey = minElement->key;
        int positionOfMinElement;
        if (rootList.length() != 0)
        {
            positionOfMinElement = 0;
        }
        while (positionOfMinElement < rootList.length())
        {
            if (rootList[positionOfMinElement] == minElement)
            {
                break;
            }
            positionOfMinElement++;
        }
        moveToFront(positionOfMinElement);
        rootList.delFront();
        // Add minKey's childList elements to rootList, starting from end.
        for (int i = minElement->childList.length() - 1; i >= 0; i--)
        {
            // For each element in minElement's childList, add it to the front of rootList.
            rootList.addFront(minElement->childList[i]);
            // Traverse the rootList, with the newly added element, until you get to an element with an equal or greater order. Leave the element before this element. This will automatically stop once there is no next element to compare the previous element to (i.e. index + 1 = 0)
            for (int index = 0; (index + 1) < rootList.length();)
            {
                if (rootList[index]->order() > rootList[index + 1]->order())
                {
                    // Swap the elements
                    Node *tempElement = rootList[index];
                    rootList[index] = rootList[index + 1];
                    rootList[index + 1] = tempElement;
                }
                else
                {
                    break;
                }
                index++;
            }
        }
        //  Consolidate
        extractMinFixup(0);
        delete minElement;
        findMin();
        return deletedElementKey;
    };

    // Insert
    void insert(keytype k)
    {
        Node *insertedNode = new Node(k);
        rootList.addFront(insertedNode);
        if (rootList.length() == 1)
        {
            minElement = insertedNode;
        }
        else if (insertedNode->key < minElement->key)
        {
            minElement = insertedNode;
        }
        insertFixup();
    };

    // Merge H2 into current heap. H2 will become empty.
    void merge(BHeap<keytype> &H2)
    {
        // Start at the beginning of H2's rootList
        // While H2's rootList is not empty, copy the node into H1's rootList
        while (H2.rootList.length() > 0)
        {
            // Node *nodeToInsert = new Node(H2.rootList[0]->key);
            Node *nodeToInsert = H2.rootList[0];
            // buildHeapCopy(nodeToInsert, H2.rootList[0]);
            //  Traverse H1 with the node to insert until you reach a node with greater or equal order. Leave node to insert before these.
            rootList.addFront(nodeToInsert);
            for (int i = 0; (i + 1) < rootList.length();)
            {
                if (rootList[i]->order() > rootList[i + 1]->order())
                {
                    Node *tempElement = rootList[i];
                    rootList[i] = rootList[i + 1];
                    rootList[i + 1] = tempElement;
                }
                else
                {
                    break;
                }
                extractMinFixup(0); //                                          THIS MAY NEED TO BE REMOVED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                i++;
            }
            // Destroy the element we just copied from H2
            // delete H2.rootList[0];
            H2.rootList.delFront();
            extractMinFixup(0);
            // Fixup the heap
            // extractMinFixup(0);
            findMin();
        }
    };

    // Merge H2 into current heap. H2 will become empty.
    void mergeSpecial(BHeap<keytype> &H2)
    {
        // Start at the beginning of H2's rootList
        // While H2's rootList is not empty, copy the node into H1's rootList
        while (H2.rootList.length() > 0)
        {
            Node *nodeToInsert = new Node(H2.rootList[0]->key);
            buildHeapCopy(nodeToInsert, H2.rootList[0]);
            // Traverse H1 with the node to insert until you reach a node with greater or equal order. Leave node to insert before these.
            rootList.addFront(nodeToInsert);
            for (int i = 0; (i + 1) < rootList.length();)
            {
                if (rootList[i]->order() > rootList[i + 1]->order())
                {
                    Node *tempElement = rootList[i];
                    rootList[i] = rootList[i + 1];
                    rootList[i + 1] = tempElement;
                }
                else
                {
                    break;
                }
                i++;
            }
            // Destroy the element we just copied from H2
            delete H2.rootList[0];
            H2.rootList.delFront();
            // Fixup the heap
            extractMinFixup(0);
            findMin();
        }
    };

    // Print everything. Start with smallest tree first.
    void printKey()
    {
        if (rootList.length() == 0)
        {
            return;
        }
        for (int i = 0; i < rootList.length(); i++)
        {
            cout << "B" << rootList[i]->order() << endl;
            cout << rootList[i]->key << " ";
            printChildList(rootList[i]);
            cout << endl
                 << endl;
        }
    };

    // Helper Functions
    /*Insert Fixup :    If the first and second nodes in the array are ACTUALLY in the array, then proceed with this function.
                        In the rootList, take the order of the first node. Compare it with the second node.
                        If they have a different order, then exit the function.
                        If they have the same order, compare the keytypes of the two nodes.
                        If the first node has the smaller key, add the next node to its childList.
                        If the second node has the smaller key, add the first node to its childList.
                        If the first node had the smaller key, swap the places of the first and second node in the array. Then deleteFront.
                        If the second node had the smaller key, then deleteFront.
    */
    void insertFixup()
    {
        if (rootList.length() >= 2)
        {
            if (rootList[0]->order() == rootList[1]->order())
            {
                if (rootList[0]->key > rootList[1]->key)
                {
                    // Add 0 to childList of 1
                    rootList[1]->childList.addFront(rootList[0]);
                    // DeleteFront
                    rootList.delFront();
                    // Call insertFixup() again
                    insertFixup();
                }
                else if (rootList[0]->key <= rootList[1]->key)
                {
                    // Add 1 to childList of 0
                    rootList[0]->childList.addFront(rootList[1]);
                    // Swap places of 0 and 1 in the rootList
                    Node *tempNode = rootList[0];
                    rootList[0] = rootList[1];
                    rootList[1] = tempNode;
                    // DeleteFront
                    rootList.delFront();
                    // Call insertFixup() again
                    insertFixup();
                }
            }
            else
            {
                return;
            }
        }
        return;
    };

    // Print each child list
    void printChildList(Node *element)
    {
        for (int i = 0; i < element->childList.length(); i++)
        {
            cout << element->childList[i]->key << " ";
            printChildList(element->childList[i]);
        }
    };

    // Push element to front of rootList
    void moveToFront(int index)
    {
        while (index > 0)
        {
            Node *tempElement = rootList[index];
            rootList[index] = rootList[index - 1];
            rootList[index - 1] = tempElement;
            index--;
        }
    };

    // Find the minimum element. Useful after multiple extracts or merges
    void findMin()
    {
        if (rootList.length() != 0)
        {
            minElement = rootList[0];
            for (int i = 0; i < rootList.length(); i++)
            {
                if (rootList[i]->key < minElement->key)
                {
                    minElement = rootList[i];
                }
            }
        }
    };

    // Fixup after extract min. Works for other things. May rename as generalConsolidate
    void extractMinFixup(int position)
    {
        if ((position + 1) < rootList.length())
        {
            if (rootList[position]->order() == rootList[position + 1]->order())
            {
                if (rootList[position]->key > rootList[position + 1]->key)
                {
                    rootList[position + 1]->childList.addFront(rootList[position]);
                    moveToFront(position);
                    rootList.delFront();
                    extractMinFixup(position);
                }
                else
                {
                    rootList[position]->childList.addFront(rootList[position + 1]);
                    moveToFront(position + 1);
                    rootList.delFront();
                    extractMinFixup(position);
                }
            }
            else if (rootList[position]->order() > rootList[position + 1]->order())
            {
                Node *tempElement = rootList[position];
                rootList[position] = rootList[position + 1];
                rootList[position + 1] = tempElement;
                extractMinFixup(position);
            }
            else
            {
                extractMinFixup(position + 1);
            }
        }
        else
        {
            return;
        }
    };

    // Copy a node from one heap to another and make sure that all of the descendants are there.
    void buildHeapCopy(Node *B1, Node *B2)
    {
        while (B2->childList.length() > 0)
        {
            Node *newB1Node = new Node(B2->childList[0]->key);
            B1->childList.addEnd(newB1Node);
            buildHeapCopy(newB1Node, B2->childList[0]);
            delete B2->childList[0];
            B2->childList.delFront();
        }
    };

    // A special version of buildHeapCopy that does not delete the contents of B2
    void buildHeapCopySpecial(Node *B1, Node *B2)
    {
        for (int i = 0; i < B2->childList.length(); i++)
        {
            Node *newB1Node = new Node(B2->childList[i]->key);
            B1->childList.addEnd(newB1Node);
            buildHeapCopySpecial(newB1Node, B2->childList[i]);
        }
    };
};

int main()
{
    int T1KeyValues[20] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int T1MoreKeyValues[10] = {1, 2, 3, 4, 5, 11, 12, 13, 14, 15};
    int T2MoreKeyValues[11] = {6, 7, 8, 9, 10, 16, 17, 18, 19, 20, 21};
    string T1StringValues[10] = {"the", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "log", "tonight"};

    BHeap<int> T1;

    //BHeap<string> T1(T1StringValues, 10);

    for (int i = 0; i < 1000; i++)
    {
        T1.insert(i);
    };

    // cout<<"Printing T1 Before the stuff"<<endl;
    // T1.printKey();

    // BHeap<int> T1;
    // BHeap<int> T2(T2MoreKeyValues, 11);
    // BHeap<int> T2(T1);
    BHeap<int> T2;
    T2 = T1;

    cout << "Printing T1" << endl;
    T1.printKey();

    cout << "Printing T2" << endl;
    T2.printKey();

    // cout << "Done" << endl;
    // T1.printKey();

    // cout << "Done" << endl;
    // T2.printKey();

    T1.merge(T2);

    // cout << "DONE" << endl;
    // T1.printKey();

    // cout << "DONE" << endl;
    // T2.printKey();

    // cout<<"I'm Here!"<<endl;
    // T1.insert(3);
    // cout<<"I made it!"<<endl;
    // T1.insert(4);
    // cout<<"I made it again!"<<endl;
    // T1.insert(2);
    // cout<<"I made it a third time!"<<endl;
    // T1.printKey();
    // cout<<endl;
    // cout<<T1.peekKey()<<endl;

    // for(int i = 0; i < 10000; i++)
    // {
    //     T1.insert(i);
    //     // T1.printKey();
    //     // cout<<endl;
    // }
    // for(int i = 0; i < 1000; i++)
    // {
    //     cout<<T2.extractMin()<<endl;
    //     // T1.printKey();
    //     // cout<<endl;
    // }

    // T1.insert(1);
    // T1.insert(2);
    // T1.insert(3);

    // cout << T1.extractMin() << endl;
    // cout << T1.extractMin() << endl;
    // cout << T1.extractMin() << endl;

    cout << "Done" << endl;
    T2.printKey();
    cout<<"Done again. There should be output below this line."<<endl;
    T1.printKey();

    // cout << endl;
    //  cout<<T1.peekKey()<<endl;
    //  cout<<T1.peekKey()<<endl;
    return 0;
}

#endif