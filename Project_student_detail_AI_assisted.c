
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define SEMESTERS 8       // Total number of semesters
#define MAX_STUDENTS 100 // Maximum number of students

// Structure to store the details of each student
typedef struct
{
    int sapID;
    int roll_no;
    char name[100];
    char phone_no[16];
    char email[50];
    int year;
    int semester;
    float sgpa[SEMESTERS]; // Stores SGPA of all 8 semesters
} Student;

// Global array to store student records
Student stu[MAX_STUDENTS];

// Keeps track of the number of students currently stored
int count = 0;


// Function declarations
void add_student_detail(void);
int findStudent(int sapid);
float getCgpa(const Student *s);
void displayStudent(const Student *s);
void searchStudent(void);
void avgCGPAyear(void);
void displayAll(void);
void deleteStudent(void);
void sortBySAP(void);
void sortByName(void);
void academicAdvisor(void);

int readInt(const char *prompt, int min, int max);
float readFloat(const char *prompt, float min, float max);
void readString(const char *prompt, char *str, int size);
int compareNames(const char *a, const char *b);


// Function to read an integer and validate its range
int readInt(const char *prompt, int min, int max)
{
    char input[100];
    char *end;
    long value;

    while (1)
    {
        printf("%s", prompt);

        // Read the complete input line
        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        // Convert the entered string into an integer
        value = strtol(input, &end, 10);

        // Ignore spaces after the number
        while (isspace((unsigned char)*end))
            end++;

        // Check whether the input is a valid integer
        if (end == input || *end != '\0')
        {
            printf("Invalid input! Please enter a valid integer.\n");
            continue;
        }

        // Check whether the integer is within the allowed range
        if (value < min || value > max)
        {
            printf("Please enter a value between %d and %d.\n",
                   min, max);
            continue;
        }

        return (int)value;
    }
}


// Function to read and validate a floating-point number
float readFloat(const char *prompt, float min, float max)
{
    char input[100];
    char *end;
    float value;

    while (1)
    {
        printf("%s", prompt);

        // Read input as a string
        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        // Convert the string into a floating-point number
        value = strtof(input, &end);

        // Ignore spaces after the number
        while (isspace((unsigned char)*end))
            end++;

        // Check for invalid input
        if (end == input || *end != '\0')
        {
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }

        // Check whether the SGPA is between the given limits
        if (value < min || value > max)
        {
            printf("Please enter a value between %.2f and %.2f.\n",
                   min, max);
            continue;
        }

        return value;
    }
}


// Function to read a string, including spaces
void readString(const char *prompt, char *str, int size)
{
    size_t len;

    while (1)
    {
        printf("%s", prompt);

        // Read the entire line of text
        if (fgets(str, size, stdin) == NULL)
            exit(0);

        len = strlen(str);

        // Remove the newline character from the end
        if (len > 0 && str[len - 1] == '\n')
        {
            str[len - 1] = '\0';
        }
        else
        {
            // Clear extra characters if the input was too long
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
        }

        // Do not allow an empty string
        if (strlen(str) == 0)
        {
            printf("This field cannot be empty. Try again.\n");
            continue;
        }

        return;
    }
}


// Function to compare two names without considering case
int compareNames(const char *a, const char *b)
{
    // Compare characters one by one
    while (*a && *b)
    {
        int charA = tolower((unsigned char)*a);
        int charB = tolower((unsigned char)*b);

        // Return the difference if characters are different
        if (charA != charB)
            return charA - charB;

        a++;
        b++;
    }

    // Compare the remaining characters
    return tolower((unsigned char)*a) -
           tolower((unsigned char)*b);
}


// Function to search for a student using SAP ID
// Returns the index if found, otherwise returns -1
int findStudent(int sapid)
{
    for (int i = 0; i < count; i++)
    {
        // Check whether the SAP ID matches
        if (stu[i].sapID == sapid)
            return i;
    }

    return -1; // Student not found
}


// Function to calculate CGPA using available SGPA values
float getCgpa(const Student *s)
{
    float total = 0.0f;
    int sem = 0;

    // Check all eight semesters
    for (int i = 0; i < SEMESTERS; i++)
    {
        // Only include SGPA values greater than zero
        if (s->sgpa[i] > 0.0f)
        {
            total += s->sgpa[i];
            sem++;
        }
    }

    // Return zero if no SGPA values are available
    if (sem == 0)
        return 0.0f;

    // Calculate average SGPA
    return total / sem;
}


