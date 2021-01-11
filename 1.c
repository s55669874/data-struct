#include<stdio.h>
#include<math.h>

struct node//每個點的值.座標以及鄰居數
{
    int ID;
    double x, y;
    int value;
    int neighbor[5001];
    int num_neighbor;
}nodes[5001];


double distance(double disX1, double disY1, double disX2, double disY2)//計算兩點距離, 用以判斷是否相連
{
    double difx=disX1-disX2;
    double dify=disY1-disY2;
    return sqrt((difx*difx)+(dify*dify));
}

void add_to_neighborlist(int person1, int person2)//假如兩點距離小於1,把彼此加到對方的鄰居列表裡面,並且鄰居數+1
{
    nodes[person1].neighbor[nodes[person1].num_neighbor]=person2;
    nodes[person2].neighbor[nodes[person2].num_neighbor]=person1;
    nodes[person1].num_neighbor++;
    nodes[person2].num_neighbor++;
}


int main()
{
    int node_number, round;
    scanf("%d %d", &node_number, &round);

    int token, token1;//2個計數器
    for(token=0;token<node_number;token++)//輸入每個點的數值以及初始化
    {
        scanf("%d %lf %lf %d",&nodes[token].ID, &nodes[token].x, &nodes[token].y, &nodes[token].value);
        nodes[token].num_neighbor=0;
    }

    for(token=0;token<node_number-1;token++)//判斷是否為鄰居,而後將其加入鄰居列表
    {
        for(token1=token+1;token1<node_number;token1++)
        {
            if(distance(nodes[token].x, nodes[token].y, nodes[token1].x, nodes[token1].y)<1)
            {
                add_to_neighborlist(nodes[token].ID, nodes[token1].ID);
            }
            else
                continue;
        }
    }

    int token_round, change_value;//回合計數器, 後面所需的改變數值的計數器

    double tempt_value[5000], old_value[5000];//記錄每一輪後改變的數值
    for(token=0;token<node_number;token++)//把原先的int轉變成double以方便處理
        old_value[token]=nodes[token].value;

    printf("%d %d\n", node_number, round);
    for(token=0;token<node_number;token++)//印出第一次的數值
       {
           printf("%.2f ", old_value[token]);
       }
    printf("\n");
    for(token_round=1;token_round<round;token_round++)
    {
            for(token=0;token<node_number;token++)//判斷完鄰居數量之後進行計算
        {
            double new_value=0, weight_total=0;
            for(token1=0;token1<nodes[token].num_neighbor;token1++)//對每個點的鄰居做計算, weight_total是用來計算他自己
            {
                if(nodes[token].num_neighbor>nodes[nodes[token].neighbor[token1]].num_neighbor)
                {
                    new_value+=old_value[nodes[token].neighbor[token1]]*(1.0/(2.0*nodes[token].num_neighbor));
                    weight_total+=1.0/(2*nodes[token].num_neighbor);
                }
                else
                {
                    new_value+=old_value[nodes[token].neighbor[token1]]*(1.0/(2.0*nodes[nodes[token].neighbor[token1]].num_neighbor));
                    weight_total+=1.0/(2*nodes[nodes[token].neighbor[token1]].num_neighbor);
                }
            }
            new_value+=old_value[token]*(1.0-weight_total);
            printf("%.2lf  ", new_value);
            tempt_value[token]=new_value;//因為此回合尚未結束,我們先把改變後的數值儲存起來
        }
        for(change_value=0;change_value<node_number;change_value++)
            {
                old_value[change_value]=tempt_value[change_value];//回合結束,把原本的數值改變為計算後的
            }
        printf("\n");
    }
    return 0;
}
