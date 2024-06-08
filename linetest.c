/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linetest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kami <kami@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:36:44 by abrabant          #+#    #+#             */
/*   Updated: 2024/06/08 13:15:20 by kami             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define MLX_ERROR 1

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		cur_img;
	int		bg_color;
	int		rect_x;
	int		rect_y;
	  int     mouse_x;
    int     mouse_y; 
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_circ
{
	int	x;
	int	y;
	int radius;
	int color;
}	t_circ;

int	render(t_data *data);

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
    {
        return;
    }
	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int get_pixel_color(t_img *img, int x, int y)
{
    char *pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    return (*(int *)pixel);
}
/* 
void draw_text(t_data *data, int x, int y, char *text, int color)
{
    int i, j;
    int text_len = strlen(text);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 50, 50, 0xFFFFFF, "Hello, world!");
	
    for (i = 0; i < text_len; i++) {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + i * 8, y, color);
        for (j = 1; j < 8; j++) {
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + i * 8 + j, y + j, color);
        }
    }
} */
int render_rect(t_data *data, t_rect rect, float alpha)
{
    int i;
    int j;
    int rect_color;
    int bg_color;
    rect_color = WHITE_PIXEL; // or any other color you want

    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width)
        {
            // Get the background color at this pixel
            bg_color = get_pixel_color(&data->img, j, i);

            // Blend the rectangle color with background color based on alpha
            int blended_color = alpha * rect_color + (1 - alpha) * bg_color;

            img_pix_put(&data->img, j++, i, blended_color);
        }
        ++i;
    }
    return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_space)
	{
		int red = rand() % (256 - 50 + 1) + 50;
		int green  = rand() % (256 - 50 + 1) + 50;
		int blue = rand() % (256 - 50 + 1) + 50;
    	data->bg_color = ft_create_trgb(0, red, green, blue);
		printf("Space pressed, changing background color\n");
		render(data);
	}	
	printf("Keypress: %d\n", keysym);
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		// ft_print_ascii_art("YEAH DONE", KCYN, 1);
		exit(0);
	}
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	printf("Keyrelease: %d %p\n", keysym, data);
	return (0);
}

int	handle_mousewheel(int button, int x, int y, t_data *data)
{
	int red, green, blue;
	red = (data->bg_color >> 16) & 0xFF;
	green = (data->bg_color >> 8) & 0xFF;
	blue = data->bg_color & 0xFF;
	if (button == 4)
	{
		if (red < 180)
			red += 10;
		if (green < 180)
			green += 10;
		if (blue < 180)
			blue += 10;		
	}
	else if (button == 5)
	{
		if (red > 40)
			red -= 10;
		if (green > 40)
			green -= 10;
		if (blue > 40)
			blue -= 10;			
	}
	data->bg_color = ft_create_trgb(0, red, green, blue);
	printf("Mouse wheel moved at position (%d, %d), new background color: 0x%X\n", x, y, data->bg_color);
	render(data);
	return (0);
}

int handle_mousehook(int button, int x, int y, t_data *data)
{
	t_rect rect = {0, WINDOW_HEIGHT - 200, WINDOW_WIDTH, 160, WHITE_PIXEL};
	data->mouse_x = x;
	data->mouse_y = y; 
	if (button == 4 || button == 5)
		return handle_mousewheel(button, x, y, data);
	if (x >= rect.x && x < rect.x + rect.width &&
		y >= rect.y && y < rect.y + rect.height)
	{
		printf("Mouse is over the rectangle at (%d, %d)\n", x, y);
	}
	else
	{
		printf("Mouse button %d clicked at position (%d, %d)\n", button, x, y);
	}
	render(data);
	return (0);
}

int render(t_data *data)
{
	int bgcolor;
	float alpha = 0.2;
	char mouse_pos[50]; 
	char bg_color_value[50]; 
	if (data->win_ptr == NULL)
		return (1);
	bgcolor = data->bg_color;
	render_background(&data->img, bgcolor);
	t_rect rect = {0, WINDOW_HEIGHT - 200, WINDOW_WIDTH, 160, WHITE_PIXEL};
	render_rect(data, rect, alpha);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	sprintf(mouse_pos, "Mouse position (at event): %d, %d", data->mouse_x, data->mouse_y);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 50, WINDOW_HEIGHT - 150, 0x000000, mouse_pos);
	sprintf(bg_color_value, "BGCOLOR: %d ", data->bg_color);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 50, WINDOW_HEIGHT - 120, 0x000000, bg_color_value);	
	return (0);
}


int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	data.bg_color = 0xAAAAAA;
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_mouse_hook(data.win_ptr, &handle_mousehook, &data);
	render(&data);
	mlx_loop(data.mlx_ptr);
	while(1)
		;
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
