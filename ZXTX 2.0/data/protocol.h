

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


#define HBTK_1000Q 		0xA1  //��ͨ��ת��ģ�飩��һ��̽����
#define HBTK_1000D		0xA2  //D��̽����
#define HBTK_1000X		0xA3  //һ����Ͷ�̽����HBTK-1000X
#define HBTK_1000XW		0xA4	//
#define HBTK_1000QX		0xA5	//new HBTK-1000QX

#define HBTK_1000DQ		0xA2
#define HBTK_1000XQ		0xA3
#define HBTK_1000WQ		0xA4
#define HBTK_1000LQ		0xA5	
#define HBTK_1000HQ		0xA6
#define HBTK_1000LB		0xA7

//̽ͷ����
#define HBTT_TYPE_S     0xA0	//����ʣ�����̽ͷ
#define HBTT_TYPE_W     0xA1	//�����¶�̽ͷ
#define HBTT_TYPE_LD	0xaa	//©��̽��������
#define HBTT_TYPE_DL	0xab	//����̽��������
#define HBTT_TYPE_WD	0xac	//�¶�̽��������
#define HBTT_TYPE_YD	0xad	//��һ��������
#define HBTT_TYPE_DX	0xae	//����̽ͷ
#define HBTT_TYPE_NX	0xAF	//N��̽ͷ

									
#define SYN_BYTE	0xAA		//ͬ����
#define ERR_BYTE	0xA5		//������

#define DATA_NORMAL        0
#define DATA_GZ_BDKL       1           /*�������*/
#define DATA_GZ_TXGZ       2           /*ͨ�Ź���*/
#define DATA_GZ_ZXDL       3           /*�����߶�·*/
#define DATA_GZ_BDGD       4           /*���繩��*/
#define DATA_GZ_MKDX       5           /*ͨ��ģ�����*/
#define DATA_GZ_TKSYSB     6           /*����ʧ��*/
#define DATA_GZ_TKDX       7           /*̽��������*/
#define DATA_GZ_CANERR     8           /*CAN���߹���*/
#define DATA_GZ_TT         10          /*̽ͷ����*/
#define DATA_GZ_ZCOM       11          /*��ͨ�Ź���*/
#define DATA_GZ_ZKDX       12          /*����豸����*/

#define DATA_GZ_MIN        1
#define DATA_GZ_MAX        50

#define DATA_BJ            51           /*����*/
#define DATA_YJ            52

#define DATA_CZ_MIN        101
#define DATA_CZ_MAX        150

#define DATA_CZ_RESET      101          /*������λ*/
#define DATA_CZ_XY         102          /*����*/
#define DATA_CZ_KAIJI      103          /*����*/
#define DATA_CZ_GUANJI     104          /*�ػ�*/

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



