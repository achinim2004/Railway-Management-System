#ifndef TRAIN_FLEET_H
#define TRAIN_FLEET_H

/* ================================================================
   train_fleet.h — Member 1 | Data Structure: ARRAY
   Module: Train Fleet Registry
   ================================================================
   RESPONSIBILITY:
     Stores all trains in the Sri Lanka Railways fleet.
     Fixed capacity models the real constraint of a national
     rail network — you cannot run more trains than you have.
     Bubble sort ranks trains by seat capacity so operations
     staff can quickly see the highest-capacity trains first.

   EXTRA FUNCTION:
     calculateTotalSeatCapacity()
     → SUM of seatCapacity across entire fleet array
     → Answers: "What is the total passenger capacity
       of the entire Sri Lanka Railways fleet?"
   ================================================================ */

#include "shared_types.h"

/* ---------- Train record structure ---------- */
typedef struct {
    int  trainID;
    char trainName[NAME_LEN];   /* "Udarata Menike","Ruhunu Kumari" */
    char trainType[20];         /* "Express","Intercity","Local"    */
    int  seatCapacity;          /* total seats on this train        */
    int  currentLoad;           /* passengers currently on board    */
    char status[STATUS_LEN];    /* "Active","Maintenance","Retired" */
    char depot[40];             /* home depot: "Colombo","Kandy"    */
    char assignedRoute[50];     /* "Colombo-Kandy","Colombo-Galle"  */
} Train;

/* ---------- Global array & counter ---------- */
extern Train fleet[MAX_TRAINS];
extern int   trainCount;

/* ---------- Base operations ---------- */
void addTrain();                /* register new train into array    */
void removeTrain();             /* deregister by trainID            */
void updateTrainInfo();         /* edit capacity, status, depot     */
void searchTrain();             /* find by trainID or name          */
void displayFleet();            /* traverse and print all trains    */
int  isFleetFull();             /* check if array is at capacity    */
int  isFleetEmpty();            /* check if array is empty          */

/* ---------- Sort ---------- */
void bubbleSortByCapacity();    /* sort high seat count → low       */

/* ---------- Extra function ---------- */
void calculateTotalSeatCapacity(); /* SUM all seat counts in fleet  */

/* ---------- Formatted display ---------- */
void displayFleetTable();       /* formatted box table              */

/* ---------- Sub-menu ---------- */
void trainFleetMenu();

/* ---------- Helper used by other modules ---------- */
Train* findTrainByID(int id);

#endif /* TRAIN_FLEET_H */
