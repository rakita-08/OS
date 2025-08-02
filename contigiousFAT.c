#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 100
#define MAX_FILES 50

typedef struct {
    char name[20];
    int start;
    int length;
} File;

int main() {
    int disk[MAX_BLOCKS] = {0}; // 0 = free, 1 = occupied
    File files[MAX_FILES];
    int n, i, j;

    printf("Enter total number of blocks on disk (max %d): ", MAX_BLOCKS);
    int total_blocks;
    scanf("%d", &total_blocks);

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nFile %d\n", i + 1);
        printf("Enter file name: ");
        scanf("%s", files[i].name);

        printf("Enter starting block (0 to %d): ", total_blocks - 1);
        scanf("%d", &files[i].start);

        printf("Enter length (number of blocks required): ");
        scanf("%d", &files[i].length);

        int canAllocate = 1;

        // Check if requested blocks are free and within bounds
        if (files[i].start < 0 || files[i].start + files[i].length > total_blocks) {
            canAllocate = 0;
        } else {
            for (j = files[i].start; j < files[i].start + files[i].length; j++) {
                if (disk[j] == 1) {
                    canAllocate = 0;
                    break;
                }
            }
        }

        if (canAllocate) {
            for (j = files[i].start; j < files[i].start + files[i].length; j++) {
                disk[j] = 1;
            }
            printf("File '%s' allocated successfully.\n", files[i].name);
        } else {
            printf("Cannot allocate file '%s'. Space not available or out of bounds.\n", files[i].name);
            // Mark as invalid
            strcpy(files[i].name, "-");
            files[i].start = -1;
            files[i].length = 0;
        }
    }

    // Display allocation table
    printf("\nFile Allocation Table:\n");
    printf("File Name\tStart Block\tLength\tBlocks Allocated\n");
    for (i = 0; i < n; i++) {
        if (files[i].start != -1) {
            printf("%s\t\t%d\t\t%d\t", files[i].name, files[i].start, files[i].length);
            for (j = files[i].start; j < files[i].start + files[i].length; j++) {
                printf("%d ", j);
            }
            printf("\n");
        }
    }
    printf("Name: Rakita Rimal, Roll No: 27, Lab No: 3.8a\n");

    return 0;
}
