#include<stdlib.h>
#include<time.h>
#include"draw_my_ui.hpp"
#include"logic.hpp"
#define WINDOW_W 700       //���ڿ� ����Ϊ��λ
#define WINDOW_H 750      //���ڸ� ����Ϊ��λ

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));
	IntoDrawMode();
	CreatWindow("������",WINDOW_W, WINDOW_H);
	MAP_W=WINDOW_W,MAP_H=WINDOW_H;
	SetBrushColor(0, 0, 0);
	Canvas can1 = initCanvas();
	Canvas can2 = initCanvas();
	int at, bt;		//���ڼ�ʱ
	redraw();
	SDL_GetWindowSize(Main_Window, &tw, &th);	 //th,tw�������Ż�ȡ���ĵ�ǰ���ڵĳߴ�

	if (tw > th)
		size = th *0.8;
	else
		size = tw *0.8;
	qx = (tw - size) / 2;                       //qx,qy���������Ͻ�����
	qy = (th - size) / 2;
	i = size / (H-9);
	if (i*(H-9) != size)
		size = (i + 1)*(H-9);
	each_cell = size / (H-9);
	while (!quit)				//ͼ�γ������ѭ��
	{
		at = clock();
		i = 0;

		while (EQ != 0)			//�����������ʱ���¼���������������ѭ��
		{
			switch (ET)
			{

			case e_QUIT:
				quit = 1;		//quit����ֵ 1 ����ѭ���˳�
				break;

			case e_KEYDOWN:
				if (iswin() == 0)	//����ϸ�ѭ������Ϸ�������������»����߼���ͼ
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

			case e_MOUSE_DOWN:					//�����갴��
				if (e.button.button ==SDL_BUTTON_LEFT)	//�������������
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
			case e_MOUSE_UP:						//�����굯��
				if (iswin() == 0)	//����ϸ�ѭ������Ϸ�������������»����߼���ͼ
				{
					redraw();
					break;
				}
				if (e.button.button ==SDL_BUTTON_LEFT)	//�������������
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
							i = 0;			//i����Ϸ����״̬��¼
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
			case left:             /*��һ��if��ֹ���ͺڰ��ӽ������ڶ���if��ֹ��ǰ�����ɺڰ��ӣ�������*/
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
						AI();			    //AI���Է���һ�����꣬������µ���
						baiqi_flag = 1;   //��¼��������û��
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
