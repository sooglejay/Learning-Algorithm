#include <iostream>
#include <vector>
//https://leetcode.com/problems/fraction-addition-and-subtraction/#/description
using namespace std;

int measure(int x, int y) {
    int z = y;
    while (x % y != 0) {
        z = x % y;
        x = y;
        y = z;
    }
    return z;
}

string add(string a, string b) {
    bool fuhao = false;
    int aLen = a.size(), bLen = b.size();

    int aFather = 0, aSon = 0;
    int bFather = 0, bSon = 0;

    int i = (a[0] == '-') ? 1 : 0;
    while (i < aLen && a[i] != '/') {
        aFather *= 10;
        aFather = aFather + a[i] - '0';
        i++;
    }
    i++;
    while (i < aLen) {
        aSon *= 10;
        aSon = aSon + a[i] - '0';
        i++;
    }

    i = (b[0] == '-') ? 1 : 0;;
    while (i < bLen && b[i] != '/') {
        bFather *= 10;
        bFather = bFather + b[i] - '0';
        i++;
    }
    i++;
    while (i < bLen) {
        bSon *= 10;
        bSon = bSon + b[i] - '0';
        i++;
    }
    int father = (b[0] == '-' ? (-1) : 1) * bFather * aSon + (a[0] == '-' ? (-1) : 1) * aFather * bSon;
    int son = bSon * aSon;
    int g = measure(abs(father), abs(son));
    father = father / g;
    son = son / g;
    string res;
    res += to_string(father) + "/" + to_string(son);
    return res;

}

string fractionAddition(string expression) {
    int len = expression.size();
    if (len < 1) {
        return "";
    }
    vector<string> V;
    for (int i = 0; i < len; ++i) {
        string firstWord;
        firstWord += expression[i];
        i++;
        while (i < len&&expression[i] != '+') {
            if(expression[i]=='-'){
                i-=1;
                break;
            }
            firstWord += expression[i];
            i++;
        }
        V.push_back(firstWord);
    }

    string result = V[0];
    cout<<V[0]<<endl;
    for (int j = 1; j < V.size(); ++j) {
        cout<<V[j]<<endl;

        result = add(V[j],result);
    }
    return result;
}

//https://leetcode.com/problems/longest-harmonious-subsequence/#/description

int findLHS(vector<int> &nums) {
    int len = int(nums.size());
    if (len < 1)
        return 0;
    bool upVisited[len], downVisited[len];
    memset(upVisited, false, sizeof(upVisited));
    memset(downVisited, false, sizeof(downVisited));
    int maxV = 0;
    for (int i = 0; i < len; ++i) {
        if (upVisited[i] || downVisited[i])continue;
        int upC = 1, downC = 1;
        bool upF = false, downF = false;
        for (int j = i + 1; j < len; ++j) {
            int upV = nums[j] - nums[i];
            int downV = nums[i] - nums[j];
            if (upV >= 0 && upV <= 1) {
                if (upV == 1)upF = true;
                if (upV == 0) {
                    upVisited[j] = true;
                }
                upC++;
            }
            if (downV >= 0 && downV <= 1) {
                if (downV == 1)downF = true;
                if (downV == 0) {
                    downVisited[j] = true;
                }
                downC++;
            }
        }
        int maxT = max(upC, downC);
        if (maxT == upC) {
            if (upF) {
                maxV = max(maxV, maxT);
                for (int j = i + 1; j < len; ++j) {
                    downVisited[j] = false;
                }
            }
        } else if (maxT == downC) {
            if (downF) {
                maxV = max(maxV, maxT);
                for (int j = i + 1; j < len; ++j) {
                    upVisited[j] = false;
                }
            }
        }
    }
    return maxV;
}

int main() {
    cout<<fractionAddition("1/3-1/2")<<endl;
    return 0;
    cout<<add("-1/2","1/3")<<endl;
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(6);
    v.push_back(5);
    v.push_back(-5);
    v.push_back(10);
    v.push_back(-1);
    v.push_back(-2);
    v.push_back(5);
    v.push_back(4);
    v.push_back(4);
    v.push_back(-1);
    v.push_back(7);
    cout << findLHS(v) << endl;
}