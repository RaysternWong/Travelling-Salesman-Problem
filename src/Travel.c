#include "Travel.h"
#include "unity.h"
#include <malloc.h>
#include <math.h>
#include "InitCity.h"
#include "CityCoordinate.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include "Random.h"

void printOutACities( City *cities){
  int stop = cities->ID;
  printf("%d\n",cities->ID);

  cities = cities->next;
  while(cities->ID != stop){
    printf("%d\n",cities->ID);
    cities = cities->next;
  }
}

/** Input: coordinate1 and coordinate2
*
*   Output: distance between them
*/
float findDistance( City *first, City *second){
  float  x,y, powX, powY, ans, rounded;
  // Cartesian formula
  x    = (*second).x_axis - (*first).x_axis;
  y    = (*second).y_axis - (*first).y_axis;
  powX = x*x;
  powY = y*y;
  ans  = sqrt(powX + powY);

  return ((int)(ans * 1000 + .5) / 1000.0); // correct number to 3 significant
}

/** Input: Path without distance data
*
*   Output: Path with distance data
*/
Path getDistanceFromPath( Path path){
  City *cities = path.cities, *cityNext;
  int   headID = cities->ID;
  float TotalDistance  = 0;

  TotalDistance = findDistance( cities,cities->next);
  cityNext = cities->next;
  int size = 1;

  while(cityNext->ID != headID){
    TotalDistance = TotalDistance + findDistance( cityNext, cityNext->next);
    cityNext = cityNext->next;
    size = size + 1;
  }
  path.size     = size ;
  path.distance = TotalDistance;

  return path;
}

/** Input:  Path and 2 points been select to do mutation
*
*   Process: 1. It is a pre checking of mutation, to determine the mutation
*               whether can produce a better chromosome.
*            2. First it calculate the distance of original link and
*               mutated link
*            3. If the mutation link distance is shorter then original, then
*               send 1 as true to do mutation, else the linked is longer or the
*               points are same then send 0 as false
*
*   Output: True (1) or false (0) of the command
*/
int checkingFor2opt(City *cities, City targetA, City targetB){
  if(targetA.ID == targetB.ID)
    return 0;

  City *pointA = cities;
  City *pointB = cities;

  while(pointA->ID != targetA.ID)
    pointA = pointA->next;
  while(pointB->ID != targetB.ID)
    pointB = pointB->next;

  float oldLink = findDistance( pointA, pointA->next) + findDistance( pointB, pointB->next);
  float newLink = findDistance( pointA, pointB) + findDistance( pointA->next, pointB->next);

  if(newLink < oldLink)
    return 1;
  return 0;
}

/** Input: Path and 2 points been select to do mutation
*
*   Process: 1. tour1 and tour2 is the link of cities
*            2. tour1 and tour2 will locate the position of targetA and targetB'
*            3. tour1 and tour2 will do reverse linkedList between them
*            4. tour1 will point to tour2, tour1's next point to tour2's next
*            5. a mutation city list form

*   Output: mutation city list
*/
Path MutationCities(Path path, City targetA, City targetB){
  if(targetA.ID == targetB.ID)
    return;

  City *tourA =  path.cities , *tourB = path.cities;

  while(tourA->ID != targetA.ID)
    tourA = tourA->next;
  while(tourB->ID != targetB.ID)
    tourB = tourB->next;
  City *temp1 =  tourA->next , *temp2 = tourB->next;

  reverseTheLinkBetween2City( path.cities, tourA, tourB);
  tourA->next = tourB;
  temp1->next = temp2;

  path = getDistanceFromPath(path);
  return path;
}

City copyCity ( City city){
  City clone;
  clone.x_axis = city.x_axis;;
  clone.y_axis = city.y_axis;
  clone.ID     = city.ID;
  clone.next   = NULL;
  return clone;
}

