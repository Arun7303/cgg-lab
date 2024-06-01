#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

// Function to draw a line using DDA (Digital Differential Analyzer) algorithm
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps, k;
    float xIncrement, yIncrement, x = x1, y = y1;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xIncrement = dx / (float) steps;
    yIncrement = dy / (float) steps;

    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        putpixel((int)(x + 0.5), (int)(y + 0.5), WHITE);
    }
}

// Function to draw a circle using Bresenham's circle drawing algorithm
void brescir(int x, int y, int r, int color) {
    int i = 0, j = r, p = 3 - 2 * r;
    while (i <= j) {
        putpixel(x + i, y + j, color);
        putpixel(x - i, y - j, color);
        putpixel(x + j, y + i, color);
        putpixel(x - j, y - i, color);
        putpixel(x - i, y + j, color);
        putpixel(x + i, y - j, color);
        putpixel(x - j, y + i, color);
        putpixel(x + j, y - i, color);
        if (p < 0) {
            i++;
            p = p + 4 * i + 6;
        } else {
            i++;
            j--;
            p = p + 4 * (i - j) + 10;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int x, y;
    initgraph(&gd, &gm, "C:/TURBOC3/BGI");

    // Draw the square
    drawLine(50, 50, 250, 50);
    drawLine(250, 50, 250, 250);
    drawLine(250, 250, 50, 250);
    drawLine(50, 250, 50, 50);

    // Initial coordinates of the ball
    x = 58;
    y = 242;

    while (1) {
        // Clear the screen
        cleardevice();

        // Draw the square
        drawLine(50, 50, 250, 50);
        drawLine(250, 50, 250, 250);
        drawLine(250, 250, 50, 250);
        drawLine(50, 250, 50, 50);

        // Draw the ball
        brescir(x, y, 10, WHITE);

        // Delay to slow down the speed of the ball
        delay(50);

        // Check for Enter key press to exit
        if (kbhit() && getch() == 13) {
            break;
        }

        // Logic to move the ball in a square path
        if (x <= 58 && y > 58)
            y -= 5;
        else if (x < 242 && y <= 58)
            x += 5;
        else if (x >= 242 && y < 242)
            y += 5;
        else if (x > 58 && y >= 242)
            x -= 5;
    }

    getch();
    closegraph();
    return 0;
}
