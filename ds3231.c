/*
 * ds3231.c
 *
 *  Created on: Oct 13, 2021
 *      Author: saranyan
 */

#include <stdint.h>
#include "general_utility_functions.h"
#include "i2c.h"
#include "ds3231.h"

#define BCD_TO_INT_H(X) (X >> 4)
#define BCD_TO_INT_L(X) (X & 0b00001111)

char date_time[36] = "Date: 00-00-2000     Time: 00:00:00";

char * Get_Date_Time()
{
	char string_pointer[2];

	//--------------Time-------------//
	//------------Seconds------------//
	Integer_to_Characters((uint8_t)BCD_TO_INT_L(i2c_data_buffer[0]), string_pointer);
	date_time[34] = string_pointer[0];
	Integer_to_Characters((uint8_t)BCD_TO_INT_H(i2c_data_buffer[0]), string_pointer);
	date_time[33] = string_pointer[0];

	//------------Minutes------------//
	Integer_to_Characters((uint8_t)BCD_TO_INT_L(i2c_data_buffer[1]), string_pointer);
	date_time[31] = string_pointer[0];
	Integer_to_Characters((uint8_t)BCD_TO_INT_H(i2c_data_buffer[1]), string_pointer);
	date_time[30] = string_pointer[0];

	//-------------Hour--------------//
	Integer_to_Characters((uint8_t)BCD_TO_INT_L(i2c_data_buffer[2]), string_pointer);
	date_time[28] = string_pointer[0];
	Integer_to_Characters((uint8_t)(BCD_TO_INT_H(i2c_data_buffer[2]) & 0b00000001), string_pointer);
	date_time[27] = string_pointer[0];


	//-------------Date--------------//
	//--------------Day--------------//
	Integer_to_Characters((uint8_t)BCD_TO_INT_L(i2c_data_buffer[4]), string_pointer);
	date_time[7] = string_pointer[0];
	Integer_to_Characters((uint8_t)(BCD_TO_INT_H(i2c_data_buffer[4]) & 0b00000011), string_pointer);
	date_time[6] = string_pointer[0];

	//-------------Month-------------//
	Integer_to_Characters((uint8_t)BCD_TO_INT_L(i2c_data_buffer[5]), string_pointer);
	date_time[10] = string_pointer[0];
	Integer_to_Characters((uint8_t)(BCD_TO_INT_H(i2c_data_buffer[5]) & 0b00000001), string_pointer);
	date_time[9] = string_pointer[0];
	//--------------Year-------------//
	Integer_to_Characters((uint8_t)BCD_TO_INT_L(i2c_data_buffer[6]), string_pointer);
	date_time[15] = string_pointer[0];
	Integer_to_Characters((uint8_t)BCD_TO_INT_H(i2c_data_buffer[6]), string_pointer);
	date_time[14] = string_pointer[0];

	return date_time;
}