/** Input:   sample path
*
*   Output: cloned path
*/
Path copyPath (Path path, City arr[]){
  int i, size = path.size , stop;
  City *cities = path.cities, *newCites, *cloneCities , head;
  Path newPath;
  stop = cities->ID;

  for( i = 0; i < size ; i ++){
    arr[i] = *cities;
    cities = cities->next;
  }

  newPath = convertArrayToPath( arr,  size);
  newPath.size     = path.size;
  newPath.distance = path.distance;
  return newPath;
}

/** Input:  cities and  target city
*
*   Output: the front city of the target in the cities list
*/
City getFrontCity(City *cities, City target){
  City frontCity, *front;

  if(cities->ID == target.ID)
    cities = cities->next;

  while(cities->next->ID != target.ID)
    cities = cities->next;
  frontCity = copyCity(*cities);
  return frontCity;
}

/** Input:  cities and  target city
*
*   Output: the back city of the target in the cities list
*/
City getBackCity(City *cities, City target){
  City backCity, *back;

  while(cities->ID != target.ID)
    cities = cities->next;
  backCity = copyCity(*cities->next);
  return backCity;
}

/** Input: city array and target city
*
*   Process: to determine whether the target city is inside the array
*            if not inside return1 , else return 0
*
*   Output: True (1) or false (0) of the command
*/
int checkIsCityNotUsed( City arr[], City target, int range){
  int i;

  for(i = 0 ; i < range ; i ++){
    if( arr[i].ID == target.ID)
      return 0;    
  }
  return 1;
}

/** Input:  array city and  target city
*
*   Process: endID is the last city's ID of the array, so it know how to add the newCity to back
*
*   Output: array city with added target city in the back
*/
void addCityToBack (City arr[], City target, int range, int endID){
  int i;
  for(i = 0 ; i < range ; i ++){
    if(arr[i].ID == endID){
      arr[i+1] = copyCity(target);
      break;
    }
  }
}

/** Input:  array city and  target city
*
*   Output: array city with added target city in the front
*/
void addCityToFront(City arr[], City target, int range){
  int i;
  City arr2[range];

  for(i = 0 ; i < range; i ++)
    arr2[i+1] = arr[i];
  arr2[0] = copyCity(target);
  for(i= 0; i < range; i ++)
    arr[i] = arr2[i];
}

/** Input: an array
*
*   Output: a path been convert from the array
*/
Path convertArrayToPath( City arr[], int range){
  int i;
  Path path;
  City *cities;

  arr[0].next = NULL;
  cities =  cityListNew(&arr[0]);
  City *head = cities;

  for(i = 1 ; i < range; i ++){
    arr[i].next = NULL;
    addCityList(&cities, &arr[i]);
  }
  addCityList(&cities, head);

  path.cities = cities;
  return path;
}

/** Input: an unsorted neighBour array
*
*   Output: a sorted neighBour array according distance
*/
void bubbleSortForNeighBour( NeighBour route[], int size){
  int i,j;
  NeighBour temp;

  for (i = 1; i < size; i++){
    for (j = 0; j < size - 1; j++) {
      if( route[j].distance >route[j+1].distance ){
        temp= route[j+1];
        route[j+1] = route[j];
        route[j] = temp;
      }
    }
  }
}

/** Input: an unsorted Path array
*
*   Output: a sorted Path array according distance
*/
void bubbleSortForPath( Path path[], int size){
  int i,j;
  Path temp;

  for (i = 1; i < size; i++){
    for (j = 0; j < size - 1; j++){
      if( path[j].distance >path[j+1].distance ){
        temp= path[j+1];
        path[j+1] = path[j];
        path[j] = temp;
      }
    }
  }
}

