#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Represents a student record
typedef struct {
    int id;
} Student;

// Creates a sorted array of student records
Student* create_array(int size) {
    Student *students = malloc(size * sizeof(Student));

    if (students == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        students[i].id = i;
    }

    return students;
}

__attribute__((noinline))
Student* binary_search(Student *students, int size, int target_id) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (students[mid].id == target_id) {
            return &students[mid];
        }

        if (students[mid].id < target_id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return NULL;
}

int main(void) {
    int sizes[] = {1000, 10000, 100000, 500000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    const int repetitions = 1000;

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];

        Student *students = create_array(size);
        int target_id = size - 1;

        // Verify that binary search works
        Student *result = binary_search(students, size, target_id);

        if (result == NULL || result->id != target_id) {
            printf("Search failed for size %d\n", size);
            free(students);
            return 1;
        }

        // Measure search time
        clock_t start = clock();

        for (int j = 0; j < repetitions; j++) {
            int search_id = target_id - (j % 10);
            result = binary_search(students, size, search_id);

            if (result == NULL) {
                printf("Search failed\n");
                free(students);
                return 1;
            }
        }

        clock_t end = clock();

        double elapsed_ms =
            ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

        printf("Size: %d | Time: %.3f ms | Found ID: %d\n",
            size, elapsed_ms, result->id);

        free(students);
    }

    return 0;
}
