#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#define PI 3.14159265358979323846
// Function to draw a line using Bresenham's algorithm
void bresenhamLine(int x0, int y0, int x1, int y1, int color) {
int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
int err = dx + dy, e2;
while (1) {
putpixel(x0, y0, color);
if (x0 == x1 && y0 == y1) break;
e2 = 2 * err;
if (e2 >= dy) { err += dy; x0 += sx; }
if (e2 <= dx) { err += dx; y0 += sy; }
}
}
// Function to draw a full circle using Bresenham's algorithm
void bresenhamCircle(int xc, int yc, int radius, int color) {
int x = 0, y = radius, d = 3 - 2 * radius;
while (y >= x) {
// Draw all octants
putpixel(xc+x, yc+y, color);
putpixel(xc-x, yc+y, color);
putpixel(xc+x, yc-y, color);
putpixel(xc-x, yc-y, color);
putpixel(xc+y, yc+x, color);
putpixel(xc-y, yc+x, color);
putpixel(xc+y, yc-x, color);
putpixel(xc-y, yc-x, color);
x++;
if (d > 0) {
y--;
d = d + 4 * (x - y) + 10;
} else {
d = d + 4 * x + 6;
}
}
}
// Function to draw a semicircle (top half) using simple circle math
void drawSemicircle(int xc, int yc, int radius, int color) {
	
	int x = -radius, y = 0, err = 2-2*radius; // Initial values
do {
putpixel(xc-x, yc-y, color); // Upper semicircle
putpixel(xc+y, yc+x, color); // Left semicircle
putpixel(xc-y, yc+x, color); // Right semicircle
int e2 = err;
if (e2 <= y) err += ++y*2+1;
if (e2 > x || err > y) err += ++x*2+1;
} while (x < 0);
}
// Function to draw a wheel with spokes
void drawWheelWithSpokes(int xc, int yc, int radius, int spokes, int color) {
bresenhamCircle(xc, yc, radius, color);
float angle = 360.0 / spokes;
for (int i = 0; i < spokes; i++) {
float rad = angle * i * PI / 180;
int xend = xc + radius * cos(rad);
int yend = yc + radius * sin(rad);
bresenhamLine(xc, yc, xend, yend, color);
}
}
int main() {
int gd = DETECT, gm;
initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
int x_center = getmaxx() / 2;
int y_center = getmaxy() / 2;
// Draw the body of the car
bresenhamLine(x_center - 100, y_center, x_center + 100, y_center, WHITE);
// Bottom
bresenhamLine(x_center - 100, y_center, x_center - 100, y_center - 50,
WHITE); // Left vertical
bresenhamLine(x_center + 100, y_center, x_center + 100, y_center - 50,
WHITE); // Right vertical
bresenhamLine(x_center - 100, y_center - 50, x_center - 50, y_center - 50,
WHITE); // Top left
bresenhamLine(x_center + 50, y_center - 50, x_center + 100, y_center - 50,
WHITE); // Top right
// Draw the roof and windshield
bresenhamLine(x_center - 50, y_center - 50, x_center - 30, y_center - 80,
WHITE); // Windshield left
bresenhamLine(x_center + 50, y_center - 50, x_center + 30, y_center - 80,
WHITE); // Windshield right

bresenhamLine(x_center - 30, y_center - 80, x_center + 30, y_center - 80,
WHITE); // Roof
// Draw wheel arches
drawSemicircle(x_center - 60, y_center + 10, 20, WHITE);
drawSemicircle(x_center + 60, y_center + 10, 20, WHITE);
// Draw the wheels with spokes
drawWheelWithSpokes(x_center - 60, y_center + 10, 20, 6, WHITE); // Left
drawWheelWithSpokes(x_center + 60, y_center + 10, 20, 6, WHITE); // Right

getch();
closegraph();
return 0;

}