/** Input:  city array with missing and linkList
*
*   Process: 1. determine the missing cities in the array by comparing a complete linked list
*            2. put the missing cities inside neighbour type array
*            3. get the distance of the missing city between the last element inside the original array
*            4. sort the neighBour type array according distance
*            5. put the cities from the neighBour type array to original array
*
*   Output: city array with all city , and the missing cities are sorted according neighbour distance
*/
void addCityOfNeighbour(City arr[], City lastCityInArr, City *cities, int stop, int range){
  NeighBour near[range];
  int i = 0 , sizeNear = 0;

  while(cities->ID != stop){
    if(checkIsCityNotUsed( arr, *cities, range)){
      near[i].neighBour = copyCity(*cities);
      sizeNear = sizeNear + 1;
      i++;
    }
    cities = cities->next;
  }

  for (i = 0; i < sizeNear ; i++)
    near[i].distance = findDistance( &lastCityInArr, &near[i].neighBour);

  bubbleSortForNeighBour( near, sizeNear);

  for (i = 0; i < sizeNear ; i++){
    addCityToBack (arr, near[i].neighBour, range, lastCityInArr.ID);
    lastCityInArr = near[i].neighBour;
  }
}

/** Input:  2 path , target City to do mutation , internal array
*
*   Process: 1. During computing a crossover cities, I need to first building them into a array first,
*               because if the building structure's is linkedList, the data will continue overwrite in a while loop
*            2. Assign array[0] to target, and start to putting element from path1's left and path2's right
*            3. If the coming element was inside the array, then the building process stop.
*            3. the array will looking the missing element by compare a complete linkedList
*            4. put the missing cities into array according neighBour's distance of last city of array
*            5. convert the complete array to path, and return the path
*
*   Output: crossover path,  and some of path's cities was arranged
*/
Path crossoverCities(Path path1, Path path2, City target, City arr[]){
  int range = path1.size;
  City *head1 = path1.cities, *head2 = path2.cities, front, back, lastCityInArr;
  Path path;
  arr[0] = target;
  lastCityInArr = arr[0];

  while(head1->ID != target.ID)
    head1 = head1->next;
  while(head2->ID != target.ID)
    head2 = head2->next;

  front = getFrontCity(head1, target);
  back  = getBackCity (head2, target);
  
  while(checkIsCityNotUsed( arr, front, range)){
    addCityToFront(arr, front, range);
    front = getFrontCity(head1, front);

    if(checkIsCityNotUsed( arr, back, range)){
      addCityToBack (arr, back, range, lastCityInArr.ID);
      lastCityInArr = back;
      back = getBackCity(head2, back);
    } else break;
  }
  head1 = head1->next;    //LinkedList point to next, because head1 is the target which already contain in the array
  addCityOfNeighbour( arr, lastCityInArr, head1, target.ID, range);

  path = convertArrayToPath(arr, range);
  path = getDistanceFromPath(path);
  return path;
}

/** Input: city array contained data
*
*   Output: city array without data
*/
void clearCityArray(City arr[], int size){
  int i;
  City empty;
       empty.x_axis = 0;
       empty.y_axis = 0;
       empty.ID = 0;
  for(i = 0 ; i<size; i++ )
    arr[i] = empty;
}

/** Input:  sample array
*
*   Output: clone array
*/
void copyArray( City clone[], City arr[], int size){
  int i;
  for(i=0 ; i < size ; i++){
    clone[i] = arr[i];
  }
}

void initPopulationTable( int sizeOfPopulation, int size, Path population[], City tour[sizeOfPopulation][size], City arr[]){
  City temp;
  int i,j,x;

  for( i=0 ; i<sizeOfPopulation; i++){
    copyArray( tour[i], arr, size);
    for ( j=0 ; j < size ; j++){   // shuffle the array
      x = rand()%(size);
      temp = tour[i][x];
      tour[i][x] = tour[i][j];
      tour[i][j] = temp;
    }
    population[i] = convertArrayToPath( tour[i], size);
    population[i] = getDistanceFromPath( population[i]);
  }
}

