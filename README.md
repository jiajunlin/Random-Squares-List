# Random-Squares-List
***Project Description***
Generating a random list of square values and iterating through the list with the use of iterators and List functions.
Implemented using a Singly Linked List.

I created lists L1, L2, L3, and L4, containing zero Square elements. 
Next, inserted 20 Square objects into L1, in a loop, as follows:
  While(L1.size()<=20) {
• Generated a random integers k in the range 1 to 100 with ((rand() % 100)+1 )). 
•	Constructed a Square object x with side value k (change the type of side data member to be int instead of double for the purpose of this project).
•	Checked if the list L3 already contains a Square object of size k. If it does not contain a Square of size k, then I inserted x  into L3 at a random position p where p=0 if L3 is empty; otherwise p is a random number  in the range 0 to  L3.size(), generated with  rand() % (L3.size()+1). (Position 0 is the first element, and position L3.size() is the position after the last element).
•	If(L3.size()==5) { 
      L4.pop_front(); L4.pop_back(); }
•	If(L1.size()==5) { 
o	Copy constructed a new list object L5 with initial value of L1.  
o	Deleted all odd sized Squares (i.e. side value is one of  1, 3, 5, ...,99) from list L5.  

After deleting each odd-sized square, I used the operator--() to access the previous node if it exists, and then printed the size of the square in that node.

o	Printed L5, and Cleared L5.}
•	Printed L1, L2, L3, L4.
} End While Loop
Cleared L1, L2, L3, and L4, and printed them all.
