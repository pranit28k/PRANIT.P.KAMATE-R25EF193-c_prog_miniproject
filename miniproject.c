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
            canvas[y][x] = '_';
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
/* =========================
   Object Management
   ========================= */

void addObject(Shape s) {
    if (objectCount < MAX_OBJECTS)
        objects[objectCount++] = s;
}

void deleteObject(int index) {
    if (index < 0 || index >= objectCount)
        return;

    for (int i = index; i < objectCount - 1; i++)
        objects[i] = objects[i + 1];

    objectCount--;
}

void modifyObject(int index, Shape newShape) {
    if (index < 0 || index >= objectCount)
        return;

    objects[index] = newShape;
}

/* =========================
   Redraw Scene
   ========================= */

void redrawScene() {
    clearCanvas();

    for (int i = 0; i < objectCount; i++) {

        Shape *s = &objects[i];

        switch (s->type) {

        case LINE:
            drawLine(
                s->x1, s->y1,
                s->x2, s->y2,
                s->symbol);
            break;

        case RECTANGLE:
            drawRectangle(
                s->x1, s->y1,
                s->x2, s->y2,
                s->symbol);
            break;

        case CIRCLE:
            drawCircle(
                s->x1, s->y1,
                s->radius,
                s->symbol);
            break;

        case TRIANGLE:
            drawTriangle(
                s->x1, s->y1,
                s->x2, s->y2,
                s->x3, s->y3,
                s->symbol);
            break;
        }
    }
}

/* =========================
   Utility
   ========================= */

void printObjects() {
    printf("\nObjects:\n");

    for (int i = 0; i < objectCount; i++) {
        printf("%d : ", i);

        switch (objects[i].type) {
        case LINE:
            printf("Line\n");
            break;
        case RECTANGLE:
            printf("Rectangle\n");
            break;
        case CIRCLE:
            printf("Circle\n");
            break;
        case TRIANGLE:
            printf("Triangle\n");
            break;
        }
    }
}

/* =========================
   Main
   ========================= */

int main() {

    Shape s;

    /* Add Line */
    s.type = LINE;
    s.x1 = 2;  s.y1 = 2;
    s.x2 = 25; s.y2 = 10;
    s.symbol = '*';
    addObject(s);

    /* Add Rectangle */
    s.type = RECTANGLE;
    s.x1 = 35; s.y1 = 2;
    s.x2 = 65; s.y2 = 10;
    s.symbol = '*';
    addObject(s);

    /* Add Circle */
    s.type = CIRCLE;
    s.x1 = 15;
    s.y1 = 18;
    s.radius = 5;
    s.symbol = '*';
    addObject(s);

    /* Add Triangle */
    s.type = TRIANGLE;
    s.x1 = 45; s.y1 = 15;
    s.x2 = 65; s.y2 = 22;
    s.x3 = 30; s.y3 = 22;
    s.symbol = '*';
    addObject(s);

    printf("INITIAL PICTURE\n\n");
    redrawScene();
    displayCanvas();

    printObjects();

    /* Delete Rectangle */
    printf("\nDeleting object 1 (Rectangle)...\n\n");
    deleteObject(1);

    redrawScene();
    displayCanvas();

    /* Modify Circle */
    printf("\nModifying Circle...\n\n");
  

    Shape newCircle;
    newCircle.type = CIRCLE;
    newCircle.x1 = 55;
    newCircle.y1 = 8;
    newCircle.radius = 7;
    newCircle.symbol = '*';
    printf("hi");

    modifyObject(1, newCircle);

    redrawScene();
    displayCanvas();

    return 0;
}