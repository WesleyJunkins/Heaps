#ifndef heap
#define heap

#include <iostream>
#include "CircularDynamicArray.cpp"
using namespace std;

template <typename keytype>
class Heap
{
public:
    CircularDynamicArray<keytype> mainArray;

    // Default Constructor
    Heap(){

    };

    // Special Constructor
    Heap(keytype k[], int s)
    {
        for (int i = 0; i < s; i++)
        {
            mainArray.addEnd(k[i]);
        }
        // int currentIndex = mainArray.eIndexActual();
        for (int i = ((mainArray.length() - 2) / 2); i >= 0; i--)
        {
            heapify(i);
        }
    };

    // Copy Constructor
    Heap(const Heap &other)
    {
        mainArray = CircularDynamicArray<keytype>(other.mainArray);
    };

    // Copy Assignment Operator
    Heap &operator=(const Heap &other)
    {
        if (this != &other)
        {
            mainArray = CircularDynamicArray<keytype>(other.mainArray);
        }
        return *this;
    }

    // Show minimum. Make no changes.
    keytype peekKey()
    {
        return mainArray[0];
    };

    // Show minimum. Then remove it.
    keytype extractMin()
    {
        keytype minKey = mainArray[0];
        mainArray[0] = mainArray[mainArray.length() - 1];
        mainArray.delEnd();
        heapify(0);
        return minKey;
    };

    // Insert
    void insert(keytype k)
    {
        mainArray.addEnd(k);
        int currentIndex = mainArray.eIndexActual();
        bubbleUp(currentIndex);
    };

    // Print all keys in the array, starting at the root.
    void printKey()
    {
        for (int i = 0; i < mainArray.length(); i++)
        {
            cout << mainArray[i] << " ";
        }
        cout << endl;
    };

    // Helper Functions
    // index's parent
    int parentOf(int index)
    {
        return (index - 1) / 2;
    };

    // index's left child
    int leftChildOf(int index)
    {
        return (2 * index) + 1;
    };

    // index's right child
    int rightChildOf(int index)
    {
        return (2 * index) + 2;
    };

    // Bubble Up Function
    void bubbleUp(int index)
    {
        while ((index > 0) && (mainArray[index] < mainArray[parentOf(index)]))
        {
            keytype tempNode = mainArray[index];
            mainArray[index] = mainArray[parentOf(index)];
            mainArray[parentOf(index)] = tempNode;
            index = parentOf(index);
        }
    };

    // Heapify Function
    void heapify(int index)
    {
        int smallestOfTheBunch = index;
        int leftChild = leftChildOf(index);
        int rightChild = rightChildOf(index);
        if ((leftChild < mainArray.length()) && (mainArray[leftChild] < mainArray[smallestOfTheBunch]))
        {
            smallestOfTheBunch = leftChild;
        }
        if ((rightChild < mainArray.length()) && (mainArray[rightChild] < mainArray[smallestOfTheBunch]))
        {
            smallestOfTheBunch = rightChild;
        }
        if (smallestOfTheBunch != index)
        {
            keytype tempNode = mainArray[index];
            mainArray[index] = mainArray[smallestOfTheBunch];
            mainArray[smallestOfTheBunch] = tempNode;
            heapify(smallestOfTheBunch);
        }
    };
};

#endif