// Function to add a new student's details
void add_student_detail(void)
{
    Student s;
    char prompt[100];

    // Check whether the maximum student limit is reached
    if (count >= MAX_STUDENTS)
    {
        printf("\nStudent limit reached!\n");
        return;
    }

    printf("\n====== ADD STUDENT DETAILS ======\n");

    // Enter SAP ID
    s.sapID = readInt("Enter SAP ID: ", 1, INT_MAX);

    // Check for duplicate SAP ID
    if (findStudent(s.sapID) != -1)
    {
        printf("\nSAP ID already exists!\n");
        return;
    }

    // Enter basic student details
    s.roll_no = readInt("Enter Roll Number: ", 1, INT_MAX);

    readString("Enter Name: ", s.name, sizeof(s.name));

    readString("Enter Phone Number: ",
               s.phone_no, sizeof(s.phone_no));

    readString("Enter Email ID: ",
               s.email, sizeof(s.email));

    // Enter year of study
    s.year = readInt("Enter Year (1-4): ", 1, 4);

    // Calculate the valid semester range for the selected year
    int minSemester = (s.year - 1) * 2 + 1;
    int maxSemester = s.year * 2;

    sprintf(prompt, "Enter Current Semester (%d-%d): ",
            minSemester, maxSemester);

    s.semester = readInt(prompt, minSemester, maxSemester);

    // Enter SGPA values for all eight semesters
    printf("\n====== ENTER SGPA DETAILS ======\n");
    printf("Enter 0 if SGPA is not available for a semester.\n");

    for (int i = 0; i < SEMESTERS; i++)
    {
        sprintf(prompt, "Enter SGPA for Semester %d (0-10): ", i + 1);

        // Accept SGPA only between 0 and 10
        s.sgpa[i] = readFloat(prompt, 0.0f, 10.0f);
    }

    // Store the new student in the global array
    stu[count] = s;

    // Increase the student count
    count++;

    printf("\nStudent record added successfully!\n");
}


// Function to display the details of one student
void displayStudent(const Student *s)
{
    // Calculate the student's CGPA
    float cgpa = getCgpa(s);

    printf("\n====================================\n");

    // Display personal and academic details
    printf("SAP ID:             %d\n", s->sapID);
    printf("Roll Number:        %d\n", s->roll_no);
    printf("Name:               %s\n", s->name);
    printf("Phone Number:       %s\n", s->phone_no);
    printf("Email ID:           %s\n", s->email);
    printf("Year:               %d\n", s->year);
    printf("Current Semester:   %d\n", s->semester);

    // Display SGPA for all semesters
    printf("\nSGPA DETAILS\n");

    for (int i = 0; i < SEMESTERS; i++)
    {
        if (s->sgpa[i] > 0.0f)
            printf("Semester %d: %.2f\n", i + 1, s->sgpa[i]);
        else
            printf("Semester %d: Not Available\n", i + 1);
    }

    // Display CGPA if at least one SGPA is available
    if (cgpa > 0.0f)
        printf("\nCGPA: %.2f\n", cgpa);
    else
        printf("\nCGPA: Not Available\n");

    printf("====================================\n");
}


// Function to search and display a student by SAP ID
void searchStudent(void)
{
    int sapid;
    int index;

    printf("\n====== SEARCH STUDENT ======\n");

    // Ask the user for the SAP ID
    sapid = readInt("Enter SAP ID to search: ", 1, INT_MAX);

    // Find the student's position in the array
    index = findStudent(sapid);

    if (index == -1)
    {
        printf("\nStudent record not found!\n");
    }
    else
    {
        printf("\nStudent record found!\n");

        // Display the matching student's details
        displayStudent(&stu[index]);
    }
}


// Function to calculate average CGPA for each academic year
void avgCGPAyear(void)
{
    float total;
    float cgpa;
    int studentcount;

    // Check whether any student records exist
    if (count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n====== AVERAGE CGPA BY YEAR ======\n");

    // Calculate the average separately for each year
    for (int year = 1; year <= 4; year++)
    {
        total = 0.0f;
        studentcount = 0;

        // Check all student records
        for (int i = 0; i < count; i++)
        {
            if (stu[i].year == year)
            {
                cgpa = getCgpa(&stu[i]);

                // Include only students with available CGPA
                if (cgpa > 0.0f)
                {
                    total += cgpa;
                    studentcount++;
                }
            }
        }

        printf("Year %d: ", year);

        // Calculate and display the average CGPA
        if (studentcount > 0)
        {
            printf("Average CGPA = %.2f\n",
                   total / studentcount);
        }
        else
        {
            printf("No CGPA data available.\n");
        }
    }
}


// Function to display all stored student records
void displayAll(void)
{
    // Check whether the array is empty
    if (count == 0)
    {
        printf("\nNo student records available!\n");
        return;
    }

    printf("\n====== ALL STUDENT RECORDS ======\n");

    // Display every student using displayStudent()
    for (int i = 0; i < count; i++)
    {
        displayStudent(&stu[i]);
    }
}


// Function to delete a student record using SAP ID
void deleteStudent(void)
{
    int sapid;
    int index;

    // Check whether any records exist
    if (count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n====== DELETE STUDENT ======\n");

    // Enter SAP ID of the student to delete
    sapid = readInt("Enter SAP ID to delete: ", 1, INT_MAX);

    // Find the student's array position
    index = findStudent(sapid);

    if (index == -1)
    {
        printf("\nStudent record not found!\n");
        return;
    }

    // Shift all records after the deleted student one position left
    for (int i = index; i < count - 1; i++)
    {
        stu[i] = stu[i + 1];
    }

    // Decrease the total number of students
    count--;

    printf("\nStudent record deleted successfully!\n");
}


// Function to sort student records in ascending SAP ID order
void sortBySAP(void)
{
    Student temp;

    // Check whether records exist
    if (count == 0)
    {
        printf("\nNo records available!\n");
        return;
    }

    // Compare SAP IDs and swap records when necessary
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (stu[j].sapID < stu[i].sapID)
            {
                // Swap the complete student structures
                temp = stu[i];
                stu[i] = stu[j];
                stu[j] = temp;
            }
        }
    }

    printf("\nRecords sorted by increasing SAP ID.\n");

    // Display the sorted records
    displayAll();
}


