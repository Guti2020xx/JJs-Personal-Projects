//---------------------------------------------------------
// Dr. Art Hanna and JJ
// Problem #40
// Problem40.c
//---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Permutations.h" 

//---------------------------------------------------------
int main()
//---------------------------------------------------------
{
   bool IsSolution(const int P[]);
   void DisplaySolution(const int P[]);

   PERMUTATIONS object;
   int countPermutations = 0, countSolutions = 0;
   int P[11]; // as it is better in terms of space / memory usage

   ConstructPermutations(&object,10,USE_LEXICOGRAPHIC_PERMUTE); // or USE_JOHNSON_TROTTER (your choice)
   FindFirstPermutation(&object);
   countPermutations++;
    
	do{
		for (int i = 1; i <= 10; i++)
		{
		    P[i] = GetPermutationsElement(&object,i) % 10; 	
		}
		
		if(IsSolution(P))
		{
			countSolutions++;
			DisplaySolution(P);
		}
		
	    FindNextPermutation(&object);
	    countPermutations++;
	} while(!AtEndOfPermutations(&object));

   printf("%10d permutations checked, %10d solutions found (%9.5f%%)\n",
      countPermutations,countSolutions,
      100*((double) countSolutions/countPermutations));
   DestructPermutations(&object);

   free(P);
   system("PAUSE");
   return( 0 );
}

//---------------------------------------------------------
bool IsSolution(const int P[])
//---------------------------------------------------------
{
	// could I also do this with toString()?
	bool result;
	
	int R1 = P[7]*1000 + 5*100 + P[3]*10 + P[1];  // first row calculated through using decimal number system
	int R2 = P[8]*1000 + P[6]*100 + P[4]*10 + 5; // second row
	int R3 = P[10]*10000 + P[9]*1000 + 600 + P[5]*10 + P[2]; // third row
  
    result = ((R1 + R2) == R3) ? true : false;
    return result; 
}

//---------------------------------------------------------
void DisplaySolution(const int P[])
//---------------------------------------------------------
{
// Assumes mapping of P[1:10] detailed in IsSolution() prolog comment
   printf("%d%d%d%d",          P[7],   5,P[3],P[1]);
   printf(" + %d%d%d%d",       P[8],P[6],P[4],   5);
   printf(" = ");
   printf("%d%d%d%d%d\n",P[10],P[9],   6,P[5],P[2]);
}

