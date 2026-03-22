#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

/* ================================================================
   shared_types.h -- Common definitions used across ALL modules
   Sri Lanka Railway Network Management System
   ================================================================
   Universal Linking Keys:
     trainID   -> Fleet -> Journey Log, Route Rotation,
                           Maintenance, Seat Reservations
     stationID -> Station Directory -> Journey Log, Boarding Queue
   ================================================================ */

/* ---------- Capacity limits ---------- */
#define MAX_TRAINS       50     /* max trains in fleet array        */
#define MAX_SEATS       100     /* max seats per train (array size) */
#define MAX_BOARDING    100     /* max passengers in boarding queue */
#define MAX_MAINTENANCE  50     /* max entries in maintenance queue */

/* ---------- String sizes ---------- */
#define NAME_LEN    60
#define CODE_LEN    10
#define STATUS_LEN  25
#define TIME_LEN    25
#define DESC_LEN   100

/* ---------- Screen clear ---------- */
#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

/* ---------- Display helpers ---------- */
#define DIVIDER "--------------------------------------------------------------\n"
#define HEADER  "==============================================================\n"

#endif /* SHARED_TYPES_H */
