#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define PI 3.14159265

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
    int centerX = 100; // Adjusted centerX for larger view
    int centerY = 200; // Adjusted centerY for larger view
    int amplitude = 100; // Increased amplitude for larger wave
    int wavelength = 200; // Increased wavelength for larger wave
    int i;
    float angle = 0;

    int gd = DETECT, gm, x, y;
    initgraph(&gd, &gm, "C:/TURBOC3/BGI");

    while (1) {
        cleardevice();

        // Draw the sine wave with two wavelengths
        for (i = 0; i < 4 * wavelength; i++) { // Increased range to display larger wave
            int waveY = centerY + (int)(amplitude * sin(i * 2 * PI / wavelength));
            putpixel(centerX + i, waveY, WHITE);
        }

        // Calculate position of moving circle along wave pattern
        x = centerX + (int)(angle);
        y = centerY + (int)(amplitude * sin(angle * 2 * PI / wavelength)) - 8;

        // Draw the moving circle
        brescir(x, y, 10, WHITE);

        // Delay to control the speed of the moving circle
        delay(10);

        // Update the angle for the next position
        angle += 0.1;

        // Check if Enter key is pressed to exit
        if (kbhit()) {
            if (getch() == '\r') // '\r' represents Enter key
                break;
        }
    }

    getch();
    closegraph();
    return 0;
}
