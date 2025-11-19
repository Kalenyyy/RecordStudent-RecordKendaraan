    /* PROGRAM CopyStudentData */

/* DECLARATION: */
/* all names that are used globally declared here */
#include <stdio.h>
typedef struct {
    int id;
    char name[100];
    float grade;
} Student;

void copyStudentData(FILE *studentFile1, FILE *studentFile2);

void main()
{
    /* DECLARATION: */
    FILE *studentFile1;
    FILE *studentFile2;

    /* ALGORITHM: */
    copyStudentData(studentFile1, studentFile2);
    printf("\n Copy File Success");

}

void copyStudentData(FILE *studentFile1, FILE *studentFile2) {
    /* DECLARATION: */
    Student student;

    /* ALGORITHM: */
    studentFile1 = fopen("studentFile.dat", "rb");
    studentFile2 = fopen("studentFile2.dat", "wb");

    while (fread(&student, sizeof(student), 1, studentFile1) == 1) {
        fwrite(&student, sizeof(student), 1, studentFile2);
    }
    fclose(studentFile1);
    fclose(studentFile2);

}



