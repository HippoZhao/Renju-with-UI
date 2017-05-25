#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<SDL2/SDL_ttf.h>
#include <windows.h>
int ellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int filledCircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int boxRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int vlineRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int pixelRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int hlineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int hline(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y);

typedef struct Canvas
{
	SDL_Texture *tex;
	SDL_Rect rect;
} Canvas;

SDL_Window* Main_Window;
SDL_Renderer* Main_Renderer;
SDL_Surface* Loading_Surf;
SDL_Event e;
Canvas WINCANV;
int MapWidth;
int MapHight;
SDL_Rect SrcR;      //画布复制时源方块区域
SDL_Rect DestR;			//画布复制时目的画布区域
TTF_Font* font = NULL;


SDL_Color color = { 178,34,89 };
SDL_Surface* surttf;
SDL_Rect rectTxt = { 0,0,300,300 };
char ch[1024] = { 0 };



char *localeToUTF8(const char *src) {
	static char *buf = NULL;
	if (buf) {
		free(buf);
		buf = NULL;
	}
	wchar_t *unicode_buf;
	int nRetLen = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
	unicode_buf = (wchar_t*)malloc((nRetLen + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, src, -1, unicode_buf, nRetLen);
	nRetLen = WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, NULL, 0, NULL, NULL);
	buf = (char*)malloc(nRetLen + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, buf, nRetLen, NULL, NULL);
	free(unicode_buf);
	return buf;
}
void setttf()
{
	TTF_Init();
	font = TTF_OpenFont(localeToUTF8("a.ttf"), 200);
}

SDL_Surface *LoadImageFromFile(const char * filename) // 加载图片函数
{
	SDL_Surface* loadedImage = NULL;
	loadedImage = IMG_Load(filename);
	return loadedImage;
}


void IntoDrawMode()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	setttf();
	//初始化窗口画布
	WINCANV.tex = NULL;
	WINCANV.rect.x = 0;
	WINCANV.rect.y = 0;
	WINCANV.rect.w = MapWidth;
	WINCANV.rect.h = MapHight;

}



void CreatWindow(const char *title, int WindowWidth, int WindowHight)  //创建窗口    窗口内建就可以了，因为创建渲染器需要窗口
{
	MapWidth = WindowWidth;    //窗口全局变量在此处被赋值
	MapHight = WindowHight;
	Main_Window = SDL_CreateWindow(localeToUTF8(title), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHight, 0);
	Main_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(Main_Renderer, 255, 255,255, 0); //默认画笔颜色是白色
	SDL_RenderClear(Main_Renderer);
}

void SetBrushColor(int r,int g,int b)
{
	SDL_SetRenderDrawColor(Main_Renderer, r, g, b, 255);
}

void SetBrushColorAlpha(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(Main_Renderer, r, g, b, a);
}


void SetDrawTarget(Canvas targetCanvas)
{

	SDL_SetRenderTarget(Main_Renderer, targetCanvas.tex);

}


//或者在定义时就确定画布的宽度和长，用下面这个函数

Canvas initCanvas()
{
	Canvas target;
	target.tex = SDL_CreateTexture(Main_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, MapWidth, MapHight);
	target.rect.x = 0;
	target.rect.y = 0;
	target.rect.w = MapWidth;
	target.rect.h = MapHight;

	return target;
}

void ClearScreen()
{
	SDL_RenderClear(Main_Renderer);
}

void ClearScreenWithColor(int r,int g,int b)
{
	Uint8 now_r = 0, now_g = 0, now_b = 0, now_a = 0;
	SDL_GetRenderDrawColor(Main_Renderer, &now_r, &now_g, &now_b,&now_a);
	SDL_SetRenderDrawColor(Main_Renderer, r, g, b, 255);
	SDL_RenderClear(Main_Renderer);
	SDL_SetRenderDrawColor(Main_Renderer, now_r, now_g, now_b, now_a);
}

void CopyFromCanvas(Canvas target,int x,int y,int w,int h,int nx,int ny,int nw,int nh)
{
	SrcR.x = x; SrcR.y = y; SrcR.w = w; SrcR.h = h;
	DestR.x = nx; DestR.y = ny; DestR.w = nw; DestR.h = nh;
	SDL_RenderCopy(Main_Renderer, target.tex, &SrcR, &DestR);

}

void CopyFromFullCanvas(Canvas target)
{
	SDL_RenderCopy(Main_Renderer, target.tex, NULL, NULL);
}


#define ShowScreen() SDL_RenderPresent(Main_Renderer)

