#include<iostream>
using namespace std;

struct NumwithNode{
	int num;
	int start;
	int end;
};/*设置一个保存最大子列和和对应位置的结构*/

NumwithNode Max3(NumwithNode A, NumwithNode B, NumwithNode C)
{
	A.num > B.num ? A: A= B;
	A.num > C.num ? A : A = C;
	return A;
}
NumwithNode Addmy(NumwithNode a, NumwithNode b,int maxsum)
{
	NumwithNode c;
	if ((a.start==a.end)&(b.start==b.end))
	{
		c.num = 0;
		c.start = 0;
		c.end = maxsum;
		return c;
	}
	if (a.start==a.end)
	{
		return b;
	}
	if (b.start==b.end)
	{
		return a;
	}
	c.num = a.num + b.num;
	c.start = a.start;
	c.end = b.end;
	return c;
}
//尝试用nlogn复杂度的算法求解，未完成
NumwithNode Maxsub3(int list[], int left, int right)
{
	NumwithNode MaxLeftSum, MaxRightSum;
	NumwithNode MaxLeftBorderSum, MaxRightBorderSum,BordenSum;
	NumwithNode Leastnum;
	NumwithNode LeftBorderSum, RightBorderSum;
	int center, i;
	if (left == right)
	{
		if (list[left] > 0) {
			Leastnum.num = list[left];
			Leastnum.start = left;
			Leastnum.end = left;
			return Leastnum;
		}
		else {
			Leastnum.num = 0;
			Leastnum.start = left;
			Leastnum.end = left;
			return Leastnum;
		}
	}

	center = (left + right) / 2;
	MaxLeftSum = Maxsub3(list, left, center);
	MaxRightSum = Maxsub3(list, center+1, right);

	MaxLeftBorderSum.num = 0; LeftBorderSum.num = 0;
	MaxLeftBorderSum.start = MaxLeftBorderSum.end = center;
	LeftBorderSum.start = LeftBorderSum.end = center;
	for (i = center; i >= left; i--)
	{
		LeftBorderSum.num += list[i];
		LeftBorderSum.start = i;
		if (LeftBorderSum.num>MaxLeftBorderSum.num)
		{
			MaxLeftBorderSum = LeftBorderSum;
		}
	}

	MaxRightBorderSum.num = 0; RightBorderSum.num = 0;
	MaxRightBorderSum.start = MaxRightBorderSum.end = center + 1;
	RightBorderSum.start = RightBorderSum.end = center + 1;
	for (i = center + 1; i <= right; i++) { /* 从中线向右扫描 */
		RightBorderSum.num += list[i];
		RightBorderSum.end = i;
		if (RightBorderSum.num > MaxRightBorderSum.num)
			MaxRightBorderSum = RightBorderSum;
	} /* 右边扫描结束 */
	
	BordenSum.num = MaxLeftBorderSum.num + MaxRightBorderSum.num;
	BordenSum.start = MaxLeftBorderSum.start;
	BordenSum.end = MaxRightBorderSum.end;
	BordenSum = Addmy(MaxLeftBorderSum, MaxRightBorderSum, right);
	return Max3(MaxLeftSum, MaxRightSum, BordenSum);
}
//尝试用n复杂度的算法求解，成功
NumwithNode Maxsub4(int a[], int n)
{	
	NumwithNode ThisSum, MaxSum;
	/*设置当前子列和和最大子列和*/
	ThisSum.num = 0; ThisSum.start = ThisSum.end = 0;
	MaxSum.num = 0; MaxSum.start =0, MaxSum.end = n-1;
	/*初始化两个数*/
	for (int i = 0; i < n; i++)
	{
		ThisSum.num += a[i];
		ThisSum.end = i;
		/*更新当前子列和的末尾*/
		if (ThisSum.num>MaxSum.num)
		{
			MaxSum = ThisSum;
			/*当当前子列和大于最大子列和时，更新最大子列和*/
		}
		else if (ThisSum.num==0&ThisSum.num==MaxSum.num)
		{
			MaxSum = ThisSum;
			/*当存在数组内只有负数和0时，0所在的位置就是最大子列和的首和尾*/
		}
		else if (ThisSum.num < 0)
		{
			ThisSum.num = 0;
			ThisSum.start = i + 1;
			/*当当前子列和为负数时，从新开始计算当前子列和并更新子列和的首位*/
		}
	}
	return MaxSum;
}

int main()
{
	int n;
	cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	NumwithNode result1;
	result1=Maxsub4(a,n);
	
	cout << result1.num << ' ' << a[result1.start] << ' ' << a[result1.end];
	delete[]a;
	return 0;
}
