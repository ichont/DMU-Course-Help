package game;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

public class GameFrame extends JFrame implements ActionListener{
	static boolean judge = true;
	static String name;
	public GameFrame() {
		setSize(288, 512);//设置窗口大小(288,512);
		setLocationRelativeTo(null);//窗口位于电脑的正中间；
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//关闭按键
		setResizable(false);
		setTitle("Flappy Bird终极豪华版");
		init();
 }
	public static void main(String[] args){
		GameFrame frame = new GameFrame();
		GamePanel panel = new GamePanel();
		frame.add(panel);//添加到界面
		frame.setVisible(true);
	}
	public void actionPerformed(ActionEvent e) {}
	void init() {
		JMenuBar menubar = new JMenuBar();
		JMenu menu = new JMenu("菜单");
		JMenu birdcolor = new  JMenu("小鸟颜色");
		JMenu bgcolor = new JMenu("背景主题");
		JMenu column = new JMenu("柱子颜色");
		menubar.add(menu);
		JMenuItem itembc1 = new JMenuItem("黄色");
		JMenuItem itembc2 = new JMenuItem("蓝色");
		JMenuItem itembc3 = new JMenuItem("红色");
		menu.add(birdcolor);
		birdcolor.add(itembc1);
		birdcolor.add(itembc2);
		birdcolor.add(itembc3);
		JMenuItem itembg1 = new JMenuItem("白天");
		JMenuItem itembg2 = new JMenuItem("黑夜");
		menu.add(bgcolor);
		bgcolor.add(itembg1);
		bgcolor.add(itembg2);
		JMenuItem itemc1 = new JMenuItem("绿色");
		JMenuItem itemc2 = new JMenuItem("橙色");
		menu.add(column);
		column.add(itemc1);
		column.add(itemc2);
		setJMenuBar(menubar);
		itembc1.addActionListener(this);
		itembc2.addActionListener(this);
		itembc3.addActionListener(this);
		itembg1.addActionListener(this);
		itembg2.addActionListener(this);
		itemc1.addActionListener(this);
		itemc2.addActionListener(this);
		itembc1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
					Bird.i = 0;
			}
		});
		itembc2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
					Bird.i = 1;
				}
			});
		itembc3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
					Bird.i = 2;
				}
			});
		itemc1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
					Column.j = 0;
			}
		});
		itemc2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
					Column.j = 1;
			}
		});
		itembg1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
					GamePanel.j = 1;
			}
		});
		itembg2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
					GamePanel.j = 0;
			}
		});
		
	}
}
