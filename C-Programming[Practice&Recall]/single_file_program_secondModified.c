#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct students {
    int id;
    float gpa;
    char *name;
};
int initialize_database(void);
void save_to_file(struct students *storage, int size);
int count_students(void);
struct students *create_storage(int *size);
struct students *load_data(struct students *storage, int *size);
void trim_name(struct students *storage, int *size);
void print_data(struct students *storage, int *size);
struct students *add_more_students(struct students *storage, int *size);
struct students *edit_by_id(struct students *storage, int *size);
struct students *delete_by_id(struct students *storage, int *size);
void free_memory(struct students *storage, int *size);
int main(void)
{
    if(!(initialize_database())){
        return 1;
    }
    int total_students = count_students();
    struct students *storage = create_storage(&total_students);
    if(total_students > 0){
        load_data(storage, &total_students);
    }
    int choice;
    while(1){
        printf("==============STUDENT'S DATABASE==============\n");
        printf("===================ACTIONS====================\n");
        printf("1. View all students\n");
        printf("2. Add new students\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");
        printf("===============================================\n");
        if(scanf("%d", &choice) != 1){
            printf("Invalid input. Try Again!\n");
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
                  storage = add_more_students(storage, &total_students);
                    break;
                    case 3:
                     storage = edit_by_id(storage, &total_students);
                        break;
                        case 4:
                          storage = delete_by_id(storage, &total_students);
                            break;
                            default:
                                printf("Invalid input. Try Again!\n");
                                break;
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
        return 1;
    }
    char choice;
    printf("File is empty or missing. Do you wanna create new one? [Y/N]:\t");
    scanf(" %c", &choice);
    if(choice == 'Y' || choice == 'y'){
        FILE *fptr = fopen("students_details.txt", "w");
        if(fptr == NULL){
            printf("File creation failed. Check for permissions.\n");
            return 0;
        }
        printf("File created successfully.\n");
        save_to_file(NULL, 0);
        fclose(fptr);
        return 1;
    }
    return 0;
}
void save_to_file(struct students *storage, int size){
    FILE *fptr = fopen("students_details.txt", "w");
    if(fptr == NULL){
        return;
    }
    fprintf(fptr, "%-10s | %-10s | %-20s | %s\n", "S.No.", "ID", "Name", "GPA");
    fprintf(fptr, "___________________________________________________________\n");
    if(storage != NULL && size > 0){
        for (int i = 0; i < size; ++i){
            fprintf(fptr, "%-10d | %-10d | %-20s | %.2f\n", i + 1, (storage + i)->id, (storage + i)->name, (storage + i)->gpa);
        }
    }
    fclose(fptr);
}
int count_students(void){
    FILE *fptr = fopen("students_details.txt", "r");
    if(fptr == NULL){
        return 0;
    }
    char junk[256];
    fgets(junk, sizeof(junk), fptr);
    fgets(junk, sizeof(junk), fptr);
    int count = 0;
    while(fgets(junk, sizeof(junk), fptr)){
        if(strlen(junk) > 10){
            count++;
        }
    }
    fclose(fptr);
    return count;
}
struct students *create_storage(int *size){
    struct students *storage = (struct students *)malloc(*size * sizeof(struct students));
    if(storage == NULL){
        return NULL;
    }
    for (int i = 0; i < *size; ++i){
        (storage + i)->name = (char *)malloc(50 * sizeof(char));
        if((storage + i)->name == NULL){
            for (int k = 0; k < i; ++k){
                free((storage + k)->name);
            }
            free(storage);
        }
    }
    return storage;
}
struct students *load_data(struct students *storage, int *size){
    FILE *fptr = fopen("students_details.txt", "r");
    if(fptr == NULL){
        return NULL;
    }
    char junk[256];
    fgets(junk, sizeof(junk), fptr);
    fgets(junk, sizeof(junk), fptr);
    for (int i = 0; i < *size; ++i){
        int sn;
        fscanf(fptr, "%d | %d | %[^|] | %f\n", &sn, &(storage + i)->id, (storage + i)->name, &(storage + i)->gpa);
    }
    fclose(fptr);
    int total_students = *size;
    trim_name(storage, &total_students);
    return storage;
}
void trim_name(struct students *storage, int *size){
    for (int i = 0; i < *size; ++i){
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
    printf("_____________________________________________________\n");
    for (int i = 0; i < *size; ++i){
        printf("%-10d | %-10d | %-20s | %.2f\n", i + 1, (storage + i)->id, (storage + i)->name, (storage + i)->gpa);
    }
}
struct students *add_more_students(struct students *storage, int *size){
    char choice;
    printf("Do you wanna add new student? [Y/N]:\t");
    if(!scanf(" %c", &choice)){
        return storage;
    }
        while(choice == 'y' || choice == 'Y'){
            struct students *temp = realloc(storage, (*size + 1) * sizeof(struct students));
            if(temp == NULL){
                printf("Error: Cannot add more students.\n");
                break;
            }
            storage = temp;
            (storage + *size)->name = (char *)malloc(50 * sizeof(char));
            printf("ID:\t");
            scanf("%d", &(storage + *size)->id);
            getchar();
            printf("Name:\t");
            fgets((storage + *size)->name, 50 * sizeof(char), stdin);
            (storage + *size)->name[strcspn((storage + *size)->name, "\n")] = '\0';
            printf("GPA:\t");
            scanf("%f", &(storage + *size)->gpa);
            (*size)++;
            save_to_file(storage, *size);
            printf("Wanna add more students? [Y/N]:\t");
            scanf(" %c", &choice);
        }
        return storage;
}
struct students *edit_by_id(struct students *storage, int *size){
    int search_id;
    printf("Enter the ID of the student you wanna update:\t");
    if(!scanf("%d", &search_id)){
        printf("Error: Please enter valid input. Try Again!\n");
        return storage;
    }
    int found_index = -1;
    for (int i = 0; i < *size; ++i){
        if(search_id == (storage + i)->id){
            found_index = i;
            break;
        }
    }
    if(found_index == -1){
        printf("Student with ID: %d not found on database.\n", search_id);
        return storage;
    }
    printf("ID:\t");
    scanf("%d", &(storage + found_index)->id);
    getchar();
    printf("Name:\t");
    fgets((storage + found_index)->name, 50 * sizeof(char), stdin);
    (storage + found_index)->name[strcspn((storage + found_index)->name, "\n")] = '\0';
    printf("GPA:\t");
    scanf("%f", &(storage + found_index)->gpa);
    save_to_file(storage, *size);
    return storage;
}
struct students *delete_by_id(struct students *storage, int *size){
    int search_id;
    printf("Enter the ID of the student you wanna delete:\t");
    if(!(scanf("%d", &search_id))){
        printf("Error: Enter valid input. Try Again!\n");
        return storage;
    }
    int found_index = -1;
    for (int i = 0; i < *size; ++i)
    {
        if(search_id == (storage + i)->id){
            found_index = i;
            break;
        }
    }
    if(found_index == -1){
        printf("Student with ID: %d not found on database.\n", search_id);
        return storage;
    }
    free((storage + found_index)->name);
    int num_to_move = *size - found_index - 1;
    if(num_to_move > 0){
        memmove((storage + found_index), (storage + found_index + 1), num_to_move * sizeof(struct students));
    }
    (*size)--;
    if(*size > 0){
        struct students *temp = realloc(storage, *size * sizeof(struct students));
        if(temp != NULL){
            storage = temp;
        }
    }
    else{
        free(storage);
        return NULL;
    }
    save_to_file(storage, *size);
    return storage;
}
void free_memory(struct students *storage, int *size){
    for (int i = 0; i < *size; ++i){
        free((storage + i)->name);
    }
    free(storage);
}