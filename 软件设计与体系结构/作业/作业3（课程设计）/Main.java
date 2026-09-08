import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.*;
import java.util.List;
import java.util.stream.Collectors;

class MazeGameApp {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MazeGameGUI mazeGameGUI = new MazeGameGUI();
            mazeGameGUI.setVisible(true);
        });
    }

    // 单例模式：确保只有一个迷宫游戏实例
    public static class MazeGame {
        private static MazeGame instance;

        private MazeGame() {
        }

        public static synchronized MazeGame getInstance() {
            if (instance == null) {
                instance = new MazeGame();
            }
            return instance;
        }

        // 使用深度优先搜索（DFS）生成迷宫
        public Maze createMaze(MazeFactory factory) {
            int size = 5;
            Room[][] rooms = new Room[size][size];
            Maze maze = new Maze();

            // 创建房间
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    rooms[i][j] = factory.createRoom(i * size + j + 1, i, j);
                    maze.addRoom(rooms[i][j]);
                }
            }

            // 使用DFS生成迷宫，确保生成可通的迷宫
            boolean[][] visited = new boolean[size][size];
            Stack<Room> stack = new Stack<>();
            Room startRoom = rooms[0][0];
            Room endRoom = rooms[size - 1][size - 1];
            stack.push(startRoom);
            visited[0][0] = true;

            while (!stack.isEmpty()) {
                Room current = stack.peek();
                int x = current.getX();
                int y = current.getY();

                List<Direction> directions = new ArrayList<>(Arrays.asList(Direction.values()));
                Collections.shuffle(directions);

                boolean moved = false;

                for (Direction direction : directions) {
                    int newX = x;
                    int newY = y;

                    switch (direction) {
                        case NORTH:
                            newX = x - 1;
                            break;
                        case SOUTH:
                            newX = x + 1;
                            break;
                        case EAST:
                            newY = y + 1;
                            break;
                        case WEST:
                            newY = y - 1;
                            break;
                    }

                    if (newX >= 0 && newX < size && newY >= 0 && newY < size && !visited[newX][newY]) {
                        Room nextRoom = rooms[newX][newY];
                        visited[newX][newY] = true;
                        stack.push(nextRoom);
                        moved = true;

                        // 创建门连接房间
                        Door door = factory.createDoor(current, nextRoom);
                        current.setSide(direction, door);
                        nextRoom.setSide(direction.getOpposite(), door);
                        break;
                    }
                }

                if (!moved) {
                    stack.pop();
                }
            }

            startRoom.setStart(true);
            endRoom.setEnd(true);

            // 打开从起点到终点的所有门
            openPath(rooms, startRoom, endRoom);

            return maze;
        }

        // 打开从起点到终点的所有门
        private void openPath(Room[][] rooms, Room startRoom, Room endRoom) {
            int size = rooms.length;
            boolean[][] visited = new boolean[size][size];
            Stack<Room> stack = new Stack<>();
            stack.push(startRoom);

            while (!stack.isEmpty()) {
                Room current = stack.pop();
                int x = current.getX();
                int y = current.getY();

                visited[x][y] = true;

                if (current == endRoom) {
                    return;
                }

                for (Direction direction : Direction.values()) {
                    int newX = x;
                    int newY = y;

                    switch (direction) {
                        case NORTH:
                            newX = x - 1;
                            break;
                        case SOUTH:
                            newX = x + 1;
                            break;
                        case EAST:
                            newY = y + 1;
                            break;
                        case WEST:
                            newY = y - 1;
                            break;
                    }

                    if (newX >= 0 && newX < size && newY >= 0 && newY < size && !visited[newX][newY]) {
                        Room nextRoom = rooms[newX][newY];
                        MazeComponent side = current.getSide(direction);
                        if (side instanceof Door) {
                            ((Door) side).setOpen(true);
                        }
                        stack.push(nextRoom);
                    }
                }
            }
        }
    }

    // 抽象工厂模式：创建不同类型的迷宫组件
    public abstract static class MazeFactory {
        public abstract Room createRoom(int roomNumber, int x, int y);

        public abstract Wall createWall();

        public abstract Door createDoor(Room room1, Room room2);
    }

    // 具体工厂：创建带魔法的迷宫组件
    public static class EnchantedMazeFactory extends MazeFactory {
        private Set<String> spells = new HashSet<>();
        private String[] spellOptions = {"abra", "hocu", "open", "magic", "unlock"};
        private Random random = new Random();

        @Override
        public Room createRoom(int roomNumber, int x, int y) {
            // 每个房间有一定机率成为魔法房间
            if (random.nextFloat() < 0.3) {  // 假设30%的概率生成魔法房间
                return new EnchantedRoom(roomNumber, generateUniqueSpell(), x, y);
            } else {
                return new Room(roomNumber, x, y);
            }
        }

        @Override
        public Wall createWall() {
            return new Wall();
        }

        @Override
        public Door createDoor(Room room1, Room room2) {
            // 每个门有一定机率成为魔法门
            if (random.nextFloat() < 0.3) {  // 假设30%的概率生成魔法门
                return new EnchantedDoor(room1, room2, generateUniqueSpell());
            } else {
                return new Door(room1, room2);
            }
        }

        private String generateUniqueSpell() {
            List<String> availableSpells = Arrays.stream(spellOptions)
                    .filter(spell -> !spells.contains(spell))
                    .collect(Collectors.toList());

            if (availableSpells.isEmpty()) {
                return spellOptions[random.nextInt(spellOptions.length)];
            }

            String spell = availableSpells.get(random.nextInt(availableSpells.size()));
            spells.add(spell);
            return spell;
        }
    }

    // 枚举：方向
    public enum Direction {
        NORTH, SOUTH, EAST, WEST;

        public Direction getOpposite() {
            switch (this) {
                case NORTH:
                    return SOUTH;
                case SOUTH:
                    return NORTH;
                case EAST:
                    return WEST;
                case WEST:
                    return EAST;
            }
            return null;
        }
    }

    // 组合模式：迷宫组件基类
    public static abstract class MazeComponent {
        public void add(MazeComponent component) {
            throw new UnsupportedOperationException();
        }

        public void remove(MazeComponent component) {
            throw new UnsupportedOperationException();
        }

        public MazeComponent getChild(int i) {
            throw new UnsupportedOperationException();
        }
    }

    // 房间类
    public static class Room extends MazeComponent {
        private int roomNumber;
        private int x, y;
        private Map<Direction, MazeComponent> sides;
        private boolean isStart;
        private boolean isEnd;

        public Room(int roomNumber, int x, int y) {
            this.roomNumber = roomNumber;
            this.x = x;
            this.y = y;
            sides = new HashMap<>();
        }

        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }

        public void setSide(Direction direction, MazeComponent component) {
            sides.put(direction, component);
        }

        public MazeComponent getSide(Direction direction) {
            return sides.get(direction);
        }

        public int getRoomNumber() {
            return roomNumber;
        }

        public boolean isStart() {
            return isStart;
        }

        public void setStart(boolean start) {
            isStart = start;
        }

        public boolean isEnd() {
            return isEnd;
        }

        public void setEnd(boolean end) {
            isEnd = end;
        }

        public String getSideInfo(Direction direction) {
            MazeComponent side = sides.get(direction);
            if (side instanceof Wall) {
                return "墙";
            } else if (side instanceof EnchantedDoor) {
                EnchantedDoor door = (EnchantedDoor) side;
                return door.isOpen() ? "开门 (咒语: " + door.getSpell() + ")" : "关门 (咒语: " + door.getSpell() + ")";
            } else if (side instanceof Door) {
                Door door = (Door) side;
                return door.isOpen() ? "开门" : "关门";
            } else {
                return "未知";
            }
        }
    }

    // 墙类
    public static class Wall extends MazeComponent {
    }

    // 门类
    public static class Door extends MazeComponent {
        private Room room1, room2;
        private boolean isOpen;

        public Door(Room room1, Room room2) {
            this.room1 = room1;
            this.room2 = room2;
            this.isOpen = false; // 确保门初始为关闭状态
        }

        public Room getOtherRoom(Room room) {
            return room == room1 ? room2 : room1;
        }

        public boolean isOpen() {
            return isOpen;
        }

        public void setOpen(boolean open) {
            isOpen = open;
        }
    }

    // 迷宫类
    public static class Maze {
        private List<Room> rooms;

        public Maze() {
            rooms = new ArrayList<>();
        }

        public void addRoom(Room room) {
            rooms.add(room);
        }

        public Iterator<Room> iterator() {
            return rooms.iterator();
        }
    }

    // 迷宫游戏的GUI界面
    public static class MazeGameGUI extends JFrame {
        private Maze maze;
        private MazeFactory factory;
        private Room currentRoom;
        private Set<Integer> keysCollected;
        private List<Room> path; // 用于记录路径

        public MazeGameGUI() {
            factory = new EnchantedMazeFactory();
            maze = MazeGame.getInstance().createMaze(factory);
            currentRoom = maze.iterator().next(); // 从第一个房间开始
            keysCollected = new HashSet<>();
            path = new ArrayList<>();
            path.add(currentRoom); // 起始房间
            initUI();
        }

        // 初始化界面
        private void initUI() {
            setTitle("迷宫游戏");
            setSize(800, 800);
            setLocationRelativeTo(null);
            setDefaultCloseOperation(EXIT_ON_CLOSE);
            setLayout(new GridLayout(5, 5)); // 根据迷宫大小调整布局

            for (Iterator<Room> it = maze.iterator(); it.hasNext(); ) {
                Room room = it.next();
                RoomPanel roomPanel = new RoomPanel(room, this);
                add(roomPanel);
            }

            addKeyListener(new KeyAdapter() {
                @Override
                public void keyPressed(KeyEvent e) {
                    int keyCode = e.getKeyCode();
                    Direction direction = null;

                    switch (keyCode) {
                        case KeyEvent.VK_UP:
                            direction = Direction.NORTH;
                            break;
                        case KeyEvent.VK_DOWN:
                            direction = Direction.SOUTH;
                            break;
                        case KeyEvent.VK_LEFT:
                            direction = Direction.WEST;
                            break;
                        case KeyEvent.VK_RIGHT:
                            direction = Direction.EAST;
                            break;
                    }

                    if (direction != null) {
                        move(direction);
                    }
                }
            });

            setFocusable(true);
        }

        private void move(Direction direction) {
            MazeComponent side = currentRoom.getSide(direction);
            if (side instanceof EnchantedDoor) {
                EnchantedDoor enchantedDoor = (EnchantedDoor) side;
                String spellInput = JOptionPane.showInputDialog("请输入咒语以打开门:");
                if (spellInput != null && !spellInput.isEmpty()) {
                    enchantedDoor.castSpell(spellInput);
                    System.out.println("门的状态： " + enchantedDoor.isOpen()); // 日志输出门的状态
                    if (enchantedDoor.isOpen()) {
                        currentRoom = enchantedDoor.getOtherRoom(currentRoom);
                        path.add(currentRoom);
                        revalidate();
                        repaint();
                        System.out.println("进入房间：" + currentRoom.getRoomNumber());
                    } else {
                        System.out.println("咒语错误，门无法打开！");
                    }
                } else {
                    System.out.println("未输入咒语，无法进入房间：" + enchantedDoor.getOtherRoom(currentRoom).getRoomNumber());
                }
            } else if (side instanceof Door) {
                Door door = (Door) side;
                if (door.isOpen()) {
                    currentRoom = door.getOtherRoom(currentRoom);
                    path.add(currentRoom);
                    revalidate();
                    repaint();
                    System.out.println("进入房间：" + currentRoom.getRoomNumber());
                } else {
                    System.out.println("门是关着的，无法进入房间：" + door.getOtherRoom(currentRoom).getRoomNumber());
                }
            } else if (side instanceof Wall) {
                System.out.println("撞到墙了，无法进入！");
            } else {
                System.out.println("该方向没有门！");
            }

            // 检查是否有钥匙
            if (currentRoom instanceof EnchantedRoom) {
                EnchantedRoom enchantedRoom = (EnchantedRoom) currentRoom;
                if (enchantedRoom.hasKey() && !keysCollected.contains(enchantedRoom.getRoomNumber())) {
                    keysCollected.add(enchantedRoom.getRoomNumber());
                    System.out.println("你找到了一把钥匙在房间：" + currentRoom.getRoomNumber());
                }
            }

            // 检查是否到达终点
            if (currentRoom.isEnd()) {
                System.out.println("恭喜你到达终点！");
                printPath();
            }
        }

        // 打印路径
        private void printPath() {
            System.out.println("路径:");
            for (Room room : path) {
                System.out.println("房间 " + room.getRoomNumber() + " (" + room.getX() + ", " + room.getY() + ")");
            }
        }


        public Room getCurrentRoom() {
            return currentRoom;
        }
    }

    // 房间面板
    public static class RoomPanel extends JPanel {
        private Room room;
        private MazeGameGUI mazeGameGUI;

        public RoomPanel(Room room, MazeGameGUI mazeGameGUI) {
            this.room = room;
            this.mazeGameGUI = mazeGameGUI;
            setBorder(BorderFactory.createLineBorder(Color.BLACK));
            if (room instanceof EnchantedRoom) {
                setBackground(Color.LIGHT_GRAY);
            } else {
                setBackground(Color.WHITE);
            }
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            if (mazeGameGUI.getCurrentRoom() == room) {
                setBackground(Color.YELLOW); // 高亮显示当前房间
            } else if (room.isStart()) {
                setBackground(Color.GREEN); // 起点
            } else if (room.isEnd()) {
                setBackground(Color.RED); // 终点
            } else if (room instanceof EnchantedRoom) {
                setBackground(Color.LIGHT_GRAY); // 施了魔法的房间
            } else {
                setBackground(Color.WHITE);
            }
            g.drawString("房间 " + room.getRoomNumber(), 10, 20);
            g.drawString("(" + room.getX() + ", " + room.getY() + ")", 10, 40);

            // 显示房间四个方向的信息
            for (Direction dir : Direction.values()) {
                g.drawString(dir + ": " + room.getSideInfo(dir), 10, 60 + dir.ordinal() * 20);
            }

            // 显示房间中的钥匙和咒语
            if (room instanceof EnchantedRoom) {
                EnchantedRoom enchantedRoom = (EnchantedRoom) room;
                g.drawString("钥匙: " + (enchantedRoom.hasKey() ? "有" : "无"), 10, 140);
                g.drawString("咒语: " + enchantedRoom.getSpell(), 10, 160); // 显示咒语
            }
        }
    }

    // 施了魔法的房间类
    public static class EnchantedRoom extends Room {
        private boolean hasKey;
        private String spell;

        public EnchantedRoom(int roomNumber, String spell, int x, int y) {
            super(roomNumber, x, y);
            hasKey = new Random().nextBoolean(); // 随机决定房间里是否有钥匙
            this.spell = spell;
        }

        public boolean hasKey() {
            return hasKey;
        }

        public String getSpell() {
            return spell;
        }
    }

    // 施了魔法的门类
    public static class EnchantedDoor extends Door {
        private String spell;

        public EnchantedDoor(Room room1, Room room2, String spell) {
            super(room1, room2);
            this.spell = spell;
        }

        public String getSpell() {
            return spell;
        }

        public void castSpell(String spell) {
            if (this.spell.equals(spell)) {
                setOpen(true);
                System.out.println("咒语正确，门已打开！");
            } else {
                setOpen(false);  // 明确设置门为关闭状态
                System.out.println("咒语错误，门无法打开！");
            }
        }
    }
}
