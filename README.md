# HostelSense – Smart Hostel Fee & Room Report System

A C++ console program that works out the hostel fee for a room by its type, splits the extra AC electricity bill among the students, and saves the final report to a text file.

**Course:** Object Oriented Programming (OOP 204ES)
**Student:** Neel Parag Thakkar (ID: 25EC407), Batch A
**Lab Faculty:** Mayur Sevak
**Institute:** Birla Vishvakarma Mahavidyalaya, Vallabh Vidyanagar

---

## Problem Statement

Hostel fees depend on room type, and AC rooms also have a shared electricity bill. Doing this by hand leads to wrong amounts, the same student entered twice, and bills divided incorrectly. HostelSense automates this for one room (three students) at a time.

## Features

- Three room types with fixed fee per student:

| Choice | Room type | Fee per student |
|---|---|---|
| 1 | Attached bathroom, Non-AC | Rs. 95,000 |
| 2 | Non-attached bathroom, Non-AC | Rs. 73,000 |
| 3 | AC with attached bathroom | Rs. 1,25,000 |

- Rejects a repeated roll number within a room
- AC electricity bill = units × rate, split equally among 3 students and kept separate from the hostel fee
- Prints the report on screen and saves the same report to `HostelReport.txt`
- Input checks: invalid room type, negative or unreadable units/rate, and file-creation failure

## OOP Concepts Used

| Concept | Where |
|---|---|
| Classes and objects | `Room` and `ACRoom` objects created in `main()` |
| Inheritance | `ACRoom` publicly inherits `Room` and adds `units`, `rate`, `inputAC()`, `bill()` |
| Encapsulation | Room data and the functions that use it are kept together in the class |
| Constructor | `ACRoom()` initialises `units` and `rate` to 0 |
| Function reuse | `show(ostream&, ...)` prints to both `cout` and the file stream, so the report format is written once |
| File handling | `ofstream` writes `HostelReport.txt` |

## Classes

- **Room** (base): `roomCode`, `names[3]`, `rollNo[3]`; `input()`, `show()`
- **ACRoom** (derived): adds `units`, `rate`; `ACRoom()`, `inputAC()`, `bill()`

## How to Compile and Run

Requires any C++ compiler (g++ recommended). Uses only standard libraries: `iostream`, `fstream`, `string`.

```bash
g++ main.cpp -o hostelsense
./hostelsense        # Windows: hostelsense.exe
```

> Replace `main.cpp` with the actual name of your source file.

## Sample Run (AC room)

```
Select room type: 3
Enter room code (e.g. 4S13): 3S12
Enter student 1 name: D
Enter student 1 college roll no: 25PE307
Enter student 2 name: E
Enter student 2 college roll no: 24ME300
Enter student 3 name: F
Enter student 3 college roll no: 25EL402
Enter AC units consumed: 300
Enter rate per unit (Rs.): 1

--- HostelSense Report ---
Room: 3S12
Type: AC with Attached Bathroom

=== HOSTEL FEE ===
Student 1: D (Roll no: 25PE307)
   TOTAL HOSTEL FEE PAYABLE : Rs. 125000.00
Student 2: E (Roll no: 24ME300)
   TOTAL HOSTEL FEE PAYABLE : Rs. 125000.00
Student 3: F (Roll no: 25EL402)
   TOTAL HOSTEL FEE PAYABLE : Rs. 125000.00
Total hostel fee from this room: Rs. 375000.00

=== EXTRA ELECTRICITY BILL (paid separately) ===
Room electricity bill: Rs. 300.00
D (Roll no: 25PE307) pays: Rs. 100.00
E (Roll no: 24ME300) pays: Rs. 100.00
F (Roll no: 25EL402) pays: Rs. 100.00
Report saved successfully!
```

## Testing Summary

Seven runs covered all three room types, duplicate roll number, invalid room type, negative rate, and a decimal rate (250 units × Rs. 8.50 = Rs. 2125, share Rs. 708.33). All results matched hand calculations.

## Limitations

- One room (exactly 3 students) per run
- Duplicate roll check works only inside the same room
- Roll number format is not validated
- Each run overwrites `HostelReport.txt`
- Fee amounts are hard-coded in `main()`
- Money is stored as `double`, so shares can differ by a paisa when added up

## Future Scope

- Multiple rooms per run with hostel-wide duplicate checking
- Search by roll number
- Fine/damage charges
- Append or per-room report files
- Read fee amounts from a file
- Database or GUI version

## Documentation

The full project report (`HostelSense_Report.pdf`) includes the algorithm, flowchart, class diagram, code walkthrough, and all test outputs.
