/*
 * hiduser.c
 *
 *  Created on: 2016Äê12ÔÂ14ÈÕ
 *      Author: Administrator
 */

#if 0

#include "mytype.h"
typedef uint8 U8;
typedef uint16 U16;
typedef uint32 U32;

#define __weak   __WEAK__

#define __packed __PACKED__


/* USB Standard Configuration Descriptor */
typedef __packed struct _USB_CONFIGURATION_DESCRIPTOR {
  U8  bLength;
  U8  bDescriptorType;
  U16 wTotalLength;
  U8  bNumInterfaces;
  U8  bConfigurationValue;
  U8  iConfiguration;
  U8  bmAttributes;
  U8  bMaxPower;
} USB_CONFIGURATION_DESCRIPTOR;



// <h> USB Host
//   <e> USB Host 0
//     <i> Enable the USB Host 0 functionality
//     <o1> Controller Interface
//       <i> Selects the USB Host 0 controller interface
//       <0=> Custom <1=> OHCI <2=> Custom EHCI for NXP Devices
//   </e>
#define USBH0_ENABLE                0
#define USBH0_HC_IF                 1

//   <e> USB Host 1
//     <i> Enable the USB Host 1 functionality
//     <o1> Controller Interface
//       <i> Selects the USB Host 1 controller interface
//       <0=> Custom <1=> OHCI <2=> Custom EHCI for NXP Devices
//   </e>
#define USBH1_ENABLE                0
#define USBH1_HC_IF                 0

//   <h> Class Configuration
//     <i> Selects supported classes
//     <e0.0> Mass Storage Device Class (MSC)
//       <o1> Number of concurrent MSC Devices on single USB Host controller <0-15>
//     </e>
//     <e0.1> Human Interface Device Class (HID)
//       <o2> Number of concurrent HID Devices on single USB Host controller <0-15>
//     </e>
//     <e0.2> USB Device Class
//       <o3> Number of concurrent Custom Class Devices on single USB Host controller <0-15>
//     </e>
//   </h>
#define USBH_CLASS                  0x0001
#define USBH_MSC_NUM                1
#define USBH_HID_NUM                0
#define USBH_CLS_NUM                0

// </h>


/*------------------------------------------------------------------------------
 *      USB Device Configuration
 *----------------------------------------------------------------------------*/

// <e> USB Device
//   <i> Enable the USB Device functionality
#define USBD_ENABLE                 1

//   <o0.0> High-speed
//     <i> Enable high-speed functionality (if device supports it)
#define USBD_HS_ENABLE              0

//   <h> Device Settings
//     <i> These settings affect Device Descriptor
//     <o0> Power
//       <i> Default Power Setting
//       <0=> Bus-powered
//       <1=> Self-powered
//     <o1> Max Endpoint 0 Packet Size
//       <i> Maximum packet size for endpoint zero (bMaxPacketSize0)
//       <8=> 8 Bytes <16=> 16 Bytes <32=> 32 Bytes <64=> 64 Bytes
//     <o2.0..15> Vendor ID <0x0000-0xFFFF>
//       <i> Vendor ID assigned by the USB-IF (idVendor)
//     <o3.0..15> Product ID <0x0000-0xFFFF>
//       <i> Product ID assigned by the manufacturer (idProduct)
//     <o4.0..15> Device Release Number <0x0000-0xFFFF>
//       <i> Device release number in binary-coded decimal (bcdDevice)
//   </h>
#define USBD_POWER                  0
#define USBD_MAX_PACKET0            64
#define USBD_DEVDESC_IDVENDOR       0xC251
#define USBD_DEVDESC_IDPRODUCT      0xF001
#define USBD_DEVDESC_BCDDEVICE      0x0100

//   <h> Configuration Settings
//     <i> These settings affect Configuration Descriptor
//     <o0.5> Remote Wakeup
//       <i> Configuration support for remote wakeup (D5: of bmAttributes)
//     <o1.0..7> Maximum Power Consumption (in mA) <0-510><#/2>
//       <i> Maximum power consumption of the USB device
//       <i> from the bus in this specific configuration
//       <i> when the device is fully operational (bMaxPower)
//   </h>
#define USBD_CFGDESC_BMATTRIBUTES   0x80
#define USBD_CFGDESC_BMAXPOWER      0x32

