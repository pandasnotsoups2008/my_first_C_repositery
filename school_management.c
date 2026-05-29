#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TEACHERS 50
#define MAX_STUDENTS 100
#define NAME_SIZE 50

typedef struct {
    char name[NAME_SIZE];
    int salary;
} Teacher;

typedef struct {
    int id;
    char name[NAME_SIZE];
    float grade_x;
    float grade_y;
} Student;

static void clear_input_buffer(void) {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static void read_line(char text[], int size) {
    if (fgets(text, size, stdin) == NULL) {
        text[0] = '\0';
        return;
    }

    text[strcspn(text, "\n")] = '\0';
}

static int get_random_salary(void) {
    return 30000 + rand() % 70001;
}

static int find_student_by_id(Student students[], int student_count, int id) {
    int i;

    for (i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }

    return -1;
}

static void add_teacher(Teacher teachers[], int *teacher_count) {
    if (*teacher_count >= MAX_TEACHERS) {
        printf("Teacher list is full.\n");
        return;
    }

    printf("Enter teacher name: ");
    read_line(teachers[*teacher_count].name, NAME_SIZE);
    teachers[*teacher_count].salary = get_random_salary();

    printf("Teacher added with random salary: Rs. %d\n",
           teachers[*teacher_count].salary);
    (*teacher_count)++;
}

static void add_student(Student students[], int *student_count) {
    int id;

    if (*student_count >= MAX_STUDENTS) {
        printf("Student list is full.\n");
        return;
    }

    printf("Enter unique student ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (find_student_by_id(students, *student_count, id) != -1) {
        printf("A student with ID %d already exists.\n", id);
        return;
    }

    students[*student_count].id = id;

    printf("Enter student name: ");
    read_line(students[*student_count].name, NAME_SIZE);

    printf("Enter grade X: ");
    if (scanf("%f", &students[*student_count].grade_x) != 1) {
        printf("Invalid grade.\n");
        clear_input_buffer();
        return;
    }

    printf("Enter grade Y: ");
    if (scanf("%f", &students[*student_count].grade_y) != 1) {
        printf("Invalid grade.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Student added successfully.\n");
    (*student_count)++;
}

static void list_teachers(Teacher teachers[], int teacher_count) {
    int i;

    if (teacher_count == 0) {
        printf("No teachers available.\n");
        return;
    }

    printf("\n%-5s %-30s %-12s\n", "No.", "Teacher Name", "Salary");
    printf("--------------------------------------------------\n");

    for (i = 0; i < teacher_count; i++) {
        printf("%-5d %-30s Rs. %-8d\n",
               i + 1,
               teachers[i].name,
               teachers[i].salary);
    }
}

static void list_students(Student students[], int student_count) {
    int i;

    if (student_count == 0) {
        printf("No students available.\n");
        return;
    }

    printf("\n%-8s %-30s %-10s %-10s %-10s\n",
           "ID", "Student Name", "Grade X", "Grade Y", "Average");
    printf("---------------------------------------------------------------------\n");

    for (i = 0; i < student_count; i++) {
        float average = (students[i].grade_x + students[i].grade_y) / 2.0f;

        printf("%-8d %-30s %-10.2f %-10.2f %-10.2f\n",
               students[i].id,
               students[i].name,
               students[i].grade_x,
               students[i].grade_y,
               average);
    }
}

static void search_student(Student students[], int student_count) {
    int id;
    int index;

    printf("Enter student ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    index = find_student_by_id(students, student_count, id);

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("\nStudent found:\n");
    printf("ID: %d\n", students[index].id);
    printf("Name: %s\n", students[index].name);
    printf("Grade X: %.2f\n", students[index].grade_x);
    printf("Grade Y: %.2f\n", students[index].grade_y);
    printf("Average: %.2f\n",
           (students[index].grade_x + students[index].grade_y) / 2.0f);
}

static void show_menu(void) {
    printf("\n===== School Management System =====\n");
    printf("1. Add teacher\n");
    printf("2. Add student\n");
    printf("3. List teachers\n");
    printf("4. List students\n");
    printf("5. Search student by ID\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

int main(void) {
    Teacher teachers[MAX_TEACHERS];
    Student students[MAX_STUDENTS];
    int teacher_count = 0;
    int student_count = 0;
    int choice;

    srand((unsigned int)time(NULL));

    do {
        show_menu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                add_teacher(teachers, &teacher_count);
                break;
            case 2:
                add_student(students, &student_count);
                break;
            case 3:
                list_teachers(teachers, teacher_count);
                break;
            case 4:
                list_students(students, student_count);
                break;
            case 5:
                search_student(students, student_count);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Please choose a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
