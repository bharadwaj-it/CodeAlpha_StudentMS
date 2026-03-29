#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student 
{
    int id;
    char name[50];
    float marks;
};
void addStudent() 
{
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}
void displayStudents() 
{
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(s), 1, fp))
    printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
    fclose(fp);
}

void searchStudent() 
{
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    int id, found = 0;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) 
    {
        if (s.id == id) 
        {
            printf("Found: ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found)
    printf("Student not found!\n");
    fclose(fp);
}
void updateStudent() 
{
    FILE *fp = fopen("students.dat", "rb+");
    struct Student s;
    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) 
    {
        if (s.id == id) 
        {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);
            fseek(fp, -(long)sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            printf("Record updated!\n");
            found = 1;
            break;
        }
    }
    if (!found)
    printf("Student not found!\n");
    fclose(fp);
}

void deleteStudent() 
{
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Student s;
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) 
    {
        if (s.id != id)
        fwrite(&s, sizeof(s), 1, temp);
        else
        found = 1;
    }
    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");
    if (found)
    printf("Record deleted successfully!\n");
    else
    printf("Student not found!\n");
}
int main() 
{
    int choice;
    while (1) 
    {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}