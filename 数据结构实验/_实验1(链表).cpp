#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
typedef struct Book{
    char no[50];
    char name[100];
    float price;
    struct Book*next;
}book;
HWND hNo, hName, hPrice, hList, hAddButton, hSortButton, hSearchButton, hSearchName, hDeleteButton;
HWND hxiugaibutton,hnixubutton,hsearchexpensive,hinsertposbutton,hpos,hquchong;
book*booklist=NULL;
book* creatbook(char*no,char*name,float price){
    book*newbook=(book*)malloc(sizeof(book));
    strcpy(newbook->name,name);
    strcpy(newbook->no,no);
    newbook->price=price;
    newbook->next=NULL;
    return newbook;
}
void addbook (char*no,char*name,float price){
    book*newbook=creatbook(no,name,price);
    if(booklist==NULL){
        booklist=newbook;
    }
    else{
        book*cur=booklist;
        while(cur->next!=NULL){
            cur=cur->next;
        }cur->next=newbook;
    }
}
void updatedbooklist(HWND hlist){
    char buffer[1024]="";
    book *cur=booklist;
    while(cur!=NULL){
        char bookinfo[256];
        sprintf(bookinfo, "NO:  %s, Name:  %s, Price: %.2f\r\n", cur->no, cur->name, cur->price);
        //printf("NO: %s, Name: %s, Price: %.2f\n", cur->no, cur->name, cur->price);

        //MessageBox(NULL, bookinfo, "Debug Info", MB_OK);
        //printf("Buffer: %s\n", buffer);

        strcat(buffer,bookinfo);
        cur=cur->next;
    }
    //printf("Buffer: %s\n", buffer);
    SetWindowText(hlist,buffer);
}
int count(){
    book*cur=booklist;
    int count=0;
    while(cur!=NULL){
        count++;
        cur=cur->next;
    }
    return count;
}
void deletebook(char* name) {
    book* cur = booklist;
    book* pre = NULL;
    while (cur != NULL) {
        if (strcmp(cur->name, name) == 0) {
            if (pre == NULL) { 
                booklist = cur->next;
            } else {
                pre->next = cur->next;
            }
            free(cur); 
            return;    
        }
        pre = cur;
        cur = cur->next;
    }
}
void searchname(char*name){
    char buffer[1024]="search results:\n";
    book*cur=booklist;
    while (cur!=NULL){
        if(strstr(cur->name,name)!=NULL){
            char bookinfo[256];
            sprintf(bookinfo, "NO: %s, Name: %s, Price: %.2f\r\n", cur->no, cur->name, cur->price);
            strcat(buffer,bookinfo);
        }
        cur=cur->next;
    }
    MessageBox(NULL,buffer,"result search:",MB_OK);
}
void swap(book*i,book*j){
    char tempNo[50], tempName[100];
    float tempPrice;
    strcpy(tempNo, i->no);
    strcpy(tempName, i->name);
    tempPrice = i->price;
    strcpy(i->no, j->no);
    strcpy(i->name, j->name);
    i->price = j->price;
    strcpy(j->no, tempNo);
    strcpy(j->name, tempName);
    j->price = tempPrice;
}
void sortbook(){
    if(booklist==NULL||booklist->next==NULL)return;
    for(book *i=booklist;i!=NULL;i=i->next){
        for(book*j=booklist;j!=NULL;j=j->next){
            if (i->price<j->price){
                swap(i,j);
            }
        }
    }
}
void xiugaijiage(){
    float sum=0,ave=0;
    int length;
    length=count();
    book *cur=booklist;
    while(cur!=NULL){
        sum+=cur->price;
        cur=cur->next;
    }
    cur=booklist;
    ave=sum/length;
    while(cur!=NULL){
        if(cur->price<ave){
            cur->price*=1.2;
        }
        if(cur->price>ave){
            cur->price*=1.;
        }
        cur=cur->next;
    }
}
void nixu() {
    book* cur = booklist; // 当前节点
    book* pre = NULL;     // 前一节点
    book* next =NULL;    // 下一节点
    while (cur != NULL) {
        next = cur->next; // 暂存下一节点
        cur->next = pre;  // 当前节点指向前一节点，实现反转
        pre = cur;        // 前一节点移动到当前节点
        cur = next;       // 当前节点移动到下一节点
    }
    // 更新链表头为反转后的第一个节点
    booklist = pre;
}
Book* findMostExpensiveBook() {
    Book* mostExpensive = booklist;
    Book* current = booklist->next;
    while (current) {
        if (current->price > mostExpensive->price) {
            mostExpensive = current;
        }
        current = current->next;
    }
    return mostExpensive;
}
void insert(int pos, char* no, char* name, float price) {
    book* newbook = creatbook(no, name, price);
    char buffer[1024]="search results:\n";
    if (pos >0 || booklist == NULL) { // 插入到头部
        newbook->next = booklist;
        booklist = newbook;
        return;
    }
    if(pos<=0){
        sprintf(buffer,"sorry position fail");
        MessageBox(NULL,buffer,"result search:",MB_OK);
    }
    book* cur = booklist;
    for (int i = 1; i < pos && cur->next != NULL; i++) {
        cur = cur->next;
    }
    newbook->next = cur->next;
    cur->next = newbook;
}
void removeDuplicates() {
    Book* current = booklist;
    while (current && current->next) {
        Book* prev = current;
        Book* temp = current->next;
        while (temp) {
            if (strcmp(current->name, temp->name) == 0 && strcmp(current->no, temp->no) == 0) {
                // 删除重复节点
                prev->next = temp->next;
                delete temp;
                temp = prev->next;
            } else {
                prev = temp;
                temp = temp->next;
            }
        }
        current = current->next;
    }
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
                         OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                         DEFAULT_PITCH | FF_SWISS, "Arial");

            // 数据输入区
            CreateWindow("static", "No:", WS_VISIBLE | WS_CHILD, 20, 20, 50, 20, hwnd, NULL, NULL, NULL);
            hNo = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 20, 200, 20, hwnd, NULL, NULL, NULL);
            SendMessage(hNo, WM_SETFONT, (WPARAM)hFont, TRUE);

            CreateWindow("static", "Name:", WS_VISIBLE | WS_CHILD, 20, 50, 50, 20, hwnd, NULL, NULL, NULL);
            hName = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 50, 200, 20, hwnd, NULL, NULL, NULL);
            SendMessage(hName, WM_SETFONT, (WPARAM)hFont, TRUE);

            CreateWindow("static", "Price:", WS_VISIBLE | WS_CHILD, 20, 80, 50, 20, hwnd, NULL, NULL, NULL);
            hPrice = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 80, 200, 20, hwnd, NULL, NULL, NULL);
            SendMessage(hPrice, WM_SETFONT, (WPARAM)hFont, TRUE);

            // 功能按钮区
            hAddButton = CreateWindow("button", "Add", WS_VISIBLE | WS_CHILD, 20, 120, 60, 30, hwnd, (HMENU)1, NULL, NULL);
            hSortButton = CreateWindow("button", "Sort", WS_VISIBLE | WS_CHILD, 100, 120, 60, 30, hwnd, (HMENU)2, NULL, NULL);
            hxiugaibutton = CreateWindow("button", "Change", WS_VISIBLE | WS_CHILD, 180, 120, 60, 30, hwnd, (HMENU)5, NULL, NULL);
            hnixubutton = CreateWindow("button", "Reverse", WS_VISIBLE | WS_CHILD, 260, 120, 60, 30, hwnd, (HMENU)6, NULL, NULL);
            hsearchexpensive = CreateWindow("button", "Costly", WS_VISIBLE | WS_CHILD, 340, 120, 60, 30, hwnd, (HMENU)7, NULL, NULL);

            // 列表显示区
            hList = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 
                                20, 170, 380, 200, hwnd, NULL, NULL, NULL);
            SendMessage(hList, WM_SETFONT, (WPARAM)hFont, TRUE);

            // 高级操作区
            CreateWindow("static", "Search Name:", WS_VISIBLE | WS_CHILD, 300, 20, 90, 20, hwnd, NULL, NULL, NULL);
            hSearchName = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 400, 20, 200, 20, hwnd, NULL, NULL, NULL);
            hSearchButton = CreateWindow("button", "Search", WS_VISIBLE | WS_CHILD, 520, 50, 60, 30, hwnd, (HMENU)3, NULL, NULL);

            CreateWindow("static", "Position:", WS_VISIBLE | WS_CHILD, 420, 170, 60, 20, hwnd, NULL, NULL, NULL);
            hpos = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 480, 170, 60, 20, hwnd, NULL, NULL, NULL);
            hinsertposbutton = CreateWindow("button", "Insert", WS_VISIBLE | WS_CHILD, 420, 200, 60, 30, hwnd, (HMENU)8, NULL, NULL);
            hquchong=CreateWindow("button", "quchong", WS_VISIBLE | WS_CHILD, 420,120, 60, 30, hwnd, (HMENU)11, NULL, NULL);
            hDeleteButton = CreateWindow("button", "Delete", WS_VISIBLE | WS_CHILD, 500, 120, 60, 30, hwnd, (HMENU)4, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == 1) { // 添加图书
                char no[50], name[100], priceStr[50];
                GetWindowText(hNo, no, sizeof(no));
                GetWindowText(hName, name, sizeof(name));
                GetWindowText(hPrice, priceStr, sizeof(priceStr));
                float price = atof(priceStr);
                //printf("Debug Price: %.2f\n", price);
                addbook(no, name, price);
                updatedbooklist(hList);
                SetWindowText(hNo, "");
                SetWindowText(hName, "");
                SetWindowText(hPrice, "");
            } else if (LOWORD(wParam) == 2) { // 排序图书
                sortbook();
                updatedbooklist(hList);
            } else if (LOWORD(wParam) == 3) { // 查找图书
                char name[100];
                GetWindowText(hSearchName, name, sizeof(name));
                searchname(name);
            } else if (LOWORD(wParam) == 4) { // 删除图书
                char name[100];
                GetWindowText(hName, name, sizeof(name));
                deletebook(name);
                updatedbooklist(hList);
            }else if(LOWORD(wParam)==5){
                xiugaijiage();
                updatedbooklist(hList);
            }else if(LOWORD(wParam)==6){
                nixu();
                updatedbooklist(hList);
            }else if(LOWORD(wParam==7)){
                book*expensive=findMostExpensiveBook();
                char bookinfo[256];
                char buffer[1024]="search results:\n";
                sprintf(bookinfo, "NO:  %s, Name:  %s, Price: %.2f\n", expensive->no, expensive->name, expensive->price);
                strcat(buffer,bookinfo);
                MessageBox(NULL,buffer,"result search:",MB_OK);
            }else if(LOWORD(wParam)==8){
                char pos[10];
                GetWindowText(hpos, pos, sizeof(pos));
                int position;
                position=atoi(pos);
                char no[50], name[100], priceStr[50];
                GetWindowText(hNo, no, sizeof(no));
                GetWindowText(hName, name, sizeof(name));
                GetWindowText(hPrice, priceStr, sizeof(priceStr));
                float price = atof(priceStr);
                insert(position,no,name,price);
                updatedbooklist(hList);
                SetWindowText(hNo, "");
                SetWindowText(hName, "");
                SetWindowText(hPrice, "");
                SetWindowText(hpos,"");
            }else if(LOWORD(wParam)==11){
                removeDuplicates();
                updatedbooklist(hList);
            }
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "BookManager";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("BookManager", "Book Management System", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
                             100, 100, 600, 500, NULL, NULL, hInstance, NULL);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}