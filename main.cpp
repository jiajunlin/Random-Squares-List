#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include <cstdlib>   // for rand(), srand()
#include <ctime>     // for time()
#include <assert.h>
#include <math.h>    // for math functions like sqrt() etc
#include "List.h"
#include "Square.h"


int main()
{
	List<Square> L1;		//first step 
	List<Square> L2;
	List<Square> L3;
	List<Square> L4;		//creating lists L1, L2, L3, and L4, containing zero Square elements. 
	srand((unsigned int)time(NULL));	// seed rand() with system time

	cout << "L1 Size: " << L1.size() << endl;
	cout << "L2 Size: " << L2.size() << endl;
	cout << "L3 Size: " << L3.size() << endl;
	cout << "L4 Size: " << L4.size() << endl;
	cout << "\n\n"; 
	while (L1.size() < 20)	//insert 20 Square objects into L1 in a loop which is the while loop
	{
		//generate random integers k
		int k = (rand() % 100) + 1; // limit data to 0 to 99.
		Square x(k);				//construct square object x with side k which is an int
		L1.push_front(x);			//inserting square objects x into L1
		L2.push_back(x);			//inserting x into L2 in the opposite order

		bool flag = false;			
		for (auto it = L3.begin(); it != L3.end(); ++it)
		{
			if ((*it).getSide() == k)	//to check if L3 already contains square object k
			{
				flag = true;
				break;
			}
		}

		if (!flag)	//if it doesnt, we insert x into L3 into random positions 
		{
			int position = (L3.empty()) ? 0 : (rand() % (L3.size() + 1)); 
			auto it = L3.begin(); 
			while (position-- > 0)
			{
				it++; 
			}
			L3.insert(it, x); 
			//printing the Lists to check if it inserts
			cout << "L1" << endl;
			for (auto& x : L1) {
				x.print(cout);
				cout << ", "; 
			}
			cout << endl; 
			cout << "L2: " << endl;
			for (auto& x : L2) {
				x.print(cout);
				cout << ", ";
			}
			cout << endl;
			cout << "L3: " << endl;
			for (auto& x : L3) {
				x.print(cout);
				cout << ", ";
			}
			cout << endl;
			cout << "L4: " << endl;
			for (auto& x : L4) {
				x.print(cout);
				cout << ", ";
			}
			cout << endl << endl; 
		}

		if (L3.size() == 5)
		{
			cout << "Adding to L4..." << endl; 
			L4.clear();
			List<Square>::iterator iterator = L3.begin();
			//here, i didn't do L4 = L3. Instead i iteratively pushed back L3 into L4. 
			for (auto it = L3.begin(); it != L3.end(); it++)
			{
				L4.push_back(*it); 
			}
			L4.pop_front();
			L4.pop_back();
		}
		

		if (L1.size() == 5)
		{
			cout << "Creating L5..." << endl; 
			List<Square> L5(L1);				//copy construct a new list L5 with initial value of L1
			auto it = L5.begin(); 
			//it begins and while loops it to the end of L5
			while (it != L5.end())
			{
				if (((*it).getSide() % 2) == 1)
				{
					//deletion of all odd sized squares
					cout << "Deleting Odd sized square with side: " << (*it).getSide() << endl;

					if (it == L5.begin())
					{
						cout << "Size of square in the Previous Node: N/A. Deleted odd square at head." << endl << endl;
					}
					else 
					{
						auto previousIt = it--;			//using the operator--() to access the previous node
						cout << "Size of square in the Previous Node: " << (*previousIt).getSide() << endl << endl;
					}
					it = L5.erase(it);	//we are erasing the odd sized squares
				}
				else
				{
				 it++;					//continue iterating
				}
			}
			//print L5 to see values
			cout << "L5: " << endl;
			for (auto& x : L5) {
				x.print(cout);
				cout << ", ";
			}
			cout << endl << endl;
			//clearing L5
			cout << "Clearing L5..." << endl; 
			L5.clear(); 
			//for L5 aftering clearing
			cout << "L5: " << endl;
			for (auto& x : L5) {
				x.print(cout);
				cout << ", ";
			}
			cout << endl << endl;
		}
	}	//end of while loop

	//checking the sizes of the lists 
	cout << "\n\n----------------------------------------------------" << endl;
	cout << "L1 Size: " << L1.size() << endl;
	cout << "L2 Size: " << L2.size() << endl;
	cout << "L3 Size: " << L3.size() << endl;
	cout << "L4 Size: " << L4.size() << endl;
	cout << "----------------------------------------------------\n\n\n\n" << endl;

	// Print L1, L2, L3, L4
	cout << "L1" << endl;
	for (auto& x : L1) {
		x.print(cout);
		cout << ", ";
	}
	cout << endl;
	cout << "L2: " << endl;
	for (auto& x : L2) {
		x.print(cout);
		cout << ", ";
	}
	cout << endl;
	cout << "L3: " << endl;
	for (auto& x : L3) {
		x.print(cout);
		cout << ", ";
	}
	cout << endl;
	cout << "L4: " << endl;
	for (auto& x : L4) {
		x.print(cout);
		cout << ", ";
	}
	cout << endl << endl;

	//finishes printing and next is clearing
	char c;
	cout << "Enter any char to clear lists : ";
	cin >> c;
	cout << endl; 

	//clearing  the Lists
	cout << "Clearing L1..." << endl; 
	L1.clear(); 
	cout << "Clearing L2..." << endl;
	L2.clear(); 
	cout << "Clearing L3..." << endl;
	L3.clear(); 
	cout << "Clearing L4..." << endl;
	L4.clear(); 

	// RePrint L1, L2, L3, L4 after clearing
	cout << "L1" << endl;
	for (auto& x : L1) {
		x.print(cout);
		cout << ", ";
	}
	cout << endl;
	cout << "L2: " << endl;
	for (auto& x : L2) {
		x.print(cout);
		cout << ", ";
	}
	cout << endl;
	cout << "L3: " << endl;
	for (auto& x : L3) {
		x.print(cout);
		cout << ", ";
	}
	cout << endl;
	cout << "L4: " << endl;
	for (auto& x : L4) {
		x.print(cout);
		cout << ", ";
	}
	cout << endl << endl;
	cout << "\n";


	return 0;
}
