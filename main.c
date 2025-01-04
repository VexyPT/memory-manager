#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_BLOCKS 100

typedef struct {
    void *address;
    size_t size;
} MemoryBlock;

MemoryBlock blocks[MAX_BLOCKS];
int block_count = 0;
size_t total_allocated = 0;

/**
 * Safely reads an unsigned integer from user input.
 */
size_t safe_input_size(const char *prompt) {
    char buffer[128];
    char *endptr;
    size_t size = 0;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        errno = 0;
        size = strtoul(buffer, &endptr, 10);

        if (errno == ERANGE) {
            printf("Number out of range. Please try again.\n");
        } else if (endptr == buffer || *endptr != '\0') {
            printf("Invalid input. Please enter a valid size in bytes.\n");
        } else {
            break;
        }
    }
    return size;
}

/**
 * Safely reads an integer from user input.
 */
int safe_input_int(const char *prompt) {
    char buffer[128];
    char *endptr;
    int value = 0;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        errno = 0;
        long result = strtol(buffer, &endptr, 10);

        if (errno == ERANGE || result < INT_MIN || result > INT_MAX) {
            printf("Number out of range. Please try again.\n");
        } else if (endptr == buffer || *endptr != '\0') {
            printf("Invalid input. Please enter a valid integer.\n");
        } else {
            value = (int)result;
            break;
        }
    }
    return value;
}

/**
 * Allocates a block of memory based on user input.
 */
void allocate_memory() {
    if (block_count == MAX_BLOCKS) {
        printf("Error: Maximum number of memory blocks reached.\n");
        return;
    }

    size_t size = safe_input_size("Enter the size of memory block to allocate (in bytes): ");

    void *block = malloc(size);
    if (block == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    blocks[block_count].address = block;
    blocks[block_count].size = size;
    block_count++;
    total_allocated += size;

    printf("Memory allocated: Address=%p, Size=%zu bytes\n", block, size);
}

/**
 * Frees a previously allocated memory block.
 */
void free_memory() {
    if (block_count == 0) {
        printf("No memory blocks to free.\n");
        return;
    }

    char prompt[128];
    sprintf(prompt, "Enter the index of the memory block to free (0-%d): ", block_count - 1);
    int index = safe_input_int(prompt);

    if (index < 0 || index >= block_count) {
        printf("Error: Invalid index.\n");
        return;
    }

    free(blocks[index].address);
    total_allocated -= blocks[index].size;

    printf("Memory block freed: Address=%p, Size=%zu bytes\n",
           blocks[index].address, blocks[index].size);

    // Shift remaining blocks down to maintain array integrity.
    for (int i = index; i < block_count - 1; i++) {
        blocks[i] = blocks[i + 1];
    }
    block_count--;
}

/**
 * Displays the current state of memory allocation.
 */
void display_memory_status() {
    printf("\n--- Memory Status ---\n");
    printf("Total allocated memory: %zu bytes\n", total_allocated);
    printf("Number of active blocks: %d\n", block_count);
    for (int i = 0; i < block_count; i++) {
        printf("Block %d -> Address: %p, Size: %zu bytes\n",
               i, blocks[i].address, blocks[i].size);
    }
    printf("---------------------\n");
}

/**
 * Checks for memory leaks and reports any unfreed blocks.
 */
void detect_memory_leaks() {
    if (block_count > 0) {
        printf("\n--- Memory Leaks Detected ---\n");
        printf("Unfreed blocks: %d\n", block_count);
        for (int i = 0; i < block_count; i++) {
            printf("Block %d -> Address: %p, Size: %zu bytes\n",
                   i, blocks[i].address, blocks[i].size);
        }
        printf("---------------------------\n");
    } else {
        printf("\nNo memory leaks detected. All memory was freed successfully.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n--- Memory Management Simulator ---\n");
        printf("1. Allocate memory\n");
        printf("2. Free memory\n");
        printf("3. Display memory status\n");
        printf("4. Exit\n");
        choice = safe_input_int("Enter your choice: ");

        switch (choice) {
            case 1:
                allocate_memory();
                break;
            case 2:
                free_memory();
                break;
            case 3:
                display_memory_status();
                break;
            case 4:
                detect_memory_leaks();
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