void printfOutThePopulatointable(int sizeOfPopulation, int size, Path population[]){
  int i,j;
  City *cities;
  printf("\n");
  printf("-------------------Table of City ID-------------------\n");

  for(j = 0; j <size; j ++)
    printf("   %d ",j+1);
    printf("\n");

  for(j = 0; j <size; j ++)
    printf("------");
    printf("\n");

  for ( i = 0; i < sizeOfPopulation ; i++){
    cities = population[i].cities;
    printf("%d| ",i+1);
    for( j = 0 ; j < size ; j ++){
      printf("%d  ",cities->ID);
      cities = cities->next;
    }
    printf("\n");
  }
  printf("\n");
}

void freePopulationTable(Path population[], int sizeOfPopulation){
  int i;
  City *cities;
  for( i = 0 ; i < sizeOfPopulation ; i++)
    clearCityList(population[i].cities);
  
}


/** Input: array of all cities, size of population, size of cities
*
*   Process: 1. The function is combined mutation and crossover 
*            2. First, created a population table for the give size, declare a targetNumber, which is  (sizeOfPopulation + sizeOfCity)
*            3. Created a while loop, the while loop break when the counter increment until reach value of targetNumber 
*            4. do mutation and crossover by randomly select the target from the population table
*            4. Record the table[0] distance as "pre",
*               arrange the population table according distance
*               Record the table[0] distance as "post",
*            5. If the "post" value is less then "pre" value, clear the counter, else increment the counter
*            6. while the counter increment reach the target number , break the loop
*            7. Record table[0] as shortest path, and return it.
*   Output: path of compute shortest distance
*/
Path travelInShortestPath( City arr[], int sizeOfPopulation, int size){
  Path population[sizeOfPopulation], crossPath, shortestPath;
  City storeArr[sizeOfPopulation][size], tempArr[sizeOfPopulation][size], crossArr[size], shortestArr[size]; // those arrays are use to store the element for the population table 
  int  targetNumber = sizeOfPopulation + size, counter = 0, i = 0 ,a, b, c;
  float pre , post;
  
  clearCityArray( crossArr, 8); // To ensure crossArr is empty
  initPopulationTable( sizeOfPopulation, size, population, storeArr, arr);
 // printfOutThePopulatointable( sizeOfPopulation, size, population);

  while (counter < targetNumber){
    a = rand()%sizeOfPopulation;
    population[a] = doMutation( population[a], arr, size);

    do{  b = rand()%sizeOfPopulation;
         c = rand()%sizeOfPopulation;
      } while ( b == c );
    crossPath = doCrossover( population[b], population[c], arr, crossArr, size);

    if( crossPath.distance < population[b].distance &&  crossPath.distance < population[c].distance){
      population[b] = copyPath ( crossPath, tempArr[i]);
      i++;
    } clearCityArray( crossArr, size);

    pre  = population[0].distance;
    bubbleSortForPath (population, sizeOfPopulation);
    post = population[0].distance;
    if( post < pre )
      counter = 0 ; 
    else counter = counter + 1;   
    
    printf( "Distance : %f\n", population[0].distance);
  }  
 // printfOutThePopulatointable( sizeOfPopulation, size, population);
 
  shortestPath = copyPath(population[0], shortestArr);
  return shortestPath; 
}

Path doMutation( Path path, City arr[], int size){
  City rand1, rand2;
  int A,B;

  do{
      A = rand()%size;
      B = rand()%size;
    } while ( A == B);
  rand1 = arr[A];
  rand2 = arr[B];

  if( checkingFor2opt( path.cities, rand1, rand2))
    path = MutationCities( path, rand1, rand2);
  return path;
}

Path doCrossover( Path path1, Path path2, City arr[], City crossArr[], int size){
  int  A = rand()%size;
  City rand1 = arr[A];
  Path crossoverPath;

  crossoverPath = crossoverCities( path1, path2, rand1, crossArr);
  return crossoverPath;
}