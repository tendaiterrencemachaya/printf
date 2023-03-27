#include "main.h"

void print_buffer(char buffer[], int *buffInd);

/**
 * _printf - Printf function alx project
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int index, printCount = 0, printedChars = 0;
	int flags, width, precision, size, buffInd = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (index = 0; format && format[index] != '\0'; index++)
	{
		if (format[index] != '%')
		{
			buffer[buffInd++] = format[index];
			if (buffInd == BUFF_SIZE)
				print_buffer(buffer, &buffInd);
			/* write(1, &format[index], 1);*/
			printedChars++;
		}
		else
		{
			print_buffer(buffer, &buffInd);
			flags = get_flags(format, &index);
			width = get_width(format, &index, list);
			precision = get_precision(format, &index, list);
			size = get_size(format, &index);
			++index;
			printCount = handle_print(format, &index, list, buffer,
				flags, width, precision, size);
			if (printCount == -1)
				return (-1);
			printedChars += printCount;
		}
	}

	print_buffer(buffer, &buffInd);

	va_end(list);

	return (printedChars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buffInd: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buffInd)
{
	if (*buffInd > 0)
		write(1, &buffer[0], *buffInd);

	*buffInd = 0;
}

