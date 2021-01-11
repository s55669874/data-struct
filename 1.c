#include<stdio.h>
#include<math.h>

struct node//�C���I����.�y�ХH�ξF�~��
{
    int ID;
    double x, y;
    int value;
    int neighbor[5001];
    int num_neighbor;
}nodes[5001];


double distance(double disX1, double disY1, double disX2, double disY2)//�p����I�Z��, �ΥH�P�_�O�_�۳s
{
    double difx=disX1-disX2;
    double dify=disY1-disY2;
    return sqrt((difx*difx)+(dify*dify));
}

void add_to_neighborlist(int person1, int person2)//���p���I�Z���p��1,�⩼���[���誺�F�~�C��̭�,�åB�F�~��+1
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

    int token, token1;//2�ӭp�ƾ�
    for(token=0;token<node_number;token++)//��J�C���I���ƭȥH�Ϊ�l��
    {
        scanf("%d %lf %lf %d",&nodes[token].ID, &nodes[token].x, &nodes[token].y, &nodes[token].value);
        nodes[token].num_neighbor=0;
    }

    for(token=0;token<node_number-1;token++)//�P�_�O�_���F�~,�ӫ�N��[�J�F�~�C��
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

    int token_round, change_value;//�^�X�p�ƾ�, �᭱�һݪ����ܼƭȪ��p�ƾ�

    double tempt_value[5000], old_value[5000];//�O���C�@������ܪ��ƭ�
    for(token=0;token<node_number;token++)//������int���ܦ�double�H��K�B�z
        old_value[token]=nodes[token].value;

    printf("%d %d\n", node_number, round);
    for(token=0;token<node_number;token++)//�L�X�Ĥ@�����ƭ�
       {
           printf("%.2f ", old_value[token]);
       }
    printf("\n");
    for(token_round=1;token_round<round;token_round++)
    {
            for(token=0;token<node_number;token++)//�P�_���F�~�ƶq����i��p��
        {
            double new_value=0, weight_total=0;
            for(token1=0;token1<nodes[token].num_neighbor;token1++)//��C���I���F�~���p��, weight_total�O�Ψӭp��L�ۤv
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
            tempt_value[token]=new_value;//�]�����^�X�|������,�ڭ̥�����ܫ᪺�ƭ��x�s�_��
        }
        for(change_value=0;change_value<node_number;change_value++)
            {
                old_value[change_value]=tempt_value[change_value];//�^�X����,��쥻���ƭȧ��ܬ��p��᪺
            }
        printf("\n");
    }
    return 0;
}
