#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
#define ok 'k'		//������j
#define H (10+15)		//�����������߼������������߼�����������
// H = H - 9;//H�ǿ���̨�����̳��ȣ���������ת��
int MAP_W,MAP_H;
int x, y, nextx, nexty, wint, turn, now, you, maxm = 0, maxy = 0, maxmcoordx = 0, maxmcoordy = 0, maxycoordx = 0, maxycoordy = 0, map[30][30];
int rr2 = 10, gg2 = 20, bb2 = 30, rr3 = 0, gg3 = 0, bb3 = 0;	//������ڱ�����ɫ�Ľ���
int baiqi_flag = 0;
int baiqi_x, baiqi_y;	//��������¼��������λ��
char game_begain = 0;	//Ϊ�˽������ʱ�а������ӵ���ɫ����
char win_flag = 0;		//Ĭ��û��Ӯ�������iswin�ķ���ֵ�෴�����ø�iswin()��
int mouse_x = 0, mouse_y = 0, mouse_x_down = 0, mouse_x_up = 0, mouse_y_down = 0, mouse_y_up = 0, mouse_down_flag = 0;
const int H2 = H - 9;	//H2�ǿ����ģ���ʾ����������
int i = 0, j = 0, at, bt, quit = 0, step;
int tw, th, size, qx, qy, each_cell;
void AI();
void compare();
void drawMap();
void swap();
void redraw();
int iswin();
void redraw()
{
	int i, j;
	for (i = 0; i<H; i++)
		for (j = 0; j<H; j++)
			map[i][j] = 9;
	x = H/ 2, y = H / 2;
	for (i = 4; i<H - 4; i++)
		for (j = 4; j<H - 4; j++)
			map[i][j] = 4;
	map[x][y] = 3;
	game_begain = 1;
}

void swap()
{
	int temp;
	temp = map[nextx][nexty];
	map[nextx][nexty] = map[x][y];
	map[x][y] = temp;
	x = nextx, y = nexty;
}




void drawMap()
{
	ClearScreenWithColor(70, 102, 53);
	if (rr3 - rr2 != 0)
		if (rr3 - rr2 > 0)
			rr2++;
		else
			rr2--;
	else
		rr3 = rand() % 255;

	if (gg3 - gg2 != 0)
		if (gg3 - gg2 > 0)
			gg2++;
		else
			gg2--;
	else
		gg3 = rand() % 255;

	if (bb3 - bb2 != 0)
		if (bb3 - bb2 > 0)
			bb2++;
		else
			bb2--;
	else
		bb3 = rand() % 255;
	SetBrushColorAlpha(rr2, gg2, bb2,255);
	//SetBrushColorAlpha(196, 186, 31, 255);
	txt("������", MAP_W*0.4, MAP_H*0.001, MAP_W * 1 / 5.0, MAP_H*0.1);
	SetBrushColorAlpha(0, 0, 0, 255);
	txt("wsad�ƶ���k����,���������", MAP_W*0.02, MAP_H*0.945, MAP_W * 0.5, MAP_H*0.05);
	SetBrushColor(136, 197, 116);
	rect(qx, qy, size, size);
	for (step = 0; step < size / each_cell; step++)
		line(qx, qy + each_cell*step, qx + size, qy + each_cell*step);
	for (step = 0; step < size / each_cell; step++)
		line(qx + each_cell*step, qy, qx + each_cell*step, qy + size);
	for (i = 4; i < H - 4; i++)
	{
		for (j = 4; j < H - 4; j++)
		{
			SetBrushColorAlpha(1, 1, 1, 255);
			if (map[i][j] == 1)
				fill_circle(qx + (j - 4) * each_cell, qy + (i - 4) * each_cell, each_cell / 2);

			SetBrushColorAlpha(255, 255, 255, 255);
			if (map[i][j] == 0)
			{
				fill_circle(qx + (j - 4) * each_cell, qy + (i - 4) * each_cell, each_cell / 2);
			}

		}
	}
		SetBrushColorAlpha(255, 20, 211, 110);	//���ƹ�����ѭ����
		box(qx + (y - 4)* each_cell - 0.3*each_cell, qy + (x - 4)* each_cell - 0.3*each_cell, 0.6*each_cell, 0.6*each_cell);

		win_flag = !iswin();		//����֮��������win_flag����Ϊ��������Ҫ��
	if (win_flag )
	{
		SetBrushColorAlpha(158, 219, 245, 70);		//AlphaֵԽ��Խ͸��
		box(MAP_W*0.15, MAP_H*0.3, MAP_W*0.7, MAP_H*0.3);
		SetBrushColorAlpha(253, 57, 57, 80);
		{
			if (wint == 1)
				txt("����Ӯ�ˣ�", MAP_W*0.25, MAP_H*0.30, MAP_W*0.6, MAP_H*0.15);
			else
				txt("����Ӯ�ˣ�", MAP_W*0.25, MAP_H*0.30, MAP_W*0.6, MAP_H*0.15);
			txt("��Ϸ����������������¿�ʼ", MAP_W*0.20, MAP_H*0.45, MAP_W*0.61, MAP_H*0.07);
		}
	}
	if (game_begain == 0&&baiqi_flag==0)
	{
		SetBrushColorAlpha(0, 0, 211, 110);	//��������λ��
		box(qx + (baiqi_y - 4)* each_cell - 0.3*each_cell, qy + (baiqi_x - 4)* each_cell - 0.3*each_cell, 0.6*each_cell, 0.6*each_cell);
	}

	//�����������
	//SetBrushColor(255, 255, 255);
	//circle(mouse_x, mouse_y, 10);
	//fill_circle(tmpx, tmpy, 10);

	//txt(ch2, 10, 10, 700, 50);
}

