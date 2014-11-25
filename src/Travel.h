#ifndef Travel_H
#define Travel_H
#include "CityCoordinate.h"

float findDistance( City *first, City *second);
City **createPathOfCityVisit( int numOfCities);
void getDistanceFromPath( Path path);
void genericBubbleSort ( Path table[], int size);


#endif // Travel_H
