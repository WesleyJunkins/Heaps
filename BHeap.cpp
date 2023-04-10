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
    BHeap(keytype k[], int s){
        for(int i = 0; i < s; i++)
        {
            insert(k[i]);
        }
    };

    // Destructor
    ~BHeap(){

    };

    // Copy Constructor

    // Copy Assignment Operator

    // Show minimum. Make no changes.
    keytype peekKey(){
        return minElement->key;
    };

    // Show minimum. Then remove it.
    keytype extractMin(){
        keytype deletedElementKey = minElement->key;
        int positionOfMinElement;
        if(rootList.length() != 0)
        {
            positionOfMinElement = 0;
        }
        while(positionOfMinElement < rootList.length())
        {
            if(rootList[positionOfMinElement] == minElement)
            {
                break;
            }
            positionOfMinElement++;
        }
        moveToFront(positionOfMinElement);
        rootList.removeFront();
        //START HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    };

    // Insert
    void insert(keytype k)
    {
        Node *insertedNode = new Node(k);
        rootList.addFront(insertedNode);
        if(rootList.length() == 1)
        {
            minElement = insertedNode;
        }else
        if(insertedNode->key < minElement->key)
        {
            minElement = insertedNode;
        }
        insertFixup();
    };

    // Merge H2 into current heap. H2 will become empty.
    void merge(BHeap<keytype> &H2){

    };

    // Print everything. Start with smallest tree first.
    void printKey(){
        // cout<<"Printing rootList"<<endl;
        // for(int i = 0; i < rootList.length(); i++)
        // {
        //     cout<<rootList[i]->key<<" ";
        // }
        if(rootList.length() == 0)
        {
            return;
        }
        for(int i = 0; i < rootList.length(); i++)
        {
            cout<<"B"<<rootList[i]->order()<<endl;
            cout<<rootList[i]->key<<" ";
            printChildList(rootList[i]);
            cout<<endl<<endl;
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
        //cout<<"In Insert Fixup"<<endl;
        if (rootList.length() >= 2)
        {
            //cout<<"rootList has at least two elements"<<endl;
            if (rootList[0]->order() == rootList[1]->order())
            {
                //cout<<"Same orders"<<endl;
                if (rootList[0]->key > rootList[1]->key)
                {
                    //cout<<"First element is bigger than second element"<<endl;
                    //Add 0 to childList of 1
                    rootList[1]->childList.addFront(rootList[0]);
                    //DeleteFront
                    rootList.delFront();
                    //Call insertFixup() again
                    insertFixup();
                }
                else if (rootList[0]->key <= rootList[1]->key)
                {
                    //cout<<"Second element is bigger than first element"<<endl;
                    //Add 1 to childList of 0
                    rootList[0]->childList.addFront(rootList[1]);
                    //Swap places of 0 and 1 in the rootList
                    Node* tempNode = rootList[0];
                    rootList[0] = rootList[1];
                    rootList[1] = tempNode;
                    //DeleteFront
                    rootList.delFront();
                    //Call insertFixup() again
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

    //Print each child list
    void printChildList(Node* element)
    {
        for(int i = 0; i < element->childList.length(); i++)
        {
            cout<<element->childList[i]->key<<" ";
            printChildList(element->childList[i]);
        }
    };

    //Push element to front of rootList
    void moveToFront(int index)
    {
        while(index > 0)
        {
            Node* tempElement = rootList[index];
            rootList[index] = rootList[index - 1];
            rootList[index - 1] = tempElement;
            index--;
        }
    };

    //Find the minimum element. Useful after multiple extracts or merges
    void findMin()
    {
        minElement = rootList[0];
        for(int i = 0; i < rootList.length(); i++)
        {
            if(rootList[i]->key < minElement->key)
            {
                minElement = rootList[i];
            }
        }
    };

    //Fixup after extract min. Works for other things. May rename as generalConsolidate
    void extractMinFixup(int position)
    {
        if((position + 1) < rootList.length())
        {
            if(rootList[position]->order() == rootList[position + 1]->order())
            {
                if(rootList[position]->key > rootList[position + 1]->key)
                {
                    rootList[position + 1]->childList.addFront(rootList[position]);
                    moveToFront(position);
                    rootList.delFront();
                    extractMinFixup(position);
                }else
                {
                    rootList[position]->childList.addFront(rootList[position + 1]);
                    moveToFront(position + 1);
                    rootList.delFront();
                    extractMinFixup(position);
                }
            }else
            if(rootList[position]->order() > rootList[position + 1]->order())
            {
                Node* tempElement = rootList[position];
                rootList[position] = rootList[position + 1];
                rootList[position + 1] = tempElement;
                extractMinFixup(position);
            }else
            {
                extractMinFixup(position + 1);
            }
        }else
        {
            return;
        }
    }


};

int main()
{
    int T1KeyValues[20] = {1,3,5,7,9,11,13,15,17,19, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

    BHeap<int> T1(T1KeyValues, 20);
    //BHeap<int> T1;

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
    cout<<"Done"<<endl;
    T1.printKey();

    cout<<endl;
    cout<<T1.peekKey()<<endl;
    return 0;
}