//   <h> String Settings
//     <i> These settings affect String Descriptor
//     <o0.0..15> Language ID <0x0000-0xFCFF>
//       <i> English (United States) = 0x0409
//     <s0.126> Manufacturer String
//       <i> String descriptor describing manufacturer
//     <s1.126> Product String
//       <i> String descriptor describing product
//     <e1.0> Serial Number
//       <i> Enable serial number string
//       <i> If disabled serial number string will not be assigned to the USB Device
//       <s2.126> Serial Number String
//         <i> String descriptor describing device's serial number
//     </e>
//   </h>
#define USBD_STRDESC_LANGID         0x0409
#define USBD_STRDESC_MAN            L"Keil Software"
#define USBD_STRDESC_PROD           L"STM32 CMSIS-DAP"
#define USBD_STRDESC_SER_ENABLE     1
#define USBD_STRDESC_SER            L"0001A0000000"

//   <e0> Class Support
//     <i> Enables USB Device Class specific Requests
#define USBD_CLASS_ENABLE           1

//     <e0.0> Human Interface Device (HID)
//       <i> Enable class support for Human Interface Device (HID)
//       <h> Interrupt Endpoint Settings
//         <o1.0..4> Interrupt In Endpoint Number                  <1=>   1 <2=>   2 <3=>   3
//                                                 <4=>   4        <5=>   5 <6=>   6 <7=>   7
//                                                 <8=>   8        <9=>   9 <10=> 10 <11=> 11
//                                                 <12=>  12       <13=> 13 <14=> 14 <15=> 15
//         <o2.0..4> Interrupt Out Endpoint Number <0=>   Not used <1=>   1 <2=>   2 <3=>   3
//                                                 <4=>   4        <5=>   5 <6=>   6 <7=>   7
//                                                 <8=>   8        <9=>   9 <10=> 10 <11=> 11
//                                                 <12=>  12       <13=> 13 <14=> 14 <15=> 15
//           <i> If interrupt out endpoint is not used select "Not used"
//         <h> Endpoint Settings
//           <o3.0..7> Maximum Endpoint Packet Size (in bytes) <0-64>
//           <o4.0..7> Endpoint polling Interval (in ms) <1-255>
//           <e5> High-speed
//             <i> If high-speed is enabled set endpoint settings for it
//             <o6.0..10> Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <o6.11..12> Additional transactions per microframe <0=> None <1=> 1 additional <2=> 2 additional
//             <o7.0..7> Endpoint polling Interval (in ms) <1=>      1 <2=>      2 <3=>      4 <4=>      8
//                                                         <5=>     16 <6=>     32 <7=>     64 <8=>    128
//                                                         <9=>    256 <10=>   512 <11=>  1024 <12=>  2048
//                                                         <13=>  4096 <14=>  8192 <15=> 16384 <16=> 32768
//           </e>
//         </h>
//       </h>
//       <h> Human Interface Device Settings
//         <i> Device specific settings
//         <s0.126> HID Interface String
//         <o8.0..4> Number of Input Reports <1-32>
//         <o9.0..4> Number of Output Reports <1-32>
//         <o10.0..15> Maximum Input Report Size (in bytes) <1-65535>
//         <o11.0..15> Maximum Output Report Size (in bytes) <1-65535>
//         <o12.0..15> Maximum Feature Report Size (in bytes) <1-65535>
//       </h>
//     </e>
#define USBD_HID_ENABLE             1
#define USBD_HID_EP_INTIN           1
#define USBD_HID_EP_INTOUT          1
#define USBD_HID_WMAXPACKETSIZE     64
#define USBD_HID_BINTERVAL          1
#define USBD_HID_HS_ENABLE          0
#define USBD_HID_HS_WMAXPACKETSIZE  4
#define USBD_HID_HS_BINTERVAL       6
#define USBD_HID_STRDESC            L"USB_HID"
#define USBD_HID_INREPORT_NUM       1
#define USBD_HID_OUTREPORT_NUM      1
#define USBD_HID_INREPORT_MAX_SZ    64
#define USBD_HID_OUTREPORT_MAX_SZ   64
#define USBD_HID_FEATREPORT_MAX_SZ  1

