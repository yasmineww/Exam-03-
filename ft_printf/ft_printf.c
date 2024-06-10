#include  <stdio.h>
#include  <stdarg.h>
#include  <unistd.h>

void	ft_putchar(int c, int *size)
{
	(*size)++;
	write(1, &c, 1);
}

void	ft_putstr(char *s, int *size)
{
	if (s == NULL)
	{
		*size += 6;
		write(1, "(null)", 6);
		return ;
	}
	while (*s)
	{
		ft_putchar(*s, size);
		s++;
	}
}

void	ft_putnbr(long long n, int *size)
{
	// if (n == -2147483648)
	// {
	// 	ft_putstr("-2147483648", size);
	// }
	if (n < 0)
	{
		n = n * -1;
		ft_putchar('-', size);
		ft_putnbr(n, size);
	}
	else if (n > 9)
	{
		ft_putnbr((n / 10), size);
		ft_putnbr((n % 10), size);
	}
	else
	{
		ft_putchar((n + '0'), size);
	}
}

void	ft_printhex(unsigned long n, int *size)
{
	char	*str;

	str = "0123456789abcdef";
	if (n >= 16)
	{
		ft_printhex((n / 16), size);
		ft_printhex((n % 16), size);
	}
	else if (n < 16)
	{
		ft_putchar(str[n], size);
	}
}


static void	ft_helper(const char *format, int *size, va_list ap)
{
	if (*format == 'd')
		ft_putnbr(va_arg(ap, int), size);
	else if (*format == 's')
		ft_putstr(va_arg(ap, char *), size);
	else if (*format == 'x')
		ft_printhex(va_arg(ap, unsigned int), size);
	else
		ft_putchar(*format, size);
}
int	ft_printf(const char *format, ...)
{
	int		size;
	va_list	ap;

	va_start(ap, format);
	size = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				break ;
			ft_helper(format, &size, ap);
		}
		else
		{
			write(1, format, 1);
			size++;
		}
		format++;
	}
	va_end(ap);
	return (size);
}