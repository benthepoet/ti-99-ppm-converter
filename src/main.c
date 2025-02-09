#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Filename is required");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char word[64];

    // Pull header
    fgets(word, 64, file);
    printf("%s", word);

    // Pull comment
    fgets(word, 64, file);
    printf("%s", word);

    int width, height = 0;

    // Pull width and height
    fscanf(file, "%d", &width);
    printf("%d\n", width);

    fscanf(file, "%d", &height);
    printf("%d\n", height);

    int maxValue = 0;

    // Pull maximum color value
    fscanf(file, "%d\n", &maxValue);
    printf("%d\n", maxValue);

    int **pixels;
    pixels = (int **)malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        pixels[i] = (int *)malloc(width * sizeof(int));
    }

    int row, col = 0;

    int pixel = fgetc(file);
    while (row < height) {
        pixels[row][col] = pixel;
        printf("%d\n", pixel);
        printf("%d %d\n", row, col);
        if (++col > width - 1) {
            col = 0;
            row++;
        }
        pixel = fgetc(file);
    }



    free(pixels);
    fclose(file);

    return 0;
}
