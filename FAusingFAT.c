#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 100
#define MAX_FILES 20

typedef struct {
    char name[20];
    int start;
    int length;
} File;

int FAT[MAX_BLOCKS]; // -2 = free, -1 = end of file, else next block index

int main() {
    int total_blocks, n, i, j, block;

    File files[MAX_FILES];

    // Initialize FAT table
    for (i = 0; i < MAX_BLOCKS; i++)
        FAT[i] = -2;

    printf("Enter total number of blocks on disk (max %d): ", MAX_BLOCKS);
    scanf("%d", &total_blocks);

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nFile %d\n", i + 1);
        printf("Enter file name: ");
        scanf("%s", files[i].name);

        printf("Enter number of blocks required: ");
        scanf("%d", &files[i].length);

        int blocks[files[i].length];

        printf("Enter block numbers for the file (space-separated): ");
        int valid = 1;

        for (j = 0; j < files[i].length; j++) {
            scanf("%d", &block);

            if (block < 0 || block >= total_blocks || FAT[block] != -2) {
                valid = 0;
            }
            blocks[j] = block;
        }

        if (!valid) {
            printf("Allocation failed for file '%s' (some blocks already used or invalid).\n", files[i].name);
            strcpy(files[i].name, "-");
            files[i].start = -1;
            files[i].length = 0;
            continue;
        }

        // Link blocks in FAT
        for (j = 0; j < files[i].length - 1; j++)
            FAT[blocks[j]] = blocks[j + 1];
        FAT[blocks[files[i].length - 1]] = -1;

        files[i].start = blocks[0];

        printf("File '%s' allocated successfully.\n", files[i].name);
    }

    // Display File Table
    printf("\nFile Allocation Table (FAT):\n");
    printf("File Name\tStart Block\tLength\tBlocks (via FAT)\n");

    for (i = 0; i < n; i++) {
        if (files[i].start != -1) {
            printf("%s\t\t%d\t\t%d\t", files[i].name, files[i].start, files[i].length);
            int current = files[i].start;
            while (current != -1) {
                printf("%d", current);
                current = FAT[current];
                if (current != -1) printf(" -> ");
            }
            printf(" -> NULL\n");
        }
    }

    // Optionally display the full FAT table
    printf("\nFAT Table (block : next block):\n");
    for (i = 0; i < total_blocks; i++) {
        if (FAT[i] != -2) {
            printf("Block %2d : ", i);
            if (FAT[i] == -1)
                printf("EOF\n");
            else
                printf("%d\n", FAT[i]);
        }
    }
    printf("Name: Rakita Rimal, Roll No: 27, Lab No: 3.8c\n");

    return 0;
}
