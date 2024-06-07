/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asciiart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:09:38 by fschuh            #+#    #+#             */
/*   Updated: 2024/06/04 17:05:43 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// can be in the libft
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

static	char (*asciifont1())[4][20]
{
	static char ascii_table1[44][4][20] = {
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

static	void	ft_print_ascii_top_line(char teststring[26])
{
	int	i;

	i = 0;
	ft_printf(" _");
	while (teststring[i])
	{
		if (ft_toupper(teststring[i]) >= 'A' 
			&& ft_toupper(teststring[i]) <= 'Z')
			ft_printf("____");
		else if ((teststring[i] >= '0' && teststring[i] <= '9') 
			|| teststring[i] == '_' || teststring[i] == '.' 
			|| teststring[i] == ':' || teststring[i] == '('
			|| teststring[i] == ')' || teststring[i] == ' ')
			ft_printf("____");
		i++;
	}
	i = 0;
	ft_printf("\n/ ");
	while (teststring[i])
	{
		if (ft_toupper(teststring[i]) >= 'A' 
			&& ft_toupper(teststring[i]) <= 'Z')
			ft_printf("    ");
		else if ((teststring[i] >= '0' && teststring[i] <= '9') 
			|| teststring[i] == '_' || teststring[i] == '.'
			|| teststring[i] == ':' || teststring[i] == '('
			|| teststring[i] == ')')
			ft_printf("    ");
		else if (teststring[i] == ' ')
			ft_printf("    ");
		i++;
	}
	ft_printf("\\\n");
}

static	void	ft_print_ascii_line1(char teststring[26], char (*ascii_table)[4][20])
{
	int	i;

	i = 0;
	ft_printf("| ");
	while (teststring[i])
	{
		if (ft_toupper(teststring[i]) >= 'A' 
			&& ft_toupper(teststring[i]) <= 'Z')
			ft_printf("%s░", ascii_table[ft_toupper(teststring[i]) - 'A'][1]);
		else if (teststring[i] >= '0' && teststring[i] <= '9')
			ft_printf("%s░", ascii_table[teststring[i] - '0' + 26][1]);
		else if (teststring[i] == '_')
			ft_printf("%s░", ascii_table[40][1]);
		else if (teststring[i] == '.')
			ft_printf("%s░", ascii_table[36][1]);
		else if (teststring[i] == ':')
			ft_printf("%s░", ascii_table[39][1]);
		else if (teststring[i] == '(')
			ft_printf("%s░", ascii_table[42][1]);
		else if (teststring[i] == ')')
			ft_printf("%s░", ascii_table[43][1]);
		else if (teststring[i] == ' ')
			ft_printf("░░░░");
		i++;
	}
	ft_printf("|\n");
}

static	void	ft_print_ascii_line2(char teststring[26], char (*ascii_table)[4][20])
{
	int	i;

	i = 0;
	ft_printf("| ");
	while (teststring[i])
	{
		if (ft_toupper(teststring[i]) >= 'A' && ft_toupper(teststring[i]) <= 'Z')
			ft_printf("%s░", ascii_table[ft_toupper(teststring[i]) - 'A'][2]);
		else if (teststring[i] >= '0' && teststring[i] <= '9')
			ft_printf("%s░", ascii_table[teststring[i] - '0' + 26][2]);
		else if (teststring[i] == '_')
			ft_printf("%s░", ascii_table[40][2]);
		else if (teststring[i] == '.')
			ft_printf("%s░", ascii_table[36][2]);
		else if (teststring[i] == ':')
			ft_printf("%s░", ascii_table[39][2]);
		else if (teststring[i] == '(')
			ft_printf("%s░", ascii_table[42][2]);
		else if (teststring[i] == ')')
			ft_printf("%s░", ascii_table[43][2]);
		else if (teststring[i] == ' ')
			ft_printf("░░░░");
		i++;
	}
	ft_printf("|\n");
}

static	void	ft_print_ascii_line3(char teststring[26], char (*ascii_table)[4][20])
{
	int	i;

	i = 0;
	ft_printf("| ");
	while (teststring[i])
	{
		if (ft_toupper(teststring[i]) >= 'A' && ft_toupper(teststring[i]) <= 'Z')
			ft_printf("%s░", ascii_table[ft_toupper(teststring[i]) - 'A'][3]);
		else if (teststring[i] >= '0' && teststring[i] <= '9')
			ft_printf("%s░", ascii_table[teststring[i] - '0' + 26][3]);
		else if (teststring[i] == '_')
			ft_printf("%s░", ascii_table[40][3]);
		else if (teststring[i] == '.')
			ft_printf("%s░", ascii_table[36][3]);
		else if (teststring[i] == ':')
			ft_printf("%s░", ascii_table[39][3]);
		else if (teststring[i] == '(')
			ft_printf("%s░", ascii_table[42][3]);
		else if (teststring[i] == ')')
			ft_printf("%s░", ascii_table[43][3]);
		else if (teststring[i] == ' ')
			ft_printf("░░░░");
		i++;
	}
	ft_printf("|\n");
}

static	void	ft_print_ascii_bottom_line(char teststring[26])
{
	int	i;

	i = 0;
	ft_printf("\\_");
	while (teststring[i])
	{
		if (ft_toupper(teststring[i]) >= 'A' && ft_toupper(teststring[i]) <= 'Z')
			ft_printf("____");
		else if ((teststring[i] >= '0' && teststring[i] <= '9')
			|| teststring[i] == '_' || teststring[i] == '.' 
			|| teststring[i] == ':' || teststring[i] == '(' 
			|| teststring[i] == ')')
			ft_printf("____");
		else if (teststring[i] == ' ')
			ft_printf("____");
		i++;
	}
	ft_printf("/\n");
}

void	ft_print_ascii_art(char teststring[26], char color[], int fd)
{
	char	(*ascii_table)[4][20] = asciifont1();
	fd++;
	ft_printf("%s", color);
	ft_print_ascii_top_line(teststring);
	ft_print_ascii_line1(teststring, ascii_table);
	ft_print_ascii_line2(teststring, ascii_table);
	ft_print_ascii_line3(teststring, ascii_table);
	ft_print_ascii_bottom_line(teststring);
	ft_printf("%s", KNRM);

}
