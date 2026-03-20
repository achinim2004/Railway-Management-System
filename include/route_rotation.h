#ifndef ROUTE_ROTATION_H
#define ROUTE_ROTATION_H

/* ================================================================
   route_rotation.h — Member 4 | Data Structure: CIRCULAR LINKED LIST
   Module: Train Route Rotation
   ================================================================
   RESPONSIBILITY:
     Cycles trains through route deployments endlessly.
     After the last train's trip the rotation loops back
     to the first — modelling real railway scheduling where
     trains continuously cycle on their assigned routes.
     The last node's next pointer points back to head —
     no NULL terminator, just an endless cycle.

   EXTRA FUNCTION:
     getRouteSize()
     → traverses circular cycle COUNTING nodes until
       the loop back to head is detected
     → necessary because circular list has NO NULL
       end to detect — must count manually
     → genuinely different from array .length or
       a regular linked list count
   ================================================================ */

#include "shared_types.h"

/* ---------- Rotation node structure ---------- */
typedef struct RouteNode {
    int    trainID;               /* links to Train Fleet            */
    char   trainName[NAME_LEN];
    char   routeName[50];         /* "Colombo-Kandy","Colombo-Galle" */
    char   scheduleTime[TIME_LEN];/* departure time for this slot    */
    char   direction[20];         /* "Northbound","Southbound"       */
    int    tripsCompleted;        /* trips done this rotation cycle  */
    struct RouteNode* next;       /* last node → points back to head */
} RouteNode;

/* ---------- Rotation head pointer ---------- */
extern RouteNode* currentTrain;  /* always points to active train   */

/* ---------- Base operations ---------- */
void addTrainToRoute();          /* insert train into cycle          */
void removeTrainFromRoute();     /* remove, re-link circular cycle   */
void updateRouteInfo();          /* edit schedule, direction         */
void searchTrainInRoute();       /* find by trainID in cycle         */
void displayRouteRotation();     /* print full circular cycle        */

/* ---------- Navigation — defining CLL operations ---------- */
void nextTrainOnRoute();         /* advance pointer to next train    */
void getCurrentTrain();          /* show currently deployed train    */

/* ---------- Extra function ---------- */
void getRouteSize();             /* COUNT via circular traversal     */

/* ---------- Formatted display ---------- */
void displayRotationTable();     /* formatted rotation schedule      */

/* ---------- Sub-menu ---------- */
void routeRotationMenu();

#endif /* ROUTE_ROTATION_H */
