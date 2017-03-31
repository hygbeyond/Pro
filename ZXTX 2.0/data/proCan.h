
#ifndef __PROCAN_H__
#define __PROCAN_H__

#include "mytype.h"
#include "can.h"

typedef struct TCAN_msg
{
    union{
		uint32 IDCOUNT;
		struct {
			uint32 id       :29;        /* 29 bit identifier */
			uint32 IDEXT    :3;
		};

		struct{//ͨ��Э�������ݷֲ�
            uint32 IDTK     :11;  /*̽������ַ     0  - 10 */
            uint32 IDTT     :8;   /*��λ̽ͷ��ַ   11 - 18 */
            uint32 IDcmd    :8;   /*��������       19 - 26 */
            uint32 IDstate  :2;   /*��չλ״̬     27 - 28 */
			uint32 IDext    :3;   
        };
    };
    union{
        uint8  buff[8];
		struct __PACKED__
        {
            uint8  TKtype;
            uint8  TTcnt;
			union{
				uint16  TKstate;
				struct{
					uint16  Zstate :1;        /*���翪��״̬ 1�� 0��*/
					uint16  Bstate :1;        /*���翪��״̬ 1�� 0��*/
					uint16  Tstate :1;        /*������״̬  0 ���� 1����*/
					uint16  Wstate :1;        /*�¶�״̬    0 ���� 1����*/
					uint16  Za     :2;        /*����A��״̬ 0 ���� 1��ѹ 2Ƿѹ 3�ϵ�*/
					uint16  Zb     :2;        /*����B��״̬*/
					uint16  Zc     :2;        /*����C��״̬*/
					uint16  Ba     :2;        /*����A��״̬*/
					uint16  Bb     :2;        /*����B��״̬*/
					uint16  Bc     :2;        /*����C��״̬*/
				};
			};
			uint8  ZKaddr;
        };
		struct __PACKED__
        {//29λID�������ݸ�ʽ
            uint8  Dtype;
            uint8  Dstate;
            uint16 Dvalue;
			uint8  DZKaddr;
        };
		union{
			uint16 data;
			struct {
				uint16 value :13;
				uint16 type  :3;
			};
		}Data[4];
        struct{
            uint32 DataA;
            uint32 DataB;
        };
    };
    uint8  cnt;
    uint8  IO;
    uint8  num;
}__PACKED__ TCAN_msg;


typedef struct TProCan
{
    uint8   cmd;
    union{
        uint8 buff[15];
        TCAN_msg msg;
    };
} __PACKED__ TProCan;


void ProCAN_Init(void);
int  ProCAN_Trans ( int port );
int ProCAN_Add(int port, CAN_msg *pMsg );
int ProCAN_Rect( uint8 dat );


#endif //__PROCAN_H__


