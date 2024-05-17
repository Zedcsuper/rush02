#ifndef FT_H
# define FT_H

typedef struct	s_list
{
	unsigned long long int	nb;
	char	*val;
}		t_list;
unsigned long long int	ft_atoi(const char *str);
char	*ft_strdup(char *src);
void	ft_putstr(char *str);
char	*ft_getnb(int fd);
char	*ft_getval(int fd, char *c);
t_list	*process(char *file);

#endif
