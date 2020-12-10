#include <bits/stdc++.h>
#define ll long long
#define fast                          \
    ios_base::sync_with_stdio(false); \
    std::cin.tie(0);                  \
    std::cout.tie(0)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define PB push_back
#define MP make_pair
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define deb(x) std::cout << #x << " " << x << std::endl
#define PI 3.141592653589793238
#define GC 9.8
#define NUM 4294967296

using namespace std;

template <typename T>
void print(vector<T> &vec)
{
    for (int i = 0; i < (int)vec.size(); i++)
    {
        cout << vec[i] << "\n";
    }
    // cout << endl;
}

vector<int> decimalToBinary(int val)
{
    vector<int> res;
    while (val != 0)
    {
        res.push_back(val % 2);
        val /= 2;
    }
    res.resize(8);
    reverse(res.begin(), res.end());
    return res;
}

vector<long double> initialize(vector<int> &K)
{
    if (K.empty())
    {
        cerr << "Error: Key Not Found" << endl;
        exit(1);
    }
    // for (int i = 0; i < (int).size(); i++)
    // {
    //     int v = key[i];
    //     vector<int> bin = decimalToBinary(v);
    //     K.insert(K.end(), bin.begin(), bin.end());
    // }
    // cout << K.size() << endl;
    // print(K);
    int len = K.size();
    vector<vector<int>> k(4, vector<int>());
    for (int i = 0; i < len / 4; i++)
    {
        k[0].push_back(K[i]);
        k[1].push_back(K[len / 4 + i]);
        k[2].push_back(K[len / 2 + i]);
        k[3].push_back(K[3 * len / 4 + i]);
    }
    // print(k[0]);
    // print(k[1]);
    vector<vector<int>> param(7, vector<int>());

    int j = 0;
    while (j < 64)
    {
        int i = 0;
        while (i < len / 4)
        {
            param[0].push_back(k[0][i] ^ k[1][i]);
            param[1].push_back(k[0][i] ^ k[2][i]);
            param[2].push_back(k[0][i] ^ k[3][i]);
            param[3].push_back(k[1][i] ^ k[2][i]);
            param[4].push_back(k[1][i] ^ k[3][i]);
            param[5].push_back(k[2][i] ^ k[3][i]);
            param[6].push_back(k[0][i]);
            i++;
            j++;
            if (j >= 64)
            {
                break;
            }
        }
    }
    // for (int i = 0; i < 7; i++)
    // {
    //     print(param[i]);
    // }

    vector<long double> res(8, 0);

    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            res[j] += param[j][i] * powl(2.0, 0 - i);
        }
        res[6] += param[6][i] * powl(2.0, 4 - i);
    }
    res[7] = len;
    return res;
}

// utility function for concatenating two numbers bit by bit
long long concat(int a, int b)
{
    vector<int> a_bin;
    while (a != 0)
    {
        a_bin.push_back(a % 2);
        a /= 2;
    }
    a_bin.resize(32);
    vector<int> b_bin;
    while (b != 0)
    {
        b_bin.push_back(b % 2);
        b /= 2;
    }
    b_bin.resize(32);
    vector<int> res;
    for (int i = 0; i < 32; i++)
    {
        res.push_back(b_bin[i]);
        res.push_back(a_bin[i]);
    }
    // reverse(res.begin(), res.end());
    long long out = 0, run_mul = 1;
    for (int i = 0; i < 64; i++)
    {
        out += res[i] * run_mul;
        run_mul *= 2;
    }
    return out;
}

vector<long long> dualPendPRNG(vector<int> &key, long long mod, int F = 1)
{
    vector<long double> res = initialize(key);
    long double l1, l2, m1, m2, t1, t2, r;
    l1 = res[0];
    l2 = res[1];
    m1 = res[2];
    m2 = res[3];
    t1 = res[4];
    t2 = res[5];
    r = res[6];
    int t0 = r * res[7];
    int i = 0, j = 0, k = 0;
    vector<long long> S;
    long double v1 = 0, v2 = 0;
    long double h = 0.002;

    while (j <= F)
    {
        long double den = 2 * m1 + m2 - m2 * cos(2 * t1 - 2 * t2);
        long double a1 = -1 * GC * (2 * m1 + m2) * sin(t1) - m2 * GC * sin(t1 - 2 * t2) - 2 * sin(t1 - t2) * m2 * (v2 * v2 * l2 + v1 * v1 * l1 * cos(t1 - t2));
        a1 /= l1 * den;
        long double a2 = 2 * sin(t1 - t2) * (v1 * v1 * l1 * (m1 + m2) + GC * (m1 + m2) * cos(t1) + v2 * v2 * l2 * m2 * cos(t1 - t2));
        a2 /= l2 * den;

        long double x2, y2;
        long long X, Y;
        if (i < t0)
        {
            v1 += h * a1;
            v2 += h * a2;
            t1 += h * v1;
            t2 += h * v2;
            x2 = l1 * sin(t1) + l2 * sin(t2);
            y2 = -l1 * cos(t1) - l2 * cos(t2);
            // cout << x2 << " " << y2 << endl;
            i++;
        }
        else
        {
            v1 += h * a1;
            v2 += h * a2;
            t1 += h * v1;
            t2 += h * v2;
            x2 = l1 * sin(t1) + l2 * sin(t2);
            y2 = -l1 * cos(t1) - l2 * cos(t2);
            // cout << x2 << " " << y2 << endl;
            X = floor(fmod(x2 * 1000, 1.0) * NUM);
            Y = floor(fmod(y2 * 1000, 1.0) * NUM);
            // cout << X << " " << Y << endl;
            long long temp = concat(X, Y);
            temp = temp % mod;
            if (temp < 0)
            {
                temp += mod;
            }
            S.push_back(temp);
            // print(temp);
            i++;
            j++;
        }
    }
    return S;
}

int main()
{
    vector<int> key = {0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1};
    vector<long long> res = dualPendPRNG(key, 100, 10);
    print(res);

    // long double X = fmod((long double)1703.48, (long double)1);
    // cout << X << endl;

    return 0;
}