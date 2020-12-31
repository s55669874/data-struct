#include<iostream>
#include<string.h>
using namespace std;
int main()
{
    string answer[10][5];

    answer[0][0] = "*****";
    answer[0][1] = "*   *";
    answer[0][2] = "*   *";
    answer[0][3] = "*   *";
    answer[0][4] = "*****";

    answer[1][0] = "    *";
    answer[1][1] = "    *";
    answer[1][2] = "    *";
    answer[1][3] = "    *";
    answer[1][4] = "    *";

    answer[2][0] = "*****";
    answer[2][1] = "    *";
    answer[2][2] = "*****";
    answer[2][3] = "*    ";
    answer[2][4] = "*****";

    answer[3][0] = "*****";
    answer[3][1] = "    *";
    answer[3][2] = "*****";
    answer[3][3] = "    *";
    answer[3][4] = "*****";

    answer[4][0] = "*   *";
    answer[4][1] = "*   *";
    answer[4][2] = "*****";
    answer[4][3] = "    *";
    answer[4][4] = "    *";

    answer[5][0] = "*****";
    answer[5][1] = "*    ";
    answer[5][2] = "*****";
    answer[5][3] = "    *";
    answer[5][4] = "*****";

    answer[6][0] = "*****";
    answer[6][1] = "*    ";
    answer[6][2] = "*****";
    answer[6][3] = "*   *";
    answer[6][4] = "*****";

    answer[7][0] = "*****";
    answer[7][1] = "    *";
    answer[7][2] = "    *";
    answer[7][3] = "    *";
    answer[7][4] = "    *";

    answer[8][0] = "*****";
    answer[8][1] = "*   *";
    answer[8][2] = "*****";
    answer[8][3] = "*   *";
    answer[8][4] = "*****";

    answer[9][0] = "*****";
    answer[9][1] = "*   *";
    answer[9][2] = "*****";
    answer[9][3] = "    *";
    answer[9][4] = "    *";

    string s;
    while (cin >> s)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < s.length(); j++)
            {
                if (j > 0) // 第一格不用印空白
                    cout << " ";
                cout << answer[s[j] - '0'][i];

                if(j == s.length() - 1) //最後要換行
                    cout << endl;
            }
        }
    }
    return 0;
}
