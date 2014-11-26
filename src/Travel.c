#include "Travel.h"
#include "unity.h"
#include <malloc.h>
#include <math.h>
#include "InitCity.h"
#include "CityCoordinate.h"
#include <stdio.h>
#include <stdlib.h>

City **createPathOfCityVisit( int numOfCities){
  City **cities = malloc(sizeof(City**) * numOfCities);
  City  *city   = *cities;
  return cities;
}

void genericBubbleSort( Path table[], int size){
  int i,j;
  Path temp;

  for (i = 1; i < size; i++){
    for (j = 0; j < size - 1; j++) {
      if( table[j].distance >table[j+1].distance ){
        temp= table[j+1];
        table[j+1] = table[j];
        table[j] = temp;
      }
    }
  }
}


// Cartesian formula
float findDistance( City *first, City *second){
  float  x,y, powX, powY, ans, rounded;

  x    = (*second).x_axis - (*first).x_axis;
  y    = (*second).y_axis - (*first).y_axis;
  powX = x*x;
  powY = y*y;
  ans  = sqrt(powX + powY);

  return ((int)(ans * 1000 + .5) / 1000.0); // correct number to 3 significant
}

void getDistanceFromPath( Path path){
  // City cities = path.cities;
  // printf("%d\n", cities.ID);
  // printf("%p\n", cities.next);
  // City *A = &cities;
  // City *B = cities.next;
   // printf("%d\n", A->ID);
   // printf("%p\n", B);


// float totalDistance = findDistance (A,B);

}

// Path formPathFromCities( City **cities, int size){
  // int   i;
  // float distance, rounded, totalDistance = 0;
  // Path  path;

  // for(i=0; i<size; i++){
    // distance = findDistance( &(*cities[i]), &(*cities[i+1]));
    // totalDistance = totalDistance + distance;
    // printf("distance:  %f\n", distance);
  // }
  // printf("%Total   : %f\n", totalDistance);
  // rounded = ((int)(totalDistance * 1000 + .5) / 1000.0); // correct number to 3 significant
  // setPath(&path,rounded,cities,size);
  // return path;
// }

