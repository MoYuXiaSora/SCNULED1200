#include "algorithm_library.h"

/*
* 偶校验2
* uint8_t *data 输入数组 
* uint16_t start_i 开始校验数组序号（包含）
* uint16_t start_j 结束校验数组序号（包含）
*/

uint8_t even_parity(uint8_t *data, uint16_t start_i, uint16_t start_j)
{
    unsigned char parity = 0;
    unsigned char n_bits = 0;
    uint16_t data_long = 0;
    unsigned char value = 0;

    uint16_t i=start_i;
    data_long = start_j - start_i + 1;

    for (i=start_i; i < start_i+data_long; i++)
    {
      /* code */
      value = data[i];
			n_bits = sizeof(data[start_i]) * 8;
      while( n_bits >0)
      {
          parity += value & 1;
          value >>=1;
          n_bits -=1;
      }
    }
    
    /*
    * 当实际数据中“1”的个数为偶数，校验位是“1”，否则校验位是“0”
    */
    return (parity % 2) != 0;
	
}