Hostel Mess Management System
A command-line Object-Oriented Programming (OOP) project built in C++ to manage hostel mess operations. This system provides a dual-role interface for Students and Mess Authorities to streamline meal scheduling, attendance tracking, billing, and food waste management.

Features
Mess Authority (Admin) Controls:

Menu Management: Add, update, and remove meals across a weekly 7-day schedule. Adjust food items, prices, and prepared quantities dynamically.

Student Roster: Register new students, remove users, and view the active/inactive status and pending dues of the entire hostel.

Analytics & Reports: Generate automated food waste reports comparing plates prepared vs. consumed, and financial reports tracking total outstanding dues.

Feedback System: View anonymous or named ratings and text feedback submitted by students.

Student Controls:

Meal Attendance: View the weekly menu and mark attendance for specific meals. The system checks availability (stock) before confirming the meal.

Automated Billing: Automatically adds the exact meal price to the student's pending dues upon marking attendance. Features a bill payment gateway to clear outstanding balances.

Membership Toggles: Students can pause (deactivate) their account during holidays to avoid charges, or permanently revoke their membership (requires clearing all dues first).

Project Structure
This project follows a standard C++ multi-file architecture to separate declarations from logical definitions and prevent circular dependencies:

main.cpp - Contains the main execution loop and dual-role menu interface.

MessAuthority.h / .cpp - Manages the global menu, student vectors, and administrative reports.

student.h / .cpp - Handles individual student data, billing, attendance, and membership status.

menu.h / .cpp - Organizes the 7-day weekly schedule and stores meal vectors.

meal.h / .cpp - Defines individual meal properties (items, price, stock quantity).

utils.h / .cpp - Contains shared helper functions like readInt() for robust input validation.

Prerequisites:

A C++ compiler (GCC/MinGW for Windows, Clang for macOS, or standard Linux GCC).

Git Bash or any standard terminal.

Visual Studio Code (or preferred IDE).
