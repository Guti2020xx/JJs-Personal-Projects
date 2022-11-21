//---------------------------------------------------------
// Dr. Art Hanna
// CS2315 Algorithms (Iterative)
// Combinations.h
//---------------------------------------------------------
#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include <stdbool.h>

//==============================================================
// Data model definitions
//==============================================================
typedef struct COMBINATIONS
{
   int n;
   int k;

// combination[i], i in [ 1,n ]
   bool *combination;
   bool atEnd;
} COMBINATIONS;

//==============================================================
// Public member function prototypes
//==============================================================
void ConstructCombinations(COMBINATIONS *combinations,const int n,const int k);
void DestructCombinations(COMBINATIONS *combinations);
void FindFirstCombination(COMBINATIONS *combinations);
void FindNextCombination(COMBINATIONS *combinations);
bool GetCombinationsElement(const COMBINATIONS *combinations,const int i);
void GetCombination(const COMBINATIONS *combinations,int combination[]);
bool AtEndOfCombinations(const COMBINATIONS *combinations);

//==============================================================
// Private utility member function prototypes
//==============================================================
//static void Step(COMBINATIONS *combinations);
//static int CountTs(const COMBINATIONS *combinations);

#endif
