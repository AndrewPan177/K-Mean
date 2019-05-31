// K-mean.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "math.h"
#include "malloc.h"
#pragma warning(disable:4996)

struct sample {
	double x1; double x2;
};

int m, n;

//确立新的聚类中心
void Update(sample *x, int *G, sample *z, int N) {
	double sum1 = 0.0, sum2 = 0.0;
	for (int i = 0; i < N; i++) {
		sum1 += x[G[i]].x1;
		sum2 += x[G[i]].x2;
	}
	z[1].x1 = sum1 / N;
	z[1].x2 = sum2 / N;
}

//相减,进行分类
void Subtract(sample *x, sample *z1, sample *z2, int *G1, int*G2, int &p, int &q) {
	printf("\n"); 
	
	for (int i = 0; i < 20; i++) {
		if ((fabs(x[i].x1 - z1[0].x1) + fabs(x[i].x2 - z1[0].x2)) < (fabs(x[i].x1 - z2[0].x1) + fabs(x[i].x2 - z2[0].x2))) {
			G1[p] = i;
			//printf("G1[%d]=%d i=%d\n", p, G1[p],i);
			p++;	
		}
		else {
			G2[q] = i;
			//printf("G2[%d]=%d i=%d\n", q, G2[q], i);
			q++;
		}
	}
	//printf("p=%d\tq=%d\n", p, q);
}

//其中，z1[0],z2[0]均用来存储初始聚类中心，z1[1],z2[1]用来存储新的聚类中心
void K(sample *x, sample *z1, sample *z2) {

	int *G1 = (int*)malloc(25*sizeof(int));
	int *G2 = (int*)malloc(25*sizeof(int));
	int p = 0, q = 0, N1, N2;

	Subtract(x, z1, z2, G1, G2, p, q);
	N1 = p; N2 = q;

	printf("\n");
	Update(x, G1, z1, N1);
	Update(x, G2, z2, N2);

	//打印z1和z2
	printf("\n");
	for (int i = 0; i < 2; i++) {
		printf("z1[%d].x1=%.2lf\t z1[%d].x2=%.2lf\n", i, z1[i].x1, i, z1[i].x2);
		printf("z2[%d].x1=%.2lf\t z2[%d].x2=%.2lf\n", i, z2[i].x1, i, z2[i].x2);
	}

	printf("\n\n");

	//递归调用
	if (z1[0].x1 == z1[1].x1 && z1[0].x2 == z1[1].x2 && z2[0].x1 == z2[1].x1 && z2[0].x1 == z2[1].x1) {
		
		printf("G1:\t");
		for (int i = 0; i < N1; i++)
			printf("%d\t", G1[i] + 1);

		printf("\nG2:\t");
		for (int i = 0; i < N2; i++)
			printf("%d\t", G2[i] + 1);

		printf("\n分类完毕！\n");

		return;
	}
	else {
		//更新聚类中心
		z1[0].x1 = z1[1].x1;
		z1[0].x2 = z1[1].x2;
		z2[0].x1 = z2[1].x1;
		z2[0].x2 = z2[1].x2;
		z1[1].x1 = 0;
		z1[1].x2 = 0;
		z2[1].x1 = 0;
		z2[1].x2 = 0;

		free(G1); free(G2);
		K(x, z1, z2);
	}

	free(G1); free(G2);
	printf("\n");
}

int main()
{
	int a[40] = { 0,0,1,0,0,1,1,1,2,1,
				  1,2,2,2,3,2,6,6,7,6,
				  8,6,6,7,7,7,8,7,9,7,
				  7,8,8,8,9,8,8,9,9,9};
	sample x[20], z1[2], z2[2];

	int k = 0;
	for (int i = 0; i < 20; i++) {
		
			x[i].x1 = a[k];
			k++;
			x[i].x2 = a[k];
			k++;
	}

	printf("请输入初始聚类中心：");
	scanf("%d %d", &m, &n);

	//为初始聚类中心赋值
	z1[0].x1 = x[m].x1;
	z1[0].x2 = x[m].x2;
	z2[0].x1 = x[n].x1;
	z2[0].x2 = x[n].x2;

	K(x, z1, z2);

	printf("\n\n");
    return 0;
}

