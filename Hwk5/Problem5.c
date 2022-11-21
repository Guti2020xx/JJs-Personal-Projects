//--------------------------------------------------
// Dr. Art Hanna and JJ
// Problem #5
// Problem5.c
//--------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

#include "Random.h"

//--------------------------------------------------
int main()
//--------------------------------------------------
{
   void BuildRandomArray(int A[],const int n);
   void CopyArray(int copyA[],const int A[],const int n);
   void DisplayArraySlice(const char label[],const int A[],const int n,const int L,const int R);
   int NumberOfInversions(const int A[],const int n,bool (*AreInverted)(const int LHS,const int RHS));
   void DoBubbleSort(int A[],const int n,
                     bool (*ShouldSwap)(const int LHS,const int RHS),
                     int *numberCompares,
                     int *numberMoves);
   void DoSelectionSort(int *A,const int n,
                        bool (*ShouldSelect)(const int LHS,const int RHS),
                        int *numberCompares,
                        int *numberMoves);
   void DoInsertionSort(int *A,const int n,
                        bool (*ShouldInsert)(const int LHS,const int RHS),
                        int *numberCompares,
                        int *numberMoves);
   bool Ascending(const int LHS,const int RHS);
   bool Descending(const int LHS,const int RHS);

   int n;

   SetRandomSeed();
   printf("n? ");
   while ( scanf("%d",&n) != EOF )
   {
      int *A     = (int *) malloc(sizeof(int)*n);
      int copyA[n];
      int numberCompares;
      int numberMoves;
//
      BuildRandomArray(A,n);
      DisplayArraySlice("Unsorted",A,n,0,n-1);
      printf("\n# of  ascending-order inversions is %d\n",
         NumberOfInversions(A,n,Ascending));
      printf("# of descending-order inversions is %d\n",
         NumberOfInversions(A,n,Descending));

      CopyArray(copyA,A,n);
      DoBubbleSort(copyA,n,Ascending,&numberCompares,&numberMoves);
      DisplayArraySlice("Bubble Sort (Ascending)",copyA,n,0,n-1);
      printf("\n# of compares is %d\n",numberCompares);
      printf("\n# of moves    is %d\n",numberMoves);
      printf("\n# of  ascending-order inversions is %d\n",
         NumberOfInversions(copyA,n,Ascending));

      CopyArray(copyA,A,n);
      DoBubbleSort(copyA,n,Descending,&numberCompares,&numberMoves);
      DisplayArraySlice("Bubble Sort (Descending)",copyA,n,0,n-1);
      printf("\n# of compares is %d\n",numberCompares);
      printf("\n# of moves    is %d\n",numberMoves);
      printf("\n# of descending-order inversions is %d\n",
         NumberOfInversions(copyA,n,Descending));

      CopyArray(copyA,A,n);
      DoSelectionSort(copyA,n,Ascending,&numberCompares,&numberMoves);
      DisplayArraySlice("Selection Sort (Ascending)",copyA,n,0,n-1);
      printf("\n# of compares is %d\n",numberCompares);
      printf("\n# of moves    is %d\n",numberMoves);
      printf("\n# of  ascending-order inversions is %d\n",
         NumberOfInversions(copyA,n,Ascending));

      CopyArray(copyA,A,n);
      DoSelectionSort(copyA,n,Descending,&numberCompares,&numberMoves);
      DisplayArraySlice("Selection Sort (Descending)",copyA,n,0,n-1);
      printf("\n# of compares is %d\n",numberCompares);
      printf("\n# of moves    is %d\n",numberMoves);
      printf("\n# of descending-order inversions is %d\n",
         NumberOfInversions(copyA,n,Descending));

      CopyArray(copyA,A,n);
      DoInsertionSort(copyA,n,Ascending,&numberCompares,&numberMoves);
      DisplayArraySlice("Insertion Sort (Ascending)",copyA,n,0,n-1);
      printf("\n# of compares is %d\n",numberCompares);
      printf("\n# of moves    is %d\n",numberMoves);
      printf("\n# of  ascending-order inversions is %d\n",
         NumberOfInversions(copyA,n,Ascending));

      CopyArray(copyA,A,n);
      DoInsertionSort(copyA,n,Descending,&numberCompares,&numberMoves);
      DisplayArraySlice("Insertion Sort (Descending)",copyA,n,0,n-1);
      printf("\n# of compares is %d\n",numberCompares);
      printf("\n# of moves    is %d\n",numberMoves);
      printf("\n# of descending-order inversions is %d\n",
         NumberOfInversions(copyA,n,Descending));

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
   int i;

   for (i = 0; i <= n-1; i++)
      A[i] = RandomInt(1,10*n);
}

//--------------------------------------------------
void CopyArray(int copyA[],const int A[],const int n)
//--------------------------------------------------
{
   int i;

// for (int i = 0; i <= n-1; i++)
   i = 0;
TOL1:
   if ( !(i <= n-1) ) goto BOL1;
   copyA[i] = A[i];
   i++;
   goto TOL1;
BOL1:; // Do nothing
}

//--------------------------------------------------
void DisplayArraySlice(const char label[],const int A[],const int n,const int L,const int R)
//--------------------------------------------------
{
	
   for (int i = L; i <= R; i++)
   {
      if(i % 10 == 0)
      {
      	printf("\n %d :", i);
	  }
	  printf(" %d ", A[i]);
   }
}

//--------------------------------------------------
int NumberOfInversions(const int A[],const int n,bool (*AreInverted)(const int LHS,const int RHS))
//--------------------------------------------------
{
   int i,r;

   for (i = 0,r = 0; i <= n-2; i++)
      for (int j = i+1; j <= n-1; j++)
         if ( AreInverted(A[i],A[j]) ) r++;
   return( r );
}

//--------------------------------------------------
bool Ascending(const int LHS,const int RHS)
//--------------------------------------------------
{
   return( (LHS > RHS) ? true : false );
}

//--------------------------------------------------
bool Descending(const int LHS,const int RHS)
//--------------------------------------------------
{
   return( LHS < RHS );
}

//--------------------------------------------------
void DoBubbleSort(int A[],const int n,
                  bool (*ShouldSwap)(const int LHS,const int RHS),
                  int *numberCompares,
                  int *numberMoves)
//--------------------------------------------------
{
   int pass;
   bool swapMade;

   pass = 1;
   *numberCompares = 0;
   *numberMoves = 0;
   
TOL2:
   	    swapMade = false;
   	    int i = 0;
TOL3:
		    if (!(i<=n-(pass+1))) goto BOL3;
        {
            *numberCompares += 1;
            if ( !(ShouldSwap(A[i],A[i+1])) ) goto BOIF;
           {
               int T = A[i]; A[i] = A[i+1]; A[i+1] = T;

              *numberMoves += 3;
              swapMade = true;
           } 
       }
BOIF: 
// in class he added BOL2:
	       i++;
	       goto TOL3;
BOL3:;
       pass++;
BOL2:  if (swapMade) goto TOL2;
}

//--------------------------------------------------
void DoSelectionSort(int *A,const int n,
                     bool (*ShouldSelect)(const int LHS,const int RHS),
                     int *numberCompares,
                     int *numberMoves)
//--------------------------------------------------
{
   *numberCompares = 0;
   *numberMoves = 0;
int i = 0;   
TOL1:
    if(!(i <= n-2)) goto BOL1;
      int T,select = i; int j = i+1;
TOL2: if(!(j <= n-1)) goto BOL2;
        
         if ( !(*ShouldSelect)(A[select],A[j]) ) goto BOIF1;
		 select = j;
         *numberCompares += 1;
BOIF1:
      j++;
BOL2:;
      T = A[i]; A[i] = A[select]; A[select] = T;
      ++*numberMoves, *numberMoves += 1, (*numberMoves)++;
    i++;  
    BOL1:;
}

//--------------------------------------------------
void DoInsertionSort(int A[1],const int n,
                     bool (*ShouldInsert)(const int LHS,const int RHS),
                     int *numberCompares,
                     int *numberMoves)
//--------------------------------------------------
{
   int i=1;
   
   *numberCompares = 0;
   *numberMoves = 0;
TOL:   
   if(!(i <= n-1)) goto BOL;
   {
      int v = A[i];
      int j = i-1;
      
      *numberMoves += 1;
TOL2: 
      if (!( (j >= 0) && (*ShouldInsert)(A[j],v))) goto BOL2;
      {
         *numberCompares += 1;
         A[j+1] = A[j];
         *numberMoves += 1;
         j--;
      }
BOL2:
      *numberCompares += 1;
      A[j+1] = v;
      *numberMoves += 1;
      i++;
   }
BOL:;
}

