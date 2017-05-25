#include<stdlib.h>
#include<time.h>
#include"draw_my_ui.hpp"
#include"logic.hpp"
#define WINDOW_W 700       //窗口宽 像素为单位
#define WINDOW_H 750      //窗口高 像素为单位

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));
	IntoDrawMode();
	CreatWindow("五子棋",WINDOW_W, WINDOW_H);
	MAP_W=WINDOW_W,MAP_H=WINDOW_H;
	SetBrushColor(0, 0, 0);
	Canvas can1 = initCanvas();
	Canvas can2 = initCanvas();
	int at, bt;		//用于计时
	redraw();
	SDL_GetWindowSize(Main_Window, &tw, &th);	 //th,tw是用来放获取到的当前窗口的尺寸

	if (tw > th)
		size = th *0.8;
	else
		size = tw *0.8;
	qx = (tw - size) / 2;                       //qx,qy是棋盘左上角坐标
	qy = (th - size) / 2;
	i = size / (H-9);
	if (i*(H-9) != size)
		size = (i + 1)*(H-9);
	each_cell = size / (H-9);
	while (!quit)				//图形程序的主循环
	{
		at = clock();
		i = 0;

		while (EQ != 0)			//如果程序运行时有事件发生，则进入这个循环
		{
			switch (ET)
			{

			case e_QUIT:
				quit = 1;		//quit被赋值 1 ，主循环退出
				break;

			case e_KEYDOWN:
				if (iswin() == 0)	//如果上个循环里游戏结束，这里重新绘制逻辑地图
				{
					redraw();
					break;
				}
				switch (KEY)
				{
				case SDLK_a:i = left; break;
				case SDLK_d:i = right; break;
				case SDLK_w:i = up; break;
				case SDLK_s:i = down; break;
				case SDLK_k:i = ok; break;
				default:i = 0; break;
				}
				break;

			case e_MOUSE_XY:
				mouse_x = e.motion.x;
				mouse_y = e.motion.y;
				break;

			case e_MOUSE_DOWN:					//如果鼠标按下
				if (e.button.button ==SDL_BUTTON_LEFT)	//如果鼠标左键按下
				{
					mouse_x_down = e.button.x;
					mouse_y_down = e.button.y;
					mouse_down_flag = 1;

				}

				if (e.button.button = SDL_BUTTON_RIGHT)
				{
					;
				}
				break;
			case e_MOUSE_UP:						//如果鼠标弹起
				if (iswin() == 0)	//如果上个循环里游戏结束，这里重新绘制逻辑地图
				{
					redraw();
					break;
				}
				if (e.button.button ==SDL_BUTTON_LEFT)	//如果鼠标左键弹起
				{
					mouse_x_up = e.button.x;
					mouse_y_up = e.button.y;

					mouse_down_flag = 0;

					if (mouse_x_up >= qx && mouse_x_up <= qx + size && mouse_y_up >= qy && mouse_y_up <= qy + size)
					{
						if (((mouse_x_up - qx) % each_cell) / (each_cell*1.0) <= 0.25 || ((mouse_x_up - qx) % each_cell) / (each_cell*1.0) >= 0.75 || ((mouse_y_up - qy) % each_cell) / (each_cell*1.0) <= 0.25 || ((mouse_y_up - qy) % each_cell) / (each_cell*1.0) >= 0.75)
						{
							int tmpx = 0, tmpy = 0;
							if (((mouse_x_up - qx) % each_cell) / (each_cell*1.0) <= 0.5)
							{
								tmpx = (mouse_x_up - qx) / each_cell;
							}

							if (((mouse_x_up - qx) % each_cell) / (each_cell*1.0) > 0.5)
							{
								tmpx = (mouse_x_up - qx) / each_cell + 1;
							}

							if (((mouse_y_up - qy) % each_cell) / (each_cell*1.0) <= 0.5)
							{
								tmpy = (mouse_y_up - qy) / each_cell;
							}

							if (((mouse_y_up - qy) % each_cell) / (each_cell*1.0) > 0.5)
							{
								tmpy = (mouse_y_up - qy) / each_cell + 1;
							}
							x = tmpy + 4;
							y = tmpx + 4;
							i = ok;
						}
						else
							i = 0;			//i是游戏控制状态记录
					}

				}
				break;
			}


		}
			SetDrawTarget(can1);

			int t = 0;
		one:


			switch (i)
			{
			case left:             /*第一个if防止光标和黑白子交换，第二个if防止当前坐标变成黑白子，跟着走*/
				nextx = x;
				if (y == 4)
					//goto one;
					;
				else
					nexty = y - 1;
				if (map[x][y] == 1 || map[x][y] == 0)
				{
					if (map[nextx][nexty] == 1 || map[nextx][nexty] == 0)
						;
					else
						map[nextx][nexty] = 3;
					x = nextx, y = nexty;
					break;
				}
				if (map[nextx][nexty] == 1 || map[nextx][nexty] == 0)
				{
					map[x][y] = 4;
					x = nextx, y = nexty;
					break;
				}
				swap(); break;
			case right:
				nextx = x;
				if (y == H - 5)
					//goto one;
					;
				else
					nexty = y + 1;
				if (map[x][y] == 1 || map[x][y] == 0)
				{
					if (map[nextx][nexty] == 1 || map[nextx][nexty] == 0)
						;
					else
						map[nextx][nexty] = 3;
					x = nextx, y = nexty;
					break;
				}
				if (map[nextx][nexty] == 1 || map[nextx][nexty] == 0)
				{
					map[x][y] = 4;
					x = nextx, y = nexty;
					break;
				}
				swap(); break;
			case up:
				if (x == 4)
					//goto one;
					;
				else
					nextx = x - 1;
				nexty = y;
				if (map[x][y] == 1 || map[x][y] == 0)
				{
					if (map[nextx][nexty] == 1 || map[nextx][nexty] == 0)
						;
					else
						map[nextx][nexty] = 3;
					x = nextx, y = nexty;
					break;
				}
				if (map[nextx][nexty] == 1 || map[nextx][nexty] == 0)
				{
					map[x][y] = 4;
					x = nextx, y = nexty;
					break;
				}
				swap(); break;
			case down:
				if (x == H - 5)
					//goto one;
					;
				else
					nextx = x + 1;
				nexty = y;
				if (map[x][y] == 1 || map[x][y] == 0)
				{
					if (map[nextx][nexty] == 1 || map[nextx][nexty] == 0)
						;
					else
						map[nextx][nexty] = 3;
					x = nextx, y = nexty;
					break;
				}
				if (map[nextx][nexty] == 1 || map[nextx][nexty] == 0)
				{
					map[x][y] = 4;
					x = nextx, y = nexty;
					break;
				}
				swap();
				break;
			case ok:
				if (map[x][y] == 0 || map[x][y] == 1)
					//goto one;
					;//do nothing
				else
				{
					map[x][y] = 1;
					if (!win_flag)
					{
						AI();			    //AI可以返回一个坐标，白旗刚下的子
						baiqi_flag = 1;   //记录白棋落子没有
					}

					goto end;
				}
				break;
			default:break;
			}
		end:;


			drawMap();
			SetDrawTarget(WINCANV);
			CopyFromFullCanvas(can1);

			ShowScreen();
			if (baiqi_flag == 1)
			{
				Delay(650);
				map[baiqi_x][baiqi_y] = 0;
				baiqi_flag = 0;
			}

			bt = clock();
			bt = 80 - (bt - at) / 1000;
			if (bt>0)
				Delay(bt);
		}




	QuitDrawMode();
	return 0;
}
