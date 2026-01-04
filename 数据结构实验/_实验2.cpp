#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;
// 函数声明
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int BF(char *s, char *t, int start,int &stepcount,int &compareCount);
int KMP(char *s, char *t, int start,int&stepCount,int &compareCount,int next[],int m);
int KMP_nextval(char *s, char *t, int start,int&stepcount,int&comparecount,int nextval[],int m);
void getnext(char *t, int *next);
void getnextval(char *t, int *nextval);

// 全局变量
char s[100], t[100];
int start = 0;
HWND hEditMain, hEditSub, hEditStart, hResult,hResult1,hResult2,hvisual;
// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "PatternMatchingWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "kmp",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 600,
        NULL, NULL, hInstance, NULL
    );
    if (!hwnd) {
        MessageBox(NULL, "fail", "error", MB_ICONERROR);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

// 窗口过程函
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        // 设置字体
        HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                                DEFAULT_PITCH | FF_SWISS, "Arial");

        // 创建输入框和标签
        CreateWindow("Static", "String s:", WS_VISIBLE | WS_CHILD, 40, 40, 120, 30, hwnd, NULL, NULL, NULL);
        hEditMain = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 170, 40, 400, 30, hwnd, NULL, NULL, NULL);

        CreateWindow("Static", "Pattern t:", WS_VISIBLE | WS_CHILD, 40, 90, 120, 30, hwnd, NULL, NULL, NULL);
        hEditSub = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 170, 90, 400, 30, hwnd, NULL, NULL, NULL);

        CreateWindow("Static", "Start Position:", WS_VISIBLE | WS_CHILD, 40, 140, 120, 30, hwnd, NULL, NULL, NULL);
        hEditStart = CreateWindow("Edit", "0", WS_VISIBLE | WS_CHILD | WS_BORDER, 170, 140, 100, 30, hwnd, NULL, NULL, NULL);

        // 创建按钮
        CreateWindow("Button", "BF", WS_VISIBLE | WS_CHILD, 40, 200, 200, 40, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow("Button", "KMP", WS_VISIBLE | WS_CHILD, 250, 200, 200, 40, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow("Button", "KMP (NextVal)", WS_VISIBLE | WS_CHILD, 460, 200, 200, 40, hwnd, (HMENU)3, NULL, NULL);
        // 创建结果显示区域
        hResult1 = CreateWindow("Static", "Result:", WS_VISIBLE | WS_CHILD | WS_BORDER, 40, 260, 620, 100, hwnd, NULL, NULL, NULL);
        hResult2 = CreateWindow("Static", "Next/NextVal:", WS_VISIBLE | WS_CHILD | WS_BORDER, 40, 400, 620, 30, hwnd, NULL, NULL, NULL);
        hvisual=CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL, 700, 10, 300, 540, hwnd, NULL, NULL, NULL);
        // 应用字体
        SendMessage(hEditMain, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hEditSub, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hEditStart, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hResult1, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hResult2, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hvisual, WM_SETFONT, (WPARAM)hFont, TRUE);

        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 3) {
            // 获取用户输入
            GetWindowText(hEditMain, s, sizeof(s));
            GetWindowText(hEditSub, t, sizeof(t));
            char startStr[10];
            GetWindowText(hEditStart, startStr, sizeof(startStr));
            start = atoi(startStr);
            int next[256] = {0}, nextVal[256] = {0};
            int n = strlen(t);
            int result = -1;
            char resultStr[256] = {0};
            char nextResult[512] = "Next Array: ";
            int stepCount = 0, compareCount = 0;
            // 调用对应的算法
            if (LOWORD(wParam) == 1) {
                result = BF(s, t, start, stepCount, compareCount);
            } else if (LOWORD(wParam) == 2) {
                result = KMP(s, t, start, stepCount, compareCount, next, n);
                for (int i = 0; i < n; i++) {
                    char buffer[10];
                    sprintf(buffer, " %d ", next[i]+1);
                    strcat(nextResult, buffer);
                }
            } else if (LOWORD(wParam) == 3) {
                result = KMP_nextval(s, t, start, stepCount, compareCount, nextVal, n);
                strcpy(nextResult, "NextVal Array: ");
                for (int i = 0; i < n; i++) {
                    char buffer[10];
                    sprintf(buffer, " %d ", nextVal[i]+1);
                    strcat(nextResult, buffer);
                }
            }
            // 结果输出
            if (result != -1) {
                sprintf(resultStr, "Success\nPosition: %d\nSteps: %d\nComparisons: %d", result, stepCount, compareCount);
            } else {
                strcpy(resultStr, "Match Failed");
            }
            SetWindowText(hResult1, resultStr);
            SetWindowText(hResult2, nextResult);
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

}

