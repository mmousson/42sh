/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_stty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:59:18 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:59:19 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_stty(int index, char **name, char **desc)
{
	static char	*flag_tab[64] = {
		"-brkint", "-clocal", "-columns", "-cread", "-cs8", "-cstopb",
		"-discard", "-dsusp", "-echo", "-echoctl", "-echoe", "-echok",
		"-echoke", "-echonl", "-echoprt", "-eof", "-eol", "-eol2",
		"-erase", "-flusho", "-hupcl", "-icanon", "-icrnl", "-iexten",
		"-ignbrk", "-igncr", "-ignpar", "-imaxbel", "-inlcr", "-inpck",
		"-intr", "-isig", "-istrip", "-iuclc", "-ixany", "-ixoff",
		"-ixon", "-kill", "-lnext", "-noflsh", "-ocrnl", "-ofdel",
		"-ofill", "-olcuc", "-onlcr", "-onlret", "-onocr", "-opost",
		"-parenb", "-parext", "-parmrk", "-parodd", "-pending", "-quit",
		"-raw", "-reprint", "-rows", "-sane", "-start", "-stop",
		"-susp", "-tostop", "-werase", "-xcase"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(" ");
	return (64);
}
