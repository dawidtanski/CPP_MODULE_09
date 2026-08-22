// PSEUDO CODE

//	1) Recursively divide into pairs of numbers, pairs of pairs of numbers, pairs of pairs of pairs of numbers... etc, and sort them by the biggest number, until we can't form any pair anymore. If there is an unpaired odd element, leave it be.
// I will also refer to the units on which we operate on as elements. elements can be numbers, pairs of numbers, pairs of pairs of numbers etc...
// We will refer to the smallest element in each pair as b, and to the biggest as a. Depending on the index of the pair, we will call them b1, a1, b2, a2... bx, ax.

//	2) Create a sequence (also referred to as S or the main chain in Wikipedia and Knuth's book respectively) out of the smallest element of the smallest pair (b1) and the rest of as. If the first step was done correctly, this sequence will be sorted. Create the sequence that consists of the rest of bs (also referred to as the pend), and the odd element if there is any.
//	I will refer to those sequences as the main and the pend from now on.

//	3) Binary insert the elements from the pend into the main, in the order based on Jacobsthal numbers. I will explain later why and how it works. If we can't insert elements into the main using Jacobsthal numbers anymore, we insert them in reverse order, using similar approach to the plain good ol' binary insertion.