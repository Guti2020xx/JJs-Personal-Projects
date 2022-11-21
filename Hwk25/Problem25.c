//--------------------------------------------------
// Dr. Art Hanna and JJ
// Problem #25
// Problem25.c
//--------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>
#include <assert.h>

#include "Random.h"

#define SIZEX 100.0
#define SIZEY 100.0

typedef struct POINT
{
   double x;
   double y;
} POINT;

typedef struct SEGMENT
{
   POINT p1;
   POINT p2;
} SEGMENT;

//--------------------------------------------------
int main()
//--------------------------------------------------
{
   void FindConvexHull(const POINT points[],const int n,SEGMENT segments[],int *s);
   void BuildOUTFile(const POINT points[],const int n,const SEGMENT segments[],const int s);

   int n,s;
   POINT *points;
   SEGMENT *segments;

   printf("n? "); scanf("%d",&n);
   points = (POINT *) malloc(sizeof(POINT)*(n+1));
   segments = (SEGMENT *) malloc(sizeof(SEGMENT)*(n+1));

   SetRandomSeed();

// choose n random points
   for (int i = 1; i <= n; i++)
   {
      points[i].x = floor((RandomDouble()*SIZEX)*10)/10;
      points[i].y = floor((RandomDouble()*SIZEY)*10)/10;
   }

// find line segments that make up convex hull
   FindConvexHull(points,n,segments,&s);

// build output file
   BuildOUTFile(points,n,segments,s);

   free(points);
   free(segments);

   system("PAUSE");
   return( 0 );
}

//--------------------------------------------------
void FindConvexHull(const POINT points[],const int n,SEGMENT segments[],int *s)
//--------------------------------------------------
{
   double b, c, a; int negCount, posCount;
   
   *s = 0;
  for (int i =1; i <= n-1; i++)
  {
    for (int j = i +1; j <= n; j++)
    {
    	        b = points [i].x - points[j].x ;
                a = points[j].y - points[i].y ;
                c = (points[i].x * points[j].y) - (points[j].x * points[i].y);
            negCount = 0; posCount = 0;
        for (int k =1; k <= n; k++)
        {
            if( i != k && j !=k)
            {
                // ax + by - c = 0
                if( ((a*points[k].x) + (b * points[k].y) - c) < 0)
                {
                	negCount += 1;
				}
				else if ( ((a*points[k].x) + (b * points[k].y) - c) > 0)
				{
					posCount += 1;
				}
	      			
				// have to be on the other side and then we add it to segments
            }
            
        }
        
				if(posCount == 0 || negCount == 0)
				{
					*s += 1;
					assert( *s <= n );
					segments[*s].p2 = points[j]; // adding it ?? is this right
					segments[*s].p1 = points[i];
				}	
    }
  }
  /* Student provides missing code to compute the convex-hull of the
      n points contained in points[i], i   [ 1,n ]. The convex-hull consists of the
      *s segments contained in segments[i], i   [ 1,*s ]. Use the algorithm
      described on pages 111 and 112 of the textbook. See *FYI #2* and *FYI #7* for
      help understanding the roles of the FindComplexHull() formal parameters.

      Hint #1 Our textbook suggests "...we need to find the sign of the expression
         ax + by - c for each of the other n-2 points."

      Hint #2 A line segment is part of the convex-hull if-and-only-if (iff) the number 
         of points on the positive side of the line segment is 0 *OR* the
         number of points on the negative side of the line segment is 0.

      Note For the sake of simplicity, the foregoing algorithm ignores the possibility that
         (ax + by - c = 0.0)!? Question Where is a point (x,y) located when the condition
         (ax + by - c = 0.0) is true? Answer *ON* the line segment being considered, not on 
         either side of it. How would the algorithm need to change to be able to take the condition
         (ax + by - c = 0.0) into account?!
         */

}

//--------------------------------------------------
void BuildOUTFile(const POINT points[],const int n,const SEGMENT segments[],const int s)
//--------------------------------------------------
{
   FILE *OUT;

   OUT = fopen("Problem25.out","w");
   fprintf(OUT,"%5.1f %5.1f\n",SIZEX,SIZEY);
   fprintf(OUT,"%4d\n",n);
   for (int i = 1; i <= n; i++)
       fprintf(OUT,"%5.1f %5.1f\n",points[i].x,points[i].y);
   fprintf(OUT,"%4d\n",s);
   for (int i = 1; i <= s; i++)
   {
      fprintf(OUT,"%5.1f %5.1f  ",segments[i].p1.x,segments[i].p1.y);
      fprintf(OUT,"%5.1f %5.1f\n",segments[i].p2.x,segments[i].p2.y);
   }
   fclose(OUT);
}

