/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:54:43 by malde-ch          #+#    #+#             */
/*   Updated: 2024/12/05 19:54:46 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isblank(char c)
{
	if (c <= 32)
		return (1);
	return (0);
}

static int	ft_isvalid(char c, int base, char *digits, char *digits2)
{
	while (base--)
		if (digits[base] == c || digits2[base] == c)
			return (1);
	return (0);
}

static int	ft_value_of(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

static void	create_malloc(char **digits, char **digits2)
{
	*digits = ft_strdup("0123456789abcdef");
	if (!digits)
		return ;
	*digits2 = ft_strdup("0123456789ABCDEF");
	if (!digits2)
	{
		free(digits);
		return ;
	}
}

int	ft_atoi_base(const char *str, int str_base)
{
	int		result;
	int		sign;
	char	*digits;
	char	*digits2;

	create_malloc(&digits, &digits2);
	if (!digits || !digits2)
		return (0);
	result = 0;
	while (ft_isblank(*str))
		str++;
	if (*str == '-')
		sign = -1;
	else
		sign = 1;
	while (*str == '-' || *str == '+')
		str++;
	while (ft_isvalid(*str, str_base, digits, digits2))
		result = result * str_base + ft_value_of(*str++);
	free(digits);
	free(digits2);
	return (result * sign);
}
