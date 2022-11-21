//-------------------------------------------------------------
// Dr. Art Hanna & JJ
// Problem #48
// Problem48.c
//-------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>

#include "Combinations.h"

//-------------------------------------------------------------
int main()
//-------------------------------------------------------------
{
   bool IsPrime(const int x);

   int LB,UB, sum = 0;

   printf("LB? ");
   while ( scanf("%d",&LB) != EOF )
   {
      int n;
      int count;

      printf("UB? "); scanf("%d",&UB);
      n = (int) (sqrt(UB)+0.5);
      count = 0;
   
      for (int x = LB; x <= UB; x++)
      {
        // bool isExpressable = false;
        // bool isExpression1 = true;
        int expressionsOfX = 0;

         for (int k = 1; k <= n; k++)
         {
            COMBINATIONS C;
            int combination[k+1];
            
            ConstructCombinations(&C,n,k);
            FindFirstCombination(&C);
            
            do
            {
            	sum = 0;
               	GetCombination( &C, combination);
               	for (int i = 1; i<=k; i++)
               	{
               	sum = sum+combination[i]*combination[i];
                }

				if (sum == x)
				{
					expressionsOfX++;
					printf("%7d = ", x );
					bool firstTerm = true; // boundary case for first element for outputting purposes
					for(int i = 1; i <= n; i++)
					{
						if (GetCombinationsElement(&C, i))
						{
							printf(" %s%d^2", (firstTerm) ? "" : " + ", i);
							firstTerm = false;
						}
						
						
//						printf("\n");
					}
					if( expressionsOfX == 1 )
						{
							if(IsPrime(x))
							{
								printf(" (prime)");
							}
						}
					printf("\n");
				}
               FindNextCombination(&C);
            } while ( !AtEndOfCombinations(&C) );
            DestructCombinations(&C);
         }
         if ( expressionsOfX == 0 )
         {
            count++;
            printf("***%2d: %7d",count,x);
            if ( IsPrime(x) )
               printf(" (prime)");
            printf("\n");
         }
      }
      printf("\nLB? ");
   }

   system("PAUSE");
   return( 0 );
}

//-------------------------------------------------------------
bool IsPrime(const int x)
//-------------------------------------------------------------
{
   bool r;

   if ( x == 1 )
      r = false;
   else
   {
      r = true;
      for (int i = 2; i <= (int) (sqrt(x)+0.5); i++)
         r = r && (x%i != 0);
   }
   return( r );
}

