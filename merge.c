    /* PROGRAM MergeTwoDataStudent */

/* DECLARATION: */
/* all names that are used globally declared here */
#include <stdio.h>
typedef struct {
    int id;
    char name[100];
    float grade;
} Student;

void main()
{
    /* DECLARATION: */
    Student student;
    FILE *studentFile1;
    FILE *studentFile2;
    FILE *studentFile3;

    /* ALGORITHM: */
    studentFile1 = fopen("studentFile.dat", "rb");
    studentFile2 = fopen("studentFile2.dat", "rb");
    studentFile3 = fopen("studentFile3.dat", "wb");

    while (fread(&student, sizeof(student), 1, studentFile1) == 1) {
        fwrite(&student, sizeof(student), 1, studentFile3);
    }

    while (fread(&student, sizeof(student), 1, studentFile2) == 1) {
        fwrite(&student, sizeof(student), 1, studentFile3);
    }

    fclose(studentFile1);
    fclose(studentFile2);
    fclose(studentFile3);

}





