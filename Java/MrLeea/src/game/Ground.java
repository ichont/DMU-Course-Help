package game;

import java.awt.image.BufferedImage;

public class Ground {
	int x;
	int y;
	int w;
	int h;
	BufferedImage img;
	Ground ground;
	public Ground(){//构造方法
		img = Tools.getImg("../img/land.png");
		h = img.getHeight();
		w = img.getWidth();
		x = 0;//初始化x
		y = 512 - h;//初始化y
	}
	public void move(){
		if(x <= -(w - 288)) {//地面有限，地面重复出现，保证地面
			x = 0;
		}
		x --;
	}
}
