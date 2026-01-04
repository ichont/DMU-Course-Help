#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> 
using namespace std;
// 图书结构
struct Book {
    string no;
    string name;
    float price;
};
// 全局变量
vector<Book> books; // 图书列表
HWND hNo, hName, hPrice, hList, hAddButton,hSortButton,hxiugaiButton,hnixuButton,hsearchButton,hSearchName,hDeduplicateButton;
HWND hshowButton,hexpensiveButton,hgui, hPosition,hDeleteButto,hloveshow,hinsertButton,hFindMostExpensiveButton,DeleteButton;
 // 控件句柄
// 添加图书的辅助函数
void insert(const string& no, const string& name,float price) {
    books.push_back({no, name, price});
}
bool CompareBooksByPrice(const Book& a, const Book& b) {
    return a.price > b.price; // 降序排序
}
void insertAtPosition(int position, const string& no, const string& name, float price) {
    if (position < 0 || position > books.size()) {
        // 如果位置不合法，则插入到末尾
        books.push_back({no, name, price});
    } else {
        // 否则，将图书插入到指定位置
        books.insert(books.begin() + position, {no, name, price});
    }
}
vector<Book> searchBooksByName(const string& name) {
    vector<Book> results;
    for (const auto& book : books) {
        if (book.name.find(name) != string::npos) { // 如果名字包含搜索的字符串
            results.push_back(book);
        }
    }
    return results;
}
vector<Book> searchexpensive(const string& name) {
    vector<Book> results;
    for (const auto& book : books) {
        if (book.name.find(name) != string::npos) { // 如果名字包含搜索的字符串
            results.push_back(book);
        }
    }
    return results;
}
// 修改图书价格
void adjustPrices() {
    float totalPrice = 0,averagePrice=0;
    for (auto& book : books) {
        totalPrice += book.price;
    }
    averagePrice=totalPrice / books.size();
    for (auto& book : books) {
        if (book.price < averagePrice) {
            book.price *= 1.2; // 低于平均价格，提高20%
        } else {
            book.price *= 1.1; // 高于或等于平均价格，提高10%
        }
    }
}
void removeDuplicates() {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.no < b.no; // 按编号排序，便于查找重复项
    });

    books.erase(unique(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.no == b.no; // 如果编号相同，则认为是重复图书
    }), books.end());
}
// 更新图书列表显示
void UpdateBookList(HWND hList,const vector<Book>& bookList) {
    stringstream ss;
    for (const auto& book : books) {
        ss << "NO: " << book.no 
           << ", Name: " << book.name 
           << ", Price: " << book.price << "\r\n";
    }
    SetWindowText(hList, ss.str().c_str());
}
void deleteBookByName(const string& name) {
    auto it = remove_if(books.begin(), books.end(), [&](const Book& book) {
        return book.name == name; // 查找名字匹配的图书
    });
    books.erase(it, books.end()); // 删除匹配的图书
}
// 窗口过程函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // 创建控件
            HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
                         OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                         DEFAULT_PITCH | FF_SWISS, "Arial");