void AI()
{
	game_begain = 0;	//�������ӣ���Ϸ�Ϳ�ʼ�ˣ���ʱ��ʼ��ʾ������������
	now = 0, you = 1;
	turn = 1;
	compare();
	if (maxm > maxy)
	{
		//map[maxmcoordx][maxmcoordy] = 0;
		baiqi_x = maxmcoordx;
		baiqi_y = maxmcoordy;
	}
	if (maxm < maxy)
	{
		//map[maxycoordx][maxycoordy] = 0;
		baiqi_x = maxycoordx;
		baiqi_y = maxycoordy;
	}
	if (maxm == maxy)
	{
		now = rand() % 2;
		if (now == 1)
		{
			//map[maxycoordx][maxycoordy] = 0;
			baiqi_x = maxycoordx;
			baiqi_y = maxycoordy;
		}
		else
		{
			//map[maxmcoordx][maxmcoordy] = 0;
			baiqi_x = maxycoordx;
			baiqi_y = maxycoordy;
		}




	}
	//clrscr();
	//drawMap();
}

void compare()
{
	int i, j, score = 0, coord[H*H][2] = { 0 }, max = 0, t = 0;//t������
	for (i = 4; i<H - 4; i++)
	{
		for (j = 4; j<H - 4; j++)
		{

			//����ûһ������
			if (map[i][j] == 4)
			{//�����ǰ�ǿո�
				if (map[i + 1][j] == now || map[i][j + 1] == now || map[i + 1][j + 1] == now || map[i - 1][j + 1] == now || map[i + 1][j - 1] == now || map[i - 1][j - 1] == now || map[i][j - 1] == now || map[i - 1][j] == now)   //����˸��������
																																																									//�����ǰ�Ŀո��¸�����
				{

					//�һ�һ
					if (map[i][j + 1] == now&&map[i][j + 2] == 4)
						score += 20;
					//����һ
					if (map[i][j + 1] == now&&map[i][j + 2] == 9 || map[i][j + 1] == now&&map[i][j + 2] == you)
						score += 4;
					//�һ��
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == 4)
						score += 400;
					//������
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == 9 || map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == you)
						score += 90;
					//�һ���
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == 4)
						score += 6000;
					//������
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == you || map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == 9)
						score += 800;
					//�һ���
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == now&&map[i][j + 5] == 4)
						score += 20000;
					//������
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == now&&map[i][j + 5] == you || map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == now&&map[i][j + 5] == 9)
						score += 10000;
					//���һ
					if (map[i][j - 1] == now&&map[i][j - 2] == 4)
						score += 20;
					//����һ
					if (map[i][j - 1] == now&&map[i][j - 2] == you || map[i][j - 1] == 0 && map[i][j - 2] == 9)
						score += 4;
					//����
					if (map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == 4)
						score += 400;
					//������
					if (map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == you || map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == 9)
						score += 90;
					//�����
					if (map[i][j - 1] == you&&map[i][j - 2] == you&&map[i][j - 3] == you&&map[i][j - 4] == 4)
						score += 6000;
					//������
					if (map[i][j - 1] == 0 && map[i][j - 2] == 0 && map[i][j - 3] == 0 && map[i][j - 4] == you || map[i][j - 1] == 0 && &map[i][j - 2] == 0 && map[i][j - 3] == 0 && map[i][j - 4] == 9)
						score += 800;
					//�����
					if (map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == now&&map[i][j - 4] == now&&map[i][j - 5] == 4)
						score += 20000;
					//������
					if (map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == now&&map[i][j - 4] == now&&map[i][j - 5] == you || map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == now&&map[i][j - 4] == now&&map[i][j - 5] == 9)
						score += 10000;
					//�»�һ
					if (map[i + 1][j] == now&&map[i + 2][j] == 4)
						score += 20;
					//����һ
					if (map[i + 1][j] == now&&map[i + 2][j] == you || map[i + 1][j] == now&&map[i + 2][j] == 9)
						score += 4;
					//�»��
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == 4)
						score += 400;
					//������
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == 9 || map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == you)
						score += 90;
					//�»���
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == 4)
						score += 6000;
					//������
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == you || map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == 9)
						score += 800;
					//�»���
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == now&&map[i + 5][j] == 4)
						score += 20000;
					//������
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == now&&map[i + 5][j] == you || map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == now&&map[i + 5][j] == 9)
						score += 10000;
					//�ϻ�һ
					if (map[i - 1][j] == now&&map[i - 2][j] == 4)
						score += 20;
					//����һ
					if (map[i - 1][j] == now&&map[i - 2][j] == you || map[i - 1][j] == now&&map[i - 2][j] == 9)
						score += 4;
					//�ϻ��
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i][j - 3] == 4)
						score += 400;
					//������
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == 9 || map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == you)
						score += 90;
					//�ϻ���
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == 4)
						score += 6000;
					//������
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == you || map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == 9)
						score += 800;
					//�ϻ���
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == now&&map[i - 5][j] == 4)
						score += 20000;
					//������
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == now&&map[i - 5][j] == you || map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == now&&map[i - 5][j] == 9)
						score += 10000;
					//���»�һ
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == 4)
						score += 20;
					//������һ
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == 9 || map[i + 1][j + 1] == now&&map[i + 2][j + 2] == you)
						score += 4;
					//���»��
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == 4)
						score += 400;
					//��������
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == 9 || map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == you)
						score += 90;
					//���»���
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == 4)
						score += 6000;
					//��������
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == you || map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == 9)
						score += 800;
					//���»���
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == now&&map[i + 5][j + 5] == 4)
						score += 20000;
					//��������
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == now&&map[i + 5][j + 5] == you || map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == now&&map[i + 5][j + 5] == 9)
						score += 10000;
					//���ϻ�һ
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == 4)
						score += 20;
					//������һ
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == 9 || map[i - 1][j - 1] == now&&map[i - 2][j - 2] == you)
						score += 4;
					//���ϻ��
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == 4)
						score += 400;
					//��������
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == 9 || map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == you)
						score += 90;
					//���ϻ���
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == 4)
						score += 6000;
					//��������
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == you || map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == 9)
						score += 800;
					//���ϻ���
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == now&&map[i - 5][j - 5] == 4)
						score += 20000;
					//��������
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == now&&map[i - 5][j - 5] == you || map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == now&&map[i - 5][j - 5] == 9)
						score += 10000;
					//���»�һ
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == 4)
						score += 20;
					//������һ
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == you || map[i + 1][j - 1] == now&&map[i + 2][j - 2] == 9)
						score += 4;
					//���»��
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == 4)
						score += 400;
					//��������
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == 9 || map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == you)
						score += 90;
					//���»���
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == 4)
						score += 6000;
					//��������
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == you || map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == 9)
						score += 800;
					//���»���
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == now&&map[i + 5][j - 5] == 4)
						score += 20000;
					//��������
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == now&&map[i + 5][j - 5] == you || map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == now&&map[i + 5][j - 5] == 9)
						score += 10000;
					//���ϻ�һ
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == 4)
						score += 20;
					//������һ
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == you || map[i - 1][j + 1] == now&&map[i - 2][j + 2] == 9)
						score += 4;
					//���ϻ��
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == 4)
						score += 400;
					//��������
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == 9 || map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == you)
						score += 90;
					//���ϻ���
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == 4)
						score += 6000;
					//��������
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == you || map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == 9)
						score += 800;
					//���ϻ���
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == now&&map[i - 5][j + 5] == 4)
						score += 20000;
					//��������
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == now&&map[i - 5][j + 5] == you || map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == now&&map[i - 5][j + 5] == 9)
						score += 10000;
					if (
						map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == 4 && map[i][j + 1] == now&&map[i][j + 2] == 4 ||
						map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == 4 && map[i][j - 1] == now&&map[i][j - 2] == 4 ||
						map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == 4 && map[i + 1][j] == now&&map[i + 2][j] == 4 ||
						map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == 4 && map[i - 1][j] == now&&map[i - 2][j] == 4 ||
						map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == 4 && map[i + 1][j + 1] == now&&map[i + 2][j + 2] == 4 ||
						map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == 4 && map[i - 1][j - 1] == now&&map[i - 2][j - 2] == 4 ||
						map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == 4 && map[i - 1][j + 1] == now&&map[i - 2][j + 2] == 4 ||
						map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == 4 && map[i + 1][j - 1] == now&&map[i + 2][j - 2] == 4)
						score += 5580;
				}
			}

			//�»�һ
			if (score<max)
				score = 0;
			if (score == max)
			{
				t++;
				coord[t][0] = i, coord[t][1] = j;
				score = 0;
			}
			if (score>max)
			{
				t = 0;
				coord[t][0] = i, coord[t][1] = j;
				max = score;
				score = 0;
			}
		}
	}

	if (turn == 1)
	{
		maxm = max;
		i = rand() % (t + 1);
		maxmcoordx = coord[i][0];
		maxmcoordy = coord[i][1];
		turn = 2;
		now = 1, you = 0;
		compare();
	}
	else
	{
		maxy = max;
		i = rand() % (t + 1);
		maxycoordx = coord[i][0];
		maxycoordy = coord[i][1];
	}

}

