//�t�H�[�h�t�@���J�[�\���@

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 6 //���_��
#define TRUE 1
#define FALSE 0
#define S 0 //�\�[�X
#define T 5 //�V���N
#define INF 10000000

int flag[N];

int C[N][N] = {0}; //�e�ʍs��

// �����̏���������Ԃ�
int min(int a, int b);

//s����t�ֈړ��\�Ȃ炻�̃��[�g�̍ő嗬�ʂ�Ԃ��A�s�\�Ȃ�0��Ԃ��B
int DFS(int v, int t, int f);

//s����t�ւ̍ő嗬�ʂ�Ԃ��B
int max_flow(int s, int t);

int main()
{
    // int edge = 0;
    unsigned int seed;

    /* ���ݎ��������� seed ������*/
    seed = (unsigned)time(NULL);
    srand(seed);

    //���_�Ԃ̗��ʂ����肷��
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (rand() % 2 == 1) //�l�b�g���[�NG�̕�ij���q�������߂�
            {
                C[i][j] = rand() % 10 + 1;
                // edge++;
            }
        }
    }

    // printf("�ӁF%d\n", edge);
    // clock_t start, end;
    // start = clock();
    printf("�ő嗬�ʁF%d\n", max_flow(S, T));
    // end = clock();
    // printf("%.2f�b������܂���\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int min(int a, int b)
{
    return a < b ? a : b;
}

//s����t�ֈړ��\�Ȃ炻�̃��[�g�̍ő嗬�ʂ�Ԃ��A�s�\�Ȃ�0��Ԃ��B
int DFS(int v, int t, int f)
{
    printf("%d ", v);

    if (v == t) //�\�[�X�ƃV���N����v������
        return f;

    printf("�� ");
    flag[v] = TRUE;
    for (int i = 0; i < N; i++)
    {
        if (flag[i] == FALSE && C[v][i] > 0)
        {
            int d = DFS(i, t, min(f, C[v][i]));
            if (d > 0)
            {
                //�e�ʍs����X�V(�c�]�l�b�g���[�N���쐬)
                C[v][i] -= d;
                C[i][v] += d;
                return d;
            }
        }
    }
    return 0;
}

//s����t�ւ̍ő嗬�ʂ�Ԃ��B
int max_flow(int s, int t)
{
    int flow = 0;
    for (;;)
    {
        // flag��������
        memset(flag, FALSE, sizeof(flag));
        int f = DFS(s, t, INF);
        printf("���ʁF%d\n", f);
        if (f == 0)
            return flow;
        flow += f;
    }
}

// http://even-eko.hatenablog.com/entry/2013/08/08/195120