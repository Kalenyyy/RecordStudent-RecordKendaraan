/* PROGRAM ReadStudentArchive */

/* DECLARATION: */
/* all names that are used globally declared here */
#include <stdio.h>
typedef struct {
    int id;
    char name[100];
    float grade;
} Student;

void printAllStudents();
void countGraduates(FILE *stdFile, int *nOver2);
void printGraduates();

void main()
{
    /* DECLARATION: */
    Student student;
    FILE *studentFile;
    int countStudentGraduates;


    /* ALGORITHM: */
    printAllStudents();
    countGraduates(studentFile, &countStudentGraduates);
    printf("Student who Graduates : %d \n", countStudentGraduates);
    printGraduates();



}

void printAllStudents() {
    FILE *studentFile;
    Student student;

    studentFile = fopen("studentFile.dat", "rb");

    printf("\n--- Data Mahasiswa dari File ---\n");

    while (fread(&student, sizeof(student), 1, studentFile) == 1)
    {

        printf("ID: %d, Nama: %s, Nilai: %.2f\n",
               student.id, student.name, student.grade);
    }

    fclose(studentFile);
    printf("-------------------------------------------\n\n");
}

void countGraduates(FILE *stdFile, int *nOver2) {
    Student student;

    *nOver2 = 0;
    stdFile = fopen("studentFile.dat", "rb");
    while (fread(&student, sizeof(student), 1, stdFile) == 1) {
        if (student.grade > 70) {
            *nOver2 = *nOver2 + 1;
        }
    }
}

void printGraduates() {
    FILE *studentFile;
    Student student;

    studentFile = fopen("studentFile.dat", "rb");

    // Baca dan cek setiap record
    while (fread(&student, sizeof(student), 1, studentFile) == 1) {
        if (student.grade > 70) {
            printf("ID: %d, Nama: %s, Nilai: %.2f\n",
                   student.id, student.name, student.grade);
        }
    }

    fclose(studentFile);
}



