#include "miniRT.h"

int find_elem_id(t_elem *elem)
{
	int	i;

	i = 0;
	if (elem[0].id == 0)
		return (i);
	while (1)
	{
		if (elem[i].id == 0)
			return (i);
		i++;
	}
	return (i);
}