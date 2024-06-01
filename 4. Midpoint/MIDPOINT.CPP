
#include <stdio.h>
#include<conio.h>
#include <graphics.h>

void midPointCircleDraw(int x_centre, int y_centre, int r)
{
    int x = 0, y = r;
    int p = 1 - r;
    while (x <= y)
    {
	putpixel(x + x_centre, y + y_centre, RED);
	putpixel(y + x_centre, x + y_centre, RED);
	putpixel(-x + x_centre, y + y_centre, RED);
	putpixel(-y + x_centre, x + y_centre, RED);
	putpixel(-x + x_centre, -y + y_centre, RED);
	putpixel(-y + x_centre, -x + y_centre, RED);
	putpixel(x + x_centre, -y + y_centre, RED);
	putpixel(y + x_centre, -x + y_centre, RED);

	if (p < 0)
	{
	    x++;
	    p = p + 2 * x + 1;
	}
	else
	{
	    x++;
	    y--;
	    p = p + 2 * (x - y) + 1;
	}
    }
}

int main()
{
    int gd = DETECT, gm,x_centre,y_centre,r;
    initgraph(&gd, &gm,"C:\\TURBOC3\\BGI");
    printf("Enter the coordinates of the center of the circle: ");
    scanf("%d%d", &x_centre, &y_centre);
    printf("Enter the radius of the circle: ");
    scanf("%d", &r);
    midPointCircleDraw(x_centre, y_centre, r);
    getch();
    closegraph();

}

// 320
// 240
// 150