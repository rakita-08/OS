#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_BLOCKS 100
#define MAX_POINTERS 10

typedef struct {
    char name[20];
    int size;
    int blocks[MAX_POINTERS]; // direct pointers
} Inode;

int disk[MAX_BLOCKS]; // 0 = free, 1 = allocated

int main() {
    int total_blocks, i, j, k, block, n;
    Inode files[MAX_FILES];

    // Initialize disk
    for (i = 0; i < MAX_BLOCKS; i++)
        disk[i] = 0;

    printf("Enter total number of disk blocks (max %d): ", MAX_BLOCKS);
    scanf("%d", &total_blocks);

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nFile %d\n", i + 1);
        printf("Enter file name: ");
        scanf("%s", files[i].name);

        printf("Enter number of blocks required (max %d): ", MAX_POINTERS);
        scanf("%d", &files[i].size);

        if (files[i].size > MAX_POINTERS) {
            printf("Error: Exceeds max pointers allowed per inode.\n");
            i--;
            continue;
        }

        printf("Enter %d block numbers to allocate: ", files[i].size);
        int valid = 1;
        for (j = 0; j < files[i].size; j++) {
            scanf("%d", &block);
            if (block < 0 || block >= total_blocks || disk[block] == 1) {
                valid = 0;
            }
            files[i].blocks[j] = block;
        }

        if (!valid) {
            printf("Allocation failed! Invalid or already used blocks.\n");
            i--;
            continue;
        }

        // Mark blocks as used
        for (j = 0; j < files[i].size; j++)
            disk[files[i].blocks[j]] = 1;

        printf("File '%s' allocated using inode.\n", files[i].name);
    }

    // Print inode table
    printf("\nInode Table:\n");
    printf("File Name\tSize\tBlock Pointers\n");

    for (i = 0; i < n; i++) {
        printf("%s\t\t%d\t", files[i].name, files[i].size);
        for (j = 0; j < files[i].size; j++)
            printf("%d ", files[i].blocks[j]);
        printf("\n");
    }
    printf("Name: Rakita Rimal, Roll No: 27, Lab No: 3.8d\n");

    return 0;
}
