#include "miniRT.h"

static char	*create_sub(const char *s, char *sub, unsigned int start,
		size_t len)
{
	size_t	i;

	i = 0;
	while (s[start + i] && i != len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*rt_ft_substr(t_rt *rt, char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	l_s;

	i = 0;
	l_s = ft_strlen(s);
	if (start > l_s)
	{
		sub = wrap_malloc(rt,  sizeof(*sub));
		if (!sub)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	while (s[start + i] && i != len)
		i++;
	sub = wrap_malloc(rt,  i * sizeof(*sub) + sizeof(*sub));
	if (!sub)
		return (NULL);
	else
	{
		sub = create_sub(s, sub, start, len);
		return (sub);
	}
}
