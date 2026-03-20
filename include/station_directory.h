#ifndef STATION_DIRECTORY_H
#define STATION_DIRECTORY_H

/* ================================================================
   station_directory.h — Member 2 | Data Structure: SINGLY LINKED LIST
   Module: Station Directory
   ================================================================
   RESPONSIBILITY:
     Dynamically manages all railway stations. Stations are
     added and removed as the network expands — a linked list
     grows and shrinks naturally without wasting memory.
     Insertion sort orders stations by their station code
     for quick alphabetical lookup.

   EXTRA FUNCTION:
     countStationsOnRoute()
     → FILTERED COUNT — traverses full list counting
       only stations belonging to a given routeID
     → Answers: "How many stations are on the
       Colombo-Kandy line?"
     → Different from search: returns a COUNT not a node
   ================================================================ */

#include "shared_types.h"

/* ---------- Station node structure ---------- */
typedef struct StationNode {
    int    stationID;
    char   stationName[NAME_LEN]; /* "Colombo Fort","Kandy","Galle" */
    char   stationCode[CODE_LEN]; /* "CMB","KDY","GLE","MTR"        */
    int    routeID;               /* which route this station is on  */
    char   routeName[50];         /* "Colombo-Kandy","Colombo-Galle" */
    int    platformCount;
    char   district[40];
    char   status[STATUS_LEN];    /* "Active","Closed","Under Repair" */
    struct StationNode* next;
} StationNode;

/* ---------- List head pointer ---------- */
extern StationNode* stationHead;

/* ---------- Base operations ---------- */
void addStation();              /* add new station node             */
void removeStation();           /* remove by stationID              */
void updateStationInfo();       /* edit platforms, status           */
void searchStation();           /* find by ID or name               */
void displayAllStations();      /* traverse and print all nodes     */

/* ---------- Sort ---------- */
void insertionSortByCode();     /* sort stations by station code    */

/* ---------- Extra function ---------- */
void countStationsOnRoute();    /* FILTERED COUNT by routeID        */

/* ---------- Formatted display ---------- */
void displayStationTable();     /* formatted box table              */

/* ---------- Sub-menu ---------- */
void stationDirectoryMenu();

/* ---------- Helper used by other modules ---------- */
StationNode* findStationByID(int id);

#endif /* STATION_DIRECTORY_H */