int iswin()
{
	int i, j, time = 1, xi, yi;
	for (i = 4; i<H - 4; i++)
		for (j = 4; j<H - 4; j++)
		{
			if (map[i][j] == 1 || map[i][j] == 0)
			{
				if (map[i][j] == 0)
					wint = 0;
				else
					wint = 1;
				xi = i, yi = j;
				while (yi<H - 4 && yi>3)
				{
					yi++;
					if (map[xi][yi] == wint)
					{
						time++;
						if (time == 5)
							return 0;
					}
					else break;
				}
				time = 1;
				xi = i, yi = j;
				while (xi<H - 4 && xi>3)
				{
					yi--;
					if (map[xi][yi] == wint)
					{
						time++;
						if (time == 5)
							return 0;
					}
					else break;
				}
				time = 1;
				xi = i, yi = j;
				while (xi<H - 4 && xi>3)
				{
					xi++;
					if (map[xi][yi] == wint)
					{
						time++;
						if (time == 5)
							return 0;
					}
					else break;
				}
				time = 1;
				xi = i, yi = j;
				while (xi<H - 4 && xi>3)
				{
					xi--;
					if (map[xi][yi] == wint)
					{
						time++;
						if (time == 5)
							return 0;
					}
					else break;
				}
				time = 1;
				xi = i, yi = j;
				while (xi<H - 4 && xi>3 && yi<H - 4 && yi>3)
				{
					xi++, yi++;
					if (map[xi][yi] == wint)
					{
						time++;
						if (time == 5)
							return 0;
					}
					else break;
				}
				time = 1;
				xi = i, yi = j;
				while (xi<H - 4 && xi>3 && yi<H - 4 && yi>3)
				{
					xi++, yi--;
					if (map[xi][yi] == wint)
					{
						time++;
						if (time == 5)
							return 0;
					}
					else break;
				}
				time = 1;
				xi = i, yi = j;
				while (xi<H - 4 && xi>3 && yi<H - 4 && yi>3)
				{
					xi--, yi--;
					if (map[xi][yi] == wint)
					{
						time++;
						if (time == 5)
							return 0;
					}
					else break;
				}
				time = 1;
				xi = i, yi = j;
				while (xi<H - 4 && xi>3 && yi<H - 4 && yi>3)
				{
					xi--, yi++;
					if (map[xi][yi] == wint)
					{
						time++;
						if (time == 5)
							return 0;
					}
					else break;
				}
				time = 1;
			}
		}
	return 1;
}
