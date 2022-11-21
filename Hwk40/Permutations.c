//---------------------------------------------------------
// Dr. Art Hanna
// CS2315 Algorithms (Iterative)
// Permutations.c
//---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>

#include ".\Permutations.h"

//------------------------------------------------------
static void ConstructPermutations1(PERMUTATIONS *permutations,const int n,const int algorithm)
//------------------------------------------------------
{
   assert( 1 <= n );

   permutations->algorithm = algorithm;
   permutations->n = n;
   permutations->permutation = (int *) malloc(sizeof(int)*(n+1));
   FindFirstPermutation(permutations);
}

//------------------------------------------------------
static void ConstructPermutations2(PERMUTATIONS *permutations,const int n,const int algorithm)
//------------------------------------------------------
{
   assert( 1 <= n );

   permutations->algorithm = algorithm;
   permutations->n = n;
   permutations->permutation = (int *) malloc(sizeof(int)*(n+1));
   permutations->arrow = (unsigned char *) malloc(sizeof(unsigned char)*(n+1));
   FindFirstPermutation(permutations);
}

//------------------------------------------------------
static void DestructPermutations1(PERMUTATIONS *permutations)
//------------------------------------------------------
{
   free(permutations->permutation);
}

//------------------------------------------------------
static void DestructPermutations2(PERMUTATIONS *permutations)
//------------------------------------------------------
{
   free(permutations->permutation);
   free(permutations->arrow);
}

//------------------------------------------------------
static void FindFirstPermutation1(PERMUTATIONS *permutations)
//------------------------------------------------------
{
   for (int i = 1; i <= permutations->n; i++)
      permutations->permutation[i] = i;
   permutations->atEnd = false;
}

//------------------------------------------------------
static void FindFirstPermutation2(PERMUTATIONS *permutations)
//------------------------------------------------------
{
   for (int i = 1; i <= permutations->n; i++)
   {
      permutations->permutation[i] = i;
      permutations->arrow[i] = 'L';
   }
   permutations->atEnd = false;
}

//------------------------------------------------------
static void FindNextPermutation1(PERMUTATIONS *permutations)
//------------------------------------------------------
{
// based on the LexicographicPermute() algorithm on page 146 of the 3rd edition of Levitin

   int i,j,k,T;
      
// can generate another permutation iff there are two consecutive elements in increasing order
   permutations->atEnd = true;
   i = 1;
   while ( permutations->atEnd && (i <= permutations->n-1) )
   {
      if ( permutations->permutation[i] < permutations->permutation[i+1] )
         permutations->atEnd = false;
      else
         i++;
   }

// generate next permutation
   if ( !permutations->atEnd )
   {
   // let i be the largest index such that a[i] < a[i+1]. Note a[i+1]> a[i+2] > ... > a[n]
      i = permutations->n-1;
      while ( permutations->permutation[i] > permutations->permutation[i+1] ) i--;

   // find the largest index j such that a[i] < a[j]. Note j >= i+1 since a[i] < a[i+1]
      j = permutations->n;
      while ( permutations->permutation[i] > permutations->permutation[j] ) j--;

   // swap a[i] with a[j]. Note a[i+1], a[i+2], ..., a[n] remain in descreasing order
      T = permutations->permutation[i];
      permutations->permutation[i] = permutations->permutation[j];
      permutations->permutation[j] = T;

   // reverse the order of the elements from a[i+1] to a[n], inclusive
      j = i+1; k = permutations->n;
      while ( j < k )
      {
         T = permutations->permutation[j];
         permutations->permutation[j] = permutations->permutation[k];
         permutations->permutation[k] = T;
         j++,k--;
      }
   }
}

//------------------------------------------------------
static bool IsMobile(PERMUTATIONS *permutations,const int i)
//------------------------------------------------------
{
   return( ((permutations->arrow[i] == 'L') 
         && (permutations->permutation[i-1] < permutations->permutation[  i]))
        || ((permutations->arrow[i] == 'R')
         && (permutations->permutation[  i] > permutations->permutation[i+1])) );
}

