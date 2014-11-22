#include "Travel.h"
#include <malloc.h>
#include <math.h>
#include "InitCity.h"
#include "CityCoordinate.h"
#include <stdio.h>
#include <stdlib.h>

Path genericBubbleSort(void *table, int size, int(*comapare(void*,void*))){

}

int compare(void *v1, void *v2){
	int *A,*B;
	A= (int *)v1;
	B= (int *)v2;

  if(*A>*B)
    return 1;
  if (*A<*B)
    return -1;
  return 0;
}

void swap( float *x, float *y ){
  float temp;
   temp = *x;
   *x    = *y;
   *x    = temp;
}



void bubbleSortD(double iarr[], int num) {
   int i, j, k, temp;
 
   printf("\nUnsorted Data:");
   for (k = 0; k < num; k++) {
      printf("%5d", iarr[k]);
   }
 
   for (i = 1; i < num; i++) {
      for (j = 0; j < num - 1; j++) {
         if (iarr[j] > iarr[j + 1]) {
            temp = iarr[j];
            iarr[j] = iarr[j + 1];
            iarr[j + 1] = temp;
         }
      }
 
      printf("\nAfter pass %d : ", i);
      for (k = 0; k < num; k++) {
         printf("%5d", iarr[k]);
      }
   }
}

City **createPathOfCityVisit(int numOfCities){
  City **cities = malloc(sizeof(City**) * numOfCities);
  City  *city   = *cities;
  return cities;
}

// Cartesian formula
float findDistance(City *first, City *second){
  float  x,y, powX, powY, ans, rounded;

  x    = (*second).x_axis - (*first).x_axis;
  y    = (*second).y_axis - (*first).y_axis;
  powX = x*x;
  powY = y*y;
  ans  = sqrt(powX + powY);

  return ((int)(ans * 1000 + .5) / 1000.0); // correct number to 3 significant
}

Path formPathFromCities(City **cities, int size){
  int   i;
  float distance, rounded, totalDistance = 0;
  Path  path;

  for(i=0; i<size; i++){
    distance = findDistance( &(*cities[i]), &(*cities[i+1]));
    totalDistance = totalDistance + distance;
    printf("distance:  %f\n", distance);
  }
  printf("%Total   : %f\n", totalDistance);
  rounded = ((int)(totalDistance * 1000 + .5) / 1000.0); // correct number to 3 significant
  path = setPath(path,rounded,cities,size);
  return path;
}

Path formNewPath(Path path){
// printf("distance:  %f\n", path.distance);
// printf(" %d\n", path.cities[0]->ID);
// printf(" %d\n", path.cities[1]->ID);
// printf(" %d\n", path.cities[2]->ID);
// printf(" %d\n", path.cities[3]->ID);
// printf(" %d\n", path.cities[4]->ID);
// printf(" %d\n", path.cities[5]->ID);
}