#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int bits, num_rule;
struct node//switch
{
    int id;
    int capacity;
    int neighbor[5000][2];
    int num_neighbor;
    int parent;
    int hop;
    int distance;
    int arrived;
}nodes[5000];

struct rule
{
    char source[100];
    char des[100];
    char action[100];
}rules[5000];

typedef struct Q
{
    int x;
    int y;
    int lengh_x;
    int lengh_y;
    double utility;
    int num_internal;
    int num_overlapping;
    int inter_rule[2000];
    int q_num_rule;
    int q_rule[2000];
}Q;

void q_initial(Q *q) //rewrite時候將其初始化
{
    q->num_internal = 0;
    q->num_overlapping = 0;
    q->q_num_rule = 0;
}

int calculus(int a)//切割路徑時使用,因為其長度是1,2,4,8為2的倍數
{
    return (1 << a);
}

int bin_to_dec(char tmp_s[], int status) //2進位10進位，status = 0代表*後面填0，1代表後面填1
{
    char s[10];
    strcpy(s, tmp_s);
    int len = strlen(s);
    if(s[len - 1] == '*') //把*去除
    {
        s[len - 1] = '\0';
        len--;
    }
    int dif = bits - len;
    for(int i = 0;i < dif ; i++) //把*後的數字填滿
    {
        if(status == 0)
            strcat(s, "0");
        if(status == 1)
            strcat(s, "1");
    }
    int res = 0;

    for(int i = 0; i < bits; i++) //2進位轉成10進位
    {
        res *= 2;
        res += (s[i] - '0');
    }
    return res ;
}

int my_log2(int number)//把給的bit取log
{
    int remain = 0;
    while(number != 1)
    {
        remain++;
        number /= 2;
    }
    return remain;
}
char *dec_to_bin(int num, int len)//10進位轉2
{
    char *res = (char *)malloc(sizeof(char) * (10 + 5));
    int digit = (1 << (bits - 1));
    len = my_log2( len );
    for(int i = 0;i < bits - len; i++) //digit會將num掃過
    {
        res[i] = ((num & (digit)) > 0) + '0'; //檢查num的此位bit為0 or 1
        digit >>= 1;//下一位數?
    }
    if( len > 0) //有*的情況
    {
        res[bits - len] = '*';
        res[bits - len + 1] = '\0';
    }
    else
    {
        res[bits] = '\0';
    }
    return res;
}

int rule_table[1024][1024]; //建一個一開始的rule表
void print_table()//debud用
{
    for(int i = 0;i < calculus(bits);i++)
    {
        for(int j = 0;j < calculus(bits);j++)
            printf("%d ", rule_table[i][j]);
        printf("\n");
    }
}
void build_table()
{
    for(int i = 0; i < 1024 ; i++)//表初始化
        for(int j = 0 ; j < 1024 ; j++)
            rule_table[i][j] = 0;

    for(int i = 1; i <= num_rule; i++)
    {
        int src_start = bin_to_dec(rules[i].source, 0);
        int src_end = bin_to_dec(rules[i].source, 1);
        int des_start = bin_to_dec(rules[i].des, 0);
        int des_end = bin_to_dec(rules[i].des, 1);
        for(int x = src_start; x <= src_end; x++)
        {
            for(int y = des_start; y <= des_end; y++)
            {
                if(rule_table[x][y] == 0)
                    rule_table[x][y] = i ;
            }
        }
    }
}

char *intersection(char s[], char h[]) //兩個路徑交會時找小的那個並回傳
{
    int s_len = strlen(s), h_len = strlen(h);
    if(s_len < h_len)
        return h;
    if(s_len > h_len)
        return s;
    if(s[s_len - 1] == '*')
        return h;
    if(h[h_len - 1] == '*')
        return s;
    return s;
}

