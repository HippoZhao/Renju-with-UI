#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
#define ok 'k'		//落子是j
#define H (10+15)		//这里行数是逻辑行数（程序逻辑数组行数）
// H = H - 9;//H是控制台的棋盘长度，这里做了转换
int MAP_W,MAP_H;
int x, y, nextx, nexty, wint, turn, now, you, maxm = 0, maxy = 0, maxmcoordx = 0, maxmcoordy = 0, maxycoordx = 0, maxycoordy = 0, map[30][30];
int rr2 = 10, gg2 = 20, bb2 = 30, rr3 = 0, gg3 = 0, bb3 = 0;	//这个用于标题颜色的渐变
int baiqi_flag = 0;
int baiqi_x, baiqi_y;	//这个坐标记录白旗落子位置
char game_begain = 0;	//为了解决开局时有白旗落子的蓝色坐标
char win_flag = 0;		//默认没有赢，这里和iswin的返回值相反，懒得改iswin()了
int mouse_x = 0, mouse_y = 0, mouse_x_down = 0, mouse_x_up = 0, mouse_y_down = 0, mouse_y_up = 0, mouse_down_flag = 0;
const int H2 = H - 9;	//H2是看到的，显示的棋盘行数
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
	txt("五子棋", MAP_W*0.4, MAP_H*0.001, MAP_W * 1 / 5.0, MAP_H*0.1);
	SetBrushColorAlpha(0, 0, 0, 255);
	txt("wsad移动，k放子,鼠标操作亦可", MAP_W*0.02, MAP_H*0.945, MAP_W * 0.5, MAP_H*0.05);
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
		SetBrushColorAlpha(255, 20, 211, 110);	//绘制光标放在循环外
		box(qx + (y - 4)* each_cell - 0.3*each_cell, qy + (x - 4)* each_cell - 0.3*each_cell, 0.6*each_cell, 0.6*each_cell);

		win_flag = !iswin();		//这里之所以设置win_flag是因为主函数里要用
	if (win_flag )
	{
		SetBrushColorAlpha(158, 219, 245, 70);		//Alpha值越低越透明
		box(MAP_W*0.15, MAP_H*0.3, MAP_W*0.7, MAP_H*0.3);
		SetBrushColorAlpha(253, 57, 57, 80);
		{
			if (wint == 1)
				txt("黑棋赢了！", MAP_W*0.25, MAP_H*0.30, MAP_W*0.6, MAP_H*0.15);
			else
				txt("白棋赢了！", MAP_W*0.25, MAP_H*0.30, MAP_W*0.6, MAP_H*0.15);
			txt("游戏结束！按任意键重新开始", MAP_W*0.20, MAP_H*0.45, MAP_W*0.61, MAP_H*0.07);
		}
	}
	if (game_begain == 0&&baiqi_flag==0)
	{
		SetBrushColorAlpha(0, 0, 211, 110);	//白棋落子位置
		box(qx + (baiqi_y - 4)* each_cell - 0.3*each_cell, qy + (baiqi_x - 4)* each_cell - 0.3*each_cell, 0.6*each_cell, 0.6*each_cell);
	}

	//下面和鼠标相关
	//SetBrushColor(255, 255, 255);
	//circle(mouse_x, mouse_y, 10);
	//fill_circle(tmpx, tmpy, 10);

	//txt(ch2, 10, 10, 700, 50);
}