// BF 算法实现
int BF(char *s, char *t, int start, int &stepcount, int &compareCount) {
    int n = strlen(s);
    int m = strlen(t);
    stepcount = 0;
    compareCount = 0;
    int i = start, j = 0;
    char visualBuffer[1024] = "";
    while (i < n && j < m) {
        stepcount++;
        sprintf(visualBuffer + strlen(visualBuffer), "Step %d:\r\n", stepcount);
        for (int k = 0; k < n; k++) {
            sprintf(visualBuffer + strlen(visualBuffer), "%c", s[k]);
        }
        sprintf(visualBuffer + strlen(visualBuffer), "\r\n");
        for (int k = 0; k < i - j; k++) {
            strcat(visualBuffer, " ");
        }
        for (int k = 0; k < m; k++) {
            sprintf(visualBuffer + strlen(visualBuffer), "%c", (k == j) ? t[k] : '-');
        }
        strcat(visualBuffer, "\n\n");
        SetWindowText(hvisual, visualBuffer);
        if (s[i] == t[j]) {
            compareCount++;
            i++;
            j++;
            if (j >= m) return i - m;
        } else {
            i = i - j + 1;
            j = 0;
            compareCount++;
        }
    }
    return -1;
}


// KMP 算法实现
int KMP(char *s, char *t, int start,int&stepCount,int &compareCount,int next[],int m) {
    int n = strlen(s);
    int i = start, j = 0; 
    char visualBuffer[1024] = "";
    stepCount=0;
    compareCount=0;
    getnext(t, next);
    while (i < n && j < m) {
        stepCount++;
        sprintf(visualBuffer + strlen(visualBuffer), "Step %d:\r\n", stepCount);
        for (int k = 0; k < n; k++) {
            sprintf(visualBuffer + strlen(visualBuffer), "%c", s[k]);
        }
        sprintf(visualBuffer + strlen(visualBuffer), "\r\n");
        for (int k = 0; k < i - j; k++) {
            strcat(visualBuffer, " ");
        }
        for (int k = 0; k < m; k++) {
            sprintf(visualBuffer + strlen(visualBuffer), "%c", (k == j) ? t[k] : '-');
        }
        strcat(visualBuffer, "\n\n");
        SetWindowText(hvisual, visualBuffer);
        if (j == -1 || s[i] == t[j]) {
            compareCount++;
            i++;
            j++;
            if (j >= m) return i - m;
        } else {
            compareCount++;
            j = next[j];
        }
    }
    free(next);
    
    return -1;
}

// KMP 改进算法实现
int KMP_nextval(char *s, char *t, int start,int&stepcount,int&comparecount,int nextval[],int m) {
    int n = strlen(s);
    stepcount=0;
    comparecount=0;
    int i = start, j = 0;
    char visualBuffer[1024] = "";
    getnextval(t, nextval);
    while (i < n && j < m) {
        stepcount++;
        sprintf(visualBuffer + strlen(visualBuffer), "Step %d:\r\n", stepcount);
        for (int k = 0; k < n; k++) {
            sprintf(visualBuffer + strlen(visualBuffer), "%c", s[k]);
        }
        sprintf(visualBuffer + strlen(visualBuffer), "\r\n");
        for (int k = 0; k < i - j; k++) {
            strcat(visualBuffer, " ");
        }
        for (int k = 0; k < m; k++) {
            sprintf(visualBuffer + strlen(visualBuffer), "%c", (k == j) ? t[k] : '-');
        }
        strcat(visualBuffer, "\n\n");
        SetWindowText(hvisual, visualBuffer);
        if (j == -1 || s[i] == t[j]) {
            comparecount++;
            i++;
            j++; 
            if (j >= m) return i - m;
        } else {
            comparecount++;
            j = nextval[j];
        }
    }
    free(nextval);
   
    return -1;
}

// Next 数组生成
void getnext(char *t, int *next) {
    int len = strlen(t);
    next[0] = -1;
    int i = 0, j = -1;
    while (i < len - 1) {
        if (j == -1 || t[i] == t[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

// NextVal 数组生成
void getnextval(char *t, int *nextval) {
    int len = strlen(t);
    nextval[0] = -1;
    int i = 0, j = -1;
    while (i < len - 1) {
        if (j == -1 || t[i] == t[j]) {
            ++i;
            ++j;
            if (t[i] != t[j]) nextval[i] = j;
            else nextval[i] = nextval[j];
        } else {
            j = nextval[j];
        }
    }
}