//     <e0.0> Mass Storage Device (MSC)
//       <i> Enable class support for Mass Storage Device (MSC)
//       <h> Bulk Endpoint Settings
//         <o1.0..4> Bulk In Endpoint Number                  <1=>   1 <2=>   2 <3=>   3
//                                            <4=>   4        <5=>   5 <6=>   6 <7=>   7
//                                            <8=>   8        <9=>   9 <10=> 10 <11=> 11
//                                            <12=>  12       <13=> 13 <14=> 14 <15=> 15
//         <o2.0..4> Bulk Out Endpoint Number                 <1=>   1 <2=>   2 <3=>   3
//                                            <4=>   4        <5=>   5 <6=>   6 <7=>   7
//                                            <8=>   8        <9=>   9 <10=> 10 <11=> 11
//                                            <12=>  12       <13=> 13 <14=> 14 <15=> 15
//         <h> Endpoint Settings
//           <o3> Maximum Packet Size <1-1024>
//           <e4> High-speed
//             <i> If high-speed is enabled set endpoint settings for it
//             <o5> Maximum Packet Size <1-1024>
//             <o6> Maximum NAK Rate <0-255>
//           </e>
//         </h>
//       </h>
//       <h> Mass Storage Device Settings
//         <i> Device specific settings
//         <s0.126> MSC Interface String
//         <h> Inquiry Data
//           <s1.8>  Vendor Identification
//           <s2.16> Product Identification
//           <s3.4>  Product Revision Level
//         </h>
//       </h>
//     </e>
#define USBD_MSC_ENABLE             0
#define USBD_MSC_EP_BULKIN          2
#define USBD_MSC_EP_BULKOUT         2
#define USBD_MSC_WMAXPACKETSIZE     64
#define USBD_MSC_HS_ENABLE          0
#define USBD_MSC_HS_WMAXPACKETSIZE  512
#define USBD_MSC_HS_BINTERVAL       0
#define USBD_MSC_STRDESC            L"USB_MSC"
#define USBD_MSC_INQUIRY_DATA       "Keil    "         \
                                    "LPC23xx Disk    " \
                                    "1.0 "

//     <e0.0> Audio Device (ADC)
//       <i> Enable class support for Audio Device (ADC)
//       <h> Isochronous Endpoint Settings
//         <o1.0..4> Isochronous Out Endpoint Number                 <1=>   1 <2=>   2 <3=>   3
//                                                   <4=>   4        <5=>   5 <6=>   6 <7=>   7
//                                                   <8=>   8        <9=>   9 <10=> 10 <11=> 11
//                                                   <12=>  12       <13=> 13 <14=> 14 <15=> 15
//         <h> Endpoint Settings
//           <o2.0..10> Maximum Endpoint Packet Size (in bytes) <0-1024>
//           <o3.0..10> Endpoint polling Interval (in ms) <1=>      1 <2=>      2 <3=>      4 <4=>      8
//                                                        <5=>     16 <6=>     32 <7=>     64 <8=>    128
//                                                        <9=>    256 <10=>   512 <11=>  1024 <12=>  2048
//                                                        <13=>  4096 <14=>  8192 <15=> 16384 <16=> 32768
//           <e4> High-speed
//             <i> If high-speed is enabled set endpoint settings for it
//             <o5.0..10> Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <o5.11..12> Additional transactions per microframe <0=> None <1=> 1 additional <2=> 2 additional
//           </e>
//         </h>
//       </h>
//       <h> Audio Device Settings
//         <i> Device specific settings
//         <s0.126> Audio Control Interface String
//         <s1.126> Audio Streaming (Zero Bandwidth) Interface String
//         <s2.126> Audio Streaming (Operational) Interface String
//         <o6.0..7> Audio Subframe Size (in bytes) <0-255>
//         <o7.0..7> Sample Resolution (in bits) <0-255>
//         <o8.0..23> Sample Frequency (in Hz) <0-16777215>
//         <o9> Packet Size (in bytes) <1-256>
//         <o10> Packet Count <1-16>
//       </h>
//     </e>
#define USBD_ADC_ENABLE             0
#define USBD_ADC_EP_ISOOUT          3
#define USBD_ADC_WMAXPACKETSIZE     64
#define USBD_ADC_BINTERVAL          1
#define USBD_ADC_HS_ENABLE          0
#define USBD_ADC_HS_WMAXPACKETSIZE  64
#define USBD_ADC_CIF_STRDESC        L"USB_ADC"
#define USBD_ADC_SIF1_STRDESC       L"USB_ADC1"
#define USBD_ADC_SIF2_STRDESC       L"USB_ADC2"
#define USBD_ADC_BSUBFRAMESIZE      2
#define USBD_ADC_BBITRESOLUTION     16
#define USBD_ADC_TSAMFREQ           32000
#define USBD_ADC_CFG_P_S            32
#define USBD_ADC_CFG_P_C            1

