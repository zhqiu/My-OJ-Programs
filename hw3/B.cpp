#include <stdio.h>
#include <vector>

int mid(int* a, int num)
{
	return a[(num-1)/2];
}

int midian(int* a, int* b, int num)
{
	if (num==1){
		if (a[0]>b[0])
			return b[0];
		else return a[0];
	}
	if (num==2){
		int cand_1=(a[0]>b[0])?a[0]:b[0];
		int cand_2=(a[1]<b[1])?a[1]:b[1];
		if (cand_1<cand_2) return cand_1;
		else return cand_2;
	}
	int a_mid=mid(a, num);
	int b_mid=mid(b, num);
	if (a_mid == b_mid)
		return a_mid;
	int len;
	if (num%2==0)
		len=(num/2)+1;
	else len=(num+1)/2;
	if (a_mid < b_mid){
		return midian(a+(num-1)/2, b, len);
	}
	else return midian(a, b+(num-1)/2, len);
}

int main(){
    int num;
    while(scanf("%d",&num) != EOF)
    {
    	int* a = new int[num];
    	int* b = new int[num];
    	for (int i=0;i<num;i++)
    		scanf("%d", &a[i]);
    	for (int i=0;i<num;i++)
    		scanf("%d", &b[i]);
    	printf("%d", midian(a, b, num));
	}
    return 0;
}
