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

void q_initial(Q *q) //rewrite�ɭԱN���l��
{
    q->num_internal = 0;
    q->num_overlapping = 0;
    q->q_num_rule = 0;
}

int calculus(int a)//���θ��|�ɨϥ�,�]������׬O1,2,4,8��2������
{
    return (1 << a);
}

int bin_to_dec(char tmp_s[], int status) //2�i��10�i��Astatus = 0�N��*�᭱��0�A1�N��᭱��1
{
    char s[10];
    strcpy(s, tmp_s);
    int len = strlen(s);
    if(s[len - 1] == '*') //��*�h��
    {
        s[len - 1] = '\0';
        len--;
    }
    int dif = bits - len;
    for(int i = 0;i < dif ; i++) //��*�᪺�Ʀr��
    {
        if(status == 0)
            strcat(s, "0");
        if(status == 1)
            strcat(s, "1");
    }
    int res = 0;

    for(int i = 0; i < bits; i++) //2�i���ন10�i��
    {
        res *= 2;
        res += (s[i] - '0');
    }
    return res ;
}

int my_log2(int number)//�⵹��bit��log
{
    int remain = 0;
    while(number != 1)
    {
        remain++;
        number /= 2;
    }
    return remain;
}
char *dec_to_bin(int num, int len)//10�i����2
{
    char *res = (char *)malloc(sizeof(char) * (10 + 5));
    int digit = (1 << (bits - 1));
    len = my_log2( len );
    for(int i = 0;i < bits - len; i++) //digit�|�Nnum���L
    {
        res[i] = ((num & (digit)) > 0) + '0'; //�ˬdnum������bit��0 or 1
        digit >>= 1;//�U�@���?
    }
    if( len > 0) //��*�����p
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

int rule_table[1024][1024]; //�ؤ@�Ӥ@�}�l��rule��
void print_table()//debud��
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
    for(int i = 0; i < 1024 ; i++)//���l��
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

char *intersection(char s[], char h[]) //��Ӹ��|��|�ɧ�p�����Өæ^��
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
            /*�O�_�ݭn��s*/
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
        q.utility = -1e9 ;//�@�}�l��utility�]�m�����p�A�o�˴N�@�w�|�Q���N

        for(int x_len = 1; x_len <= bits_pow_2 ; x_len *= 2 )//*=2�O�]���C���h�ˬd���O2�����ƧΦ��Aex:1.2.4.8
        {
            for(int y_len = 1 ; y_len <= bits_pow_2 ; y_len *= 2)//�o�䪺*=2�]�O�@�˪�
            {
                for(int x = 0 ; x < bits_pow_2 ; x += x_len) //�h�ˬd�n���Ϊ�rule��x����
                {
                    for(int y = 0 ; y < bits_pow_2 ; y += y_len)//���Ϊ�y����
                    {
                        //size: x_len * y_len, (x, y)
                        //x ~ x + x_len - 1�Ay ~ y +y_len - 1
                        Q tmp;//�ŧi�@�Ӥ��ΥΪ�Q
                        q_initial(&tmp);
                        tmp.x = x, tmp.y = y, tmp.lengh_x = x_len, tmp.lengh_y = y_len;
                        for( int k =1; k <= num_rule ; k++)
                        {
                            int src_start = bin_to_dec(rules[k].source, 0);//�]���n�h��ӵ۫إX�Ӫ���A�]���n10�i���
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
                                        if(rule_table[rule_x][rule_y] == k)//�p�G��rule��Q�����]��Ainside 1
                                            inside = 1;
                                    }
                                    else
                                        outside = 1;//����Q�����]��Aoutside = 1
                                }
                            }

                            if(inside)
                            {
                                tmp.q_rule[tmp.q_num_rule++] = k;//��q�O��̭����o��rule
                            }
                            if(inside == 1 && outside == 0)
                            {
                                //internal
                                tmp.inter_rule[tmp.num_internal++] = k; //�QQ�����]���������@
                            }
                            else if(inside == 1&& outside ==1)
                            {
                                //overlapping
                                tmp.num_overlapping++;//�S���Q�����]�����p�U�Aoverlapping��++
                            }
                        }
                        if(tmp.q_num_rule > nodes[cur_swi].capacity)
                            continue;//�p�G�o��switch�񤣤U�o��Q�A��U�@��

                        int need_replace = 0;//�ˬd�쥻��Q�O�_�n�Q��s
                        tmp.utility = (tmp.num_internal - 1.0) / (tmp.num_overlapping + 1.0);
                        if(tmp.utility <= 0)//�p�Gutinity<=0, ���i��O�w�g���Χ��F
                            continue;

                        if(fabs(q.utility - tmp.utility) >1e-6)//�]���i�঳�p���I�~�t(utinity�ëD���)
                        {
                            if(q.utility < tmp.utility)//�ثe��쪺q��utiniy�p�G�j��ثe�諸, ��s
                                need_replace = 1;
                        }
                        else if(q.num_internal != tmp.num_internal)
                        {
                            if(q.num_internal < tmp.num_internal)//utinity�@�˪����p�A��internal�ƶq
                                need_replace = 1;
                        }
                        else if(q.lengh_x * q.lengh_y !=tmp.lengh_x * tmp.lengh_y)
                        {
                            if(q.lengh_x * q.lengh_y > tmp.lengh_x * tmp.lengh_y)
                                need_replace = 1;//�W�z��Ӥ@�ˡA�N���Q���n
                        }
                        else
                        {
                            for(int k = 0;k < q.num_internal; k++)
                            {
                                if(q.inter_rule[k] != tmp.inter_rule[k])
                                {
                                    if(q.inter_rule[k] >tmp.inter_rule[k])
                                        need_replace = 1;//�p�G�٬O�@�ˡA��֪�rule�s���O����p��
                                    break ;
                                }
                            }
                        }
                        if(need_replace)//���N
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
        char *q_src = dec_to_bin(q.x, q.lengh_x);//�n�L�X�ӡA�ҥH�n��L��^��2�i�쪺���
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
        for(int k = num_rule;k >=1;k--)//�]���w�g���F�@��Q�A�ҥH��᭱��rule���e��
        {
            strcpy(rules[k].source, rules[k-1].source);
            strcpy(rules[k].des, rules[k-1].des);
            strcpy(rules[k].action, rules[k-1].action);
        }
        build_table();//�M��A���ت�
        // print_table();
    }
}
int main()
{
    /*          �i��ƾڿ�J            */
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

    /*          ��̵u���|       */
    for(int i=0;i<num_switch;i++)//��l��nodes
    {
        nodes[i].arrived = 0;
        nodes[i].parent = -1;
        nodes[i].distance = 1e9;
        nodes[i].hop = 1e9;
    }

    nodes[ingressid1].distance = 0;//�N�}�Y��distance�H��hop���k0
    nodes[ingressid1].hop = 0;

    shortest_path(num_switch);

    int change_p[num_switch], path[num_switch], time = 0;
    int change = egressid2;
    while(change != -1)//��ثe��쪺�̵u���|�s�_��
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

    cut_table(path, time, bits_pow_2);//�}�l��rule����switch��

    return 0;
}