//------------------------------------------------------
static void FindNextPermutation2(PERMUTATIONS *permutations)
//------------------------------------------------------
{
// based on the JohnsonTrotter() algorithm on page 145 of the 3rd edition of Levitin

   int i,n = permutations->n;

// scan from left-to-right to find first remaining mobile element, permutation[i], if it exists
   permutations->atEnd = true;
   i = ((permutations->arrow[1] == 'R') ? 1 : 2);
   while ( permutations->atEnd && (i <= ((permutations->arrow[n] == 'R') ? (n-1) : n)) )
   {
      if ( IsMobile(permutations,i) )
         permutations->atEnd = false;
      else
         i++;
   }

// find next permutation
   if ( !permutations->atEnd )
   {
   // find the largest mobile element k (i points to the first mobile element)
      int ksIndex = i;

      for(i = i+1; i <= ((permutations->arrow[n] == 'R') ? (n-1) : n); i++)
         if ( IsMobile(permutations,i) 
           && (permutations->permutation[i] > permutations->permutation[ksIndex]) ) ksIndex = i;

   // swap k with the adjacent element k's arrow points to
      if      ( permutations->arrow[ksIndex] == 'L' )
      {
         int  P = permutations->permutation[ksIndex];
         char C = permutations->arrow[ksIndex];
         
         permutations->permutation[ksIndex] = permutations->permutation[ksIndex-1];
         permutations->arrow[ksIndex] = permutations->arrow[ksIndex-1];

         permutations->permutation[ksIndex-1] = P;
         permutations->arrow[ksIndex-1] = C;
         ksIndex = ksIndex-1;
      }
      else // ( permutations->arrow[ksIndex] == 'R' )
      {
         int  P = permutations->permutation[ksIndex];
         char C = permutations->arrow[ksIndex];
         
         permutations->permutation[ksIndex] = permutations->permutation[ksIndex+1];
         permutations->arrow[ksIndex] = permutations->arrow[ksIndex+1];

         permutations->permutation[ksIndex+1] = P;
         permutations->arrow[ksIndex+1] = C;
         ksIndex = ksIndex+1;
      }
   // reverse the direction of all the elements that are greater than k
      for (i = 1; i <= n; i++)
         if ( permutations->permutation[i] > permutations->permutation[ksIndex] )
            permutations->arrow[i] = ((permutations->arrow[i] == 'L') ? 'R' : 'L');
   }
}

//------------------------------------------------------
void ConstructPermutations(PERMUTATIONS *permutations,const int n,const int algorithm)
//------------------------------------------------------
{
   switch ( algorithm )
   {
      case USE_LEXICOGRAPHIC_PERMUTE:
         ConstructPermutations1(permutations,n,algorithm);
         break;
      case USE_JOHNSON_TROTTER:
         ConstructPermutations2(permutations,n,algorithm);
         break;
   }
}

//------------------------------------------------------
void DestructPermutations(PERMUTATIONS *permutations)
//------------------------------------------------------
{
   switch ( permutations->algorithm )
   {
      case USE_LEXICOGRAPHIC_PERMUTE:
         DestructPermutations1(permutations);
         break;
      case USE_JOHNSON_TROTTER:
         DestructPermutations2(permutations);
         break;
   }
}

//------------------------------------------------------
void FindFirstPermutation(PERMUTATIONS *permutations)
//------------------------------------------------------
{
   switch ( permutations->algorithm )
   {
      case USE_LEXICOGRAPHIC_PERMUTE:
         FindFirstPermutation1(permutations);
         break;
      case USE_JOHNSON_TROTTER:
         FindFirstPermutation2(permutations);
         break;
   }
}

//------------------------------------------------------
void FindNextPermutation(PERMUTATIONS *permutations)
//------------------------------------------------------
{
   switch ( permutations->algorithm )
   {
      case USE_LEXICOGRAPHIC_PERMUTE:
         FindNextPermutation1(permutations);
         break;
      case USE_JOHNSON_TROTTER:
         FindNextPermutation2(permutations);
         break;
   }
}

//------------------------------------------------------
int GetPermutationsElement(const PERMUTATIONS *permutations,const int i)
//------------------------------------------------------
{
   assert( (1 <= i) && (i <= permutations->n) );

   return( permutations->permutation[i] );
}

//------------------------------------------------------
void GetPermutation(const PERMUTATIONS *permutations,int permutation[])
//------------------------------------------------------
{
   for (int i = 1; i <= permutations->n; i++)
      permutation[i] = permutations->permutation[i];
}

//------------------------------------------------------
bool AtEndOfPermutations(const PERMUTATIONS *permutations)
//------------------------------------------------------
{
   return( permutations->atEnd );
}
