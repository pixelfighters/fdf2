#include <stdio.h>
#include <stdint.h>

int encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    return (red << 16 | green << 8 | blue);
}

int main(void)
{
    int color;
    color = 0;

    color = encode_rgb(255,255,255);
    printf("color = %d", color);
}