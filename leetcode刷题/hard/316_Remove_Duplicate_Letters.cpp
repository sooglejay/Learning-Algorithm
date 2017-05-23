#include <iostream>

using namespace std;
//https://leetcode.com/problems/remove-duplicate-letters/#/description
/**
 *
 *
  描述

    Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

    Example:
    Given "bcabc"
    Return "abc"

    Given "cbacdcbc"
    Return "acdb"

   大意：给定一个字符串，要求去掉重复的字符，并且是原字符串中字典序最小的 子序列（包含全部字符但是没有重复字符的哟！）


   思路：使用递归，
        每一次递归都找到当前字符串的第一个符合条件的字符，
        然后截取字符串，也就是为下一次递归做准备。
        比如babac,第一次递归，字符a应该首先输出，然后截取字符串bac,并且判断它是否包含 a这个已经符合了条件被输出的字符，存在就删除a这个字符
        变为bc，然后使用bc继续递归。

        这里符合条件的字符，有两个条件：1、这个字符出现的次数是否只有一次。如果是，就直接输出了，然后为第二次迭代重新构造字符串；

        2、如果不是，那么就继续判断 ，找出 字典序最小的字符，比如'a'这个字符是最小的。

        这俩条件要统一起来，我现在写这段思路，还没有完全理解 如何将这俩条件统一起来分析。所以请看下面的代码


  总结:这道题目，递归思想用得比较灵活，递归函数里面使用for循环，这种题目要多做才行。

  后面附上其他的解决方法，虽然很牛逼，但是技巧太强，暂时没有理解


 c,判断

 */
string removeDuplicateLetters(string s) {
    if (s.length() < 1)
        return "";

    int arr[26];
    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < s.size(); ++i) {
        arr[s[i] - 'a']++;
    }
    int pos = 0;
    for (int j = 0; j < s.size(); ++j) {

        if (s[j] < s[pos]) { pos = j; }//到达这里，说明 前一个--arr[s[j－1] - 'a']至少还是1，才不会break

        if (--arr[s[j] - 'a'] == 0) {//形如 bbac这种，当j＝1的时候，arr[s[1]-'a'] 其实减到0了，那么就退出循环，输出pos位置的字符
            break;
        }
    }
    size_t start = pos + 1;
    size_t len = s.size() - start;
    string sub = s.substr(start, len);
    string modify;
    for (int k = 0; k < sub.size(); ++k) {
        if (sub[k] != s[pos]) {
            modify += sub[k];
        }
    }
    string res;
    res += s[pos];
    //继续迭代
    res += removeDuplicateLetters(modify);
    return res;
}

int main() {
    cout << removeDuplicateLetters("qwrreerreedrwqwqwqqasasas");
//    print_permutation(4, 0);
}




//其他牛逼哄哄的解决方法
string NB_removeDuplicateLetters(string s) {
    int m[256] = {0}, visited[256] = {0};
    string res = "0";
    for (auto a : s) ++m[a];
    for (auto a : s) {
        --m[a];
        if (visited[a]) continue;
        while (a < res.back() && m[res.back()]) {
            visited[res.back()] = 0;
            res.pop_back();
        }
        res += a;
        visited[a] = 1;
    }
    return res.substr(1);
}

