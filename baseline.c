#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Represents one student in the linked list
typedef struct Student {
    int id;
    struct Student *next;
} Student;

Student* create_list(int size) {
    Student *head = NULL;
    Student *tail = NULL;

    for (int i = 0; i < size; i++) {
        Student *new_student = malloc(sizeof(Student));

        if (new_student == NULL) {
            fprintf(stderr, "Memory allocation failed\n");

            while (head != NULL) {
                Student *temp = head;
                head = head->next;
                free(temp);
            }
            exit(EXIT_FAILURE);
        }

        new_student->id = i;
        new_student->next = NULL;

        if (head == NULL) {
            head = new_student;
        } else {
            tail->next = new_student;
        }

        tail = new_student;
    }

    return head;
}

__attribute__((noinline))
Student* search_student(Student *head, int target_id) {
    Student *current = head;

    while (current != NULL) {
        if (current->id == target_id) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void free_list(Student *head) {
    Student *current = head;

    while (current != NULL) {
        Student *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    int sizes[] = {1000, 10000, 100000, 500000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    const int repetitions = 1000;

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];

        Student *head = create_list(size);

        // Search for the last student
        int target_id = size - 1;

        // Verify that the search works
        Student *result = search_student(head, target_id);

        if (result == NULL || result->id != target_id) {
            printf("Search failed for size %d\n", size);
            free_list(head);
            return 1;
        }

        // Measure the search time
        clock_t start = clock();

        for (int j = 0; j < repetitions; j++) {
        int search_id = target_id - (j % 10);
        result = search_student(head, search_id);

            if (result == NULL) {
                printf("Search failed\n");
                free_list(head);
                return 1;
            }
        }

        clock_t end = clock();

        double elapsed_ms =
            ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

        printf("Size: %d | Time: %.3f ms | Found ID: %d\n",
            size, elapsed_ms, result->id);

        free_list(head);
    }

    return 0;
}