void QuitDrawMode()
{
	SDL_DestroyRenderer(Main_Renderer);
	SDL_DestroyWindow(Main_Window);
	SDL_Quit();
}


#define point(x,y) SDL_RenderDrawPoint(Main_Renderer, x, y);
#define line(x1,y1,x2,y2) SDL_RenderDrawLine(Main_Renderer,x1,y1,x2,y2)


void circle(int x, int y, int r)
{
	Uint8 now_r = 0, now_g = 0, now_b = 0, now_a = 0;
	SDL_GetRenderDrawColor(Main_Renderer, &now_r, &now_g, &now_b, &now_a);
	ellipseRGBA(Main_Renderer, x, y, r, r, now_r, now_g, now_b, now_a);
}

void fill_circle(int x, int y, int r)
{
	Uint8 now_r = 0, now_g = 0, now_b = 0, now_a = 0;
	SDL_GetRenderDrawColor(Main_Renderer, &now_r, &now_g, &now_b, &now_a);
	filledCircleRGBA(Main_Renderer, x, y, r, now_r, now_g, now_b, now_a);     //在这个函数里输入颜色，渲染器颜色会被改成这个颜色
}

void rect(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	SDL_RenderDrawRect(Main_Renderer, &rect);
}

void box(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	Uint8 now_r = 0, now_g = 0, now_b = 0, now_a = 0;
	SDL_GetRenderDrawColor(Main_Renderer, &now_r, &now_g, &now_b, &now_a);
	boxRGBA(Main_Renderer, x, y, x + w, y + h, now_r, now_g, now_b, now_a);

}

void txt(const char *txt,int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;

	Uint8 now_r = 0, now_g = 0, now_b = 0, now_a = 0;
	SDL_GetRenderDrawColor(Main_Renderer, &now_r, &now_g, &now_b, &now_a);
	SDL_Color color = { now_r,now_g,now_b };

	SDL_Surface* surttf;
	char ch[1024] = { 0 };
	sprintf(ch, txt);
	surttf = TTF_RenderUTF8_Blended(font, localeToUTF8(ch), color);
	SDL_Texture *tmp;
	tmp = SDL_CreateTextureFromSurface(Main_Renderer, surttf);
	SDL_RenderCopy(Main_Renderer, tmp, NULL, &rect);

	SDL_FreeSurface(surttf);
	SDL_DestroyTexture(tmp);
}

void load_image(Canvas target,char * filename)       //例子  can2 = load_image("a.jpg");
{
	SDL_Surface *tmps;
	SDL_Texture *tmpt;
	tmps = LoadImageFromFile(filename);
	tmpt= SDL_CreateTextureFromSurface(Main_Renderer, tmps);

	SDL_SetRenderTarget(Main_Renderer, target.tex);
	SDL_RenderCopy(Main_Renderer, tmpt, NULL, NULL);

	SDL_FreeSurface(tmps);
	SDL_DestroyTexture(tmpt);    //这里没有解决新加载一张图原画布指针释放问题

}

#define Delay(x) SDL_Delay(x);
#define EQ SDL_PollEvent(&e)  //EQ即 EventQueue ，事件队列
#define e_type e.type
#define ET e.type         //ET即事件类型
#define KEY e.key.keysym.sym
#define e_KEYDOWN SDL_KEYDOWN
#define e_QUIT SDL_QUIT
#define e_MOUSE_XY SDL_MOUSEMOTION
#define e_MOUSE_DOWN SDL_MOUSEBUTTONDOWN
#define e_MOUSE_UP SDL_MOUSEBUTTONUP

int ellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmh, xph, ypk, ymk;
	int xmi, xpi, ymj, ypj;
	int xmj, xpj, ymi, ypi;
	int xmk, xpk, ymh, yph;

	if ((rx < 0) || (ry < 0)) {
		return (-1);
	}

	if (rx == 0) {
		return (vlineRGBA(renderer, x, y - ry, y + ry, r, g, b, a));
	}

	if (ry == 0) {
		return (hlineRGBA(renderer, x - rx, x + rx, y, r, g, b, a));
	}

	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	oh = oi = oj = ok = 0xFFFF;

	if (rx > ry) {
		ix = 0;
		iy = rx * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * ry) / rx;
			k = (i * ry) / rx;

			if (((ok != k) && (oj != k)) || ((oj != j) && (ok != j)) || (k != j)) {
				xph = x + h;
				xmh = x - h;
				if (k > 0) {
					ypk = y + k;
					ymk = y - k;
					result |= point(xmh, ypk);
					result |= point(xph, ypk);
					result |= point(xmh, ymk);
					result |= point(xph, ymk);
				}
				else {
					result |= point(xmh, y);
					result |= point(xph, y);
				}
				ok = k;
				xpi = x + i;
				xmi = x - i;
				if (j > 0) {
					ypj = y + j;
					ymj = y - j;
					result |= point(xmi, ypj);
					result |= point(xpi, ypj);
					result |= point(xmi, ymj);
					result |= point(xpi, ymj);
				}
				else {
					result |= point(xmi, y);
					result |= point(xpi, y);
				}
				oj = j;
			}

			ix = ix + iy / rx;
			iy = iy - ix / rx;

		} while (i > h);
	}
	else {
		ix = 0;
		iy = ry * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * rx) / ry;
			k = (i * rx) / ry;

			if (((oi != i) && (oh != i)) || ((oh != h) && (oi != h) && (i != h))) {
				xmj = x - j;
				xpj = x + j;
				if (i > 0) {
					ypi = y + i;
					ymi = y - i;
					result |= point(xmj, ypi);
					result |= point(xpj, ypi);
					result |= point(xmj, ymi);
					result |= point(xpj, ymi);
				}
				else {
					result |= point(xmj, y);
					result |= point(xpj, y);
				}
				oi = i;
				xmk = x - k;
				xpk = x + k;
				if (h > 0) {
					yph = y + h;
					ymh = y - h;
					result |= point(xmk, yph);
					result |= point(xpk, yph);
					result |= point(xmk, ymh);
					result |= point(xpk, ymh);
				}
				else {
					result |= point(xmk, y);
					result |= point(xpk, y);
				}
				oh = h;
			}

			ix = ix + iy / ry;
			iy = iy - ix / ry;

		} while (i > h);
	}

	return (result);
}


int filledCircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	Sint16 cx = 0;
	Sint16 cy = rad;
	Sint16 ocx = (Sint16)0xffff;
	Sint16 ocy = (Sint16)0xffff;
	Sint16 df = 1 - rad;
	Sint16 d_e = 3;
	Sint16 d_se = -2 * rad + 5;
	Sint16 xpcx, xmcx, xpcy, xmcy;
	Sint16 ypcy, ymcy, ypcx, ymcx;

	if (rad < 0) {
		return (-1);
	}
	if (rad == 0) {
		return (pixelRGBA(renderer, x, y, r, g, b, a));
	}

	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);


	do {
		xpcx = x + cx;
		xmcx = x - cx;
		xpcy = x + cy;
		xmcy = x - cy;
		if (ocy != cy) {
			if (cy > 0) {
				ypcy = y + cy;
				ymcy = y - cy;
				result |= hline(renderer, xmcx, xpcx, ypcy);
				result |= hline(renderer, xmcx, xpcx, ymcy);
			}
			else {
				result |= hline(renderer, xmcx, xpcx, y);
			}
			ocy = cy;
		}
		if (ocx != cx) {
			if (cx != cy) {
				if (cx > 0) {
					ypcx = y + cx;
					ymcx = y - cx;
					result |= hline(renderer, xmcy, xpcy, ymcx);
					result |= hline(renderer, xmcy, xpcy, ypcx);
				}
				else {
					result |= hline(renderer, xmcy, xpcy, y);
				}
			}
			ocx = cx;
		}

		if (df < 0) {
			df += d_e;
			d_e += 2;
			d_se += 2;
		}
		else {
			df += d_se;
			d_e += 2;
			d_se += 4;
			cy--;
		}
		cx++;
	} while (cx <= cy);

	return (result);
}

int boxRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	Sint16 tmp;
	SDL_Rect rect;
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelRGBA(renderer, x1, y1, r, g, b, a));
		}
		else {
			return (vlineRGBA(renderer, x1, y1, y2, r, g, b, a));
		}
	}
	else {
		if (y1 == y2) {
			return (hlineRGBA(renderer, x1, x2, y1, r, g, b, a));
		}
	}

	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	rect.x = x1;
	rect.y = y1;
	rect.w = x2 - x1 + 1;
	rect.h = y2 - y1 + 1;
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderFillRect(renderer, &rect);
	return result;
}


int vlineRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawLine(renderer, x, y1, x, y2);
	return result;
}

int pixelRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawPoint(renderer, x, y);
	return result;
}

int hlineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawLine(renderer, x1, y, x2, y);
	return result;
}
int hline(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y)
{
	return SDL_RenderDrawLine(renderer, x1, y, x2, y);;
}