// 标签和输入框
            CreateWindow("static", "No:", WS_VISIBLE | WS_CHILD, 20, 20, 50, 20, hwnd, NULL, NULL, NULL);
            hNo = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 20, 200, 20, hwnd, NULL, NULL, NULL);
            SendMessage(hNo, WM_SETFONT, (WPARAM)hFont, TRUE);

            CreateWindow("static", "Name:", WS_VISIBLE | WS_CHILD, 20, 50, 50, 20, hwnd, NULL, NULL, NULL);
            hName = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 50, 200, 20, hwnd, NULL, NULL, NULL);
            SendMessage(hName, WM_SETFONT, (WPARAM)hFont, TRUE);

            CreateWindow("static", "Price:", WS_VISIBLE | WS_CHILD, 20, 80, 50, 20, hwnd, NULL, NULL, NULL);
            hPrice = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 80, 200, 20, hwnd, NULL, NULL, NULL);
            SendMessage(hPrice, WM_SETFONT, (WPARAM)hFont, TRUE);

            // 按钮区
            hAddButton = CreateWindow("button", "Add", WS_VISIBLE | WS_CHILD, 20, 120, 60, 30, hwnd, (HMENU)1, NULL, NULL);
            hSortButton = CreateWindow("button", "Sort", WS_VISIBLE | WS_CHILD, 90, 120, 60, 30, hwnd, (HMENU)2, NULL, NULL);
            hxiugaiButton = CreateWindow("button", "Modify", WS_VISIBLE | WS_CHILD, 160, 120, 60, 30, hwnd, (HMENU)3, NULL, NULL);
            hnixuButton = CreateWindow("button", "Reverse", WS_VISIBLE | WS_CHILD, 230, 120, 60, 30, hwnd, (HMENU)4, NULL, NULL);

            // 搜索区
            CreateWindow("static", "Search Name:", WS_VISIBLE | WS_CHILD, 300, 50, 90, 20, hwnd, NULL, NULL, NULL);
            hSearchName = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 400, 50, 120, 20, hwnd, NULL, NULL, NULL);
            hsearchButton = CreateWindow("button", "Search", WS_VISIBLE | WS_CHILD, 530, 50, 60, 30, hwnd, (HMENU)5, NULL, NULL);

            CreateWindow("static", "Position:", WS_VISIBLE | WS_CHILD, 300, 80, 90, 20, hwnd, NULL, NULL, NULL);
            hPosition = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 400, 80, 120, 20, hwnd, NULL, NULL, NULL);
            hinsertButton = CreateWindow("button", "Insert", WS_VISIBLE | WS_CHILD, 530, 80, 60, 30, hwnd, (HMENU)8, NULL, NULL);

            // 功能按钮
            hFindMostExpensiveButton = CreateWindow("button", "Expensive", WS_VISIBLE | WS_CHILD, 20, 160, 100, 30, hwnd, (HMENU)9, NULL, NULL);
            DeleteButton = CreateWindow("button", "Delete", WS_VISIBLE | WS_CHILD, 130, 160, 100, 30, hwnd, (HMENU)10, NULL, NULL);
            hDeduplicateButton = CreateWindow("button", "Deduplicate", WS_VISIBLE | WS_CHILD, 240, 160, 100, 30, hwnd, (HMENU)11, NULL, NULL);

            // 列表显示
            hList = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 200, 570, 200, hwnd, NULL, NULL, NULL);
            SendMessage(hList, WM_SETFONT, (WPARAM)hFont, TRUE);

            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == 1) { // 添加按钮点击事件
                char No[100], Name[100],Price[100]; 
                //float price = atof(Price);
                GetWindowText(hNo, No, 100);
                GetWindowText(hName, Name, 100);
                GetWindowText(hPrice, Price, 100);
                float price = atof(Price);
                insert(No, Name, price);
                UpdateBookList(hList, books);
                SetWindowText(hNo, "");
                SetWindowText(hName, "");
                SetWindowText(hPrice, "");
            }
            else if (LOWORD(wParam) == 2) { 
                if (books.empty()) {
                    MessageBox(hwnd, "No books in the library!", "Error", MB_OK | MB_ICONERROR);
                    return 0;   
                }// 按价格排序按钮点击事件
                sort(books.begin(), books.end(), CompareBooksByPrice); // 按价格降序排序
                UpdateBookList(hList, books);
            }
            else if (LOWORD(wParam) == 3) { // 修改价格按钮点击事件
                if (books.empty()) {
                    MessageBox(hwnd, "No books to adjust prices!", "Error", MB_OK | MB_ICONERROR);
                    return 0;
                }
                adjustPrices();
                UpdateBookList(hList, books);
                stringstream msg;
                msg << "Prices adjusted based on average price.";
                MessageBox(hwnd, msg.str().c_str(), "Price Adjustment", MB_OK);
            }
            else if (LOWORD(wParam) == 4) {
                if (books.empty()) {
                        MessageBox(hwnd, "No books in the library!", "Error", MB_OK | MB_ICONERROR);
                        return 0;
                    } // 逆序排序按钮点击事件
                reverse(books.begin(), books.end());
                UpdateBookList(hList, books);
            }
            else if (LOWORD(wParam) == 5) { // 查找最爱的图书按钮点击事件
                if (books.empty()) {
                    MessageBox(hwnd, "No books in the library!", "Error", MB_OK | MB_ICONERROR);
                    return 0;
                }
                char searchQuery[100];
                GetWindowText(hSearchName, searchQuery, 100); // 获取用户输入的书名
                string query = searchQuery;
                // 查询书名
                vector<Book> searchResults = searchBooksByName(query);
                if (searchResults.empty()) {
                    MessageBox(hwnd, "No matching book found!", "Search Result", MB_OK | MB_ICONINFORMATION);
                } else {
                    // 拼接查询结果为字符串
                    stringstream ss;
                    ss << "Found " << searchResults.size() << " book(s):\n";
                    for (const auto& book : searchResults) {
                        ss << "NO: " << book.no << "\n"
                        << "Name: " << book.name << "\n"
                        << "Price: " << book.price << "\n\n";
                    }
        // 显示查询结果
                    MessageBox(hwnd, ss.str().c_str(), "Search Result", MB_OK | MB_ICONINFORMATION);
                    }
                }

            else if (LOWORD(wParam) == 7) { // 查找按钮点击事件
                UpdateBookList(hList, books); // 更新显示
            }
            else if (LOWORD(wParam) == 8){
      
                char No[100], Name[100],Price[100],Position[100];
                stringstream msg; 
                //float price = atof(Price);
                GetWindowText(hNo, No, 100);
                GetWindowText(hName, Name, 100);
                GetWindowText(hPrice, Price, 100);
                if (strlen(No) == 0) {
                    MessageBox(hwnd, "The input box is empty!", "Warning", MB_OK | MB_ICONWARNING);
                    
                }
                else{
                    float price = atof(Price);
                    int position;
                    position = atoi(Position);
                    insertAtPosition(position, No, Name, price);
                    UpdateBookList(hList, books);
                    SetWindowText(hNo, "");
                    SetWindowText(hName, "");
                    SetWindowText(hPrice, "");
                    SetWindowText(hPosition, "");
                }
            }
            else if (LOWORD(wParam) == 9) { // 查找按钮点击事件
                if (books.empty()) {
                    MessageBox(hwnd, "No books in the library!", "Error", MB_OK | MB_ICONERROR);
                    return 0;
                }
                auto mostExpensiveBook = *max_element(books.begin(), books.end(),
                [](const Book& a, const Book& b) { return a.price < b.price; });
                stringstream ss;
                ss << "The most expensive book is:\n"
                << "NO: " << mostExpensiveBook.no << "\n"
                << "Name: " << mostExpensiveBook.name << "\n"
                << "Price: " << mostExpensiveBook.price;
                MessageBox(hwnd, ss.str().c_str(), "Most Expensive Book", MB_OK | MB_ICONINFORMATION);
            } 
            else if(LOWORD(wParam) == 10){
                char name[100];
                GetWindowText(hName, name, 100); // 获取用户输入的书名
                string bookName = name;
                // 删除图书
                deleteBookByName(bookName);
                UpdateBookList(hList,books);
            }
            else if(LOWORD(wParam) == 11){
                removeDuplicates(); // 调用去重函数
                UpdateBookList(hList,books); // 更新图书列表
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
    // 注册窗口类
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "BookManager";

    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindow("BookManager", "Book Management System", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
                             100, 100, 800, 600, NULL, NULL, hInstance, NULL);

    // 消息循环
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
