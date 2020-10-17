#include <stdio.h>
#include <math.h>

#include "miracl.h"

int main() {
	int k = 0;							//��ȫ������Security Parameter��
	int flag = 1;						//0 - ���� 1 - ����
	FILE* fp;
	miracl* mip = mirsys(1000, 0);
	char *mem = (char*)memalloc(6);
	big m = mirvar_mem(mem, 0);			//����������
	big a = mirvar_mem(mem, 1);			//��Χ���������
	big gcd = mirvar_mem(mem, 2);		//���Լ��
	big r = mirvar_mem(mem, 3);			//r = a^(m-1)(mod m)
	big one = mirvar_mem(mem, 4);		//big���͵�1
	convert(1, one);
	big temp = mirvar_mem(mem, 5);
	fp = fopen("number.txt", "r+");		//�Զ���ʽ���ļ�number.txt

	cinnum(m, fp);						//��fp�ж��������m
	printf("Input security parameter: ");
	scanf("%d", &k);					//���밲ȫ����k
	getchar();

	//Fermat���Լ���
	for (int i = 0; i < k; i++) {
		decr(m, 3, temp);				//temp = m - 3
		bigrand(temp, a);				//0 <= a <= m - 4
		incr(a, 2, a);					//a += 2, 2 <= a <= m - 2
		egcd(m, a, gcd);				//��m��a�����Լ��gcd
		if (mr_compare(gcd, one) != 0) {//�жϹ�Լ���Ƿ�Ϊ1
			flag = 0;
			printf("m is not a prime number.\n");
			break;
		}
		decr(m, 1, temp);				//temp = m - 1
		powmod(a, temp, m, r);			//r = a^(m - 1)(mod m)
		if (mr_compare(r, one) != 0) {	//�ж�ģm�����Ƿ�Ϊ1
			flag = 0;
			printf("m is not a prime number.\n");
			break;
		}
	}
	if (flag == 1) {
		printf("m is %10.8f%% likely to be a prime number.\n", 100 * (1 - pow(0.5, k)));
	}

	fclose(fp);
	mirexit();
	return 0;
}