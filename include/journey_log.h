#ifndef JOURNEY_LOG_H
#define JOURNEY_LOG_H

/* ================================================================
   journey_log.h — Member 3 | Data Structure: DOUBLY LINKED LIST
   Module: Journey Log
   ================================================================
   RESPONSIBILITY:
     Logs every train journey with full trip details.
     Controllers scroll FORWARD to see upcoming/recent
     journeys and BACKWARD to investigate past delays.
     Selection sort rebuilds the chronological departure
     timeline. Only a Doubly LL supports both directions.

   EXTRA FUNCTION:
     calculateJourneyDistance()
     → SUM of distanceKm fields by traversing DLL nodes
       for a specific trainID
     → Answers: "What is the total distance covered
       by this train across all logged journeys?"
     → Pure numeric aggregate — not search, not display
   ================================================================ */

#include "shared_types.h"

/* ---------- Journey record node ---------- */
typedef struct JourneyNode {
    int    journeyID;
    int    trainID;               /* links to Train Fleet            */
    int    fromStationID;         /* links to Station Directory      */
    int    toStationID;           /* links to Station Directory      */
    char   trainName[NAME_LEN];
    char   fromStation[NAME_LEN];
    char   toStation[NAME_LEN];
    char   departureTime[TIME_LEN];
    char   arrivalTime[TIME_LEN];
    float  distanceKm;            /* used in calculateJourneyDistance */
    int    delayMinutes;          /* 0 = on time                     */
    char   status[STATUS_LEN];    /* "On Time","Delayed","Cancelled"  */
    struct JourneyNode* prev;
    struct JourneyNode* next;
} JourneyNode;

/* ---------- List pointers ---------- */
extern JourneyNode* journeyHead;
extern JourneyNode* journeyTail;

/* ---------- Base operations ---------- */
void addJourneyRecord();        /* append new journey to log        */
void removeJourneyRecord();     /* delete by journeyID              */
void updateJourneyStatus();     /* edit delay, status, arrival time */
void searchJourneyRecord();     /* find by journeyID or trainID     */
void displayAllJourneys();      /* full forward traversal           */
void traverseForward();         /* oldest journey → latest          */
void traverseBackward();        /* latest journey → oldest          */

/* ---------- Sort ---------- */
void selectionSortByDeparture(); /* sort by departure time          */

/* ---------- Extra function ---------- */
void calculateJourneyDistance(); /* SUM distanceKm for a trainID   */

/* ---------- Formatted display ---------- */
void displayJourneyTable();     /* formatted box table              */

/* ---------- Sub-menu ---------- */
void journeyLogMenu();

#endif /* JOURNEY_LOG_H */