void shortest_path(int num_of_switch)//dijkstra
{
    for(int counter = 0; counter<num_of_switch; counter++)
    {
        int cur_node = -1;
        for(int i=0;i<num_of_switch ; i++)
        {
            if(nodes[i].arrived != 0)
                continue;
            if(cur_node == -1)
                cur_node = i;
            else if(nodes[i].distance < nodes[cur_node].distance)
                cur_node = i;
            else if(nodes[i].distance == nodes[cur_node].distance && nodes[i].hop < nodes[cur_node].hop)
                cur_node = i;
            else if(nodes[i].distance == nodes[cur_node].distance && nodes[i].hop == nodes[cur_node].hop)
            {
                int anc_i = i;
                int anc_cur = cur_node;
                int result;
                while(nodes[anc_i].parent != -1 && nodes[anc_cur].parent != -1)
                {
                    if(anc_i != anc_cur)
                        result = anc_i < anc_cur;

                    anc_i = nodes[anc_i].parent;
                    anc_cur = nodes[anc_cur].parent;
                }
                if( result )
                    cur_node = i;
            }
        }
        nodes[cur_node].arrived = 1;
        for(int i = 0; i<nodes[cur_node].num_neighbor;i++)
        {
            int update = 0;
            int neighbor = nodes[cur_node].neighbor[i][0];
            int w = nodes[cur_node].neighbor[i][1];
            /*是否需要更新*/
            if(nodes[neighbor].distance > nodes[cur_node].distance + w)
                update = 1;
            else if(nodes[neighbor].distance == nodes[cur_node].distance + w && nodes[neighbor].hop > nodes[cur_node].hop + 1)
                update = 1;
            else if (nodes[neighbor].distance == nodes[cur_node].distance + w && nodes[neighbor].hop == nodes[cur_node].hop +1)
            {
                int anc_neighbor = nodes[neighbor].parent;
                int anc_cur = cur_node;
                int result;
                while(nodes[anc_neighbor].parent != -1 && nodes[anc_cur].parent != -1)
                {
                    if(anc_neighbor != anc_cur)
                        result = anc_neighbor > anc_cur;

                    anc_neighbor = nodes[anc_neighbor].parent;
                    anc_cur = nodes[anc_cur].parent;
                }
                if( result )
                    update = 1;
            }
            if(update)
            {
                nodes[neighbor].distance = nodes[cur_node].distance +w;
                nodes[neighbor].hop = nodes[cur_node].hop +1;
                nodes[neighbor].parent = cur_node;
            }
        }
    }
}

