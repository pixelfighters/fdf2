/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asciiart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kami <kami@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:58:23 by kami              #+#    #+#             */
/*   Updated: 2024/06/11 14:28:44 by kami             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_ascii_art_line(char c, int line, char (*ascii_table)[4][20]);
static void	print_ascii_art_lines(char *teststring, char (*ascii_table)[4][20]);

static	char	(*asciifont1(void))[4][20]
{
	static char	ascii_table1[44][4][20] = {
	{"A", "█▀█", "█▀█", "▀░▀"}, {"B", "█▀▄", "█▀▄", "▀▀░"},
	{"C", "█▀▀", "█░░", "▀▀▀"}, {"D", "█▀▄", "█░█", "▀▀░"},
	{"E", "█▀▀", "█▀▀", "▀▀▀"}, {"F", "█▀▀", "█▀▀", "▀░░"},
	{"G", "█▀▀", "█░█", "▀▀▀"}, {"H", "█░█", "█▀█", "▀░▀"},
	{"I", "▀█▀", "░█░", "▀▀▀"}, {"J", "▀▀█", "░░█", "▀▀░"},
	{"K", "█░█", "█▀▄", "▀░▀"}, {"L", "█░░", "█░░", "▀▀▀"},
	{"M", "█▄█", "█░█", "▀░▀"}, {"N", "█▀█", "█░█", "▀░▀"},
	{"O", "█▀█", "█░█", "▀▀▀"}, {"P", "█▀█", "█▀▀", "▀░░"},
	{"Q", "▄▀▄", "█\\█", "░▀\\"}, {"R", "█▀▄", "█▀▄", "▀░▀"},
	{"S", "█▀▀", "▀▀█", "▀▀▀"}, {"T", "▀█▀", "░█░", "░▀░"},
	{"U", "█░█", "█░█", "▀▀▀"}, {"V", "█░█", "█░█", "░▀░"},
	{"W", "█░█", "█▄█", "▀░▀"}, {"X", "█░█", "▄▀▄", "▀░▀"},
	{"Y", "█░█", "░█░", "░▀░"}, {"Z", "▀▀█", "▀░░", "▀▀▀"},
	{"_", "░░░", "░░░", "▀▀▀"}, {" ", "░░░", "░░░", "░░░"},
	{"(", "▄▀░", "█░░", "░▀░"}, {")", "▀▄░", "░█░", "▀░░"},
	{" ", "░░░", "░░░", "░░░"}, {"(", "▄▀░", "█░░", "░▀░"},
	{")", "▀▄░", "░█░", "▀░░"}
	};

	return (ascii_table1);
}

static void	print_border(char *teststring, int line)
{
	int	i;

	i = 0;
	if (line == 2)
	{
		ft_printf("/");
		while (teststring[i++] != '\0')
			ft_printf("    ");
		ft_printf(" \\\n");
	}
	else
	{
		if (line == 5)
			ft_printf("\\_");
		else
			ft_printf(" _");
		while (teststring[i++] != '\0')
			ft_printf("____");
		if (line == 5)
			ft_printf("/");
		ft_printf("\n");
	}
}

static void	print_ascii_art_line(char c, int line, char (*ascii_table)[4][20])
{
	int	index;

	if (ft_toupper(c) >= 'A' && ft_toupper(c) <= 'Z')
		ft_printf("%s░", ascii_table[ft_toupper(c) - 'A'][line]);
	else if (c >= '0' && c <= '9')
		ft_printf("%s░", ascii_table[c - '0' + 26][line]);
	else if (strchr("_.'():", c))
	{
		index = 36 + (ft_strchr("_.'():", c) - ft_strchr("_.'():", '_'));
		ft_printf("%s░", ascii_table[index][line]);
	}
	else if (c == ' ')
		ft_printf("░░░░");
}

static void	print_ascii_art_lines(char *teststring, char (*ascii_table)[4][20])
{
	int	line;
	int	i;

	line = 1;
	i = 0;
	print_border(teststring, 1);
	print_border(teststring, 2);
	while (line <= 3)
	{
		ft_printf("| ");
		while (teststring[i])
		{
			print_ascii_art_line(teststring[i], line, ascii_table);
			i++;
		}
		ft_printf("|\n");
		i = 0;
		line++;
	}
	print_border(teststring, 5);
}

void	ft_print_ascii_art(char *teststring, char *color, int fd)
{
	char	(*ascii_table)[4][20];

	ascii_table = asciifont1();
	fd++;
	ft_printf("%s", color);
	print_ascii_art_lines(teststring, ascii_table);
	ft_printf("%s", KNRM);
}
/* 
int main()
{
	ft_print_ascii_art("TAKE ME World", KRED, 1);
	return (0);
} */