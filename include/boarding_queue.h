#ifndef BOARDING_QUEUE_H
#define BOARDING_QUEUE_H

/* ================================================================
   boarding_queue.h — Member 6 | Data Structure: QUEUE
   Module: Passenger Boarding Queue
   ================================================================
   RESPONSIBILITY:
     Manages passengers waiting to board their train at
     the platform. Passengers join at the rear and board
     from the front — strictly FIFO. First passenger to
     join the queue is the first to board. Fair, ordered,
     and predictable — exactly how real platform boarding
     works at Colombo Fort and other major stations.

   EXTRA FUNCTION:
     getAverageWaitTime()
     → computes AVERAGE number of passengers ahead
       of each person — a queue depth metric
     → Answers: "On average how long is a passenger
       waiting in this boarding queue?"
     → Numeric AVERAGE computed across all queue slots
   ================================================================ */

#include "shared_types.h"

/* ---------- Passenger record structure ---------- */
typedef struct {
    int  passengerID;
    char passengerName[NAME_LEN];
    int  trainID;                 /* links to Train Fleet            */
    int  stationID;               /* links to Station Directory      */
    char trainName[NAME_LEN];
    char stationName[NAME_LEN];
    char ticketClass[20];         /* "First","Second","Third"        */
    char ticketNumber[20];
    char joinedQueueAt[TIME_LEN]; /* when passenger joined queue     */
    char status[STATUS_LEN];      /* "Waiting","Boarding","Boarded"  */
} Passenger;

/* ---------- Queue structure (circular array) ---------- */
typedef struct {
    Passenger passengers[MAX_BOARDING];
    int front;
    int rear;
    int count;
} BoardingQueue;

/* ---------- Global queue instance ---------- */
extern BoardingQueue boardingQ;

/* ---------- Base operations ---------- */
void enqueuePassenger();         /* passenger joins boarding line    */
void dequeuePassenger();         /* next passenger boards train      */
void peekNextPassenger();        /* who boards next without removing */
void searchPassenger();          /* find by passengerID in queue     */
void displayBoardingQueue();     /* show all waiting passengers      */
void cancelBoarding();           /* remove specific passenger        */
int  isBoardingQueueEmpty();     /* check if queue is empty          */
int  isBoardingQueueFull();      /* check if queue is full           */

/* ---------- Extra function ---------- */
void getAverageWaitTime();       /* AVERAGE wait metric on queue     */

/* ---------- Formatted display ---------- */
void displayBoardingTable();     /* formatted box table              */

/* ---------- Sub-menu ---------- */
void boardingQueueMenu();

#endif /* BOARDING_QUEUE_H */
