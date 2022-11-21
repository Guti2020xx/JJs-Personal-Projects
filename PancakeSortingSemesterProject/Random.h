//--------------------------------------------------
// Dr. Art Hanna
// Header file for random-related pseudo-library
// Random.h
//--------------------------------------------------
#ifndef RANDOM_H
#define RANDOM_H

#ifndef  __cplusplus
   #include <stdlib.h>
   #include <time.h>
   #include <stdbool.h>
#else
   #include <cstdlib>
   #include <ctime>
#endif

// Initialize the "seed" used by the <stdlib.h> "rand()" function.
void SetRandomSeed(void);

// Return a uniformly and randomly-chosen integer from [ LB,UB ].
int RandomInt(const int LB,const int UB);

// Return a uniformly and randomly-chosen real number from [ 0.0,1.0 ).
double RandomDouble(void);

// Return a biased and randomly-chosen bool from { false,true }.
bool RandomBool(const double bias);

// Return a uniformly and randomly-chosen character from chars[i], i in [ 0,(size-1) ].
char RandomChar(const char chars[],const int size);

#endif
