#ifndef Travel_H
#define Travel_H
#include "CityCoordinate.h"

float findDistance( City *first, City *second);
Path getDistanceFromPath( Path path);
Path MutationOfCities(Path path, City *targetA, City *targetB);
Path crossoverCities (Path path1, Path path2, City target);
Path copyCities (Path path);
City copyCity(City A, City B);
City getFrontParent(City *cities, City target);
City getBackParent (City *cities, City target);
void addCityToFront (City arr[], City target, int range);
void addCityToBack  (City arr[], City target, int range, int end);
int checkIsCityNotUsed( City arr[], City target, int range);

City removeSameElementInCities(City *mid, int size);
int checkingFor2opt(City *targetA, City *targetB);
int checkIsTargetNotInCities( City *cities, City target);
void bubbleSortForPath ( Path table[], int size);

#endif // Travel_H
