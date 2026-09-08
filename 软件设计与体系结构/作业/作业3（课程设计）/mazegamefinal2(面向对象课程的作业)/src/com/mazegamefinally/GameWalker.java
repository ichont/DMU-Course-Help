package com.mazegamefinally;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.util.List;

import javax.swing.JOptionPane;

public class GameWalker {
	  private int i;
	  private int j;
      private GameMaze gameMaze;
	  private GamePresent gamePresent;
	  public boolean auto=false;
	  public List map;
	  private int count;
	  Image walker=Toolkit.getDefaultToolkit().getImage("pictures/walkerImg.jpg");
	  
	  public GameWalker(int i,int j, GameMaze gameMaze,GamePresent gamePresent) {
		  this.i=i;
		  this.j=j;
		  this.gameMaze=gameMaze;
		  this.gamePresent=gamePresent;
	  }
		  
	  
	  public int getI() {
		return i;
	}


	public void setI(int i) {
		this.i = i;
	}


	public int getJ() {
		return j;
	}


	public void setJ(int j) {
		this.j = j;
	}


	public void move(int type) {
		  if(type==4&&gameMaze.getMazeUnits()[i-1][j].wall==false) {
			  i=i-1;
		  }
		  else if(type==1&&gameMaze.getMazeUnits()[i][j+1].wall==false) {
			  j=j+1;
		  }
		  else if(type==2&&gameMaze.getMazeUnits()[i+1][j].wall==false) {
			  i=i+1;
		  }
		  else if(type==3&&gameMaze.getMazeUnits()[i][j-1].wall==false) {
			  j=j-1;
		  }
		  if(getRectangle().intersects(gameMaze.getEnd().getRectangle())) {
			  gamePresent.gameState=2;
			  if(gamePresent.getGameDifficulty()==3) {
			  JOptionPane.showMessageDialog(gamePresent, this,"恭喜游戏通关", 0);
			   System.exit(0);
			  }
			  
		  }
	  }
      public void paintSelf(Graphics g) {
    	  
    	  if(auto==true&&gamePresent.gameState==1) {
    	  move((int)map.get(count-1));
    		  count--;
    	  }
    	  g.setColor(Color.blue);
    	  g.drawImage(walker,gameMaze.getStart()+j*gameMaze.getLength()+2,gameMaze.getStart()+i*gameMaze.getLength()+2, gameMaze.getLength(),gameMaze.getLength(),null);
      }
      
      private Rectangle getRectangle() {
    	  return new Rectangle(gameMaze.getStart()+j*gameMaze.getLength()+2,gameMaze.getStart()+i*gameMaze.getLength()+2,gameMaze.getLength(),gameMaze.getLength());
      }
     public void getMap() {
    	  map=gameMaze.getRoadPath();
    	  count=map.size();
      }
}
