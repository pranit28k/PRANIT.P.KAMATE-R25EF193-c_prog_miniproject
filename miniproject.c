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
void displayCanvas() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++)
            printf("%c", canvas[y][x]);
        printf("\n");
    }
}
/* =========================
   Shape Definitions
   ========================= */

typedef enum {
    LINE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
} ShapeType;

typedef struct {
    ShapeType type;

    int x1, y1;
    int x2, y2;
    int x3, y3;
  int radius;

    char symbol;
} Shape;

Shape objects[MAX_OBJECTS];
int objectCount = 0;

/* =========================
   Drawing Functions
   ========================= */
   void drawLine(int x1, int y1, int x2, int y2, char ch) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;
while (1) {
        setPixel(x1, y1, ch);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle(int x1, int y1,
                   int x2, int y2,
                   char ch) {
    drawLine(x1, y1, x2, y1, ch);
    drawLine(x2, y1, x2, y2, ch);
    drawLine(x2, y2, x1, y2, ch);
    drawLine(x1, y2, x1, y1, ch);
}

void drawCircle(int xc, int yc,
                int r, char ch) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (y >= x) {

        setPixel(xc + x, yc + y, ch);
        setPixel(xc - x, yc + y, ch);
        setPixel(xc + x, yc - y, ch);
        setPixel(xc - x, yc - y, ch);

        setPixel(xc + y, yc + x, ch);
        setPixel(xc - y, yc + x, ch);
        setPixel(xc + y, yc - x, ch);
        setPixel(xc - y, yc - x, ch);

        x++;

        if (d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }
    }
}

void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3,
                  char ch) {
    drawLine(x1, y1, x2, y2, ch);
    drawLine(x2, y2, x3, y3, ch);
    drawLine(x3, y3, x1, y1, ch);
}