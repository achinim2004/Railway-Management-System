#ifndef SEAT_RESERVATIONS_H
#define SEAT_RESERVATIONS_H

/* ================================================================
   seat_reservations.h -- Member 5 | Data Structure: ARRAY (2nd use)
   Module: Seat Reservation Management
   ================================================================
   RESPONSIBILITY:
     Manages seat reservations for a specific train.
     Every train has a fixed number of seats -- this hard
     physical limit is exactly what an Array models.
     Staff select a train, then manage its seat map:
     reserve seats for passengers, release cancelled seats,
     search availability, and view the full seat layout.

   WHY ARRAY (2nd use)?
     Train Fleet [Array 1st]:
       Fixed number of TRAINS owned by railway.
       Indexed by trainID. One array for whole system.

     Seat Reservations [Array 2nd]:
       Fixed number of SEATS per train.
       Indexed directly by seat number (0 to capacity-1).
       Each train's seats never change in count.
       Direct index access by seat number is O(1).
       Completely different entity, data, and purpose.

   EXTRA FUNCTION:
     countAvailableSeats()
     -> scan array counting seats where status == Available
     -> returns how many seats are still open on the train
     -> TYPE: Conditional COUNT across array elements
   ================================================================ */

#include "shared_types.h"

/* ---------- Seat record structure ---------- */
typedef struct {
    int  seatNumber;            /* 1-based seat number              */
    char seatClass[20];         /* "First", "Second", "Third"       */
    char status[STATUS_LEN];    /* "Available", "Reserved"          */
    char passengerName[NAME_LEN];/* who reserved this seat          */
    char passengerNIC[20];      /* NIC for identity verification    */
    char reservedAt[TIME_LEN];  /* when reservation was made        */
    char journeyDate[TIME_LEN]; /* date of travel                   */
} Seat;

/* ---------- Seat map (array per train) ---------- */
/* We manage one train's seat map at a time         */
extern Seat  seatMap[MAX_SEATS];
extern int   totalSeats;        /* total seats loaded for this train */
extern int   currentTrainID;    /* which train's seats are loaded    */
extern char  currentTrainName[NAME_LEN];

/* ---------- Base operations ---------- */
void loadTrainSeats();          /* load seat map for a specific train */
void reserveSeat();             /* mark a seat as Reserved            */
void releaseSeat();             /* mark a seat back to Available      */
void updateReservation();       /* update passenger details           */
void searchSeat();              /* find by seat number or passenger   */
void displaySeatMap();          /* show full seat layout              */
int  isSeatMapEmpty();          /* check if no train loaded           */

/* ---------- Sort ---------- */
void bubbleSortBySeatNumber();  /* sort seat map by seat number       */

/* ---------- Extra function ---------- */
void countAvailableSeats();     /* COUNT available seats in array     */

/* ---------- Formatted display ---------- */
void displaySeatTable();        /* formatted seat layout table        */

/* ---------- Sub-menu ---------- */
void seatReservationsMenu();

#endif /* SEAT_RESERVATIONS_H */
