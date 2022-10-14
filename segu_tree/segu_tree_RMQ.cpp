
//参考URL
// https://www.creativ.xyz/segment-tree-entrance-999/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INFl (1LL<<60)
vector<ll> value; // ノードの値を持つ配列
int N; // 葉の数

void update(int i, ll x) {
    // i 番目の葉の値を x に変える
    i += N - 1; // i 番目の葉のノード番号
    value[i] = x;
    while (i > 0) {
        i = (i - 1) / 2; // ノード i の親ノードの番号に変える
        value[i] = min(value[i * 2 + 1], value[i * 2 + 2]); // 左右の子の min を計算しなおす
        
    }
}

//RMQ 指定区間の最小値を得るクエリ 親から子に聞く
ll query(int a, int b, int k, int l, int r) {
    // [a, b) の区間に対するクエリについて
    // ノード k （区間 [l, r) 担当）が答える
    if (r <= a || b <= l) return INFl; // 区間が被らない場合は INF を返す
    if (a <= l && r <= b)
        return value[k]; // ノード k の担当範囲がクエリ区間 [a, b) に完全に含まれる
    else {
        // 一部だけ範囲が被る場合は左右の子に委託する
        //ノードiの子ノードは2*i+1,2*i+2で得られる
        ll c1 = query(a, b, 2 * k + 1, l, (l + r) / 2); // 左の子に値を聞く
        ll c2 = query(a, b, 2 * k + 2, (l + r) / 2, r); // 右の子に値を聞く
        return min(c1, c2); // 左右の子の値の min を取る
    }
}

int main(void) {
    int n, q; // 数列のサイズとクエリの数
    cin >> n >> q;
    N = 1;
    while (N < n) N *= 2; // 葉の数を計算（n以上の最小の2冪数）

    //必要なノードの数は N + N-1=2N-1  葉の数はNで, それ以外の部分は等比数列の和の公式から求めてN-1個だから
    value = vector<ll>(2 * N - 1, INFl);

    // s<= ~ <=t までの区間の最小値を得たいなら下にように呼び出す
    query(s, t + 1, 0, 0, N);
}