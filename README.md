# Movie Ticket Booking System

A simple command-line-based movie ticket booking system implemented in C++. It allows admins to manage theaters, screens, and movies, while users can search, book, and cancel tickets.

---

## Features Implemented

### Admin Features:
1. **Add Theater**: Add a new theater with name and location.
2. **Add Screen**: Add a new screen to a theater with:
   - Movie details (title, genre, language, duration, showtime).
   - Seat configuration (rows, columns).
   - Pricing for Silver and Gold seats.

### User Features:
1. **Register**: Register as a new user with a unique ID and name.
2. **Search Movies**: Search for movies by title, genre, language, or location.
3. **Book Ticket**: Select a movie, screen, and seat. Complete payment to confirm booking.
4. **Cancel Booking**: Cancel a booking before the show starts.

---

## Installation and Setup

1. **Prerequisites**:
   - A C++ compiler (e.g., GCC, Clang).
   - A terminal or command prompt.

2. **Steps**:
   - Clone the repository or download the source code.
   - Compile the code using a C++ compiler:
     ```bash
     g++ main.cpp -o Movie_Booking_System
     ```
   - Run the executable:
     ```bash
     ./Movie_Booking_System
     ```

---

## How to Run

1. **Admin Panel**:
   - Add theaters and screens.
   - Set seat configuration and pricing.
     
     ![Screenshot 2025-02-18 210810](https://github.com/user-attachments/assets/1c8a386b-73ce-4431-a8a7-c636af3060f2)


2. **User Panel**:
   - Register as a user.
   - View movies.
   - Search for movies.
   - Book tickets.
   - Cancel bookings if needed.
     
    ![Screenshot 2025-02-18 210754](https://github.com/user-attachments/assets/8d3156de-0f1b-474d-9223-c9316b0b379f)

    2.1. **Register**:

    ![1](https://github.com/user-attachments/assets/731cfdf9-c0c3-43c3-9348-71ae690fcae0)

    2.2. **View**:
   
    ![2](https://github.com/user-attachments/assets/24ecc2db-edbe-47d1-8053-f05ee2189528)

    2.3. **Booking**:

    ![4](https://github.com/user-attachments/assets/7320604f-9430-4167-8c01-7b5e1d960cb1)

     2.4. **Cancel**:

    ![5](https://github.com/user-attachments/assets/3ff2a6c9-81fc-4994-8c74-b0c35e5d06c5)


---

  ## Future Work
  
  1. **Concurrency Handling**:
  
     - Implement locks or transactions to handle simultaneous bookings.
  
  2. **User Authentication**:
  
     - Add a login system for User and Admin.
  
  3. **Refund Rules**:
  
     - Implement refund policies based on cancellation time.
  
  4. **Graphical Interface**:
  
     - Develop a graphical user interface (GUI) for better usability.

---


