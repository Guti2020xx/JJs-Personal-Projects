//--------------------------------------------------
// Dr. Art Hanna and JJ
// Problem #24
// Problem24.c
//--------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SHOWCLIMB

//#define LARGEST_STEPSIZE 2

const int LARGEST_STEPSIZE = 2;

//--------------------------------------------------
int main()
//--------------------------------------------------
{
   void ClimbNStairs(int climb[],int steps,const int n,int *ways);

   int n;

   printf("n? ");
   while ( scanf("%d",&n) != EOF )
   {
      int *climb = (int *) malloc(sizeof(int)*(n+1));
      int ways;

      ways = 0;
      ClimbNStairs(climb,0,n,&ways);

#ifndef SHOWCLIMB
      printf("%10d ways\n",ways);
#endif

      free(climb);
      printf("n? ");
   }
   
   system("PAUSE");
   return( 0 );
}
//--------------------------------------------------
void ClimbNStairs(int climb[],int steps,const int n,int *ways)
//--------------------------------------------------
{
   int LengthOfClimb(const int climb[],const int steps);
   void ShowClimb(const int climb[],const int steps,const int ways);

   if ( LengthOfClimb(climb,steps) == n )
   {
      (*ways)++;

#ifdef SHOWCLIMB
      ShowClimb(climb,steps,*ways);
#endif

   }
   else 
   {
      int stepSize;
      
      for (int stepSize = 1; stepSize <= LARGEST_STEPSIZE; stepSize++)
      {
  			 if ( LengthOfClimb(climb,steps)+stepSize <= n )
      		{
               climb[++steps] = stepSize; // adds a stepSize step to Climb
               // recursive call if the length of climb is less than or equal to max allowed
               if(LengthOfClimb)
               {
               	  ClimbNStairs(climb,steps, n, ways); // recursive call sandwiched inbetween
			   }
			   steps--; // to reduce the number of steps
     		}
      }
      /*
      Student provides missing code to consider trying (by adding-then-deleting) a 1-stair step to climb[],
         then trying a 2-stair step to climb[],..., finally, trying a LARGEST_STEPSIZE-stair step to 
         climb[]. You must "sandwich" a recursive call between each adding-then-deleting. Note Consider the
         state-space tree that describes the solution space for this problem and notice that it is only
         possible to make a stepSize-stair step when (LengthOfClimb(climb,steps)+stepSize <= n).

      Hints To add a stepSize-stair step to climb[], use

            climb[++steps] = stepSize;

         to delete the last step taken, use

            steps--;

         Ask Dr. Hanna to draw a picture that portrays the relationship between climb[], steps, and
         the current value of stepSize.
         */
   }
}

//--------------------------------------------------
int LengthOfClimb(const int climb[],const int steps)
//--------------------------------------------------
{

   //Student provides missing code to compute the quantification
   int n=0; int i;
   
   for(i=1;i<=steps;i++)
   {
   	  n += climb[i];
   } 

   return n;
}


//--------------------------------------------------
void ShowClimb(const int climb[],const int steps,const int ways)
//--------------------------------------------------
{
	
	
	// prints info in the required format ways (climb taken): steps
	
	printf("%d (%d)", ways, steps); // prints out ways of climbing tree and how many times it was climbed
	
	for(int i = 1; i<=steps; i++) // ignoring element 0
	{
		printf("%d", climb[i]);
	}
	printf("\n"); // new line
	
/*
   Student provides missing code to display the climb[] using the required format
    
            1         2         3
   123456789012345678901234567890
   WWWWW (XXX): SSS...SSS

   where WWWWW is the value of the formal parameter ways, 
         XXX is the value of the formal parameter steps, and 
         SSS...SSS are the step-sizes of each individual step taken recorded in the formal parameter climb[]
*/

}
