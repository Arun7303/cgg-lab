#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>  // Include for abs and exit functions
#include <dos.h>     // Include for delay function

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

void main() {
    int gd = DETECT, gm, i, j = 96;
    float k = 90.5;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    brescir(320, 240, 105, WHITE);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(245, 85, "     Clock");

    setfillstyle(SOLID_FILL, 15);
    floodfill(320, 240, 15);

    while (kbhit() == 0) {
        k -= 0.1;
        j -= 6;

        for (i = 90; i >= 1; i -= 6) {
            if (kbhit() != 0) exit(0);
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            pieslice(320, 240, i, i - 1, 80);
            pieslice(320, 240, j, j - 1, 65);
            pieslice(320, 240, k, k - 1, 50);
            delay(1000); // Adjusted delay for seconds line
            setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
            pieslice(320, 240, i, i - 1, 80);
            pieslice(320, 240, j, j - 1, 65);
            pieslice(320, 240, k, k - 1, 50);
        }

        for (i = 359; i >= 91; i -= 6) {
            if (kbhit() != 0) exit(0);
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            pieslice(320, 240, i, i - 1, 80);
            pieslice(320, 240, j, j - 1, 65);
            pieslice(320, 240, k, k - 1, 50);
            delay(1000); // Adjusted delay for seconds line
            setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
            pieslice(320, 240, i, i - 1, 80);
            pieslice(320, 240, j, j - 1, 65);
            pieslice(320, 240, k, k - 1, 50);
        }

        if (j <= 6) j = 365;
        if (k <= 0.5) k = 359;
    }

    closegraph();
}
