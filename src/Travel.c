#include "Travel.h"
#include "unity.h"
#include <malloc.h>
#include <math.h>
#include "InitCity.h"
#include "CityCoordinate.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

void bubbleSortForPath( Path table[], int size){
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
// rake test:Travel
Path MutationOfCities(Path path, City *targetA, City *targetB){
  City  *temp1 =  targetA->next , *temp2 =  targetB->next;

  reverseTheLinkBetween2City( path.cities, targetA, targetB);
  targetA->next = targetB;
  temp1->next   = temp2;

  path = getDistanceFromPath(path);
  return path;
}

Path copyCities (Path path){
  City *cities = path.cities, *cloneCities, city[path.size];
  int i;
  Path clonePath;

  for(i=0; i<path.size; i++){
   city[i] = *cities;
   cities = cities->next;
   cloneCities = &city[i];
   cloneCities = cloneCities->next;
  }
  clonePath.cities   = cloneCities;
  clonePath.size     = path.size;
  clonePath.distance = path.distance;

  return clonePath;
}

City copyCity(City A, City B){
  A.x_axis = B.x_axis ;
  A.y_axis = B.y_axis;
  A.ID     = B.ID;
  A.next   = NULL;
  return A;
}

City getFrontParent(City *cities, City target){
  City frontParent, *front;

  if(cities->ID == target.ID)
    cities = cities->next;

  while(cities->next->ID != target.ID)
    cities = cities->next;
  frontParent = copyCity(frontParent, *cities);
  return frontParent;
}

City getBackParent(City *cities, City target){
  City backParent, *back;

  while(cities->ID != target.ID)
    cities = cities->next;
  backParent = copyCity(backParent, *cities->next);
  return backParent;
}

int checkIsTargetNotInCities( City *cities, City target){
  while( cities->ID != target.ID){
    cities = cities->next;

    if(cities == NULL)
      return 1;
  }
  return 0;
}

int checkIsCityUsed( int IDList[], int ID){
  int i;
  for( i =0 ; i<(sizeof(IDList)); i++){
  if(IDList[i] == ID)
    return 0;
  }
  return 1;
}


// rake test:Travel
Path crossoverCities(City *cities1st, City *cities2nd, City target){
int i,j;
  City *newWalk, front[i], back[j], mid = target, target1, target2;
  
  mid.next = NULL;
  newWalk =  cityListNew(&mid);
  front[0] = getFrontParent(cities1st, target);
  back[0]  = getBackParent (cities2nd, target);

  i =0, j= 0;
  while (front[i].ID != back[j].ID){
  printf("%d\n",front[i].ID); 
  printf("%d\n",back[j].ID); 
     if(checkIsTargetNotInCities(newWalk,front[i]))
        addCityListPrev(&newWalk, &front[i]);
     else{ printf("break1\n");   
      break;}
    
    if(checkIsTargetNotInCities(newWalk,back[j]))
      addCityList    (&newWalk, &back[j]);
    else{ printf("break2\n");
      break;}
   
   target1 =  front[i];
   target2 =  back[j];
  i++ ,j++;
  
  front[i] = getFrontParent(cities1st, target1);
  back[j]  = getBackParent (cities2nd, target2); 
}
  
  
  
    //printf("%p\n",newWalk);
   // printf("%p\n",ptrBack);
   // printf("%p\n",newWalk);
   // printf("%p\n",newWalk->next);

  
  // if(checkIsTargetNotInCities( newWalk, target2) ){
     // *ptrBack = copyCity(*ptrBack, target2);
     // ptrBack = ptrBack->next;
  // }
  // back  = getBackParent (cities2nd, target2);
  

     // printf("%d\n",newWalk->ID);
    // printf("%d\n",newWalk->next->ID);
    // printf("%d\n",newWalk->next->next->ID);
   
  // printf("%p\n",newWalk);
  // printf("%p\n",newWalk->next);
  // printf("%p\n",newWalk->next->next);
     // printf("%d\n",ptrBack->ID);
      // printf("%p\n",ptrBack);
}

int checkingFor2opt(City *targetA, City *targetB){
  float oldLink = findDistance( targetA, targetA->next) + findDistance( targetB, targetB->next);
  float newLink = findDistance( targetA, targetB) + findDistance( targetA->next, targetB->next);

  if(newLink< oldLink)
    return 1;
  return 0;
}

// printf("%d\n",Parrent1.ID);
  // printf("%d\n",Parrent2.ID);
// printf("%d\n",cloneCities->ID);
// printf("%d\n",cloneCities->next->ID);
// printf("%d\n",cloneCities->next->next->ID);
// printf("%d\n",cloneCities->next->next->next->ID);
// printf("%d\n",cloneCities->next->next->next->next->ID);
// printf("%d\n",cloneCities->next->next->next->next->next->ID);
// printf("%d\n",cloneCities->next->next->next->next->next->next->ID);
// printf("%d\n",cloneCities->next->next->next->next->next->next->next->ID);


// printf("%p\n",cities1st);
// printf("%p\n",cities1st->next);
// printf("%p\n",cities1st->next->next);
// printf("%p\n",cities1st->next->next->next);
// printf("%p\n",cities1st->next->next->next->next);
// printf("%p\n",cities1st->next->next->next->next->next);
// printf("%p\n",cities1st->next->next->next->next->next->next);
// printf("%p\n",cities1st->next->next->next->next->next->next->next);
// printf("%p\n",cities1st->next->next->next->next->next->next->next->next);

City getParentCities(City *cities, City target){
  City Parent1, Parent2;

  if(cities->ID == target.ID)
    cities = cities->next;
  else if (cities->next->ID == target.ID)
    cities = cities->next->next;

  while(cities->next->next->ID != target.ID)
    cities = cities->next;

  Parent1 = copyCity(Parent1, *cities);
  Parent2 = copyCity(Parent2, *cities->next);
  Parent1.next = &Parent2;

  return Parent1;
}

City getChildCities(City *cities, City target){
  City child1, child2;

  while(cities->ID != target.ID)
    cities = cities->next;

  child1 = copyCity(child1, *cities->next);
  child2 = copyCity(child2, *cities->next->next);
  child1.next = &child2;

  return child1;
}