//     <e0> Communication Device (CDC)
//       <i> Enable class support for Communication Device (CDC)
//       <h> Interrupt Endpoint Settings
//         <o1.0..4> Interrupt In Endpoint Number                 <1=>   1 <2=>   2 <3=>   3
//                                                <4=>   4        <5=>   5 <6=>   6 <7=>   7
//                                                <8=>   8        <9=>   9 <10=> 10 <11=> 11
//                                                <12=>  12       <13=> 13 <14=> 14 <15=> 15
//         <h> Endpoint Settings
//           <o2.0..10> Maximum Endpoint Packet Size (in bytes) <0-1024>
//           <o3.0..10> Endpoint polling Interval (in ms) <0-255>
//           <e4> High-speed
//             <i> If high-speed is enabled set endpoint settings for it
//             <o5.0..10> Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <o5.11..12> Additional transactions per microframe <0=> None <1=> 1 additional <2=> 2 additional
//             <o6.0..10> Endpoint polling Interval (in ms) <1=>      1 <2=>      2 <3=>      4 <4=>      8
//                                                          <5=>     16 <6=>     32 <7=>     64 <8=>    128
//                                                          <9=>    256 <10=>   512 <11=>  1024 <12=>  2048
//                                                          <13=>  4096 <14=>  8192 <15=> 16384 <16=> 32768
//           </e4>
//         </h>
//       </h>
//       <h> Bulk Endpoint Settings
//         <o7.0..4> Bulk In Endpoint Number                  <1=>   1 <2=>   2 <3=>   3
//                                            <4=>   4        <5=>   5 <6=>   6 <7=>   7
//                                            <8=>   8        <9=>   9 <10=> 10 <11=> 11
//                                            <12=>  12       <13=> 13 <14=> 14 <15=> 15
//         <o8.0..4> Bulk Out Endpoint Number                 <1=>   1 <2=>   2 <3=>   3
//                                            <4=>   4        <5=>   5 <6=>   6 <7=>   7
//                                            <8=>   8        <9=>   9 <10=> 10 <11=> 11
//                                            <12=>  12       <13=> 13 <14=> 14 <15=> 15
//         <h> Endpoint Settings
//           <o9> Maximum Packet Size <1-1024>
//           <e10> High-speed
//             <i> If high-speed is enabled set endpoint settings for it
//             <o11> Maximum Packet Size <1-1024>
//             <o12> Maximum NAK Rate <0-255>
//           </e10>
//         </h>
//       </h>
//       <h> Communication Device Settings
//         <i> Device specific settings
//         <s0.126> Communication Class Interface String
//         <s1.126> Data Class Interface String
//         <o13> Maximum Communication Device Buffer Size
//            <8=> 8 Bytes <16=> 16 Bytes <32=> 32 Bytes <64=> 64 Bytes
//         <o14> Maximum Communication Device Output Buffer Size
//            <8=> 8 Bytes <16=> 16 Bytes <32=> 32 Bytes <64=> 64 Bytes <128=> 128 Bytes
//       </h>
//     </e>
#define USBD_CDC_ENABLE             0
#define USBD_CDC_EP_INTIN           2
#define USBD_CDC_WMAXPACKETSIZE     16
#define USBD_CDC_BINTERVAL          2
#define USBD_CDC_HS_ENABLE          0
#define USBD_CDC_HS_WMAXPACKETSIZE  16
#define USBD_CDC_HS_BINTERVAL       2
#define USBD_CDC_EP_BULKIN          2
#define USBD_CDC_EP_BULKOUT         3
#define USBD_CDC_WMAXPACKETSIZE1    64
#define USBD_CDC_HS_ENABLE1         0
#define USBD_CDC_HS_WMAXPACKETSIZE1 64
#define USBD_CDC_HS_BINTERVAL1      0
#define USBD_CDC_CIF_STRDESC        L"USB_CDC"
#define USBD_CDC_DIF_STRDESC        L"USB_CDC1"
#define USBD_CDC_BUFSIZE            64
#define USBD_CDC_OUTBUFSIZE         128

