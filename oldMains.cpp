// For Heap
int main()
{
    Heap<int> T1;
    T1.insert(3);
    // T1.insert(4);
    // T1.insert(5);
    // T1.insert(6);
    // T1.insert(7);
    // T1.insert(8);
    // T1.insert(9);
    // T1.insert(10);
    // T1.insert(11);
    T1.insert(2);
    T1.printKey();
    cout << T1.peekKey() << endl;
    T1.printKey();
    cout << T1.extractMin() << endl;
    T1.printKey();
    cout << T1.extractMin() << endl;
    T1.printKey();
    cout << T1.extractMin() << endl;
    T1.printKey();
    return 0;
}

// For BHeap
int main()
{
    int T1KeyValues[20] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int T1MoreKeyValues[10] = {1, 2, 3, 4, 5, 11, 12, 13, 14, 15};
    int T2MoreKeyValues[11] = {6, 7, 8, 9, 10, 16, 17, 18, 19, 20, 21};
    string T1StringValues[10] = {"the", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "log", "tonight"};

    // BHeap<int> T1(T1MoreKeyValues, 10);

    BHeap<string> T1(T1StringValues, 10);

    // for (int i = 0; i < 1000000; i++)
    // {
    //     T1.insert(i);
    // };

    // cout<<"Printing T1 Before the stuff"<<endl;
    // T1.printKey();

    // BHeap<int> T1;
    // BHeap<int> T2(T2MoreKeyValues, 11);
    // BHeap<int> T2(T1);
    BHeap<string> T2;
    T2 = T1;

    cout << "Printing T1" << endl;
    T1.printKey();

    cout << "Printing T2" << endl;
    T2.printKey();

    // cout << "Done" << endl;
    // T1.printKey();

    // cout << "Done" << endl;
    // T2.printKey();

    // T1.merge(T2);

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
    // for(int i = 0; i < 10000; i++)
    // {
    //     cout<<T1.extractMin()<<endl;
    //     // T1.printKey();
    //     // cout<<endl;
    // }

    // T1.insert(1);
    // T1.insert(2);
    // T1.insert(3);

    // cout << T1.extractMin() << endl;
    // cout << T1.extractMin() << endl;
    // cout << T1.extractMin() << endl;

    // cout << "Done" << endl;
    // T1.printKey();

    // cout << endl;
    //  cout<<T1.peekKey()<<endl;
    //  cout<<T1.peekKey()<<endl;
    return 0;
}