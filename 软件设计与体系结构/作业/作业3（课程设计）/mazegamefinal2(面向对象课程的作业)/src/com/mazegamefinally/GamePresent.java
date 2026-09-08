package com.mazegamefinally;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class GamePresent extends JFrame implements KeyListener,MouseListener{
    private GameMaze gameMaze;
    private GameWalker gameWalker;
    private int gameDifficulty=1;
    private boolean hasGameMaze=false;
    private boolean hasGameWalker=false;
    private Image offScreen=null;
    private boolean auto=false;
    Image initBj=Toolkit.getDefaultToolkit().getImage("pictures/initBj.jpg");
    Image overImg=Toolkit.getDefaultToolkit().getImage("pictures/overBj.jpg");
    public int gameState=0;
    
    
    public int getGameDifficulty() {
		return gameDifficulty;
	}
	public void setGameDifficulty(int gameDifficulty) {
		this.gameDifficulty = gameDifficulty;
	}
	
	public GameWalker getGameWalker() {
		return gameWalker;
	}
	public void setGameWalker(GameWalker gameWalker) {
		this.gameWalker = gameWalker;
	}
	public void gameLaunch() {
    	this.setVisible(true);
    	this.setSize(700,700);
    	this.setResizable(true);
    	this.setTitle("超级迷宫游戏");
    	this.setDefaultCloseOperation(3);
    	this.addMouseListener(this);
    	this.addKeyListener(this);
    	
    	
    	while(true) {
    		if(gameState==1) {
    		if(hasGameMaze==false) {
    			this.gameMaze=new GameMaze(gameDifficulty,this);
    			hasGameMaze=true;
    		}
    		if(hasGameWalker==false) {
    			this.gameWalker=new GameWalker(1,1,gameMaze,this);
    			hasGameWalker=true;
    		}
    		}
    		repaint();
    		try {
    			Thread.sleep(25);
    		}catch(Exception e) {
    			e.getStackTrace();
    		}
    	}
    }
    public void paint(Graphics g) {
    	if(offScreen==null) {
    		offScreen=this.createImage(this.getWidth(),this.getHeight());
    	}
    	Graphics g_=offScreen.getGraphics();
    	if(gameState==0) {
    		super.paint(g_);
    		g_.drawImage(initBj, 0, 0,700,700, null);
    		g_.setColor(Color.red);
    		g_.setFont(new Font("仿宋",Font.BOLD,50));
    		g_.drawString("点击开始游戏",200, 350);
    		g_.drawString("按空格实现AI自动搜索", 150 ,400);
    	}
    	else if(gameState==1) {
    		super.paint(g_);
    		if(hasGameMaze&&hasGameWalker) {
    		gameMaze.paintSelf(g_);
    		gameWalker.paintSelf(g_);
    		}
    	}
    	else if(gameState==2) {
    		if(gameDifficulty!=3) {
    		super.paint(g_);
    		g_.drawImage(overImg,0,0,this.getWidth(),this.getHeight(),null);
    		g_.setColor(Color.red);
    		g_.setFont(new Font("仿宋",Font.BOLD,25));
    		g_.drawString("恭喜您成功通过难度"+gameDifficulty, 100, 250);
    		g_.drawString("按回车进入下一关"+gameDifficulty, 100, 300);
    		}
    	}
    	g.drawImage(offScreen,0,0,null);
    }
	@Override
	public void mouseClicked(MouseEvent e) {
		if(gameState==0) {
			gameState=1;
		}
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyPressed(KeyEvent e) {
		System.out.print("hee");
		if(e.getKeyCode()==KeyEvent.VK_UP) {
			gameWalker.move(4);
		}
		if(e.getKeyCode()==KeyEvent.VK_RIGHT) {
			gameWalker.move(1);
		}
		if(e.getKeyCode()==KeyEvent.VK_DOWN) {
			gameWalker.move(2);
		}
		if(e.getKeyCode()==KeyEvent.VK_LEFT) {
			gameWalker.move(3);
		}
		if(e.getKeyCode()==KeyEvent.VK_SPACE) {
			if(gameState==1) {
			gameWalker.auto=true;
			gameWalker.getMap();
			}
		}
		
		if(e.getKeyCode()==KeyEvent.VK_ENTER) {
			if(gameState==2) {
				if(gameDifficulty!=3) {
				gameState=1;
				hasGameWalker=false;
				hasGameMaze=false;
				gameDifficulty+=1;
				auto=false;
				offScreen=null;
				}
			}
		}
		
	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
	public static void main(String args[]) {
		GamePresent gamePresent=new GamePresent();
		gamePresent.gameLaunch();
	}

}
