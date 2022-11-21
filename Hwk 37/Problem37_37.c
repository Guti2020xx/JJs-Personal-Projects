//--------------------------------------------------
// Dr. Art Hanna
// Problem #37
// Problem37.c
//--------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>

#include "Random.h"

#define DISPLAYARRAY

//--------------------------------------------------
int main()
//--------------------------------------------------
{
   void BuildRandomArray(int A[],const int n);
   int NumberOfInversions(const int A[],const int n);
   int MaximumInversions(const int n);
   void DisplayArraySlice(const char label[],const int A[],const int n,const int L,const int R);
   void DoComparisonCountingSort(int A[],const int n,int *numberCompares);

   int n;

   SetRandomSeed();
   printf("n? "); 
   while ( scanf("%d",&n) != EOF )
   {
      int *A = (int *) malloc(sizeof(int)*n);
      int numberCompares;

      BuildRandomArray(A,n);

#ifdef DISPLAYARRAY
      DisplayArraySlice("UNSORTED",A,n,0,n-1);
#endif

      printf("# of inversions before sort is %10d (%.1f%% of %d)\n",
         NumberOfInversions(A,n),
         100*((double) NumberOfInversions(A,n)/MaximumInversions(n)),
         MaximumInversions(n));
      DoComparisonCountingSort(A,n,&numberCompares);
      printf("# of   compares during sort is %10d\n",numberCompares);

#ifdef DISPLAYARRAY
      DisplayArraySlice("  SORTED",A,n,0,n-1);
#endif

      printf("# of inversions  after sort is %10d\n",NumberOfInversions(A,n));

      free(A);
      printf("\nn? ");
   }
   
   system("PAUSE");
   return( 0 );
}

//--------------------------------------------------
void BuildRandomArray(int A[],const int n)
//--------------------------------------------------
{
   for (int i = 0; i <= n-1; i++) A[i] = RandomInt(1,10*n);
}

//--------------------------------------------------
void DisplayArraySlice(const char label[],const int A[],const int n,const int L,const int R)
//--------------------------------------------------
{
   const int WIDTH = (int) ceil(log10(10*n));
   char formatString[4+1];

   sprintf(formatString,"%%%dc",WIDTH);

   printf("%s",label);
   if ( !(L <= R) )
      printf(" (empty)\n");
   else
   {
      for (int i = 0; i <= n-1; i++)
         if ( (L <= i) && (i <= R) )
            printf("%*d",WIDTH+1,A[i]);
         else
            printf(formatString,' ');
      printf("\n");
   }
}

//--------------------------------------------------
int MaximumInversions(const int n)
//--------------------------------------------------
{

  		return (n * (n-1) / 2);

}

//--------------------------------------------------
int NumberOfInversions(const int A[],const int n)
//--------------------------------------------------
{
   int i,r;

  for(i = 0; i <= n - 2;  i++)
  {
  	for(int j = i+1; j <= n - 1; j++)
  	{
  		if(A[i] > A[j])
  		{
  			r++;
		}
	}
  }
  return(r);

} 

//--------------------------------------------------
void DoComparisonCountingSort(int A[],const int n,int *numberCompares)
//--------------------------------------------------
{
   int *count = (int *) malloc(sizeof(int)*n);
// int *S = (int *) malloc(sizeof(int)*n);
   int S[n];

   *numberCompares = 0;

   for(int i = 0; i <= n-1; i ++)
   {
   	  count[i] = 0;
   }
   
   for(int i = 0; i <= n-2; i++)
   {
   	  for(int j = i+1; j<= n - 1; j++)
   	  {
   	  	if(A[i] < A[j])
   	  	{
   	  		count[j] = count[i] + 1;	
		}
		else
		{
			count[i] = count[j] + 1;
		}
	  }
   }
   
   for(int i = 0; i <= n-1; i++)
   {
   	   S[count[i]] = A[i];
   }
   
/*
   Student provides missing code to implement a slightly modified version of the 
      ComparisonCountingSort algorithm found in Exercises 1.3 Problem #1 on page 23 of our textbook.
      The slight modification concerns the method used to return the array A[] after it is
      sorted-into the locally-defined array S[]. The textbook's algorithm treats A[] as an IN formal
      parameter and "returns" S[]; instead, the void-returing DoComparisionCountingSort() copies S[]
      back-into A[] (over-writing the unsorted contents with the now-sorted contents) before returning,
      thereby treating the formal parameter A[] as an IO parameter. Obviously, you will not find the
      pseudo-code for the copy-S[]-back-into-A[] modification in the textbook algorithm, so here it is!

      FOR i := 0 TO n-1
         A[i] := S[i]
      END
*/
   free(count);
// free(S);
}
