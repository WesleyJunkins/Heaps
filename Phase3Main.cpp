#include <iostream>
using namespace std;
#include "Heap.cpp"
#include "BHeap.cpp"


int main(){
	string A[10] = {"A","B","C","D","E","F","H","I","J","K"};
	int B[10] = {10,9,8,7,6,5,4,3,2,1};
	
	Heap<int> T1, T2(B,10);
	
	T2.printKey();
	//Should output  1 2 4 3 6 5 8 10 7 9
	
	for(int i=0; i<10; i++) T1.insert(B[i]);
	
	T1.printKey();
	// Should output 1 2 5 4 3 9 6 10 7 8
	
	cout << T2.peekKey() << endl;
	//Should output 1
	
	cout << T1.extractMin() << endl;
	//Should output 1
	
	T1.printKey();
	//Should output 2 3 5 4 8 9 6 10 7
	
	
	BHeap<string> X(A,10), Y, Z;

	X.printKey();
	//Should output 
	//B1
	//J K
	//
	//B3
	//A E H I F C D B

	cout << X.extractMin() << endl;
	//Should output A
	
	X.printKey();
	//Should output
	//B0
	//B
	//
	//B3
	//C E H I F J K D

	cout<<"Here is COPY= --------------------"<<endl;
	Z.insert("Z");
	Z = X;
	Z.printKey();
	cout<<"End COPY= --------------------"<<endl;

	cout<<"Here is COPY= --------------------"<<endl;
	Z.insert("Z");
	BHeap<string> W(X);
	W.printKey();
	cout<<"End COPY= --------------------"<<endl;
	
	Y.insert("M"); 
	Y.insert("O");
	Y.insert("G");
	Y.insert("N");
	Y.insert("L");
	
	Y.printKey();
	//Should output
	//B0
	//L
	//
	//B2
	//G M O N
	
	Y.merge(X);
	cout << Y.peekKey() << endl;
	//Should output B
	
	Y.printKey();
	//Should output
	//B1
	//B L
	//
	//B2
	//G M O N
	//
	//B3
	//C E H I F J K D
			

	// BHeap<int> T1;
	// T1.insert(6);
	// T1.insert(2);
	// T1.insert(10);
	// T1.insert(7);
	// T1.insert(5);
	// T1.insert(1);
	// T1.insert(11);
	// T1.insert(9);
	// T1.insert(3);
	// T1.insert(4);
	// T1.insert(8);

	// T1.printKey();

	// cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// T1.printKey();

	// cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// T1.printKey();

	// cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// T1.printKey();

	// 	cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// 		cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// 			cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// 				cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// 					cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// 						cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// 							cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// 								cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// 									cout<<"Extract Min: "<<T1.extractMin()<<endl;
	// 										cout<<"Extract Min: "<<T1.extractMin()<<endl;
	return 0;
}