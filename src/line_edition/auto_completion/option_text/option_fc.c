/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_fc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:46:56 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 18:53:17 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					auto_fc(int index, char **name, char **desc)
{
	static char		*flag_tab[5] = {"-e", "-l", "-n", "-r", "-s"};
	static char		*desc_tab[5] = {
		"  -- use the editor named to edit the commands",
		"  -- list the commands rather than invoking an editor on them",
		"  -- suppress command numbers when listing with -l",
		"  -- reverse the order of the commands listed or edited",
		"  -- re-execute the command without invoking an editor"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (5);
}
