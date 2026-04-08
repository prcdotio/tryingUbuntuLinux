#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int initialize_database(void);
struct students{
    int id;
    float gpa;
    char *name;
};
int count_students(void);
struct students *create_storage(int *size);
struct students *load_data(struct students *storage, int *size);
void trim_name(struct students *storage, int size);
void print_data(struct students *storage, int *size);
struct students *add_new_students(struct students *storage, int *size);
struct students *edit_by_id(struct students *storage, int *size);
struct students *delete_by_id(struct students *storage, int *size);
void free_memory(struct students *storage, int *size);
int main()
{
    if(!initialize_database()){
        return 1;
    }
    int choice;
    int total_students = count_students();
    struct students *storage = create_storage(&total_students);
    if(total_students > 0){
         load_data(storage, &total_students);
    }
    while(1){
        printf("================STUDENT'S DATABASE===============\n");
        printf("1. View All Students\n");
        printf("2. Add New Student\n");
        printf("3. Edit Student (by ID)\n");
        printf("4. Delete Student (by ID)\n");
        printf("5. Exit\n");
        printf("=================================================\n");
        if(scanf("%d", &choice) != 1){
            printf("Invalid input. Please enter a valid input.\n");
            while(getchar() != '\n')
                ;
            continue;
        }
        if(choice == 5){
            break;
        }
        switch(choice){
            case 1:
                print_data(storage, &total_students);
                break;
                case 2:
                    storage = add_new_students(storage, &total_students);
                    break;
                    case 3:
                        storage = edit_by_id(storage, &total_students);
                        break;
                        case 4:
                            storage = delete_by_id(storage, &total_students);
                            break;
                            default:
                                printf("Invalid choice. Try Again!\n");
                        }
    }
    free_memory(storage, &total_students);
    storage = NULL;
    printf("Good Bye!\n");
    return 0;
}
int initialize_database(void){
    FILE *fptr = fopen("students_details.txt", "r");
    if(fptr != NULL){
        fclose(fptr);
        return 1;
    }
    char choice;
    printf("Warning: 'students_details.txt' not found.\n");
    printf("Do you wanna create new one? (y/n):\t");
    scanf(" %c", &choice);
    if(choice == 'y' || choice == 'Y'){
        FILE *fptr = fopen("students_details.txt", "w");
        if(fptr == NULL){
            printf("Error: Could not create file. Check permissions.\n");
            return 0;
        }
        fprintf(fptr, " %-10s | %-10s | %-20s | %s\n", "S.No.", "ID", "Name", "GPA");
        fprintf(fptr, "_________________________________________________________\n");
        fclose(fptr);
        printf("New database created successfully.\n");
        return 1;
    }else{
        printf("Exitting Program...\n");
        return 0;
    }
}
int count_students(void){
    FILE *fptr = fopen("students_details.txt", "r");
    if(fptr == NULL){
        printf("Unable to read file.\n");
        return 0;
    }
    char junk[256];
    fgets(junk, sizeof(junk), fptr);
    fgets(junk, sizeof(junk), fptr);
    int count = 0;
    while(fgets(junk, sizeof(junk), fptr)){
        if(strlen(junk) > 0){
            count++;
        }
    }
    fclose(fptr);
    return count;
}
struct students *create_storage(int *size){
    struct students *storage = (struct students *)malloc(*size * sizeof(struct students));
    if(storage == NULL){
        printf("Memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < *size; ++i){
        (storage + i)->name = (char *)malloc(50 * sizeof(char));
        if((storage + i)->name == NULL){
            for (int k = 0; k < i; ++k){
                free((storage + k)->name);
            }
            free(storage);
            return NULL;
        }
    }
    return storage;
}
struct students *load_data(struct students *storage, int *size){
    FILE *fptr = fopen("students_details.txt", "r");
    if(fptr == NULL){
        printf("Unable to read file.\n");
        return NULL;
    }
    char junk[256];
    fgets(junk, sizeof(junk), fptr);
    fgets(junk, sizeof(junk), fptr);
    for (int i = 0; i < *size; ++i)
    {
        int sn;
        fscanf(fptr, "%d | %d | %[^|] | %f\n", &sn, &(storage + i)->id, (storage + i)->name, &(storage + i)->gpa);
    }
    trim_name(storage, *size);
}
void trim_name(struct students *storage, int size){
    for (int i = 0; i < size; ++i){
        int len = strlen((storage + i)->name);
        while(len > 0 && ((storage + i)->name[len - 1] == ' ' || (storage + i)->name[len - 1] == '\t')){
            (storage + i)->name[len - 1] = '\0';
            len--;
        }
        int start = 0;
        while((storage + i)->name[start] == ' ' || (storage + i)->name[start] == '\t'){
            start++;
        }
        if(start > 0){
            memmove((storage + i)->name, (storage + i)->name + start, strlen((storage + i)->name + start) + 1);
        }
    }
}
void print_data(struct students *storage, int *size){
    printf("%-10s | %-10s | %-20s | %s\n", "S.No.", "ID", "Name", "GPA");
    printf("________________________________________________\n");
    for (int i = 0; i < *size; ++i)
    {
        printf("%-10d | %-10d | %-20s | %.2f\n", i + 1, (storage + i)->id, (storage + i)->name, (storage + i)->gpa);
    }
}
struct students *add_new_students(struct students *storage, int *size) {
    char track_add;
    printf("Do you wanna add student? [y/n]:\t");
    scanf(" %c", &track_add);