//     <e0> Custom Class Device
//       <i> Enables USB Custom Class Requests
//       <i> Class IDs:
//       <i> 0x00 - Class Reserved ID
//       <i> 0x01 - Class Audio ID
//       <i> 0x02 - Class Communications ID
//       <i> 0x03 - Class Human Interface ID
//       <i> 0x04 - Class Monitor ID
//       <i> 0x05 - Class Physical Interface ID
//       <i> 0x06 - Class Power ID
//       <i> 0x07 - Class Printer ID
//       <i> 0x08 - Class Storage ID
//       <i> 0x09 - Class HUB ID
//       <i> 0xEF - Class Miscellaneous ID
//       <i> 0xFF - Class Vendor Specific ID
//     </e>
#define USBD_CLS_ENABLE             0

//   </e>
// </e>


/* USB Descriptor Types */
#define USB_DEVICE_DESCRIPTOR_TYPE                  1
#define USB_CONFIGURATION_DESCRIPTOR_TYPE           2
#define USB_STRING_DESCRIPTOR_TYPE                  3
#define USB_INTERFACE_DESCRIPTOR_TYPE               4
#define USB_ENDPOINT_DESCRIPTOR_TYPE                5
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE        6
#define USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE      7
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE         8
#define USB_OTG_DESCRIPTOR_TYPE                     9
#define USB_DEBUG_DESCRIPTOR_TYPE                  10
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE  11

/* USB Device Classes */
#define USB_DEVICE_CLASS_RESERVED              0x00
#define USB_DEVICE_CLASS_AUDIO                 0x01
#define USB_DEVICE_CLASS_COMMUNICATIONS        0x02
#define USB_DEVICE_CLASS_HUMAN_INTERFACE       0x03
#define USB_DEVICE_CLASS_MONITOR               0x04
#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE    0x05
#define USB_DEVICE_CLASS_POWER                 0x06
#define USB_DEVICE_CLASS_PRINTER               0x07
#define USB_DEVICE_CLASS_STORAGE               0x08
#define USB_DEVICE_CLASS_HUB                   0x09
#define USB_DEVICE_CLASS_MISCELLANEOUS         0xEF
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC       0xFF

/* bmAttributes in Configuration Descriptor */
#define USB_CONFIG_POWERED_MASK                0x40
#define USB_CONFIG_BUS_POWERED                 0x80
#define USB_CONFIG_SELF_POWERED                0xC0
#define USB_CONFIG_REMOTE_WAKEUP               0x20

/* bMaxPower in Configuration Descriptor */
#define USB_CONFIG_POWER_MA(mA)                ((mA)/2)

/* bEndpointAddress in Endpoint Descriptor */
#define USB_ENDPOINT_DIRECTION_MASK            0x80
#define USB_ENDPOINT_OUT(addr)                 ((addr) | 0x00)
#define USB_ENDPOINT_IN(addr)                  ((addr) | 0x80)

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_MASK                 0x03
#define USB_ENDPOINT_TYPE_CONTROL              0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS          0x01
#define USB_ENDPOINT_TYPE_BULK                 0x02
#define USB_ENDPOINT_TYPE_INTERRUPT            0x03
#define USB_ENDPOINT_SYNC_MASK                 0x0C
#define USB_ENDPOINT_SYNC_NO_SYNCHRONIZATION   0x00
#define USB_ENDPOINT_SYNC_ASYNCHRONOUS         0x04
#define USB_ENDPOINT_SYNC_ADAPTIVE             0x08
#define USB_ENDPOINT_SYNC_SYNCHRONOUS          0x0C
#define USB_ENDPOINT_USAGE_MASK                0x30
#define USB_ENDPOINT_USAGE_DATA                0x00
#define USB_ENDPOINT_USAGE_FEEDBACK            0x10
#define USB_ENDPOINT_USAGE_IMPLICIT_FEEDBACK   0x20
#define USB_ENDPOINT_USAGE_RESERVED            0x30




