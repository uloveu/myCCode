#include<iostream>

using namespace std;

int main(void) {
    int left[1000] = {0};
    int right[1000] = {0};
    char ch[1005][1005] = {""};
    int m, n;
    int t = 0;
    int i,j;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> ch[i][j];
            if (ch[i][j] == '*') {
                left[i]++;
                right[j]++;
                t++;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (ch[i][j] == '*') {
                if (t == (left[i] + right[j] - 1)) {
                    cout << "YES" << endl;
                    cout << i + 1 << ' ' << j + 1;
                    return 0;
                }
            } else if (t == left[i] + right[j]) {
                cout << "YES" << endl;
                cout << i + 1 << ' ' << j + 1;
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}