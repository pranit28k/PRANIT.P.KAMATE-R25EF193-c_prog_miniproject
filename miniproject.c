#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25
#define MAX_OBJECTS 100

/* =========================
   Canvas
   ========================= */

char canvas[HEIGHT][WIDTH];

void clearCanvas() {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            canvas[y][x] = ' ';
}

void setPixel(int x, int y, char ch) {
    if (x >= 0 && x < WIDTH &&
        y >= 0 && y < HEIGHT)
        canvas[y][x] = ch;
}