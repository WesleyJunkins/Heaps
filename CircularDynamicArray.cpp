#ifndef circularDynamicArray
#define circularDynamicArray

#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class CircularDynamicArray
{
public:
    CircularDynamicArray()
    {
        array = new T[2];
        aSize = 0;
        aCapacity = 2;
        isReversed = false;
        frontIndex = 0;
        endIndex = 0;
    };

    CircularDynamicArray(int s)
    {
        array = new T[s];
        aSize = s;
        aCapacity = s;
        isReversed = false;
        frontIndex = 0;
        endIndex = s - 1;
    };

    CircularDynamicArray(const CircularDynamicArray &other)
    {
        array = new T[other.aCapacity];
        for (int i = 0; i < other.aCapacity; i++)
        {
            array[i] = other.array[i];
        }
        aSize = other.aSize;
        aCapacity = other.aCapacity;
        isReversed = other.isReversed;
        frontIndex = other.frontIndex;
        endIndex = other.endIndex;
    };

    CircularDynamicArray &operator=(const CircularDynamicArray &other)
    {
        if (this != &other)
        {
            T *newArray = new T[other.aCapacity];
            for (int i = 0; i < other.aCapacity; i++)
            {
                newArray[i] = other.array[i];
            }
            delete[] array;
            array = newArray;
            aSize = other.aSize;
            aCapacity = other.aCapacity;
            isReversed = other.isReversed;
            frontIndex = other.frontIndex;
            endIndex = other.endIndex;
        }
        return *this;
    };

    ~CircularDynamicArray()
    {
        delete[] array;
    };

    T &operator[](int i)
    {
        if ((i < 0) || (i > aSize - 1))
        {
            cout << "ERROR: [" << i << "] is out of bounds for this array. Enter a value between 0 and " << aSize - 1 << ".\n";
            return returnReferenceValue;
        }
        else
        {
            if (isReversed == false)
            {
                return array[actualPosition(frontIndex + i)];
            }
            else
            {
                return array[actualPosition(frontIndex - i)];
            }
        };
    };

    const T &operator[](int i) const
    {
        if ((i < 0) || (i > aSize - 1))
        {
            cout << "ERROR: [" << i << "] is out of bounds for this array. Enter a value between 0 and " << aSize - 1 << ".\n";
            return returnReferenceValue;
        }
        else
        {
            if (isReversed == false)
            {
                return array[actualPosition(frontIndex + i)];
            }
            else
            {
                return array[actualPosition(frontIndex - i)];
            }
        };
    };

    void addEnd(T v)
    {
        if (aSize == aCapacity)
        {
            this->reallocate(aCapacity * 2);
        }
        if (isReversed == false)
        {
            if (aSize == 0)
            {
                array[actualPosition(endIndex)] = v;
                aSize++;
            }
            else
            {
                array[actualPosition(endIndex + 1)] = v;
                aSize++;
                endIndex = actualPosition(endIndex + 1);
            }
        }
        else if (isReversed == true)
        {
            if (aSize == 0)
            {
                array[actualPosition(endIndex)] = v;
                aSize++;
            }
            else
            {
                array[actualPosition(endIndex - 1)] = v;
                aSize++;
                endIndex = actualPosition(endIndex - 1);
            }
        };
    };

    void addFront(T v)
    {
        if (aSize == aCapacity)
        {
            this->reallocate(aCapacity * 2);
        }
        if (isReversed == false)
        {
            if (aSize == 0)
            {
                array[actualPosition(frontIndex)] = v;
                aSize++;
            }
            else
            {
                array[actualPosition(frontIndex - 1)] = v;
                aSize++;
                frontIndex = actualPosition(frontIndex - 1);
            }
        }
        else if (isReversed == true)
        {
            if (aSize == 0)
            {
                array[actualPosition(frontIndex)] = v;
                aSize++;
            }
            else
            {
                array[actualPosition(frontIndex + 1)] = v;
                aSize++;
                frontIndex = actualPosition(frontIndex + 1);
            }
        }
    };

    void delEnd()
    {
        if (aSize <= (int(aCapacity / 4)))
        {
            this->reallocate(int(aCapacity / 2));
        }
        if (isReversed == false)
        {
            if (aSize != 0)
            {
                endIndex = actualPosition(endIndex - 1);
                aSize--;
            }
        }
        else if (isReversed == true)
        {
            if (aSize != 0)
            {
                endIndex = actualPosition(endIndex + 1);
                aSize--;
            }
        }
    };

    void delFront()
    {
        if (aSize <= (int(aCapacity / 4)))
        {
            this->reallocate(int(aCapacity / 2));
        }
        if (isReversed == false)
        {
            if (aSize != 0)
            {
                frontIndex = actualPosition(frontIndex + 1);
                aSize--;
            }
        }
        else if (isReversed == true)
        {
            if (aSize != 0)
            {
                frontIndex = actualPosition(frontIndex - 1);
                aSize--;
            }
        }
    };

    int length()
    {
        return aSize;
    };

    int length() const
    {
        return aSize;
    };

    int capacity()
    {
        return aCapacity;
    };

    void clear()
    {
        delete[] array;
        array = new T[2];
        aSize = 0;
        aCapacity = 2;
    };

    T QuickSelect(int k)
    {
        T *tempArray = new T[aSize];
        int tempArraySize = 0;
        if (isReversed == false)
        {
            int startingIndex = actualPosition(frontIndex);
            for (int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                tempArraySize++;
                startingIndex++;
            }
        }
        else if (isReversed == true)
        {
            int startingIndex = actualPosition(frontIndex);
            for (int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                tempArraySize++;
                startingIndex--;
            }
        }
        T finalResult = select(tempArray, tempArraySize, k);
        delete[] tempArray;
        return finalResult;
    };

    T select(T tempArray[], int tempArraySize, int k)
    {
        int randomIndex = rand() % tempArraySize;
        T pivot = tempArray[randomIndex];
        T *L = new T[tempArraySize];
        T *E = new T[tempArraySize];
        T *G = new T[tempArraySize];
        int Lindex = 0;
        int Eindex = 0;
        int Gindex = 0;
        int Lsize = 0;
        int Esize = 0;
        int Gsize = 0;
        for (int i = 0; i < tempArraySize; i++)
        {
            if (tempArray[i] < pivot)
            {
                L[Lindex] = tempArray[i];
                Lindex++;
                Lsize++;
            }
            else if (tempArray[i] == pivot)
            {
                E[Eindex] = tempArray[i];
                Eindex++;
                Esize++;
            }
            else
            {
                G[Gindex] = tempArray[i];
                Gindex++;
                Gsize++;
            }
        }
        T recursiveResult;
        if (k <= Lsize)
        {
            recursiveResult = select(L, Lsize, k);
            delete[] L;
            delete[] E;
            delete[] G;
            return recursiveResult;
        }
        else if (k <= Lsize + Esize)
        {
            delete[] L;
            delete[] E;
            delete[] G;
            return pivot;
        }
        else
        {
            recursiveResult = select(G, Gsize, k - Lsize - Esize);
            delete[] L;
            delete[] E;
            delete[] G;
            return recursiveResult;
        }
    };

    void stableSort()
    {
        T *tempArray = new T[aSize];
        if (isReversed == false)
        {
            int startingIndex = actualPosition(frontIndex);
            for (int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                startingIndex++;
            }
        }
        else if (isReversed == true)
        {
            int startingIndex = actualPosition(frontIndex);
            for (int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                startingIndex--;
            }
        }
        int lowIndex = 0;
        int highIndex = aSize - 1;
        mergeSort(tempArray, lowIndex, highIndex);
        if (isReversed == false)
        {
            for (int i = 0; i < aSize; i++)
            {
                array[actualPosition(i)] = tempArray[actualPosition(i)];
            }
            frontIndex = 0;
            endIndex = actualPosition(aSize - 1);
        }
        else if (isReversed == true)
        {
            int tempCounter = 0;
            for (int i = aSize - 1; i >= 0; i--)
            {
                array[actualPosition(tempCounter)] = tempArray[actualPosition(i)];
                tempCounter++;
            }
            frontIndex = actualPosition(aSize - 1);
            endIndex = 0;
        }
        delete[] tempArray;
    };

    void mergeBack(T tempArray[], int lowIndex, int middleIndex, int highIndex)
    {
        int const leftSubArraySize = middleIndex - lowIndex + 1;
        int const rightSubArraySize = highIndex - middleIndex;

        T *leftSubArray = new T[leftSubArraySize];
        T *rightSubArray = new T[rightSubArraySize];

        for (int i = 0; i < leftSubArraySize; i++)
        {
            leftSubArray[i] = tempArray[lowIndex + i];
        }
        for (int i = 0; i < rightSubArraySize; i++)
        {
            rightSubArray[i] = tempArray[middleIndex + 1 + i];
        }

        int leftSubArrayStartingIndex = 0;
        int rightSubArrayStartingIndex = 0;
        int mergedArrayIndex = lowIndex;

        while ((leftSubArrayStartingIndex < leftSubArraySize) && (rightSubArrayStartingIndex < rightSubArraySize))
        {
            if (leftSubArray[leftSubArrayStartingIndex] <= rightSubArray[rightSubArrayStartingIndex])
            {
                tempArray[mergedArrayIndex] = leftSubArray[leftSubArrayStartingIndex];
                leftSubArrayStartingIndex++;
            }
            else
            {
                tempArray[mergedArrayIndex] = rightSubArray[rightSubArrayStartingIndex];
                rightSubArrayStartingIndex++;
            }
            mergedArrayIndex++;
        }

        while (leftSubArrayStartingIndex < leftSubArraySize)
        {
            tempArray[mergedArrayIndex] = leftSubArray[leftSubArrayStartingIndex];
            leftSubArrayStartingIndex++;
            mergedArrayIndex++;
        }

        while (rightSubArrayStartingIndex < rightSubArraySize)
        {
            tempArray[mergedArrayIndex] = rightSubArray[rightSubArrayStartingIndex];
            rightSubArrayStartingIndex++;
            mergedArrayIndex++;
        }

        delete[] leftSubArray;
        delete[] rightSubArray;
    };

    void mergeSort(T tempArray[], int const lowIndex, int const highIndex)
    {
        if (lowIndex >= highIndex)
        {
            return;
        }

        int middleIndex = lowIndex + (highIndex - lowIndex) / 2;
        mergeSort(tempArray, lowIndex, middleIndex);
        mergeSort(tempArray, middleIndex + 1, highIndex);
        mergeBack(tempArray, lowIndex, middleIndex, highIndex);
    };

    int linearSearch(T e)
    {
        if (isReversed == false)
        {
            int startingIndex = frontIndex;
            for (int i = 0; i < aSize; i++)
            {
                if (array[actualPosition(startingIndex)] == e)
                {
                    return i;
                }
                startingIndex++;
            }
        }
        else if (isReversed == true)
        {
            int startingIndex = frontIndex;
            for (int i = 0; i < aSize; i++)
            {
                if (array[actualPosition(startingIndex)] == e)
                {
                    return i;
                }
                startingIndex--;
            }
        }
        return -1;
    };

    int binSearch(T e)
    {
        T *tempArray = new T[aSize];
        if (isReversed == false)
        {
            int startingIndex = actualPosition(frontIndex);
            for (int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                startingIndex++;
            }
        }
        else if (isReversed == true)
        {
            int startingIndex = actualPosition(frontIndex);
            for (int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                startingIndex--;
            }
        }
        int lowIndex = 0;
        int highIndex = aSize - 1;
        int binSearchIndex = splitSearch(e, tempArray, lowIndex, highIndex);
        delete[] tempArray;
        if (binSearchIndex == -1)
        {
            return -1;
        }
        else
        {
            if (isReversed == false)
            {
                return binSearchIndex;
            }
            else if (isReversed == true)
            {
                return binSearchIndex;
            }
        }
        return binSearchIndex;
    };

    int splitSearch(T e, T tempArray[], int lowIndex, int highIndex)
    {
        while (lowIndex <= highIndex)
        {
            int middleIndex = (lowIndex + highIndex) / 2;
            if (tempArray[middleIndex] == e)
            {
                return middleIndex;
            }
            else if (e > tempArray[middleIndex])
            {
                lowIndex = middleIndex + 1;
            }
            else
            {
                highIndex = middleIndex - 1;
            }
        }
        return -1;
    };

    void reverse()
    {
        if (isReversed == true)
        {
            int tempIndex = frontIndex;
            frontIndex = endIndex;
            endIndex = tempIndex;
            isReversed = false;
        }
        else if (isReversed == false)
        {
            int tempIndex = frontIndex;
            frontIndex = endIndex;
            endIndex = tempIndex;
            isReversed = true;
        };
    };

    T at(int i)
    {
        return array[actualPosition(i)];
    };

    void print()
    {
        if (isReversed == false)
        {
            int currentIndex = frontIndex;
            for (int i = 0; i < aSize; i++)
            {
                cout << array[actualPosition(currentIndex)] << endl;
                currentIndex++;
            }
        }
        else if (isReversed == true)
        {
            int currentIndex = frontIndex;
            for (int i = 0; i < aSize; i++)
            {
                cout << array[actualPosition(currentIndex)] << endl;
                currentIndex--;
            }
        }
    };

    int fIndex()
    {
        return frontIndex;
    }

    int eIndex()
    {
        return endIndex;
    };

    int fIndexActual()
    {
        return actualPosition(frontIndex);
    }

    int eIndexActual()
    {
        return actualPosition(endIndex);
    };

private:
    T *array;
    int aSize;
    int aCapacity;
    bool isReversed;
    int frontIndex;
    int endIndex;
    T returnReferenceValue;

    void reallocate(int capacityNeeded)
    {
        if (isReversed == false)
        {
            T *newArray = new T[capacityNeeded];
            int currentIndex = frontIndex;
            for (int i = 0; i < aSize; i++)
            {
                newArray[i] = array[actualPosition(currentIndex)];
                currentIndex++;
            }
            delete[] array;
            array = newArray;
            aCapacity = capacityNeeded;
            frontIndex = 0;
            endIndex = aSize - 1;
            isReversed = false;
        }
        if (isReversed == true)
        {
            T *newArray = new T[capacityNeeded];
            int currentIndex = endIndex;
            for (int i = 0; i < aSize; i++)
            {
                newArray[i] = array[actualPosition(currentIndex)];
                currentIndex++;
            }
            delete[] array;
            array = newArray;
            aCapacity = capacityNeeded;
            endIndex = 0;
            frontIndex = aSize - 1;
            isReversed = true;
        }
    };

    int actualPosition(int beforeMod)
    {
        if (beforeMod < 0)
        {
            beforeMod = beforeMod + aCapacity;
        }
        int actualPosition = beforeMod % aCapacity;
        return actualPosition;
    };

    int actualPosition(int beforeMod) const
    {
        if (beforeMod < 0)
        {
            beforeMod = beforeMod + aCapacity;
        }
        int actualPosition = beforeMod % aCapacity;
        return actualPosition;
    };
};

#endif