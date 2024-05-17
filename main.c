#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define MAX_DIGITS 20 // Maximum digits for unsigned long long

typedef struct  s_list
{
    unsigned long long nb;
    char    *val;
}               t_list;

unsigned long long   ft_atoll(const char *str, int *error);
char    *ft_strdup(char *src);
void    ft_putstr(char *str);
char    *ft_getnb(int fd);
char    *ft_getval(int fd, char *c);
t_list  *process(char *file);

char    *ft_getnb(int fd)
{
    int i;
    char    c[1];
    char    *str;

    if (!(str = malloc(sizeof(char) * 128)))
        exit(1);
    i = 0;
    read(fd, c, 1);
    while (c[0] == '\n')
        read(fd, c, 1);
    while (c[0] >= '0' && c[0] <= '9')
    {
        str[i] = c[0];
        read(fd, c, 1);
        i++;
    }
    str[i] = '\0';
    return (str);
}

char    *ft_getval(int fd, char *c)
{
    int i;
    char    *str;

    if (!(str = malloc(sizeof(char) * 128)))
        exit(1);
    i = 0;
    while (c[0] != '\n')
    {
        str[i] = c[0];
        read(fd, c, 1);
        i++;
    }
    str[i] = '\0';
    return (str);
}

t_list  *process(char *file)
{
    int i;
    int fd;
    char    c[1];
    t_list  *tab;
    char *tmp;

    fd = open(file, O_RDONLY);
    if (fd == -1 || !(tab = malloc(sizeof(t_list) * 35)))
        exit(1);
    i = 0;
    while (i < 35)
    {
        int error = 0;
        tab[i].nb = ft_atoll(ft_getnb(fd), &error);
        if (error)
        {
			exit(1);
        }
        read(fd, c, 1);
        while (c[0] == ' ')
            read(fd, c, 1);
        if (c[0] == ':')
            read(fd, c, 1);
        while (c[0] == ' ')
            read(fd, c, 1);
        tmp = ft_getval(fd, c);
        tab[i].val = ft_strdup(tmp);
        free(tmp);
        i++;
    }
    close(fd);
    return (tab);
}

char    *ft_strdup(char *src)
{
    int     i;
    int     len;
    char    *dst;

    len = 0;
    while (src[len] != '\0')
        len++;
    if (!(dst = (char *)malloc(sizeof(char) * (len + 1))))
        return (0);
    i = 0;
    while (i < len)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

unsigned long long   ft_atoll(const char *str, int *error)
{
    unsigned long long   res;
    int digit_count = 0;

    if (error)
        *error = 0;

    res = 0;
    while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
            *str == '\v' || *str == '\f' || *str == '\r'))
        ++str;

    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
        {
            if (error)
                *error = 1;
            return 0;
        }
        ++str;
    }

    while (*str && (*str >= '0' && *str <= '9'))
    {
        if (digit_count >= MAX_DIGITS)
        {
            if (error)
                *error = 1;
            return 0;
        }
        res = res * 10 + (*str - '0');
        ++str;
        digit_count++;
    }

    if (*str != '\0')
    {
        if (error)
            *error = 1;
        return 0;
    }

    return res;
}

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

unsigned long long getmult(unsigned long long nb)
{
    if (nb >= 1000000000000000000ULL)
        return 1000000000000000000ULL;
    else if (nb >= 1000000000000000ULL)
        return 1000000000000000ULL;
    else if (nb >= 1000000000000ULL)
        return 1000000000000ULL;
    else if (nb >= 1000000000ULL)
        return 1000000000ULL;
    else if (nb >= 1000000ULL)
        return 1000000ULL;
    else if (nb >= 1000ULL)
        return 1000ULL;
    else if (nb >= 100ULL)
        return 100ULL;
    else if (nb >= 90ULL)
        return 90ULL;
    else if (nb >= 80ULL)
        return 80ULL;
    else if (nb >= 70ULL)
        return 70ULL;
    else if (nb >= 60ULL)
        return 60ULL;
    else if (nb >= 50ULL)
        return 50ULL;
    else if (nb >= 40ULL)
        return 40ULL;
    else if (nb >= 30ULL)
        return 30ULL;
    else if (nb >= 20ULL)
        return 20ULL;
    else
        return nb;
}

void    ft_print(unsigned long long n, t_list *tab, int *first)
{
    int i;
    unsigned long long mult;

    i = 0;
    mult = getmult(n);
    if (mult >= 100)
        ft_print(n / mult, tab, first);
    if (*first == 0)
        write(1, " ", 1);
    *first = 0;
    while (tab[i].nb != mult)
        i++;
    ft_putstr(tab[i].val);
    if (mult != 0 && n % mult != 0)
        ft_print(n % mult, tab, first);
}

int main(int ac, char **av)
{
    t_list *tab;
    int *first;
    int addr_first;
    int error = 0;
    addr_first = 1;
    first = &addr_first;
    if (ac == 2)
    {
        unsigned long long num = ft_atoll(av[1], &error);
        if (error || (num == 0 && av[1][0] != '0'))
        {
            write(1,"Dict Error\n" , 11);
            return (0);
        }
        tab = process("numbers.dict");
        ft_print(num, tab, first);
    }
/*
    else
    {
        write(1, "Usage: ./program <number>\n", 26);
    }
*/
    write(1,"\n",1);
    return (0);
}

