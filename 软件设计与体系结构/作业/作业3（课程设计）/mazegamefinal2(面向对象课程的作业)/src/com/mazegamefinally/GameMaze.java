package com.mazegamefinally;

import java.awt.Graphics;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Stack;


public class GameMaze {
	 private MazeUnit[][] mazeUnits;
	 private int rows;
	 private int cols;
	 private int length;
	 private int start=50;
	 private MazeUnit end;
	 private GameWalker gameWalker;
	 
	 private GamePresent gamePresent;
	 
	 
	 public int getLength() {
		return length;
	}
	public void setLength(int length) {
		this.length = length;
	}
	
	public int getStart() {
		return start;
	}
	public void setStart(int start) {
		this.start = start;
	}
	
	public MazeUnit getEnd() {
		return end;
	}
	public void setEnd(MazeUnit end) {
		this.end = end;
	}
	public MazeUnit[][] getMazeUnits() {
		return mazeUnits;
	}
	public void setMazeUnits(MazeUnit[][] mazeUnits) {
		this.mazeUnits = mazeUnits;
	}
	public GameMaze(int gameDifficulty,GamePresent gamePresent) {
		this.gamePresent=gamePresent;
		 getFullWallsMaze(gameDifficulty);
		 getFinalMaze();
	 }
	 //生成全是墙的初始迷宫
	 private void getFullWallsMaze(int gameDifficulty) {
		 switch(gameDifficulty) {
       	 case 1:
       		 rows=21;
       		 cols=21;
       		 length=30;
       		 break;
       	 case 2:
       		 rows=31;
       		 cols=31;
       		 length=25;
       		 gamePresent.resize(820, 820);
       		 break;
       	 case 3:
       		 rows=41;
       		 cols=41;
       		 length=18;
       		 gamePresent.resize(840, 840);
       		 break;
       	 }
       	 mazeUnits=new MazeUnit[rows][cols];
       	 for(int i=0;i<rows;i++) {
       		 for(int j=0;j<cols;j++) {
       			 mazeUnits[i][j]=new MazeUnit(i,j,length,this,false);
       		 }
       	 }
       	 end =new MazeUnit(rows-2,cols-2,length,this,true);
	 }
	 //根据prim算法打通墙得到迷宫
	 private void getFinalMaze() {
		 Random random=new Random();
		 List<MazeUnit> list=new LinkedList<MazeUnit>();
		 mazeUnits[1][1].isVisited=true;
		 mazeUnits[1][1].wall=false;
		 list.add(mazeUnits[2][1]);
		 list.add(mazeUnits[1][2]);
		 while(!list.isEmpty()) {
			 MazeUnit current;
			 int index=random.nextInt(list.size());
			 current=list.get(index);
			 if(current.j-1>0&&current.j+1<cols-1&&mazeUnits[current.i][current.j-1].isVisited==true&&mazeUnits[current.i][current.j+1].wall==true) {
				 mazeUnits[current.i][current.j].isVisited=true;
				 mazeUnits[current.i][current.j].wall=false;
				 mazeUnits[current.i][current.j+1].isVisited=true;
				 mazeUnits[current.i][current.j+1].wall=false;
				 addNeighborWalls(list,mazeUnits,mazeUnits[current.i][current.j+1]);
				 list.remove(current);
			 }
			 else if(current.j-1>0&&current.j+1<cols-1&&mazeUnits[current.i][current.j-1].wall==true&&mazeUnits[current.i][current.j+1].isVisited==true) {
				 mazeUnits[current.i][current.j].isVisited=true;
				 mazeUnits[current.i][current.j].wall=false;
				 mazeUnits[current.i][current.j-1].isVisited=true;
				 mazeUnits[current.i][current.j-1].wall=false;

				 addNeighborWalls(list,mazeUnits,mazeUnits[current.i][current.j-1]);
				 list.remove(current);
			 }
			 else if(current.i-1>0&&current.i+1<rows-1&&mazeUnits[current.i-1][current.j].isVisited==true&&mazeUnits[current.i+1][current.j].wall==true) {
				 mazeUnits[current.i][current.j].isVisited=true;
				 mazeUnits[current.i][current.j].wall=false;
				 mazeUnits[current.i+1][current.j].isVisited=true;
				 mazeUnits[current.i+1][current.j].wall=false;

				 addNeighborWalls(list,mazeUnits,mazeUnits[current.i+1][current.j]);
				 list.remove(current);
			 }
			 else if(current.i-1>0&&current.i+1<rows-1&&mazeUnits[current.i-1][current.j].wall==true&&mazeUnits[current.i+1][current.j].isVisited==true) {
				 mazeUnits[current.i][current.j].isVisited=true;
				 mazeUnits[current.i][current.j].wall=false;
				 mazeUnits[current.i-1][current.j].isVisited=true;
				 mazeUnits[current.i-1][current.j].wall=false;
				 addNeighborWalls(list,mazeUnits,mazeUnits[current.i-1][current.j]);
				 list.remove(current);
			 }
			 else {
				 list.remove(current);
			 }
		 }
		 
		 
	 }
	 
