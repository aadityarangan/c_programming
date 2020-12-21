#include <stdlib.h>
#include <stdint.h>
#include "circular_buffer.h"

uint16_t circular_buffer_push(circular_buffer_t *buffer, uint8_t *data, uint16_t length)
{
	uint16_t count = 0U, current_write, current_read;

	current_write = buffer->write;
	current_read = buffer->read;

	if ((current_write - current_read + length) > CIRCULAR_BUFFER_SIZE)
	{
		length = CIRCULAR_BUFFER_SIZE - (current_write - current_read);
	}

	for (count = 0U; count < length; count++)
	{
		buffer->data[current_write % CIRCULAR_BUFFER_SIZE] = data[count];
		current_write++;
	}

	buffer->write = current_write;
	return count;
}

uint16_t circular_buffer_pop(uint8_t *data, circular_buffer_t *buffer, uint16_t length)
{
	uint16_t count, next_read = buffer->read, next_write = buffer->write;

	if (length > (next_write - next_read))
	{
		length = next_write - next_read;
	}

	if (data != NULL)
	{
		for (count = 0U; count < length; count++)
		{
			data[count] = buffer->data[buffer->read % CIRCULAR_BUFFER_SIZE];
			buffer->read++;
			
		}
	}
	else
	{
		count = length;
		buffer->read += length;
	}

	return count;
}

uint16_t circular_buffer_peak(uint8_t *data, uint16_t startposition, circular_buffer_t *buffer, uint16_t length)
{
	uint16_t count = 0U, next_read = buffer->read, next_write = buffer->write;

	if(next_write-next_read <= startposition)
		return 0;
	next_read += startposition;

	if (length > (next_write - next_read))
	{
		length = next_write - next_read;
	}

	for (count = 0U; count < length; count++)
	{
		data[count] = buffer->data[next_read % CIRCULAR_BUFFER_SIZE];
		next_read++;
	}

	return count;
}

uint16_t compute_circular_buffer_read_space(circular_buffer_t *buffer)
{
	uint16_t read = buffer->read, write = buffer->write;
	return (write-read);
}

uint16_t compute_circular_buffer_write_space(circular_buffer_t *buffer)
{
	uint16_t read = buffer->read, write = buffer->write;
	return (CIRCULAR_BUFFER_SIZE - (write - read));
}