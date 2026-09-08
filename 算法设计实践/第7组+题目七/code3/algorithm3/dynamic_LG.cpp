#include <algorithm>
#include <cstdio>
#include <queue>
#define LL long long
#define Re register int

using namespace std;

// 定义常量和变量
const int N = 11e4 + 5, M = 6e5 + 5, inf = 2e9;
int x, y, z, w, o = 1, n, m, h, t, A, B, C, K, st, ed;
int cyf[N], pan[N], pre[N], dis[N], head[N];
LL mincost, maxflow;

// 定义边的结构体
struct QAQ {
    int w, to, next, flow;
} a[M << 1];

// 定义队列用于SPFA算法
queue<int> Q;

// 快速读入函数
inline void in(Re &x) {
    int f = 0; x = 0; char c = getchar();
    while (c < '0' || c > '9') f |= c == '-', c = getchar();
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    x = f ? -x : x;
}

// 添加边函数，x为起点，y为终点，z为流量，w为权重
inline void add(Re x, Re y, Re z, Re w) {
    a[++o].flow = z;
    a[o].w = w;
    a[o].to = y;
    a[o].next = head[x];
    head[x] = o;
}

// 添加正反边函数
inline void add_(Re a, Re b, Re flow, Re w) {
    add(a, b, flow, w);
    add(b, a, 0, -w);
}

// SPFA算法，用于寻找最短路径，返回是否存在增广路径
inline int SPFA(Re st, Re ed) {
    for (Re i = 0; i <= ed; ++i) dis[i] = inf, pan[i] = 0;
    Q.push(st);
    pan[st] = 1;
    dis[st] = 0;
    cyf[st] = inf;
    
    while (!Q.empty()) {
        Re x = Q.front();
        Q.pop();
        pan[x] = 0;
        
        for (Re i = head[x], to; i; i = a[i].next)
            if (a[i].flow && dis[to = a[i].to] > dis[x] + a[i].w) {
                dis[to] = dis[x] + a[i].w;
                pre[to] = i;
                cyf[to] = min(cyf[x], a[i].flow);
                if (!pan[to]) pan[to] = 1, Q.push(to);
            }
    }
    return dis[ed] != inf;
}

// EK算法，用于求解最小费用最大流
inline void EK(Re st, Re ed) {
    while (SPFA(st, ed)) {
        Re x = ed;
        maxflow += cyf[ed];
        mincost += (LL)cyf[ed] * dis[ed];
        while (x != st) {
            Re i = pre[x];
            a[i].flow -= cyf[ed];
            a[i^1].flow += cyf[ed];
            x = a[i^1].to;
        }
    }
}

// 坐标转换函数
inline int P(Re x, Re y, Re k) {
    return (x - 1) * n + y + k * n * n;
}

int main() {
    // 读入参数
    in(n), in(K), in(A), in(B), in(C);
    st = (K + 1) * n * n + 1;
    ed = st + 1; // 一共有(K+1)层
    
    // 添加超级源点到满油起点的边
    add_(st, P(1, 1, 0), 1, 0);
    
    // 将每一层的终点连到超级汇点
    for (Re k = 1; k <= K; ++k) add_(P(n, n, k), ed, 1, 0);
    
    // 遍历每一个位置，构建图
    for (Re i = 1; i <= n; ++i)
        for (Re j = 1; j <= n; ++j) {
            in(x);
            if (x) { // 有加油站
                for (Re k = 1; k <= K; ++k) add_(P(i, j, k), P(i, j, 0), 1, A);
                if (i < n) add_(P(i, j, 0), P(i + 1, j, 1), 1, 0); // 向下
                if (j < n) add_(P(i, j, 0), P(i, j + 1, 1), 1, 0); // 向右
                if (i > 1) add_(P(i, j, 0), P(i - 1, j, 1), 1, B); // 向上
                if (j > 1) add_(P(i, j, 0), P(i, j - 1, 1), 1, B); // 向左
            } else { // 无加油站
                for (Re k = 0; k < K; ++k) { // 从有油的状态到达下一层的四个方向
                    if (i < n) add_(P(i, j, k), P(i + 1, j, k + 1), 1, 0); // 向下
                    if (j < n) add_(P(i, j, k), P(i, j + 1, k + 1), 1, 0); // 向右
                    if (i > 1) add_(P(i, j, k), P(i - 1, j, k + 1), 1, B); // 向上
                    if (j > 1) add_(P(i, j, k), P(i, j - 1, k + 1), 1, B); // 向左
                }
                add_(P(i, j, K), P(i, j, 0), 1, A + C); // 没有加油站的地方可以自给自足
            }
        }
    
    // 运行EK算法，求最小费用最大流
    EK(st, ed);
    
    // 输出最小费用
    printf("%lld", mincost);
}