#define WBVAL(x)                          (x & 0xFF),((x >> 8) & 0xFF)
#define B3VAL(x)                          (x & 0xFF),((x >> 8) & 0xFF),((x >> 16) & 0xFF)
#define USB_DEVICE_DESC_SIZE              (sizeof(USB_DEVICE_DESCRIPTOR))
#define USB_DEVICE_QUALI_SIZE             (sizeof(USB_DEVICE_QUALIFIER_DESCRIPTOR))
#define USB_CONFIGUARTION_DESC_SIZE       (sizeof(USB_CONFIGURATION_DESCRIPTOR))
#define USB_INTERFACE_ASSOC_DESC_SIZE     (sizeof(USB_INTERFACE_ASSOCIATION_DESCRIPTOR))
#define USB_INTERFACE_DESC_SIZE           (sizeof(USB_INTERFACE_DESCRIPTOR))
#define USB_ENDPOINT_DESC_SIZE            (sizeof(USB_ENDPOINT_DESCRIPTOR))
#define USB_HID_DESC_SIZE                 (sizeof(HID_DESCRIPTOR))
#define USB_HID_REPORT_DESC_SIZE          (sizeof(USBD_HID_ReportDescriptor))



/*------------------------------------------------------------------------------
 *      USB Device Descriptors
 *----------------------------------------------------------------------------*/

#define USBD_ADC_DESC_LEN                 (USBD_MULTI_IF * USB_INTERFACE_ASSOC_DESC_SIZE + USB_INTERFACE_DESC_SIZE +                              \
                                           AUDIO_CONTROL_INTERFACE_DESC_SZ(1) + AUDIO_INPUT_TERMINAL_DESC_SIZE  +                                 \
                                           AUDIO_FEATURE_UNIT_DESC_SZ(1,1) + AUDIO_OUTPUT_TERMINAL_DESC_SIZE + USB_INTERFACE_DESC_SIZE          + \
                                           USB_INTERFACE_DESC_SIZE + AUDIO_STREAMING_INTERFACE_DESC_SIZE + AUDIO_FORMAT_TYPE_I_DESC_SZ(1)       + \
                                           AUDIO_STANDARD_ENDPOINT_DESC_SIZE + AUDIO_STREAMING_ENDPOINT_DESC_SIZE)
#define USBD_CDC_ACM_DESC_LEN             (USB_INTERFACE_DESC_SIZE + USBD_MULTI_IF * USB_INTERFACE_ASSOC_DESC_SIZE + 0x0013                     + \
                                           USB_ENDPOINT_DESC_SIZE + USB_INTERFACE_DESC_SIZE + 2*USB_ENDPOINT_DESC_SIZE)
#define USBD_HID_DESC_LEN                 (USB_INTERFACE_DESC_SIZE + USB_HID_DESC_SIZE                                                          + \
                                          (USB_ENDPOINT_DESC_SIZE*(1+(USBD_HID_EP_INTOUT != 0))))
#define USBD_MSC_DESC_LEN                 (USB_INTERFACE_DESC_SIZE + 2*USB_ENDPOINT_DESC_SIZE)
#define USBD_HID_DESC_OFS                 (USB_CONFIGUARTION_DESC_SIZE + USB_INTERFACE_DESC_SIZE                                                + \
                                           USBD_ADC_ENABLE * USBD_ADC_DESC_LEN + USBD_CDC_ACM_ENABLE * USBD_CDC_ACM_DESC_LEN)

#define USBD_WTOTALLENGTH                 (USB_CONFIGUARTION_DESC_SIZE +                 \
                                           USBD_ADC_DESC_LEN     * USBD_ADC_ENABLE     + \
                                           USBD_CDC_ACM_DESC_LEN * USBD_CDC_ACM_ENABLE + \
                                           USBD_HID_DESC_LEN     * USBD_HID_ENABLE     + \
                                           USBD_MSC_DESC_LEN     * USBD_MSC_ENABLE)