void AI()
{
	game_begain = 0;	//白旗落子，游戏就开始了，这时开始显示白棋落子坐标
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
	int i, j, score = 0, coord[H*H][2] = { 0 }, max = 0, t = 0;//t来计数
	for (i = 4; i<H - 4; i++)
	{
		for (j = 4; j<H - 4; j++)
		{

			//遍历没一个格子
			if (map[i][j] == 4)
			{//如果当前是空格
				if (map[i + 1][j] == now || map[i][j + 1] == now || map[i + 1][j + 1] == now || map[i - 1][j + 1] == now || map[i + 1][j - 1] == now || map[i - 1][j - 1] == now || map[i][j - 1] == now || map[i - 1][j] == now)   //这里八个方向遍历
																																																									//如果当前的空格下个有子
				{

					//右活一
					if (map[i][j + 1] == now&&map[i][j + 2] == 4)
						score += 20;
					//右死一
					if (map[i][j + 1] == now&&map[i][j + 2] == 9 || map[i][j + 1] == now&&map[i][j + 2] == you)
						score += 4;
					//右活二
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == 4)
						score += 400;
					//右死二
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == 9 || map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == you)
						score += 90;
					//右活三
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == 4)
						score += 6000;
					//右死三
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == you || map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == 9)
						score += 800;
					//右活四
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == now&&map[i][j + 5] == 4)
						score += 20000;
					//右死四
					if (map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == now&&map[i][j + 5] == you || map[i][j + 1] == now&&map[i][j + 2] == now&&map[i][j + 3] == now&&map[i][j + 4] == now&&map[i][j + 5] == 9)
						score += 10000;
					//左活一
					if (map[i][j - 1] == now&&map[i][j - 2] == 4)
						score += 20;
					//左死一
					if (map[i][j - 1] == now&&map[i][j - 2] == you || map[i][j - 1] == 0 && map[i][j - 2] == 9)
						score += 4;
					//左活二
					if (map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == 4)
						score += 400;
					//左死二
					if (map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == you || map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == 9)
						score += 90;
					//左活三
					if (map[i][j - 1] == you&&map[i][j - 2] == you&&map[i][j - 3] == you&&map[i][j - 4] == 4)
						score += 6000;
					//左死三
					if (map[i][j - 1] == 0 && map[i][j - 2] == 0 && map[i][j - 3] == 0 && map[i][j - 4] == you || map[i][j - 1] == 0 && &map[i][j - 2] == 0 && map[i][j - 3] == 0 && map[i][j - 4] == 9)
						score += 800;
					//左活四
					if (map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == now&&map[i][j - 4] == now&&map[i][j - 5] == 4)
						score += 20000;
					//左死四
					if (map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == now&&map[i][j - 4] == now&&map[i][j - 5] == you || map[i][j - 1] == now&&map[i][j - 2] == now&&map[i][j - 3] == now&&map[i][j - 4] == now&&map[i][j - 5] == 9)
						score += 10000;
					//下活一
					if (map[i + 1][j] == now&&map[i + 2][j] == 4)
						score += 20;
					//下死一
					if (map[i + 1][j] == now&&map[i + 2][j] == you || map[i + 1][j] == now&&map[i + 2][j] == 9)
						score += 4;
					//下活二
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == 4)
						score += 400;
					//下死二
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == 9 || map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == you)
						score += 90;
					//下活三
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == 4)
						score += 6000;
					//下死三
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == you || map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == 9)
						score += 800;
					//下活四
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == now&&map[i + 5][j] == 4)
						score += 20000;
					//下死四
					if (map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == now&&map[i + 5][j] == you || map[i + 1][j] == now&&map[i + 2][j] == now&&map[i + 3][j] == now&&map[i + 4][j] == now&&map[i + 5][j] == 9)
						score += 10000;
					//上活一
					if (map[i - 1][j] == now&&map[i - 2][j] == 4)
						score += 20;
					//上死一
					if (map[i - 1][j] == now&&map[i - 2][j] == you || map[i - 1][j] == now&&map[i - 2][j] == 9)
						score += 4;
					//上活二
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i][j - 3] == 4)
						score += 400;
					//上死二
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == 9 || map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == you)
						score += 90;
					//上活三
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == 4)
						score += 6000;
					//上死三
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == you || map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == 9)
						score += 800;
					//上活四
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == now&&map[i - 5][j] == 4)
						score += 20000;
					//上死四
					if (map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == now&&map[i - 5][j] == you || map[i - 1][j] == now&&map[i - 2][j] == now&&map[i - 3][j] == now&&map[i - 4][j] == now&&map[i - 5][j] == 9)
						score += 10000;
					//右下活一
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == 4)
						score += 20;
					//右下死一
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == 9 || map[i + 1][j + 1] == now&&map[i + 2][j + 2] == you)
						score += 4;
					//右下活二
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == 4)
						score += 400;
					//右下死二
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == 9 || map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == you)
						score += 90;
					//右下活三
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == 4)
						score += 6000;
					//右下死三
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == you || map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == 9)
						score += 800;
					//右下活四
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == now&&map[i + 5][j + 5] == 4)
						score += 20000;
					//右下死四
					if (map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == now&&map[i + 5][j + 5] == you || map[i + 1][j + 1] == now&&map[i + 2][j + 2] == now&&map[i + 3][j + 3] == now&&map[i + 4][j + 4] == now&&map[i + 5][j + 5] == 9)
						score += 10000;
					//左上活一
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == 4)
						score += 20;
					//左上死一
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == 9 || map[i - 1][j - 1] == now&&map[i - 2][j - 2] == you)
						score += 4;
					//左上活二
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == 4)
						score += 400;
					//左上死二
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == 9 || map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == you)
						score += 90;
					//左上活三
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == 4)
						score += 6000;
					//左上死三
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == you || map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == 9)
						score += 800;
					//左上活四
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == now&&map[i - 5][j - 5] == 4)
						score += 20000;
					//左上死四
					if (map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == now&&map[i - 5][j - 5] == you || map[i - 1][j - 1] == now&&map[i - 2][j - 2] == now&&map[i - 3][j - 3] == now&&map[i - 4][j - 4] == now&&map[i - 5][j - 5] == 9)
						score += 10000;
					//左下活一
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == 4)
						score += 20;
					//左下死一
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == you || map[i + 1][j - 1] == now&&map[i + 2][j - 2] == 9)
						score += 4;
					//左下活二
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == 4)
						score += 400;
					//左下死二
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == 9 || map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == you)
						score += 90;
					//左下活三
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == 4)
						score += 6000;
					//左下死三
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == you || map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == 9)
						score += 800;
					//左下活四
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == now&&map[i + 5][j - 5] == 4)
						score += 20000;
					//左下死四
					if (map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == now&&map[i + 5][j - 5] == you || map[i + 1][j - 1] == now&&map[i + 2][j - 2] == now&&map[i + 3][j - 3] == now&&map[i + 4][j - 4] == now&&map[i + 5][j - 5] == 9)
						score += 10000;
					//右上活一
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == 4)
						score += 20;
					//右上死一
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == you || map[i - 1][j + 1] == now&&map[i - 2][j + 2] == 9)
						score += 4;
					//右上活二
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == 4)
						score += 400;
					//右上死二
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == 9 || map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == you)
						score += 90;
					//右上活三
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == 4)
						score += 6000;
					//右上死三
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == you || map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == 9)
						score += 800;
					//右上活四
					if (map[i - 1][j + 1] == now&&map[i - 2][j + 2] == now&&map[i - 3][j + 3] == now&&map[i - 4][j + 4] == now&&map[i - 5][j + 5] == 4)
						score += 20000;
					//右上死四
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

			//下活一
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
