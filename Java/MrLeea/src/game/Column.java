package game;

import java.awt.image.BufferedImage;
import java.util.Random;

public class Column {//柱子的类
	BufferedImage img1;
	BufferedImage img2;
	int x;
	int y;
	int w;
	int h;
	static int j = 0;
	//柱子间距
	int d = 250;
	//用一个随机数
	Random ran = new Random();
	public Column(int i) {//i 为第几根柱子
		img1 = Tools.getImg("../img/pipe"+j+"_down.png");
		img2 = Tools.getImg("../img/pipe"+j+"_up.png");
		w = img1.getWidth();
		h = img1.getHeight();
		//x = 100;
		x = 400 + 200 * (i - 1);
		y = - 512 + 240 +ran.nextInt(200)- j * 60; //+ 140;//ran.nextInt(150) - j * 60;
	}
	public void move(){
		if(x <= - w){//地面有限，地面重复出现，保证地面
			x = 300 + d;
			y = - 512 + 240 +ran.nextInt(200)- j * 60;
		}
		x--;
	}
	public void geti(int i) {
		j = i;
	}
}
