//---------------------------------------------------
// Dr. Art Hannah and JJ
// Problem #34
// Problem34.c
//---------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#define TRACESTACK

#define   F0 0
const int F1 = 1;

int *calls;

//---------------------------------------------------
int main()
//---------------------------------------------------
{
   int F(const int n,const bool calledFromMain);
   void UnusedFunction1(void);
   void UnusedFunction2();

   int n;

   fprintf(stdout,"\nn? ");
   while ( fscanf(stdin,"%d",&n) != EOF )
   {
      int i,Fn,**totalCalls;

      calls = (int *) malloc(sizeof(int)*(n+1));
      totalCalls = (int **) malloc(sizeof(int *));
      *totalCalls = (int *) malloc(sizeof(int));

      printf(" 1) stdout           = %p, %8p\n",stdout,stdout);
      printf(" 2) stdin            = 0X%08X\n",&*stdin);
      printf(" 3) sizeof(FILE)     = 0X%04X = %2d\n",sizeof(FILE),sizeof(FILE));
      printf(" 4) &main()          = 0X%08X\n",main);
      printf(" 5) &F()             = 0X%08X\n",F);
      printf(" 6) &UnusedFunction1 = 0X%08X\n",UnusedFunction1);
      printf(" 7) &UnusedFunction2 = 0X%08X\n",UnusedFunction2);
      printf(" 8) &F1              = 0X%08X\n",&F1);
      printf(" 9) &calls           = 0X%08X\n",&calls);
      printf("10) &n               = 0X%08X\n",&n);
      printf("11) &i               = 0X%08X\n",&i);
      printf("12) &Fn              = 0X%08X\n",&Fn);
      printf("13) &totalCalls      = 0X%08X\n",&totalCalls);
      printf("14) calls            = 0X%08X\n",calls);
      printf("15) &calls[0]        = 0X%08X\n",&calls[0]);
      printf("16) &calls[n]        = 0X%08X\n",&calls[n]);
      printf("17) totalCalls       = 0X%08X\n",totalCalls);
      printf("18) *totalCalls      = 0X%08X\n",*totalCalls);
      printf("19) **totalCalls     = %10d\n",**totalCalls);
      printf("20) &\"\\nn? \"         = 0X%08X\n","\nn? ");
      printf("21) &\"\\nn? \"         = 0X%08X\n",&"\nn? ");
      printf("22) &\"%%d\"            = 0X%08X\n","%%d");

      for (i = 0; i <= n; i++) 
         calls[i] = 0;
      Fn = F(n,true);
      printf("F(%2d)  = %10d\n",n,Fn);
      **totalCalls = 0;
      for (i = 0; i <= n; i++)
      {
         **totalCalls += calls[i];
         printf("    F[%2d] called %10d times\n",i,calls[i]);
      }
      printf("   ==============================\n");
      printf("    Total calls  %10d times\n",**totalCalls);

      free(calls);
      printf("\nAfter free(calls)\n");
      printf("23) calls            = 0X%08X\n",calls);
      printf("24) calls[n]         = %10d\n",calls[n]);

      free(*totalCalls);
      printf("\nAfter free(*totalCalls)\n");
      printf("25) *totalCalls      = 0X%08X\n",*totalCalls);
      printf("26) **totalCalls     = %10d\n",**totalCalls);

      free(totalCalls);
      printf("\nAfter free(totalCalls)\n");
      printf("27) totalCalls       = 0X%08X\n",totalCalls);
      printf("28) *totalCalls      = 0X%08X\n",*totalCalls);
      printf("\nn? ");
   }
   
   system("PAUSE");
   return( 0 );
}

//---------------------------------------------------
int F(const int n,const bool calledFromMain)
//---------------------------------------------------
{
/*
         1         2         3         4         5         6         7         8         9        10
123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
   n = ##, &n = 0X######## (####), memoryLeak = 0X######## (####), mallocThenFree = 0X######## (####)
*/
   calls[n]++;

#ifdef TRACESTACK
{
   static const int *nP;
   static char *memoryLeakP;
   static double *mallocThenFreeP;

   char *memoryLeak = (char *) malloc(sizeof(char));
   double *mallocThenFree = (double *) malloc(sizeof(double));

   assert( memoryLeak != NULL );
   assert( mallocThenFree != NULL );

   if ( calledFromMain )
      printf("   n = %2d, &n = 0X%08X,        memoryLeak = 0X%08X,        mallocThenFree = 0X%08X\n",
         n,&n,memoryLeak,mallocThenFree);
   else
      printf("   n = %2d, &n = 0X%08X (%4d), memoryLeak = 0X%08X (%4d), mallocThenFree = 0X%08X (%4d)\n",
         n,&n,(nP-&n)*sizeof(int),
         memoryLeak,(memoryLeakP-memoryLeak)*sizeof(char),
         mallocThenFree,(mallocThenFreeP-mallocThenFree)*sizeof(double));

   nP = &n;
   memoryLeakP = memoryLeak;
   mallocThenFreeP = mallocThenFree;   
   free(mallocThenFree);
}
#endif

   if      ( n == 0 )
      return( F0 );
   else if ( n == 1 )
      return( F1 );
   else
      return( F(n-1,false) + F(n-2,false) );
}

//---------------------------------------------------
void UnusedFunction1(void)
//---------------------------------------------------
{
}

//---------------------------------------------------
void UnusedFunction2()
//---------------------------------------------------
{
}

