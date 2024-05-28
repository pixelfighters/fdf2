#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "mlx.h"
#include "mlx_int.h"

#define WIN1_SX 2200
#define WIN1_SY 1200
#define IM1_SX 42
#define IM1_SY 42
#define IM3_SX 242
#define IM3_SY 242

void *mlx;
void *win1;
void *win2;
void *win3;
void *im1;
void *im2;
void *im3;
void *im4;
int bpp1;
int bpp2;
int bpp3;
int bpp4;
int sl1;
int sl2;
int sl3;
int sl4;
int endian1;
int endian2;
int endian3;
int endian4;
char *data1;
char *data2;
char *data3;
char *data4;
int xpm1_x;
int xpm1_y;

int local_endian;

typedef struct s_data {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

int color_map_1(void *win, int w, int h);
void plot(void *win, int x, int y, int color);

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    if (data->endian != 0) /* Invert color value if endianness is not little-endian */
        color = (color >> 24) | ((color >> 8) & 0xff00) | ((color << 8) & 0xff0000) | (color << 24);

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void dda(void *win, int x0, int y0, int x1, int y1, int color) {
    float dx;
    float dy;
    float steps;
    float x_increment;
    float y_increment;
    float x;
    float y;

    dx = x1 - x0;
    dy = y1 - y0;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    x_increment = dx / steps;
    y_increment = dy / steps;

    x = x0;
    y = y0;

    for (int i = 0; i <= steps; i++) {
        plot(win, (int)x, (int)y, color);
        x += x_increment;
        y += y_increment;
    }
}

float fpart(float x) {
    return x - floor(x);
}

float rfpart(float x) {
    return 1.0 - fpart(x);
}

void dda_antialiased(void *win, int x0, int y0, int x1, int y1, int color) {
    float dx;
    float dy;
    float steps;
    float x_increment;
    float y_increment;
    float x;
    float y;

    dx = x1 - x0;
    dy = y1 - y0;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    x_increment = dx / steps;
    y_increment = dy / steps;

    x = x0;
    y = y0;

    for (int i = 0; i <= steps; i++) {
        plot(win, (int)x, (int)y, color);
        plot(win, (int)x + 1, (int)y, color);
        plot(win, (int)x, (int)y + 1, color);
        plot(win, (int)x + 1, (int)y + 1, color);
        x += x_increment;
        y += y_increment;
    }
}

void bresenham(void *win, int x0, int y0, int x1, int y1, int color) {
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    sx = x0 < x1 ? 1 : -1;
    sy = y0 < y1 ? 1 : -1;
    err = dx - dy;

    while (1) {
        plot(win, x0, y0, color); // Draw the current point
        if (x0 == x1 && y0 == y1) break; // Check if the end point is reached
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

int main(void)
{
    int a;
	int color;
    int x0 = 0, y0 = 0, x1 = 1000, y1 = 0;

    printf("MinilibX Test Program\n");
    a = 0x11223344;
    if (((unsigned char *)&a)[0] == 0x11)
        local_endian = 1;
    else
        local_endian = 0;
    printf(" => Local Endian : %d\n", local_endian);

    printf(" => Connection ...");
    if (!(mlx = mlx_init()))
    {
        printf(" !! KO !!\n");
        exit(1);
    }
    printf("OK\n");

    printf(" => Window1 %dx%d \"ugly_window\" ...", WIN1_SX, WIN1_SY);
    if (!(win1 = mlx_new_window(mlx, WIN1_SX, WIN1_SY, "ugly_window")))
    {
        printf(" !! KO !!\n");
        exit(1);
    }
    printf("OK\n");

    printf(" => Colormap sans event ...");
   //  color_map_1(win1, WIN1_SX, WIN1_SY);
    // printf("OK\n");
    // sleep(5);

    for (int i = 0; i < 50; i++) {
        y0 = rand() % WIN1_SY;
        x0 = rand() % WIN1_SX;
        y1 = rand() % WIN1_SY;
        x1 = rand() % WIN1_SX;		
		// color = rand() % 0x100000000; // color plus alpha
		color = 0x7F0000FF;
		// color = rand() % 0xFFFFFF; // Random value between 0 and 0xFFFFFF (24-bit color)
        // bresenham(win1, x0, y0, x1, y1, color);
		dda_antialiased(win1, x0+1, y0+1, x1+1, y1+1, color);
		dda_antialiased(win1, x0+2, y0+2, x1+2, y1+2, color);
		dda_antialiased(win1, x0+3, y0+3, x1+3, y1+3, color);
		dda_antialiased(win1, x0, y0, x1, y1, color);
		
    }
	sleep(25);
}

int color_map_1(void *win, int w, int h)
{
    int x;
    int y;
    int color;

    x = w;
    while (x--) {
        y = h;
        while (y--) {
            color = (x * 255) / w + ((((w - x) * 255) / w) << 16) + (((y * 255) / h) << 8);
            printf("%d %d\n", x, y);
            mlx_pixel_put(mlx, win, (50 + rand() % 100), y, color);
        }
    }
}

void plot(void *win, int x, int y, int color) {
	    mlx_pixel_put(mlx, win, x, y, color);
}
