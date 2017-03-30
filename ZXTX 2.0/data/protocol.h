

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


#define HBTK_1000Q 		0xA1  //（通信转换模块）第一代探测器
#define HBTK_1000D		0xA2  //D型探测器
#define HBTK_1000X		0xA3  //一带多低端探测器HBTK-1000X
#define HBTK_1000XW		0xA4	//
#define HBTK_1000QX		0xA5	//new HBTK-1000QX

#define HBTK_1000DQ		0xA2
#define HBTK_1000XQ		0xA3
#define HBTK_1000WQ		0xA4
#define HBTK_1000LQ		0xA5	
#define HBTK_1000HQ		0xA6
#define HBTK_1000LB		0xA7

//探头类型
#define HBTT_TYPE_S     0xA0	//三代剩余电流探头
#define HBTT_TYPE_W     0xA1	//三代温度探头
#define HBTT_TYPE_LD	0xaa	//漏电探测器类型
#define HBTT_TYPE_DL	0xab	//电流探测器类型
#define HBTT_TYPE_WD	0xac	//温度探测器类型
#define HBTT_TYPE_YD	0xad	//第一代控制器
#define HBTT_TYPE_DX	0xae	//多线探头
#define HBTT_TYPE_NX	0xAF	//N线探头

									
#define SYN_BYTE	0xAA		//同步码
#define ERR_BYTE	0xA5		//错误码

#define DATA_NORMAL        0
#define DATA_GZ_BDKL       1           /*备电故障*/
#define DATA_GZ_TXGZ       2           /*通信故障*/
#define DATA_GZ_ZXDL       3           /*二总线短路*/
#define DATA_GZ_BDGD       4           /*备电供电*/
#define DATA_GZ_MKDX       5           /*通信模块掉线*/
#define DATA_GZ_TKSYSB     6           /*试验失败*/
#define DATA_GZ_TKDX       7           /*探测器掉线*/
#define DATA_GZ_CANERR     8           /*CAN总线故障*/
#define DATA_GZ_TT         10          /*探头故障*/
#define DATA_GZ_ZCOM       11          /*主通信故障*/
#define DATA_GZ_ZKDX       12          /*监控设备掉线*/

#define DATA_GZ_MIN        1
#define DATA_GZ_MAX        50

#define DATA_BJ            51           /*报警*/
#define DATA_YJ            52

#define DATA_CZ_MIN        101
#define DATA_CZ_MAX        150

#define DATA_CZ_RESET      101          /*主机复位*/
#define DATA_CZ_XY         102          /*消音*/
#define DATA_CZ_KAIJI      103          /*开机*/
#define DATA_CZ_GUANJI     104          /*关机*/

#include "mytype.h"

#define TPROC_T1     0xFA
#define TPROC_T2     0xFB

typedef struct TProtocol
{
    uint8 T1;
    uint8 T2;
    uint8 Tcnt;
    uint8 buff[128];
    uint16 crc;
	uint8  state;
    uint8  size;
}__PACKED__ TProtocol;

#ifndef PROTOCOL_GLOBAL
#define EXT   extern 
#else
#define EXT
#endif 


int Pro_Add( TProtocol *pPro, uint8 dat );
int Set_Crc( TProtocol *pPro );
int ProTransData( int hcom, uint8 *dat, int size ); 
void ProInit( void );
int ProAddData( TProtocol *pPro, uint8 *dat, int size );

#undef EXT
#endif //__PROTOCOL_H__



