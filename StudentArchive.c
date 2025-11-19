/* PROGRAM CreateStudentArchive */

/* DECLARATION: */
/* all names that are used globally declared here */
#include <stdio.h>

typedef struct {
    int id;
    char name[100];
    float grade;
} Student;

typedef Student StudentArr[100 + 1];

void addFiletoArray(FILE *studentFile, StudentArr students, int *n);
void printArrayStudent(StudentArr students, int n, float *mean);

int main() {
    /* DECLARATION: */
    Student student;
    FILE *studentFile;
    StudentArr students;
    int n;
    float mean;

    /* ALGORITHM: */
    studentFile = fopen("studentFile.dat", "wb");
    printf("input Student ID : ");
    scanf("%d", &student.id);

    while (student.id != 9999) {
        printf("Name : ");
        scanf(" %[^\n]", student.name);
        printf("Grade : ");
        scanf("%f", &student.grade);

        fwrite(&student, sizeof(student), 1, studentFile);
        printf("input Student Id (9999 to Stop): ");
        scanf("%d", &student.id);
    }
    fclose(studentFile);

    addFiletoArray(studentFile, students, &n);
    printArrayStudent(students, n, &mean);

    printf("-- Hitung Rata-rata Grade Mahasiswa -- \n");
    printf("Rata-rata Grade %d Mahasiswa adalah : %.2f", n, mean);
}

void addFiletoArray(FILE *studentFile, StudentArr students, int *n) {
    studentFile = fopen("studentFile.dat", "rb");
    Student student;
    int i = 0;

    while (fread(&student, sizeof(student), 1, studentFile) == 1) {
        i = i + 1;
        students[i] = student;
    }
    fclose(studentFile);
    *n = i;
}

void printArrayStudent(StudentArr students, int n, float *mean) {
    float total = 0;

    printf("-- Lihat Data Mahasiswa -- \n\n");
    for (int i = 1; i <= n; i++) {
        printf("ID: %d \n", students[i].id);
        printf("Nama : %s\n", students[i].name);
        printf("Grade: %.2f\n\n", students[i].grade);

        total = total + students[i].grade;
    }
    *mean = total / n;
}


