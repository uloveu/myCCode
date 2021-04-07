#include <cstdio>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
const int N = 54014;
 
int f[N], rank_[N];
 
void init(int n);
int get(int x);
bool Merge(int d, int x, int y);
 
int main(){
    int n, m, d, x, y, cnt;
    scanf("%d %d", &n, &m);
    init(n);
    cnt = 0;
    while(m--){
        scanf("%d %d %d", &d, &x, &y);
        if(x > n || y > n){
            cnt++;
            continue;
        }
        if(d == 2 && x == y){
            cnt++;
            continue;
        }
        if(!Merge(d, x, y)){
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
void init(int n){
    for(int i = 1; i <= n; i++){
        f[i] = i, rank_[i] = 0;
    }
}
int get(int x){
    if(x == f[x]) return x;
    int fa = f[x];
    f[x] = get(f[x]);
    if(rank_[x] == 0 && rank_[fa] == 0) rank_[x] = 0;
    else if(rank_[x] == 0 && rank_[fa] == 1) rank_[x] = 1;
    else if(rank_[x] == 0 && rank_[fa] == 2) rank_[x] = 2;
    else if(rank_[x] == 1 && rank_[fa] == 0) rank_[x] = 1;
    else if(rank_[x] == 1 && rank_[fa] == 1) rank_[x] = 2;
    else if(rank_[x] == 1 && rank_[fa] == 2) rank_[x] = 0;
    else if(rank_[x] == 2 && rank_[fa] == 0) rank_[x] = 2;
    else if(rank_[x] == 2 && rank_[fa] == 1) rank_[x] = 0;
    else if(rank_[x] == 2 && rank_[fa] == 2) rank_[x] = 1;
    return f[x];
}
bool Merge(int d, int x, int y){
    int t1 = get(x);
    int t2 = get(y);
    if(d == 1){
        if(t1 == t2){
            if(rank_[x] != rank_[y]) return false;
            else return true;
        }
        else {
            f[t1] = t2;
            if(rank_[x] == 0 && rank_[y] == 0) rank_[t1] = 0;
            else if(rank_[x] == 0 && rank_[y] == 1) rank_[t1] = 1;
            else if(rank_[x] == 0 && rank_[y] == 2) rank_[t1] = 2;
            else if(rank_[x] == 1 && rank_[y] == 0) rank_[t1] = 2;
            else if(rank_[x] == 1 && rank_[y] == 1) rank_[t1] = 0;
            else if(rank_[x] == 1 && rank_[y] == 2) rank_[t1] = 1;
            else if(rank_[x] == 2 && rank_[y] == 0) rank_[t1] = 1;
            else if(rank_[x] == 2 && rank_[y] == 1) rank_[t1] = 2;
            else if(rank_[x] == 2 && rank_[y] == 2) rank_[t1] = 0;
            return true;
        }
    }
    else {
        if(t1 == t2){
            if(rank_[x] == 0 && rank_[y] != 2) return false;
            else if(rank_[x] == 1 && rank_[y] != 0) return false;
            else if(rank_[x] == 2 && rank_[y] != 1) return false;
            else return true;
        }
        else {
            f[t1] = t2;
            if(rank_[x] == 0 && rank_[y] == 0) rank_[t1] = 1;
            else if(rank_[x] == 0 && rank_[y] == 1) rank_[t1] = 2;
            else if(rank_[x] == 0 && rank_[y] == 2) rank_[t1] = 0;
            else if(rank_[x] == 1 && rank_[y] == 0) rank_[t1] = 0;
            else if(rank_[x] == 1 && rank_[y] == 1) rank_[t1] = 1;
            else if(rank_[x] == 1 && rank_[y] == 2) rank_[t1] = 2;
            else if(rank_[x] == 2 && rank_[y] == 0) rank_[t1] = 2;
            else if(rank_[x] == 2 && rank_[y] == 1) rank_[t1] = 0;
            else if(rank_[x] == 2 && rank_[y] == 2) rank_[t1] = 1;
            return true;
        }
    }
}