void cut_table(int find_path[], int num_find_path, int bits_pow_2)
{
    for(int i = 0;i < num_find_path ; i++)
    {
        int cur_swi = find_path[i]; // capacity = switch_size[cur_swi]
        Q q;
        q_initial(&q);
        q.utility = -1e9 ;//一開始把utility設置成極小，這樣就一定會被取代

        for(int x_len = 1; x_len <= bits_pow_2 ; x_len *= 2 )//*=2是因為每次去檢查都是2的指數形式，ex:1.2.4.8
        {
            for(int y_len = 1 ; y_len <= bits_pow_2 ; y_len *= 2)//這邊的*=2也是一樣的
            {
                for(int x = 0 ; x < bits_pow_2 ; x += x_len) //去檢查要切割的rule的x長度
                {
                    for(int y = 0 ; y < bits_pow_2 ; y += y_len)//切割的y長度
                    {
                        //size: x_len * y_len, (x, y)
                        //x ~ x + x_len - 1，y ~ y +y_len - 1
                        Q tmp;//宣告一個分割用的Q
                        q_initial(&tmp);
                        tmp.x = x, tmp.y = y, tmp.lengh_x = x_len, tmp.lengh_y = y_len;
                        for( int k =1; k <= num_rule ; k++)
                        {
                            int src_start = bin_to_dec(rules[k].source, 0);//因為要去對照著建出來的表，因此要10進位化
                            int src_end = bin_to_dec(rules[k].source, 1);
                            int des_start = bin_to_dec(rules[k].des, 0);
                            int des_end = bin_to_dec(rules[k].des, 1);
                            int inside = 0, outside = 0;
                            for(int rule_x = src_start ; rule_x <=src_end ; rule_x ++)
                            {
                                for(int rule_y = des_start ; rule_y <= des_end ; rule_y++)
                                {
                                    if(x <= rule_x && rule_x <= x + x_len - 1 && y <= rule_y && rule_y <= y + y_len -1)
                                    {
                                        if(rule_table[rule_x][rule_y] == k)//如果此rule能被完全包刮，inside 1
                                            inside = 1;
                                    }
                                    else
                                        outside = 1;//不能被完全包刮，outside = 1
                                }
                            }

                            if(inside)
                            {
                                tmp.q_rule[tmp.q_num_rule++] = k;//使q記住裡面有這個rule
                            }
                            if(inside == 1 && outside == 0)
                            {
                                //internal
                                tmp.inter_rule[tmp.num_internal++] = k; //被Q完全包刮的成員之一
                            }
                            else if(inside == 1&& outside ==1)
                            {
                                //overlapping
                                tmp.num_overlapping++;//沒有被完全包刮的情況下，overlapping數++
                            }
                        }
                        if(tmp.q_num_rule > nodes[cur_swi].capacity)
                            continue;//如果這個switch放不下這個Q，找下一個

                        int need_replace = 0;//檢查原本的Q是否要被更新
                        tmp.utility = (tmp.num_internal - 1.0) / (tmp.num_overlapping + 1.0);
                        if(tmp.utility <= 0)//如果utinity<=0, 那可能是已經分割完了
                            continue;

                        if(fabs(q.utility - tmp.utility) >1e-6)//因為可能有小數點誤差(utinity並非整數)
                        {
                            if(q.utility < tmp.utility)//目前找到的q的utiniy如果大於目前選的, 更新
                                need_replace = 1;
                        }
                        else if(q.num_internal != tmp.num_internal)
                        {
                            if(q.num_internal < tmp.num_internal)//utinity一樣的情況，比internal數量
                                need_replace = 1;
                        }
                        else if(q.lengh_x * q.lengh_y !=tmp.lengh_x * tmp.lengh_y)
                        {
                            if(q.lengh_x * q.lengh_y > tmp.lengh_x * tmp.lengh_y)
                                need_replace = 1;//上述兩個一樣，就比較Q面積
                        }
                        else
                        {
                            for(int k = 0;k < q.num_internal; k++)
                            {
                                if(q.inter_rule[k] != tmp.inter_rule[k])
                                {
                                    if(q.inter_rule[k] >tmp.inter_rule[k])
                                        need_replace = 1;//如果還是一樣，比誰的rule編號是比較小的
                                    break ;
                                }
                            }
                        }
                        if(need_replace)//取代
                        {
                            q.x =x;
                            q.y =y;
                            q.lengh_x = x_len;
                            q.lengh_y = y_len;
                            q.utility = tmp.utility;
                            q.num_internal = tmp.num_internal;
                            q.num_overlapping = tmp.num_overlapping;
                            q.q_num_rule = tmp.q_num_rule;

                            for(int k = 0;k < tmp.num_internal;k++)
                                q.inter_rule[k] = tmp.inter_rule[k];
                            for(int k = 0;k < tmp.q_num_rule ; k++)
                                q.q_rule[k] = tmp.q_rule[k];
                        }
                    }
                }
            }
        }
        printf("%d %d\n", cur_swi, q.q_num_rule);
        char *q_src = dec_to_bin(q.x, q.lengh_x);//要印出來，所以要把他轉回到2進位的表示
        char *q_des = dec_to_bin(q.y, q.lengh_y);
        for(int k = 0;k < q.q_num_rule;k++)
        {
            int index = q.q_rule[k];
            printf("%s %s %s\n", intersection(rules[index].source, q_src), intersection(rules[index].des, q_des), rules[index].action);
        }
        strcpy(rules[0].source, q_src);
        strcpy(rules[0].des, q_des);
        strcpy(rules[0].action, "Fwd");
        num_rule++;
        for(int k = num_rule;k >=1;k--)//因為已經有了一個Q，所以把後面的rule往前推
        {
            strcpy(rules[k].source, rules[k-1].source);
            strcpy(rules[k].des, rules[k-1].des);
            strcpy(rules[k].action, rules[k-1].action);
        }
        build_table();//然後再次建表
        // print_table();
    }
}
int main()
{
    /*          進行數據輸入            */
    int ingressid1, egressid2, num_switch, num_link, switchid1, switchid2, weight;
    scanf("%d", &bits);
    scanf("%d%d", &ingressid1, &egressid2);
    scanf("%d", &num_switch);
    for(int i=0;i<num_switch;i++)
    {
        scanf("%d", &nodes[i].id);
        scanf("%d", &nodes[i].capacity);
        nodes[i].num_neighbor = 0;
    }

    scanf("%d", &num_link);
    for(int i=0;i<num_link;i++)
    {
        scanf("%d", &switchid1);
        scanf("%d", &switchid2);
        nodes[switchid1].neighbor[nodes[switchid1].num_neighbor][0] = switchid2;
        nodes[switchid2].neighbor[nodes[switchid2].num_neighbor][0] = switchid1;
        scanf("%d", &weight);
        nodes[switchid1].neighbor[nodes[switchid1].num_neighbor][1] = weight;
        nodes[switchid2].neighbor[nodes[switchid2].num_neighbor][1] = weight;
        nodes[switchid1].num_neighbor++;
        nodes[switchid2].num_neighbor++;
    }

    scanf("%d", &num_rule);
    for(int i=1;i<=num_rule;i++)
    {
        scanf("%s", rules[i].source);
        scanf("%s", rules[i].des);
        scanf("%s", rules[i].action);
    }

    /*          找最短路徑       */
    for(int i=0;i<num_switch;i++)//初始化nodes
    {
        nodes[i].arrived = 0;
        nodes[i].parent = -1;
        nodes[i].distance = 1e9;
        nodes[i].hop = 1e9;
    }

    nodes[ingressid1].distance = 0;//將開頭的distance以及hop數歸0
    nodes[ingressid1].hop = 0;

    shortest_path(num_switch);

    int change_p[num_switch], path[num_switch], time = 0;
    int change = egressid2;
    while(change != -1)//把目前找到的最短路徑存起來
    {
        change_p[time] = change;
        time++;
        change = nodes[change].parent;
    }
    int time1 = time - 1 ;
    for(int i = 0;i <time; i++)
    {
        path[i]=change_p[time1];
        time1--;
    }

    build_table();

    int bits_pow_2 = calculus(bits);//size of table
    printf("%d\n", time);

    cut_table(path, time, bits_pow_2);//開始把rule分到switch中

    return 0;
}
