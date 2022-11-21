//------------------------------------------------------------
// Dr. JJ
// Problem #33
// Problem33.c
//------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>
#include <assert.h>

#define USE_INSTRUMENTATION

int numberOfMoves;

//------------------------------------------------------------
typedef struct PEG // struct for every disk and size of it
//------------------------------------------------------------
{
   int size;
   int *disks;
} PEG;

//------------------------------------------------------------
int main()
//------------------------------------------------------------
{
   void RunOneTrial(const int n,PEG pegs[]); 

   int LB,UB;
   PEG pegs[3+1];

   printf("LB? "); scanf("%d",&LB);
   printf("UB? "); scanf("%d",&UB);
   for (int n = LB; n <= UB; n++)
   {
   // Allocate peg disk space for n disks (ignore pegs[x].disks[0], x in [ 1,3 ])
      pegs[1].disks = (int *) malloc(sizeof(int)*(n+1));
      pegs[2].disks = (int *) malloc(sizeof(int)*(n+1));
      pegs[3].disks = (int *) malloc(sizeof(int)*(n+1));

#ifdef USE_INSTRUMENTATION
      clock_t startClock,nowClock;
      int repetitions = 0;

      startClock = clock();
      do
      {
         RunOneTrial(n,pegs); nowClock = clock();
         repetitions++;
      }
      while ( ((double) (nowClock-startClock)/CLOCKS_PER_SEC) < 2.0 );
      printf("%2d disks took %10d moves (%9.3f microseconds, %10d repetitions)\n",
         n,numberOfMoves,
         1E6*((double) (nowClock-startClock)/CLOCKS_PER_SEC)/repetitions,
         repetitions);
#else
      printf("%5d disks\n===========\n",n);
      RunOneTrial(n,pegs);
#endif

   // Deallocate peg disk space
      free(pegs[1].disks);
      free(pegs[2].disks);
      free(pegs[3].disks);
   }
   
   system("PAUSE");
   return( 0 );
}

//------------------------------------------------------------
void RunOneTrial(const int n,PEG pegs[])
//------------------------------------------------------------
{
   void DoTowersOfHanoi(const int n,const int F,const int T,const int H,PEG pegs[]);
/*
   Initialize pegs[1] state so that pegs[1].disks[1] is the bottom disk (the
      largest disk) and pegs[1].disks[n] is the top disk (the smallest disk).
      *Note* In general, pegs[x].disks[pegs[x].size] is the top disk stored 
      in pegs[x].
*/
   pegs[1].size = n;
   for (int i = 1; i <= n; i++)
      pegs[1].disks[i] = n-i+1;
   pegs[2].size = 0;
   pegs[3].size = 0;
   
   numberOfMoves = 0;
   DoTowersOfHanoi(n,1,3,2,pegs);
}

//------------------------------------------------------------
void DoTowersOfHanoi(const int n,const int F,const int T, const int H,PEG pegs[])
//------------------------------------------------------------
{
   if ( n > 0 )
   {
   	
    	 DoTowersOfHanoi(n-1, F, T, H, pegs);
   	
    /*  Student provides the single missing statement that makes a recursive call to move (n-1) 
         disks from peg F to peg H while using peg T as a temporary holding spot (the auxiliary).
    */
      if ( pegs[T].size > 0 ) assert( pegs[F].disks[pegs[F].size] < pegs[T].disks[pegs[T].size] );

#if defined( USE_INSTRUMENTATION )
      numberOfMoves++;
#else
      printf("%2d from %d -> %d\n",pegs[F].disks[pegs[F].size],F,T);
#endif

      pegs[T].disks[++pegs[T].size] = pegs[F].disks[pegs[F].size--];

       DoTowersOfHanoi(n-1, H, F, T, pegs);
    /*  Student provides the single missing statement that makes a recursive call to move (n-1) 
         disks from peg H to peg T while using peg F as a temporary holding spot (the auxiliary).
    */
   }
}

