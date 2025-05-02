
#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H


#define __RAM_CODE__ 		__attribute__((section("ram_code")))




/*

#include <stdint.h> // 引入标准库以使用C99特性
 
int main(void) {
    long long int my64bitVar = 0; // 定义一个64位整数变量
    return 0;
}



int main(void) {
    __int64 my64bitVar = 0; // 定义一个64位整数变量
    return 0;
}


*/


typedef long long int     int64_t;







typedef unsigned char   	uint8;
typedef unsigned char   	UINT8;
typedef unsigned char   	INT8U;
typedef signed char   		kal_int8;
typedef signed char   		int8;
typedef signed char   		sint8;
typedef signed char   		INT8S;

typedef unsigned char   	uint8_t;
typedef unsigned char   	kal_uint8;
typedef unsigned char   	u8;

typedef unsigned char 		BYTE;

typedef signed short   	  int16;
typedef unsigned short   	uint16;
typedef unsigned short   	uint16_t;
typedef unsigned short  	kal_uint16;
typedef unsigned short   	u_intHW;
typedef unsigned short   	ushort;

typedef signed int   		  int32;
typedef signed int   		  INT32;
typedef signed int   		  INT32S;
typedef signed int   		  sint32;

typedef unsigned int   		UINT32;
typedef unsigned int      INT32U;
typedef unsigned int   		uint32;
typedef unsigned int   		uint32_t;
typedef signed int   		  int32_t;
typedef unsigned int    	kal_uint32;

typedef unsigned char   	kal_bool; //* kal_bool, true=1, false=0 */

typedef unsigned char   	BOOL;

#define true		1
#define false		0	


#define TRUE		1
#define FALSE		0	


#define PUBLIC						
#define PRIVATE static
#define PROTECTED
#define CONST const
#define INT16 short
#define UINT16 unsigned short
#define INT32 int
#define UINT32 unsigned int
#define INT8 char
#define UINT8 unsigned char
#define CHAR char
#define VOID void
#define VOLATILE volatile	
#define EXPORT extern



typedef volatile unsigned short     REG16;
typedef volatile unsigned int       REG32;



#define  DEBUG_UATR0_PRINT_LOG            1
#define pDEBUG                            0




#define     __I     volatile                  /*!< defines 'read only' permissions      */
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */



#define SET_BITFIELD(reg, field, value)     (((reg) & ~field ## _MASK) | field(value))
#define GET_BITFIELD(reg, field)            (((reg) & field ## _MASK) >> field ## _SHIFT)




/* Error codes returned by API*/
#define NOERROR			    	0x00 
#define RETRY			    		0x01
#define TIMEOUT			    	0x02
#define INVALIDERRORCODE 	0xfe

#define NULL	0





/* data transport buffer */
typedef struct st_dataBuf {
    uint8  *buf;
    uint8  transport;
    uint16 dataLen;
    uint16 bufLen;
} DataBuf;




#endif 
