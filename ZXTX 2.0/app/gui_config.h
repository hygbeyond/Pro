

#ifndef __GUI_CONFIG_H__
#define __GUI_CONFIG_H__

#include "mytype.h"	 
#include "gui.h"
#include "main_mac.h"
#include "gui/FONT_MACRO.H"
#include "main_mac.h"

typedef GUI_FONT TFONT;

#define HBZK_NAME      __stringify(HNAME) 

#define  GUI_LCM_XMAX		240							/* 定义液晶x轴的点数 */
#define  GUI_LCM_YMAX		128							/* 定义液晶y轴的点数 */


#define GUI_FONTW   GUI_GetFontWidth( 0xAA)
#define GUI_FONTH   GUI_GetFontHeight(0xAA)

#define GUI_YMAX	(GUI_LCM_YMAX-12)
#define GUI_XMAX	(GUI_LCM_XMAX)


#define FONT_XBYY_EN      0
#define FONT_XBYY6_12_EN  1
#define FONT_XBYY_DEFAULT  XBYY6x12 

//#define HZ_FONT         FONT_TYPE_HZJ

#define FONT_CN_WIDTH	12
#define FONG_CN_HEIGHT	12


#define PROGRESSBAR_EN     1
#define SCROLL_EN          1
#define MENU_EN            1


//Menu配置参数
#define MMENU_CH_SIZE		4
#define MENU_RECT_EN		1
#define MMENU_SIZE			5
#define SMENU_SIZE			20 
#define MENU_FONT           GUIFont12
#define MENU_CHAR_height	GUI_GetFontHeight(0xAA)/*菜单字体高度*/

static inline
void GUI_Rect(int x,int y,int width,int height)
{
	GUI_DrawRect( x, y, x+width, y+height );
}

#define GUI_Draw(x,y,w,h,pd)           GUI_DrawBitmap( x,y,w,h,(const U8*)pd)

static inline
void GUI_Full(int x, int y, int w, int h, int color)
{
    int old = GUI_SetColor( color );
    GUI_FillRect( x, y, x+w, y+h-1 );
    GUI_SetColor( old );
}

static inline
void GUI_DrawString(int x, int y, const char *str )
{
    GUI_string( x, y, str );
}

static inline 
void GUI_FillRectExt( RECT *pRect, int color )
{
    GUI_Full( pRect->x, pRect->y, pRect->width, pRect->height, color );
}

static inline
const TFONT * GUI_SetFont( const  TFONT *pFont )
{
	return pFont;
}

static inline 
void GUI_RectDrawString(RECT *pRect, const char *str )
{
    GUI_RECT rect = {pRect->x, pRect->y, pRect->x + pRect->width, pRect->y + pRect->height };
    GUI_StringExt( &rect, str );
}

static inline
void GUI_FullBack( RECT *pRect )
{
    GUI_FillRectExt( pRect, 0 );
}


static inline 
void GUI_DrawVLine(int x, int y, int x1)
{
    GUI_HLine( x, y, x1 );
}

#if GUI_OS > 0
#define GUI_LOCK()    GUI_X_Lock()
#define GUI_UNLOCK()  GUI_X_UnLock()
#define GUI_OSINIT()  GUI_X_InitOS()
#else	 
#define GUI_LOCK() 
#define GUI_UNLOCK()
#define GUI_OSINIT()
#endif


#define GUISetColor(a)         GUI_SetColor(a)



#include "TimeGui.h"
#include "menu.h"
#include "ProgressBar.h"
#include "scroll.h"

#include "interface.h"
#include "dataGUI.h"




#endif //__GUI_CONFIG_H__



