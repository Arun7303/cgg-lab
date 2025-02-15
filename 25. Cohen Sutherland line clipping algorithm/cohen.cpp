#include <iostream>
#include <conio.h>
#include <graphics.h>

int x_max;
int y_max;
int x_min;
int y_min;

// Defining codes
const int INSIDE = 0;         // 0000
const int LEFT = 1;           // 0001
const int RIGHT = 2;          // 0010
const int BOTTOM = 4;         // 0100
const int TOP = 8;            // 1000

using namespace std;

// Function to compute op code for a point(x, y)
int OpCode(double x, double y) {
	int code = INSIDE;

	if (x < x_min)              // to the left of rectangle
		code |= LEFT;
	else if (x > x_max)         // to the right of rectangle
		code |= RIGHT;
	if (y < y_min)              // below the rectangle
		code |= BOTTOM;
	else if (y > y_max)         // above the rectangle
		code |= TOP;

	return code;
}

int sigmoid(int val) {
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

void bre(int x1, int y1, int x2, int y2) {
    int x = x1, y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;

    int xchange = sigmoid(dx); 
    int ychange = sigmoid(dy);
    dx = abs(dx);
    dy = abs(dy);

    int p = 2 * dy - dx;
    int n = 0;

    if (abs(dx) > abs(dy)) {
        // for gentle slope
        while (x != x2) {
            putpixel(x, y, WHITE);
            x += xchange;

            if (p < 0)
                p += 2 * dy;
            else {
                p += 2 * dy - 2 * dx;
                y += ychange;
            }

            n++;
        }

    } else {
        // for steep slope
        while (y != y2) {
            putpixel(x, y, WHITE);
            y += ychange;

            if (p < 0)
                p += 2 * dx;
            else {
                p += 2 * dx - 2 * dy;
                x += xchange;
            }

            n++;
        }
    }
}

void cohenSutherland(double x1, double y1, double x2, double y2) {
	int code1 = OpCode(x1, y1);
	int code2 = OpCode(x2, y2);

	bool accept = false;

	while (true) {
		if ((code1 == 0) && (code2 == 0)) {
			// If both endpoints lie within rectangle
			accept = true;
			break;
		}
		else if (code1 & code2) {
			// If both endpoints are outside rectangle, in same region
			break;
		}
		else {
			// Some segment of line lies within the rectangle
			int code_out;
			double x, y;

			// At least one endpoint is outside the rectangle, pick it.
			if (code1 != 0)
				code_out = code1;
			else
				code_out = code2;

			// Find intersection point
			if (code_out & TOP) {
				// point is above the clip rectangle
				x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
				y = y_max;
			}
			else if (code_out & BOTTOM) {
				// point is below the rectangle
				x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
				y = y_min;
			}
			else if (code_out & RIGHT) {
				// point is to the right of rectangle
				y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
				x = x_max;
			}
			else if (code_out & LEFT) {
				// point is to the left of rectangle
				y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
				x = x_min;
			}

			if (code_out == code1) {
				x1 = x;
				y1 = y;
				code1 = OpCode(x1, y1);
			}
			else {
				x2 = x;
				y2 = y;
				code2 = OpCode(x2, y2);
			}
		}
	}
	if (accept) {
        setcolor(LIGHTBLUE);
		line(x1, y1, x2, y2);
	}
	else
		cout << "Line rejected" << endl;
}

int main() {
    int gd = DETECT, gm;
    int x1, x2, y1, y2;
    initgraph(&gd, &gm,  " ");

	cout << "Enter coordinates for the clipping window\n";
	cout << "Enter x min and y min values\n";
	cin >> x_min >> y_min;
	cout << "Enter x max and y max values\n";
	cin >> x_max >> y_max;


   	 // Drawing the window
     bre(x_min, y_min, x_max, y_min);
     bre(x_max, y_min, x_max, y_max);
     bre(x_max, y_max, x_min, y_max);
     bre(x_min, y_max, x_min, y_min);

    // coordinates of line to check
	cout << "\nEnter coordinates for line:\n";
	cout << "Enter x1 and y1 coordinates\n";
	cin >> x1 >> y1;
	cout << "Enter x2 and y2 coordinates\n";
	cin >> x2 >> y2;

	bre(x1, y1, x2, y2);
	cohenSutherland(x1, y1, x2, y2);

	getch();
  closegraph();
  return 0;
}
