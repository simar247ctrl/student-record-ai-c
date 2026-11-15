# Student Record Management System

A menu-driven console application developed in **C** to manage student academic records. The program allows users to add, search, display, update academic information through the available operations, delete records, sort students, and view CGPA-based academic advice.

## Features

- Add student records with SAP ID, roll number, name, phone number, email, year, semester, and SGPA details.
- Search for a student using SAP ID.
- Display an individual student's details.
- Display all stored student records.
- Calculate CGPA using the available SGPA values.
- Calculate the average CGPA for a selected academic year.
- Delete a student record using SAP ID.
- Sort student records by SAP ID in ascending order.
- Sort student records alphabetically by name.
- Provide CGPA-based academic recommendations through an AI-Assisted Academic Advisor feature.

## Academic Advisor

The advisor uses local C `if-else` conditions to show a recommendation based on a student's CGPA. It does not connect to an online AI service or require an API key.

| CGPA range | Category |
|---|---|
| 9.00–10.00 | Excellent Performance |
| 7.50–8.99 | Good Performance |
| 6.00–7.49 | Needs Improvement |
| Greater than 0 and below 6.00 | Requires Immediate Attention |

These ranges are project-defined guidance and may be adjusted to match institutional rules.

## Technologies Used

- C programming language
- Standard C libraries
- Structures, arrays, functions, loops, and conditional statements
- Console-based input and output

## Project Structure

```text
Student-Record-Management-System/
├── student_record_management_system.c
├── AI_Usage_Log_Student_Record_Management_System.md
└── tests/
    ├── README.md
    ├── sample_input.txt
    └── expected_output.txt
```

## Requirements

- GCC compiler (MinGW GCC on Windows, or GCC on Linux/macOS)
- A terminal or command prompt

## How to Compile and Run

### Windows (MinGW)

Open Command Prompt in the project folder and run:

```cmd
gcc student_record_management_system.c -o Student_Record.exe
Student_Record.exe
```

### Linux / macOS

```bash
gcc student_record_management_system.c -o Student_Record
./Student_Record
```

## Sample Tests

The `tests` folder contains:

- `sample_input.txt` — sample menu selections and student details to enter into the program.
- `expected_output.txt` — important expected results, including academic advisor categories.
- `README.md` — instructions for running the sample test.

On Windows Command Prompt, run the sample input with:

```cmd
Student_Record.exe < tests\sample_input.txt
```

On Linux/macOS, run:

```bash
./Student_Record < tests/sample_input.txt
```

Compare the key results with `tests/expected_output.txt`. Exact menu prompts and formatting may vary.

## Data Storage Note

Student records are stored in an array while the program is running. They are not saved permanently, so the records are lost when the program exits. File handling can be added in a future version to provide permanent storage.

## AI Usage

ChatGPT was used as an assistance tool during development to review code, explain CGPA calculation logic, suggest academic-advisor categories, and help document the program. Suggestions were reviewed and adapted before inclusion.

Refer to `AI_Usage_Log_Student_Record_Management_System.md` for the prompts and ideas used.

## Author
Harsimar Singh 

---

**Note:** This project is intended for learning and demonstration of basic C programming concepts.