    while (track_add == 'y' || track_add == 'Y') {
        struct students *temp = realloc(storage, (*size + 1) * sizeof(struct students));
        
        if (temp == NULL) {
            printf("Critical Error: Memory allocation failed! Cannot add more students.\n");
            return storage; 
        }
        storage = temp;
        storage[*size].name = (char *)malloc(50 * sizeof(char));
        if (storage[*size].name == NULL) return storage;
        printf("ID:\t");
        scanf("%d", &storage[*size].id);
        getchar();
        printf("Name:\t");
        fgets(storage[*size].name, 50, stdin);
        storage[*size].name[strcspn(storage[*size].name, "\n")] = '\0';
        printf("GPA:\t");
        scanf("%f", &storage[*size].gpa);
        FILE *fptr = fopen("students_details.txt", "a");
        if (fptr != NULL) {
            fprintf(fptr, "%-10d | %-10d | %-20s | %.2f\n", *size + 1, storage[*size].id, storage[*size].name, storage[*size].gpa);
            fclose(fptr);
        }
        (*size)++;
        printf("Student added to RAM and File. Add another? [y/n]:\t");
        scanf(" %c", &track_add);
    }
    return storage;
}
struct students *edit_by_id(struct students *storage, int *size){
    int search_id;
    printf("Enter the id you wanna update:\t");
    scanf("%d", &search_id);
    int found = 0;
    for (int i = 0; i < *size; ++i){
        if(search_id == (storage + i)->id){
            found = 1;
            printf("ID:\t");
            scanf("%d", &(storage + i)->id);
            getchar();
            printf("Name:\t");
            fgets((storage + i)->name, 50, stdin);
            (storage + i)->name[strcspn((storage + i)->name, "\n")] = '\0';
            printf("GPA:\t");
            scanf("%f", &(storage + i)->gpa);
            break;
        }
    }
    if(found == 0){
        printf("Data with ID:%d not found on database. Exitting...\n", search_id);
        return storage;
    }
    FILE *fptr = fopen("students_details.txt", "w");
    if(fptr == NULL){
        return NULL;
    }
    fprintf(fptr, " %-10s | %-10s | %-20s | %s\n", "S.No.", "ID", "Name", "GPA");
    fprintf(fptr, "________________________________________________________\n");
    for (int i = 0; i < *size; ++i)
    {
        fprintf(fptr, "%-10d | %-10d | %-20s | %.2f\n", i + 1, (storage + i)->id, (storage + i)->name, (storage + i)->gpa);
    }
    fclose(fptr);
    return storage;
}
struct students *delete_by_id(struct students *storage, int *size){
    int search_id;
    printf("Enter the ID of the students you wanna delete from system:\t");
    scanf("%d", &search_id);
    int found_index = -1;
    for (int i = 0; i < *size; ++i){
        if(search_id == (storage + i)->id){
            found_index = i;
            break;
        }
    }
    if(found_index == -1){
        printf("Data having ID: %d doesn't exist on database. Exitting...\n", search_id);
        return storage;
    }
    free((storage + found_index)->name);
    for (int i = found_index; i < *size - 1; ++i){
        storage[i] = storage[i + 1];
    }
    (*size)--;
    FILE *fptr = fopen("students_details.txt", "w");
    if(fptr == NULL){
        return NULL;
    }
    fprintf(fptr, "%-10s | %-10s | %-20s | %s\n", "S.No.", "ID", "Name", "GPA");
    fprintf(fptr, "_____________________________________________________________\n");
    for (int i = 0; i < *size; ++i){
        fprintf(fptr, "%-10d | %-10d | %-20s | %.2f\n", i + 1, (storage + i)->id, (storage + i)->name, (storage + i)->gpa);
    }
    fclose(fptr);
    printf("Data having ID:%d deleted successfully.\n", search_id);
    return storage;
}
void free_memory(struct students *storage, int *size){
    for (int i = 0; i < *size; ++i){
        free((storage + i)->name);
    }
    free(storage);
}