/* USB Device Configuration Descriptor (for Full Speed) */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
__weak \
const U8 USBD_ConfigDescriptor[] = {
    /* Configuration 1 */
    USB_CONFIGUARTION_DESC_SIZE,          /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,    /* bDescriptorType */
    WBVAL(USBD_WTOTALLENGTH),             /* wTotalLength */
    USBD_IF_NUM,                          /* bNumInterfaces */
    0x01,                                 /* bConfigurationValue: 0x01 is used to select this configuration */
    0x00,                                 /* iConfiguration: no string to describe this configuration */
    USBD_CFGDESC_BMATTRIBUTES |           /* bmAttributes */
    (USBD_POWER << 6),
    USBD_CFGDESC_BMAXPOWER,               /* bMaxPower, device power consumption */

#if (USBD_ADC_ENABLE)
#if (USBD_MULTI_IF)
    ADC_DESC_IAD(USBD_ADC_CIF_NUM, 2)
#endif
    ADC_DESC
    ADC_EP
#endif

#if (USBD_MSC_ENABLE)
    MSC_DESC
    MSC_EP
#endif

#if (USBD_HID_ENABLE)
    HID_DESC
#if (USBD_HID_EP_INTOUT != 0)
    HID_EP_INOUT
#else
    HID_EP
#endif
#endif

#if (USBD_CDC_ACM_ENABLE)
#if (USBD_MULTI_IF)
    CDC_ACM_DESC_IAD(USBD_CDC_ACM_CIF_NUM, 2)
#endif
    CDC_ACM_DESC_IF0
    CDC_ACM_EP_IF0
    CDC_ACM_DESC_IF1
    CDC_ACM_EP_IF1
#endif

    /* Terminator */                                                                                            \
    0                                     /* bLength */                                                       \
};



/* USB Device Create String Descriptor */
#define USBD_STR_DEF(n)                 \
  struct {                              \
    U8  len;                            \
    U8  type;                           \
    U16 str[sizeof(USBD_##n)/2-1];      \
  } desc##n

#define USBD_STR_VAL(n)                  \
 { sizeof(USBD_##n), USB_STRING_DESCRIPTOR_TYPE, USBD_##n }

__weak \
const struct {
    struct {
        U8  len;
        U8  type;
        U16 langid;
    } desc_langid;
    USBD_STR_DEF(STRDESC_MAN);
    USBD_STR_DEF(STRDESC_PROD);
#if  (USBD_STRDESC_SER_ENABLE)
    USBD_STR_DEF(STRDESC_SER);
#endif
#if (USBD_ADC_ENABLE)
    USBD_STR_DEF(ADC_CIF_STRDESC);
    USBD_STR_DEF(ADC_SIF1_STRDESC);
    USBD_STR_DEF(ADC_SIF2_STRDESC);
#endif
#if (USBD_CDC_ACM_ENABLE)
    USBD_STR_DEF(CDC_ACM_CIF_STRDESC);
    USBD_STR_DEF(CDC_ACM_DIF_STRDESC);
#endif
#if (USBD_HID_ENABLE)
    USBD_STR_DEF(HID_STRDESC);
#endif
#if (USBD_MSC_ENABLE)
    USBD_STR_DEF(MSC_STRDESC);
#endif
} USBD_StringDescriptor
= {
    { 4, USB_STRING_DESCRIPTOR_TYPE, USBD_STRDESC_LANGID },
    USBD_STR_VAL(STRDESC_MAN),
    USBD_STR_VAL(STRDESC_PROD),
#if (USBD_STRDESC_SER_ENABLE)
    USBD_STR_VAL(STRDESC_SER),
#endif
#if (USBD_ADC_ENABLE)
    USBD_STR_VAL(ADC_CIF_STRDESC),
    USBD_STR_VAL(ADC_SIF1_STRDESC),
    USBD_STR_VAL(ADC_SIF2_STRDESC),
#endif
#if (USBD_CDC_ACM_ENABLE)
    USBD_STR_VAL(CDC_ACM_CIF_STRDESC),
    USBD_STR_VAL(CDC_ACM_DIF_STRDESC),
#endif
#if (USBD_HID_ENABLE)
    USBD_STR_VAL(HID_STRDESC),
#endif
#if (USBD_MSC_ENABLE)
    USBD_STR_VAL(MSC_STRDESC),
#endif
};

#endif
