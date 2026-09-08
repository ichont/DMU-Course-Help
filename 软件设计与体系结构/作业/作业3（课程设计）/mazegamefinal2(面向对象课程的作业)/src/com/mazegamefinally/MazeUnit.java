package com.mazegamefinally;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;

public class MazeUnit {
	public int i;
	public int j;
	private int length;
	public boolean isVisited;
	public boolean wall;
	private GameMaze gameMaze;
	private boolean isEnd=false;
	public int direction=1;
	Image wallImg=Toolkit.getDefaultToolkit().getImage("pictures/wallImg.jpg");
	Image floorImg=Toolkit.getDefaultToolkit().getImage("pictures/floorImg.jpg");
	public MazeUnit(int i,int j,int length,GameMaze gameMaze,boolean isEnd) {
		this.i=i;
		this.j=j;
		this.length=length;
		this.isVisited=false;
		this.wall=true;
		this.gameMaze=gameMaze;
		this.isEnd=isEnd;
	}

	public void paintSelf(Graphics g) {
		if(isEnd==false) {
		if(wall==true) {
			g.setColor(Color.black);
			g.drawImage(wallImg,gameMaze.getStart()+j*length+2,gameMaze.getStart()+i*length+2,length,length,null);
			//g.fillRect(gameMaze.getStart()+j*length+2,gameMaze.getStart()+i*length+2,length,length);
		}
		else {
			g.setColor(Color.white);
			g.drawImage(floorImg,gameMaze.getStart()+j*length+2,gameMaze.getStart()+i*length+2 ,length,length, null);
			//g.fillRect(gameMaze.getStart()+j*length+2,gameMaze.getStart()+i*length+2,length,length);
		}
		}
		else {
			g.setColor(Color.yellow);
			g.fillRect(gameMaze.getStart()+j*length+2,gameMaze.getStart()+i*length+2,length,length);
		}
	}
	public Rectangle getRectangle() {
		return new Rectangle(gameMaze.getStart()+j*gameMaze.getLength()+2,gameMaze.getStart()+i*gameMaze.getLength()+2,gameMaze.getLength(),gameMaze.getLength());
	}

}