// Function to sort student records alphabetically by name
void sortByName(void)
{
    Student temp;

    // Check whether records exist
    if (count == 0)
    {
        printf("\nNo records available!\n");
        return;
    }

    // Compare student names and swap records
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            // strcmp-style comparison, ignoring uppercase/lowercase
            if (compareNames(stu[j].name, stu[i].name) < 0)
            {
                // Swap the complete student structures
                temp = stu[i];
                stu[i] = stu[j];
                stu[j] = temp;
            }
        }
    }

    printf("\nRecords sorted by increasing Name.\n");

    // Display the sorted records
    displayAll();
}


// AI-ASSISTED ACADEMIC ADVISOR
// Generates academic recommendations based on the student's CGPA
void academicAdvisor(void)
{
    int sapid;
    int index;
    float cgpa;

    // Check whether any student records exist
    if (count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n====== AI-ASSISTED ACADEMIC ADVISOR ======\n");

    // Ask for the student's SAP ID
    sapid = readInt("Enter SAP ID: ", 1, INT_MAX);

    // Search for the student
    index = findStudent(sapid);

    if (index == -1)
    {
        printf("\nStudent record not found!\n");
        return;
    }

    // Calculate the student's CGPA
    cgpa = getCgpa(&stu[index]);

    printf("\nStudent Name: %s\n", stu[index].name);

    // Check whether SGPA data is available
    if (cgpa == 0.0f)
    {
        printf("CGPA: Not Available\n");
        printf("Advice cannot be generated because no SGPA data is available.\n");
        return;
    }

    printf("CGPA: %.2f\n", cgpa);

    // Give advice according to the CGPA range
    if (cgpa >= 9.0f)
    {
        // CGPA from 9.0 to 10.0
        printf("\nCategory: Excellent Performance\n");
        printf("Advice: Maintain your current study pattern.\n");
    }
    else if (cgpa >= 7.5f)
    {
        // CGPA from 7.5 to below 9.0
        printf("\nCategory: Good Performance\n");
        printf("Advice: Keep working consistently and aim for higher grades.\n");
    }
    else if (cgpa >= 6.0f)
    {
        // CGPA from 6.0 to below 7.5
        printf("\nCategory: Needs Improvement\n");
        printf("Advice: Focus more on subjects with lower SGPA.\n");
    }
    else
    {
        // CGPA below 6.0
        printf("\nCategory: Requires Immediate Attention\n");
        printf("Advice: Improve your study routine and seek academic guidance.\n");
    }

    // Explain that recommendations are generated by predefined C rules
    printf("\nNote: This recommendation is generated using predefined rules.\n");
}


// Main function: Displays the menu and controls the program
int main(void)
{
    int choice;

    // Repeat the menu until the user selects Exit
    do
    {
        printf("\n========================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        // Display all available operations
        printf("1. Add Student Details\n");
        printf("2. Search Student\n");
        printf("3. Display All Students\n");
        printf("4. Average CGPA by Year\n");
        printf("5. Delete Student\n");
        printf("6. Sort Records by SAP ID\n");
        printf("7. Sort Records by Name\n");
        printf("8. AI-Assisted Academic Advisor\n");
        printf("9. Exit\n");

        printf("========================================\n");

        // Read the user's menu choice
        choice = readInt("Enter your choice: ", 1, 9);

        // Execute the selected operation
        switch (choice)
        {
            case 1:
                add_student_detail();
                break;

            case 2:
                searchStudent();
                break;

            case 3:
                displayAll();
                break;

            case 4:
                avgCGPAyear();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                sortBySAP();
                break;

            case 7:
                sortByName();
                break;

            case 8:
                academicAdvisor();
                break;

            case 9:
                printf("\nExiting program. Thank you!\n");
                break;
        }

    } while (choice != 9);

    return 0; // End the program successfully
}
