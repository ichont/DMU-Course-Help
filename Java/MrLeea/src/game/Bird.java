package game;

import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.List;

public class Bird {
	//鸟的图片
	BufferedImage img;
	int x;
	int y;
	int w;
	int h;
	static int i = 0;
	//用来装一组图片的容器
	List<BufferedImage> list;
	double v0 = 8;//初速度
	double t = 0.3;//时间
	double s = 0;//距离
	double g = 1.2;//重力
	public Bird() {
		img = Tools.getImg("../img/bird"+i+"_0.png");
		x = 80;
		y = 245;
		w = img.getWidth();
		h = img.getHeight();
		//初始化装图片的容器
		list = new ArrayList<BufferedImage>();
		//加图片
		list.add(Tools.getImg("../img/bird"+i+"_0.png"));
		list.add(Tools.getImg("../img/bird"+i+"_1.png"));
		list.add(Tools.getImg("../img/bird"+i+"_2.png"));
	}	
	int index = 0;//标记取下标，来获取图片
	public void fly() {
		img = list.get(index%list.size());
		index++;
	}
	//小鸟运动
	public void move() {
		//计算小鸟上抛距离
		s = v0 * t;//小鸟y坐标
		y = (int)(y - s);//初始坐标-y坐标
		double v1 = v0 - g*t;//计算小鸟到达最高点时速度
		v0 = v1;//最高点速度=下落时的速度;
	}
	public void moveUp() {
		v0 = 8;
	}
	public boolean hit() {
		if(y <=-10 || y>= 360) {
			return true;
		}
		return false;
	}
	public boolean hit(Column column) {
		if(x >= column.x - w + 14 && x <= column.x + column.w - 14) {
			if(y > column.h + column.y - 12  && y < column.h + column.y + 24 + 50) {
				return false;
			}
			return true;//撞到了
		}
		return false;
	}
	public void getj(int j) {
		i = j;
	}
}