	 private void addNeighborWalls(List list,MazeUnit[][] mazeUnits,MazeUnit mazeUnit) {
		 if(!list.contains(mazeUnits[mazeUnit.i][mazeUnit.j-1])&&mazeUnit.j-1>0&&mazeUnits[mazeUnit.i][mazeUnit.j-1].wall==true) {
			 list.add(mazeUnits[mazeUnit.i][mazeUnit.j-1]);
		 }
		 if(!list.contains(mazeUnits[mazeUnit.i][mazeUnit.j+1])&&mazeUnit.j+1<cols-1&&mazeUnits[mazeUnit.i][mazeUnit.j+1].wall==true) {
			 list.add(mazeUnits[mazeUnit.i][mazeUnit.j+1]);
		 }
		 if(!list.contains(mazeUnits[mazeUnit.i-1][mazeUnit.j])&&mazeUnit.i-1>0&&mazeUnits[mazeUnit.i-1][mazeUnit.j].wall==true) {
			 list.add(mazeUnits[mazeUnit.i-1][mazeUnit.j]);
		 }
		 if(!list.contains(mazeUnits[mazeUnit.i+1][mazeUnit.j])&&mazeUnit.i+1<rows&&mazeUnits[mazeUnit.i+1][mazeUnit.j].wall==true) {
			 list.add(mazeUnits[mazeUnit.i+1][mazeUnit.j]);
		 }
	 }
	 //根据DFS计算出最短路径
	 public List<Integer> getRoadPath() {
		 List path=new ArrayList<Integer>();
		 Stack<MazeUnit> stack=new Stack<MazeUnit>();
		 for(int i=0;i<rows;i++) {
			 for(int j=0;j<cols;j++) {
				 mazeUnits[i][j].isVisited=false;
			 }
		 }
		 MazeUnit current=mazeUnits[gamePresent.getGameWalker().getI()][gamePresent.getGameWalker().getJ()];
		 do {
		 if(current.isVisited==false&&current.wall==false) {
			 current.isVisited=true;
			 stack.push(current);
			 //找到出口
			 if(current.getRectangle().intersects(end.getRectangle())) {
				 while(!stack.isEmpty()) {
					 path.add(stack.pop().direction);
				 }
				 return path;
			 }
			 current=mazeUnits[current.i][current.j+1];
		 }else {
			 if(!stack.isEmpty()) {
				 current=stack.pop();
				 while(current.direction==4&&!stack.isEmpty()) {
					 current=stack.pop();
				 }
				 if(current.direction<4) {
					 current.direction++;
					 stack.push(current);
					 switch(current.direction) {
					 case 2:
						 current=mazeUnits[current.i+1][current.j];
						 break;
					 case 3:
						 current=mazeUnits[current.i][current.j-1];
						 break;
					 case 4:
						 current=mazeUnits[current.i-1][current.j];
						 break;
					 }
				 }
			 }
		 }
		 }while(!stack.isEmpty());
		 return path;
	 }
	 
     public void paintSelf(Graphics g) {
         if(gamePresent.getGameDifficulty()!=1) {
        	 this.gameWalker=gamePresent.getGameWalker();
        	 for(int i=gameWalker.getI()-(10-gamePresent.getGameDifficulty());i<=gameWalker.getI()+(10-gamePresent.getGameDifficulty());i++) {
        		 for(int j=gameWalker.getJ()-(10-gamePresent.getGameDifficulty());j<=gameWalker.getJ()+(10-gamePresent.getGameDifficulty());j++) {
        			 if(i>=0&&j>=0&&i<rows&&j<cols) {
        			 mazeUnits[i][j].paintSelf(g);
        			 }
        		 }
        	 }
         }else {
    	 for(int i=0;i<rows;i++) {
    		 for(int j=0;j<rows;j++) {
    			 mazeUnits[i][j].paintSelf(g);
    		 }
    	 }
         }
    	 end.paintSelf(g);
     }
}
