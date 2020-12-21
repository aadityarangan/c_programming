#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdlib.h>
#include <stdint.h>

#define CIRCULAR_BUFFER_SIZE        512

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t data[CIRCULAR_BUFFER_SIZE];
    uint16_t read;
    uint16_t write;
}circular_buffer_t;


uint16_t circular_buffer_push(circular_buffer_t *buffer, uint8_t *data, uint16_t length);
uint16_t circular_buffer_pop(uint8_t *data, circular_buffer_t *buffer, uint16_t length);
uint16_t circular_buffer_peak(uint8_t *data, uint16_t startposition, circular_buffer_t *buffer, uint16_t length);
uint16_t compute_circular_buffer_read_space(circular_buffer_t *buffer);
uint16_t compute_circular_buffer_write_space(circular_buffer_t *buffer);

/*********************************************** User Wrappers ***********************************************/

#ifdef __cplusplus
}
#endif
#endif