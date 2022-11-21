//---------------------------------------------------------
// Dr. Art Hanna
// CS2315 Algorithms (Iterative)
// Combinations.c
//---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>

#include ".\Combinations.h"

//------------------------------------------------------
static void Step(COMBINATIONS *combinations)
//------------------------------------------------------
{
   bool carryIn,carryOut;

/*
carryIn combination[i] carryOut combination[i]
      F              F        F              F
      F              T        F              T
      T              F        F              T
      T              T        T              F
*/

   carryIn = true;
   for (int i = 1; i <= combinations->n; i++)
   {
      carryOut = carryIn && combinations->combination[i];
      combinations->combination[i] = (!carryIn && combinations->combination[i])
                                  || (carryIn && !combinations->combination[i]);
      carryIn = carryOut;
   }
   combinations->atEnd = carryOut;
}

//------------------------------------------------------
static int CountTs(const COMBINATIONS *combinations)
//------------------------------------------------------
{
   int r = 0;

   for (int i = 1; i <= combinations->n; i++)
      if ( combinations->combination[i] ) r++;
   return( r ); 
}

//------------------------------------------------------
void ConstructCombinations(COMBINATIONS *combinations,const int n,const int k)
//------------------------------------------------------
{
   assert( (1 <= n) && ((0 <= k) && (k <= n)) );
   
   combinations->n = n;
   combinations->k = k;
   combinations->combination = (bool *) malloc(sizeof(bool)*(n+1));
   FindFirstCombination(combinations);
}

//------------------------------------------------------
void DestructCombinations(COMBINATIONS *combinations)
//------------------------------------------------------
{
   free(combinations->combination);
}

//------------------------------------------------------
void FindFirstCombination(COMBINATIONS *combinations)
//------------------------------------------------------
{
   for (int i = 1; i <= combinations->n; i++)
      combinations->combination[i] = false;
   while ( CountTs(combinations) != combinations->k )
      Step(combinations);
   combinations->atEnd = false;
}
//------------------------------------------------------
void FindNextCombination(COMBINATIONS *combinations)
//------------------------------------------------------
{
   do
      Step(combinations);
   while ( (!combinations->atEnd) && (CountTs(combinations) != combinations->k) );
}

//------------------------------------------------------
bool GetCombinationsElement(const COMBINATIONS *combinations,const int i)
//------------------------------------------------------
{
   assert( (1 <= i) && (i <= combinations->n) );
   
   return( combinations->combination[i] );
}

//------------------------------------------------------
void GetCombination(const COMBINATIONS *combinations,int combination[])
//------------------------------------------------------
{
   for (int i = 1,j = 0; i <= combinations->n; i++)
      if ( combinations->combination[i] ) combination[++j] = i;
}

//------------------------------------------------------
bool AtEndOfCombinations(const COMBINATIONS *combinations)
//------------------------------------------------------
{
   return( combinations->atEnd );
}
