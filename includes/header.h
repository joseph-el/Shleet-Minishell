/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:42:58 by omoussao          #+#    #+#             */
/*   Updated: 2023/01/12 10:53:22 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define UNCLOSED_SQ	"unclosed single quotes"
# define UNCLOSED_DQ	"unclosed double quotes"

typedef enum e_token
{
	CMDBEGIN = 1 << 0,
	ENDOFCMD = 1 << 1,
	WSPACE = 1 << 2,
	WORD = 1 << 3,
	PIPE = 1 << 4,
	AND = 1 << 5,
	
	OR = 1 << 6,
	OPAR = 1 << 7,
	CPAR = 1 << 8,
	BG = 1 << 9,
	FG = 1 << 10,
	
	DSEMI = 1 << 11,
	VAR = 1 << 12,
	TILDE = 1 << 13,
	WILDC = 1 << 14,
	SQUOTE = 1 << 15,
	DQUOTE = 1 << 16,
	LESS = 1 << 17,
	DLESS = 1 << 18,
	GREAT = 1 << 19,
	DGREAT = 1 << 20,
	GROUP = 1 << 21,
	STRING = (GROUP | WORD | TILDE | WILDC | VAR | SQUOTE | DQUOTE),
	REDIRECT = (LESS | DLESS | GREAT | DGREAT),
	CONNECTOR = (AND | OR | PIPE | FG | BG)
}	t_token;

typedef struct s_node
{
	t_token			token;
	char			*val;
	struct s_list	*val_grp;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_list
{
	int		len;
	t_node	*top;
	t_node	*bottom;
}				t_list;