
#ifndef __CAN_H__
#define __CAN_H__


#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1

#define CAN_ERROR        (-2)
#define CAN_BUSY         (-3)


#define __ID( state, cmd, tt, tk )             (((uint32)(state)<<27) | ((uint32)(cmd) <<19 )  | ((uint32)(tt)<<11 ) | ((tk))  )
#define __DATA( value, type )                  (((uint16)(value) & 0x1FFF) | ((uint16)(type) <<13))

#define CAN_TYPE_NORMAL   0
#define CAN_TYPE_S        1
#define CAN_TYPE_I        2
#define CAN_TYPE_W        3
#define CAN_TYPE_MS       4 
#define CAN_TYPE_MW       5

#define CAN_ID_NORMAL     0
#define CAN_ID_DATA       1


#define CANMKADDR( zk, tk )          (((zk)&0x1F)<<11) + ((tk)&0x7FF)

typedef struct  {
    union
    {
        uint32 Frame;
        struct{
            uint32 IDIndex: 10;
            uint32 BP:   1;
            uint32 nc1:  5;
            uint32 len : 4;      // Bits 16..19: DLC - Data Length Counter
            uint32 nc2 : 2;
            uint32 RTR : 1;      // Bit 30: Set if this is a RTR message
            uint32 ExtID:1;      // Bit 31: Set if this is a 29-bit ID message
        };
    };
    union{
        uint32 id;        /* 29 bit identifier */
        struct{//通信协议中数据分布
            uint32 IDTK     :11;  /*探测器地址     0  - 10 */
            uint32 IDTT     :8;   /*首位探头地址   11 - 18 */
            uint32 IDcmd    :8;   /*数据命令       19 - 26 */
            uint32 IDstate  :2;   /*扩展位状态     27 - 28 */
        };
        struct{
            uint32       :11;
            uint32 IDext : 21;
        };
    };
    union
    {
         struct  __PACKED__
        {
            uint8  cmd;
            union{
                uint16 addr;
                struct {
                    uint16 TKaddr: 11;
                    uint16 ZKaddr:  5;
                };
            };
            uint8  TTaddr;
            uint16 value;
            uint8  type;
            uint8  state;
        };
		struct __PACKED__
		{
			uint8 TKtype;
			uint8 TTcnt;
			uint16 TKstate;
			uint16 BTvalue;
		};
        struct __PACKED__
        {//29位ID发送数据格式
            uint8  Dtype;
            uint8  Dstate;
            uint16 Dvalue;
            uint8  DZKaddr;
        };

        union{
            uint16 data;
            struct
            {
                uint16 value :13;
                uint16 type  :3;
            };
        }Data[4];

        struct  __PACKED__
        {
            uint32 DataA;
            uint32 DataB;
        };
        uint8  buff[8];           /* Data field */
    }; 
} __PACKED__ CAN_msg;

typedef CAN_msg  CAN_MSG;
typedef CAN_msg *pCAN_msg;



static inline int CAN_WriteBuff( CAN_msg *msg,uint32 id, uint8 *buff, int size )
{
    int i;
    int len;
    len = size>8? 8: size;
    msg->Frame  = (len<<16);
    msg->id     = id;
    for(i=0; i<len; i++)
        msg->buff[i] = buff[i];
    return msg->len;
}

static inline int CAN_WriteBuffExt( CAN_msg *msg, uint32 id, uint8 *buff, int size )
{
    int i;
    int len;
    len = size>8? 8: size;
    msg->Frame  = 0x80000000 | (len<<16);
    msg->id     = id;
    for(i=0; i<len; i++)
        msg->buff[i] = buff[i];
    return msg->len;
}

#endif //__CAN_H__


