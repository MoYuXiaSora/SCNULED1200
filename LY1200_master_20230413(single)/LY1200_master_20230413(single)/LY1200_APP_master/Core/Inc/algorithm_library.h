#ifndef ALGORITHM_LIBRARY_H_
#define ALGORITHM_LIBRARY_H_

#include "stdio.h"
#include "stdint.h"

//该逻辑遵循CMSIS_RTOS2标识符逻辑
#define thisOK 0
#define thisERROR -1

uint8_t even_parity(uint8_t *data, uint16_t start_i, uint16_t start_j);

#endif  // ALGORITHM_LIBRARY_H_