#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int d_width;
int g_dot;
int res;

static char *ft_itoa(unsigned long n, int base)
{
    int i = 0;
    unsigned long nbr = n;
    char *str = NULL;

    if (n == 0)
        i++;
    while (nbr > 0)
    {
        nbr = nbr / base;
        i++;
    }
    str = malloc(i + 1);
    str[i] = '\0';
    while (i > 0)
    {
        str[i - 1] = n % base;
        if (n % base > 9)
            str[i - 1] = str[i - 1] - 10 + 'a';
        else
            str[i - 1] = str[i - 1] + '0';
        n = n / base;
        i--;
    }
    return (str);
}

static void ft_putchar(char str)
{
    write(1, &str, 1);
    res = res + 1;
}

static int ft_strlen(char *str)
{
    int len = 0;
    int i = 0;

    while (str[i] != '\0')
    {
        len++;
        i++;
    }
    return (len);
}

static void ft_putstr(char *str, int len)
{
    int i = 0;
    while(str[i] != '\0' && len > 0)
    {
        ft_putchar(str[i]);
        i++;
        len--;
    }  
}

static void ft_printf_x(unsigned long nbr)
{
    char *str;
    str = ft_itoa(nbr, 16);
    int  len = ft_strlen(str);

    if (g_dot != -1 && g_dot > len)
        len = g_dot;
    while (d_width > len)
    {
        ft_putchar(' ');
        d_width--;
    }
    while (len > ft_strlen(str))
    {
        ft_putchar('0');
        len--;
    }
    ft_putstr(str, ft_strlen(str));
    free(str);
}

static void ft_printf_d(int nbr)
{
    char *str;
    int minus = 0;
    if (nbr < 0)
    {
        minus = 1;
        nbr = nbr *(-1);
    }
    str = ft_itoa(nbr, 10);
    int  len = ft_strlen(str);
    if (g_dot != -1 && g_dot > len)
        len = g_dot;
    if (minus == 1 && d_width > 0)
        d_width--;
    while (d_width > len)
    {
        ft_putchar(' ');
        d_width--;
    }
    if (minus == 1)
        ft_putchar('-');
    while (len > ft_strlen(str))
    {
        ft_putchar('0');
        len--;
    }
    ft_putstr(str, ft_strlen(str));
    free(str);
}

static void ft_printf_s(char *str)
{
    int len = ft_strlen(str);
    if (g_dot != - 1 && g_dot < len)
        len = g_dot;
    while(d_width > len)
    {
        ft_putchar(' '); d_width--;
    }
    ft_putstr(str, len);
}

int ft_printf(const char *str, ... )
{
    res = 0;
    int i = 0;
    va_list ap;

    va_start(ap, str);
    while (str[i] != '\0')
    {
        if (str[i] == '%' && str[i + 1] != '\0')
        {
            i++;
            d_width = 0;
            g_dot = -1;
            while (str[i] <= '9' && str[i] >= '0')
            {
                d_width = d_width * 10 + (str[i] - '0');
                i++;
            }
            if (str[i] == '.')
            {
                g_dot = 0;
                i++;
                while (str[i] <= '9' && str[i] >= '0')
                {
                    g_dot = g_dot * 10 + (str[i] - '0');
                    i++;
                }
            }
            if (str[i] == 's')
                ft_printf_s(va_arg(ap, char *));
            else if (str[i] == 'd')
                ft_printf_d(va_arg(ap, int));
            else if (str[i] == 'x')
                ft_printf_x(va_arg(ap, unsigned int));
            else
                ft_putchar(str[i]);
        }
        else
            ft_putchar(str[i]);
        i++;
    }
    va_end(ap);
    return(res);
}



int main(void)
{
    printf("[%10.2s]\n", "toto");
    ft_printf("[%10.2s]\n", "toto");
    printf("Magic [%s] is [%10.5d]\n", "number", -42);
    ft_printf("Magic [%s] is [%10.5d]\n", "number", -42);
    printf("Hexadecimal for [%.5d] is [%10.5x]\n", -42, 42);
    ft_printf("Hexadecimal for [%.5d] is [%10.5x]\n", -42, 42);
}