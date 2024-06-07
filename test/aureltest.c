/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aureltest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:36:44 by abrabant          #+#    #+#             */
/*   Updated: 2024/06/07 16:18:03 by fschuh           ###   ########.fr       */
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
        // Coordinates out of bounds, do not place the pixel
        return;
    }

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int render_shape(t_img *img, t_rect shape)
{
    int i;
    int j;
    int current_color;

    current_color = shape.color;

    i = shape.y;
    while (i < shape.y + shape.height)
    {
        j = shape.x;
        while (j < shape.x + shape.width)
            img_pix_put(img, j++, i, current_color);
         ++i;
    }
    return (0);
}

int render_rect(t_img *img, t_rect rect)
{
    int i;
    int j;
    int current_color;

    int r = 100;
    int g = 100;
    int b = rand() % 255;

    // Create a random color using ft_create_trgb
    current_color = ft_create_trgb(0, r, g, b);

    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width)
            img_pix_put(img, j++, i, current_color);
         ++i;
    }
    return (0);
}

int render_circle(t_img *img, t_circ circ)
{
    int current_color;
    current_color = circ.color;

    static const double PI = 3.1415926535;
    double i, angle, x1, y1;
    int x, y;

    // Draw the circle outline
    i = 0;
    while (i < 360)
    {
        angle = i;
        x1 = circ.radius * cos(angle * PI / 180);
        y1 = circ.radius * sin(angle * PI / 180);
        img_pix_put(img, circ.x + x1, circ.y + y1, current_color);
        i += 0.1;
    }

    // Fill the circle
    y = -circ.radius;
    while (y <= circ.radius)
    {
        current_color -= 3;
		x = -circ.radius;
        while (x <= circ.radius)
        {
            if (x * x + y * y <= circ.radius * circ.radius)
            {
                img_pix_put(img, circ.x + x, circ.y + y, current_color);
            }
            x++;
        }
        y++;
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
		// Change the background color
		int red  = rand() % 256;
		int green  = rand() % 256;
		int blue = rand() % 256;

    // Combine them into a color using ft_create_trgb
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
		ft_print_ascii_art("YEAH DONE", KCYN, 1);
		exit(0); // Terminate the program
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

	// Extract RGB components from the current background color
	red = (data->bg_color >> 16) & 0xFF;
	green = (data->bg_color >> 8) & 0xFF;
	blue = data->bg_color & 0xFF;

	// Adjust brightness based on mouse wheel input
	if (button == 4) // Mouse wheel up
	{
		red = (red + 10 > 255) ? 255 : red + 10;
		green = (green + 10 > 255) ? 255 : green + 10;
		blue = (blue + 10 > 255) ? 255 : blue + 10;
	}
	else if (button == 5) // Mouse wheel down
	{
		red = (red - 10 < 0) ? 0 : red - 10;
		green = (green - 10 < 0) ? 0 : green - 10;
		blue = (blue - 10 < 0) ? 0 : blue - 10;
	}

	// Combine them back into a color using ft_create_trgb
	data->bg_color = ft_create_trgb(0, red, green, blue);
	printf("Mouse wheel moved at position (%d, %d), new background color: 0x%X\n", x, y, data->bg_color);
	render(data);
	return (0);
}

int	handle_mousemove(int x, int y, t_data *data)
{
	render(data);
	x = 0;
	y = 0;
	return (x+y);
}

int	handle_mousehook(int button, int x, int y, t_data *data)
{
	if (button == 4 || button == 5)
		return handle_mousewheel(button, x, y, data);
	if (button == 1)
    {
        int rect_width = rand() % 100 + 20; // Random width between 20 and 120
        int rect_height = rand() % 100 + 20; // Random height between 20 and 120
        int rect_x = x - rect_width / 2; // Place rectangle centered around mouse click
        int rect_y = y - rect_height / 2;
        render_rect(&data->img, (t_rect){rect_x, rect_y, rect_width, rect_height, GREEN_PIXEL});
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
    }
	printf("Mouse button %d clicked at position (%d, %d)\n", button, x, y);
	return (0);
}

int	render(t_data *data)
{
	int bgcolor; 
	if (data->win_ptr == NULL)
		return (1);
	// color = rand() % 0xAAAAAA; 	
	 bgcolor = data->bg_color;
	 
	render_background(&data->img, bgcolor);
	render_rect(&data->img, (t_rect){10, 10, 100, 100, GREEN_PIXEL});
	render_shape(&data->img, (t_rect){150, 10, 60, 90, WHITE_PIXEL});
	render_circle(&data->img, (t_circ){200, 200, 40, GREEN_PIXEL});
	// render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	
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



	/* Setup hooks */ 
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	data.bg_color = rand() % 0xFFFFFF;
	// mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_mouse_hook(data.win_ptr, &handle_mousehook, &data);
	mlx_hook(data.win_ptr, MotionNotify, PointerMotionMask, handle_mousemove, &data);

		render(&data);
	mlx_loop(data.mlx_ptr);
	
	while(1)
		;

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);

}