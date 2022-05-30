package game;

import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JPanel;

public class GamePanel extends JPanel {//画板类
//放置背景图片的变量
	Ground ground;
	Column column1;
	Column column2;
	Column column3;
	Bird bird;
	boolean start;//游戏准备状态
	boolean gameOver;
	static int[] s = new int[4];
	static int score = s[1] + s[2] * 10 + s[3] * 100;
	static int j = 1;
	public boolean judge;
//构造器
	public GamePanel() {
		//设置背景图片
		ground = new Ground();
		column1 = new Column(1);
		column2 = new Column(2);
		column3 = new Column(3);
		bird = new Bird();
		start = false;
		gameOver = false;
		score = 0;
		change();
		MouseAdapter adapter = new MouseAdapter(){
			public void mousePressed(MouseEvent e) {
				super.mousePressed(e);
				if(start == false) {
					//运行启动
					start = true;
					start();
				}
				else if(gameOver) {//游戏回到准备状态
					start = false;
					gameOver = false;
					//重制所有对象；
					ground = new Ground();
					column1 = new Column(1);
					column2 = new Column(2);
					column3 = new Column(3);
					bird = new Bird();
					for(int i = 1 ; i <= 3 ; i++) {
						s[i] = 0;
					}
					repaint();
				}
				else {
					bird.moveUp();
				}
			}
		};
		this.addMouseListener(adapter);
	}
	//游戏开始
	public void start() {
		//启动游戏运行线程;
		Thread1 thread1 = new Thread1();//创建线程;
		//将线程装入thread1;
		Thread thread0 = new Thread(thread1);
		thread0.start();//将线程纳入调度 调度时未必运行
	}
	public void change() {
		Thread2 thread2 = new Thread2();
		Thread thread0 = new Thread(thread2);
		thread0.start();
	}
	//向画板中绘制内容的方法；
		public void paint(Graphics g) {
			super.paint(g);
			//绘制背景图片(图片,x,y,null画满)
			g.drawImage(Tools.getImg("../img/bg"+j+".png"),0,0,null);
			//绘制柱子图片
			g.drawImage(column1.img1,column1.x,column1.y ,null);//生成上面柱子
			g.drawImage(column1.img2,column1.x,column1.y + 377 + 50 + column1.j * 60,null);//生成下面柱子
			g.drawImage(column2.img1,column2.x,column2.y ,null);
			g.drawImage(column2.img2,column2.x,column2.y + 377 + 50 + column2.j * 60,null);
			g.drawImage(column3.img1,column3.x,column3.y ,null);
			g.drawImage(column3.img2,column3.x,column3.y + 377 + 50 + column3.j * 60,null);
			//绘制地面图片
			g.drawImage(ground.img,ground.x,ground.y,null);
			//绘制小鸟图片
			g.drawImage(bird.img,bird.x,bird.y,null);
			//绘制准备图片
			if(start == false) {
				g.drawImage(Tools.getImg("../img/tutorial.png"),46,200,null);
				g.drawImage(Tools.getImg("../img/text_ready.png"),40,100,null);
			}
			if(gameOver) {
				g.drawImage(Tools.getImg("../img/text_game_over.png"),30,200,null);
			}
			//绘制成绩
			for(int i = 1 ; i <= 3 ; i++) {
					g.drawImage(Tools.getImg("../img/font_"+s[i]+".png"),160 - i * 20 ,20,null);
			}
		}
	void score(int[] score) {
		for(int i = 1; i <= 2 ; i++) {
			if(score[3] == 10) {
				score[3] = score[2] = score[1] =0;
			}
			if(score[i] == 10) {
				score[i + 1]++;
				score[i] -= 10;
			}
		}
	}
	class Thread2 implements Runnable {
		public void run() {
			int i = 0;
			while(true){
			while(start == false) {//在游戏未开始时可以对所有图片进行重画
				column1 = new Column(1);
				column2 = new Column(2);
				column3 = new Column(3);
				bird = new Bird();
				repaint();
			}
			try {
				Thread.sleep(100);//节省内存
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			}
		}
	
	}
	class Thread1 implements Runnable { //多线程
		public void run() {//编写该线程需要运行的方法
			//让地面移动
			while(true) {
				ground.move();
				column1.move();
				column2.move();
				column3.move();
				bird.fly();
				bird.move();
				boolean bool = bird.hit();//检测小鸟时候在上下发生碰撞
				boolean bool1 = bird.hit(column1);//检测柱子
				boolean bool2 = bird.hit(column2);
				boolean bool3 = bird.hit(column3);
				//检测小鸟是否发生碰撞
				if(bool||bool1||bool2||bool3) {
					gameOver = true;
					return;//结束
				}
				//计算分数
				if(bird.x == column1.x + column1.w ||bird.x == column2.x + column2.w ||bird.x == column3.x + column3.w ) {
					s[1]++;
					score(s);
				}
				try {
					Thread.sleep(9);//每移动一次休息一秒
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				repaint();
			}
		}
	}
		
}
