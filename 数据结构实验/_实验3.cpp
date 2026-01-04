//ABD##EG###CF###
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
typedef struct  node{
	char data;	//数据域
	struct node *lchild ,*rchild;  //左右孩子指针
}BinTNode, *BinTree;
BinTree root = NULL;
char result[256] = {0};

   //树中结点类型
void create(BinTree *t, const char *input, int *index) {
    if (input[*index] == '\0') return;
    char ch = input[*index];
    (*index)++;
    if (ch == '#') {
        *t = NULL;
    } else {
        *t = (BinTNode *)malloc(sizeof(BinTNode));
        (*t)->data = ch;
        create(&(*t)->lchild, input, index);
        create(&(*t)->rchild, input, index);
    }
}
void drawNode(HDC hdc, int x, int y, char data) {
    char str[2] = {data, '\0'};
    Ellipse(hdc, x - 20, y - 20, x + 20, y + 20); // 圆圈
    TextOut(hdc, x - 5, y - 10, str, 1);          // 输出节点数据
}
void drawTree(HDC hdc, BinTree T, int x, int y, int offsetX, int offsetY) {
    if (!T) return;
    drawNode(hdc, x, y, T->data);
    if (T->lchild) {
        MoveToEx(hdc, x, y, NULL);                       // 移动到当前节点位置
        LineTo(hdc, x - offsetX, y + offsetY);           // 绘制连线
        drawTree(hdc, T->lchild, x - offsetX, y + offsetY, offsetX / 2, offsetY);
    }
    if (T->rchild) {
        MoveToEx(hdc, x, y, NULL);
        LineTo(hdc, x + offsetX, y + offsetY);
        drawTree(hdc, T->rchild, x + offsetX, y + offsetY, offsetX / 2, offsetY);
    }
}
void xianxu(BinTree T,char *result) {
    if (T) {
        sprintf(result + strlen(result), "%c ", T->data);
        xianxu(T->lchild,result);
        xianxu (T->rchild,result);
    }
}
void zhongxu(BinTree T,char *result) {
    if (T) {
        zhongxu(T->lchild,result);
        sprintf(result + strlen(result), "%c ", T->data);
        zhongxu(T->rchild,result);
    }
}
void houxu(BinTree T,char *result) {
    if (T) {
        houxu(T->lchild,result);
        houxu(T->rchild,result);
        sprintf(result + strlen(result), "%c ", T->data);
    }
}
void cengxu(BinTree T,char *result) {
    if (!T) return;
    BinTNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = T;
    while (front < rear) {
        BinTNode* node = queue[front++];
        sprintf(result + strlen(result), "%c ", node->data);  
        if (node->lchild) queue[rear++] = node->lchild;
        if (node->rchild) queue[rear++] = node->rchild;
    }
}
void findPath(BinTree T, char target, char path[], int pathLen, char *result) {
    if (!T) return;

    // 将当前节点加入路径
    path[pathLen++] = T->data;

    // 如果找到目标节点
    if (T->data == target) {
        for (int i = 0; i < pathLen; i++) {
            sprintf(result + strlen(result), "%c ", path[i]);  // 添加路径到结果
        }
        sprintf(result + strlen(result), "\n");
    }

    // 继续搜索左子树和右子树
    findPath(T->lchild, target, path, pathLen, result);
    findPath(T->rchild, target, path, pathLen, result);

    // 回溯处理，移除当前节点
    pathLen--;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndInput, hwndButton,hwndxianxuButton, hwndOutput1,hwndzhongxuButtton,hwndOutput2;
    static HWND hwndhouxuButton,hwndOutput3,hwndcengxuBUtton,hwndOutput4,hwndfindButton,hwndOutput5,hwndzhongxuButton;
    static char inputStr[20],targetNode[2];
    
    switch (uMsg) {
    case WM_CREATE: {
        // 创建统一字体
        HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");

        // 创建输入框和标签
        CreateWindowEx(0, "STATIC", "Input Data:", WS_CHILD | WS_VISIBLE | SS_LEFT,
                    20, 20, 100, 30, hwnd, NULL, GetModuleHandle(NULL), NULL);
        hwndInput = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                120, 20, 200, 30, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);

        // 创建功能按钮
        hwndButton = CreateWindowEx(0, "BUTTON", "Create Binary Tree", WS_CHILD | WS_VISIBLE,
                                    20, 70, 200, 30, hwnd, (HMENU)2, GetModuleHandle(NULL), NULL);
        hwndxianxuButton = CreateWindowEx(0, "BUTTON", "Preorder Traversal", WS_CHILD | WS_VISIBLE,
                                        20, 110, 200, 30, hwnd, (HMENU)3, GetModuleHandle(NULL), NULL);
        hwndzhongxuButton = CreateWindowEx(0, "BUTTON", "Inorder Traversal", WS_CHILD | WS_VISIBLE,
                                        20, 150, 200, 30, hwnd, (HMENU)5, GetModuleHandle(NULL), NULL);
        hwndhouxuButton = CreateWindowEx(0, "BUTTON", "Postorder Traversal", WS_CHILD | WS_VISIBLE,
                                        20, 190, 200, 30, hwnd, (HMENU)7, GetModuleHandle(NULL), NULL);
        hwndcengxuBUtton = CreateWindowEx(0, "BUTTON", "Level Order Traversal", WS_CHILD | WS_VISIBLE,
                                        20, 230, 200, 30, hwnd, (HMENU)9, GetModuleHandle(NULL), NULL);

        // 创建查找节点的输入框和按钮
        CreateWindowEx(0, "STATIC", "Target Node:", WS_CHILD | WS_VISIBLE | SS_LEFT,
                    20, 280, 100, 30, hwnd, NULL, GetModuleHandle(NULL), NULL);
        CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                    120, 280, 50, 30, hwnd, (HMENU)6, GetModuleHandle(NULL), NULL);
        hwndfindButton = CreateWindowEx(0, "BUTTON", "Find Path", WS_CHILD | WS_VISIBLE,
                                        190, 280, 120, 30, hwnd, (HMENU)11, GetModuleHandle(NULL), NULL);

        // 创建输出区域
        CreateWindowEx(0, "STATIC", "Output:", WS_CHILD | WS_VISIBLE | SS_LEFT,
                    20, 330, 100, 30, hwnd, NULL, GetModuleHandle(NULL), NULL);
        hwndOutput1 = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT,
                                    20, 370, 400, 100, hwnd, (HMENU)4, GetModuleHandle(NULL), NULL);

        // 应用字体到所有控件
        SendMessage(hwndInput, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hwndButton, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hwndxianxuButton, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hwndzhongxuButton, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hwndhouxuButton, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hwndcengxuBUtton, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hwndfindButton, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hwndOutput1, WM_SETFONT, (WPARAM)hFont, TRUE);

        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == 2) {  // 按钮点击事件
            GetWindowText(hwndInput, inputStr, 256);  // 获取输入框内容
            root = NULL;
            int index = 0;
            create(&root, inputStr, &index);
            InvalidateRect(hwnd, NULL, TRUE);  // 重新绘制窗口
        }
        else if (LOWORD(wParam) == 3) {  
            result[0] = '\0'; 
            xianxu(root, result);  
            SetWindowText(hwndOutput1, result);  
        }
        else if (LOWORD(wParam) == 5) {  
            result[0] = '\0';  
            zhongxu(root, result);  
            SetWindowText(hwndOutput1, result);  
        }
        else if (LOWORD(wParam) == 7) {  
            result[0] = '\0';
            houxu(root, result); 
            SetWindowText(hwndOutput1, result); 
        }
        else if (LOWORD(wParam) == 9) {  
            result[0] = '\0';
            cengxu(root, result); 
            SetWindowText(hwndOutput1, result); 
        }
        else if (LOWORD(wParam) == 11) {  
            result[0] = '\0';
            GetWindowText(GetDlgItem(hwnd, 6), targetNode, 2);
            char path[100];
            findPath(root, targetNode[0], path, 0, result); 
            SetWindowText(hwndOutput1, result); 
        }
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // 绘制二叉树
        if (root) {
            drawTree(hdc, root, 400, 50, 100, 50); // 初始位置和偏移量
        }
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// 主函数
int main() {
    // 注册窗口类
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "BinaryTreeWindow";

    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindowEx(
        0,                          // 扩展样式
        "BinaryTreeWindow",         // 窗口类名
        "visual",              // 窗口标题
        WS_OVERLAPPEDWINDOW,        // 窗口样式
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, // 窗口位置和大小
        NULL, NULL, wc.hInstance, NULL);

    if (!hwnd) return 0;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
 
    return 0;
}