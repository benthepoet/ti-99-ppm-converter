#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int debug = 0;
    const char *filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            debug = 1;
        } else if (filename == NULL) {
            filename = argv[i];
        } else {
            perror("Usage: ppm-converter [-d|--debug] <filename>");
            return 1;
        }
    }

    if (filename == NULL) {
        perror("Filename is required");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char word[64];

    // Pull header
    fgets(word, 64, file);
    if (debug) {
        printf("%s", word);
    }

    int width = 0, height = 0;

    // Pull width and height
    fscanf(file, "%d", &width);
    fscanf(file, "%d", &height);
    if (debug) {
        printf("%d %d\n", width, height);
    }

    if (width % 8 || height % 8) {
        perror("Width and height must be factors of 8.");
        return 1;
    }

    int maxValue = 0;

    // Pull maximum color value
    fscanf(file, "%d\n", &maxValue);
    if (debug) {
        printf("%d\n", maxValue);
    }

    int **pixels;
    pixels = (int **)malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        pixels[i] = (int *)malloc(width * sizeof(int));
    }

    int row = 0, col = 0;

    // Get the red value
    int pixel = fgetc(file);
    while (row < height) {
        pixels[row][col] = pixel;

        if (++col > width - 1) {
            col = 0;
            row++;
        }

        // Skip green and blue
        fgetc(file);
        fgetc(file);

        // Get the next red value
        pixel = fgetc(file);
    }

    fclose(file);
    printf("\n");

    // Convert pixels to VDP tiles
    for (int i = 0; i < width; i += 8) {
        for (int j = 0; j < height; j += 8) {
            printf("BYTE ");

            for (int k = j; k < j + 8; k++) {
                int p = 0;

                for (int l = i; l < i + 8; l++) {
                    if (pixels[k][l] == 0) {
                        p |= 0x80 >> (l - i);
                    }
                }

                if (k % 8 != 0) {
                    printf(",");
                }

                printf(">%02x", p);
            }

            printf("\n");
        }
    }

    // Clean up
    for (int i = 0; i < height; i++) {
        free(pixels[i]);
    }
    free(pixels);

    return 0;
}
