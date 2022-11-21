//---------------------------------------------------------
// Dr. Art Hanna
// CS2315 Algorithms (iterative)
// Permutations.h
//---------------------------------------------------------
#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <stdbool.h>

//==============================================================
// Data model definitions
//==============================================================
#define USE_LEXICOGRAPHIC_PERMUTE  1
#define USE_JOHNSON_TROTTER        2

typedef struct PERMUTATIONS
{
// common data members for all permutation-generating algorithms
   int algorithm;
   int n;
// permutation[i], i in [ 1,n ]
   int *permutation;
   bool atEnd;
// for USE_JOHNSON_TROTTER only
   unsigned char *arrow;
} PERMUTATIONS;

//==============================================================
// Public member function prototypes
//==============================================================
void ConstructPermutations(PERMUTATIONS *permutations,const int n,const int algorithm);
void DestructPermutations(PERMUTATIONS *permutations);
void FindFirstPermutation(PERMUTATIONS *permutations);
void FindNextPermutation(PERMUTATIONS *permutations);
int GetPermutationsElement(const PERMUTATIONS *permutations,const int i);
void GetPermutation(const PERMUTATIONS *permutations,int permutation[]);
bool AtEndOfPermutations(const PERMUTATIONS *permutations);

//==============================================================
// Private utility member function prototypes
//==============================================================
//static void ConstructPermutations1(PERMUTATIONS *permutations,const int n,const int algorithm);
//static void ConstructPermutations2(PERMUTATIONS *permutations,const int n,const int algorithm);
//static void DestructPermutations1(PERMUTATIONS *permutations);
//static void DestructPermutations2(PERMUTATIONS *permutations);
//static void FindFirstPermutation1(PERMUTATIONS *permutations);
//static void FindFirstPermutation2(PERMUTATIONS *permutations);
//static void FindNextPermutation1(PERMUTATIONS *permutations);
//static bool IsMobile(PERMUTATIONS *permutations,const int i);
//static void FindNextPermutation2(PERMUTATIONS *permutations);

#endif
