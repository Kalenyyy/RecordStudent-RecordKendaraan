/* PROGRAM CreateStudentArchive */

/* DECLARATION: */
/* all names that are used globally declared here */
#include <stdio.h>

typedef struct {
    int id;
    char name[100];
    float grade;
} Student;

void main() {
    /* DECLARATION: */
    Student student;
    FILE *studentFile;


    /* ALGORITHM: */
    studentFile = fopen("studentFile.dat", "wb");
    printf("input Student ID : ");
    scanf("%d", &student.id);

    while (student.id != 9999) {
        printf("Name : ");
        scanf("%s", student.name);
        printf("Grade : ");
        scanf("%f", &student.grade);

        fwrite(&student, sizeof(student), 1, studentFile);
        printf("input Student Id (9999 to Stop): ");
        scanf("%d", &student.id);
    }
    fclose(studentFile);
}
