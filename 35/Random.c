//-----------------------------------------------------
// Dr. Art Hanna
// Function definition file for random-related pseudo-library
// Random.c
//-----------------------------------------------------

#include ".\Random.h"

//-----------------------------------------------------
void SetRandomSeed(void)
//-----------------------------------------------------
{
   srand( (unsigned int) time(NULL) );
}

//-----------------------------------------------------
int RandomInt(const int LB,const int UB)
//-----------------------------------------------------
{
   return( (int) ((UB-LB+1)*RandomDouble()) + LB );
}

//--------------------------------------------------
double RandomDouble()
//--------------------------------------------------
{
   int R;

   do
      R = rand();
   while ( R == RAND_MAX );
   return( (double) R/RAND_MAX );
}

//-----------------------------------------------------
bool RandomBool(const double bias)
//-----------------------------------------------------
{
// Return true (0.0 <= bias <= 1.0)*100 percent of the time
   return( ((double) RandomInt(1,1000000)/1000000) <= bias );
}

//-----------------------------------------------------
char RandomChar(const char chars[],const int size)
//-----------------------------------------------------
{
   return( chars[RandomInt(0,(size-1))] );
}
