#include <iostream>

using namespace std;

/*
 *@brief 数据比较函数
 *@param
	key1：数据1
	key2：数据2
 *@retval key1>key2 1;key1==key2 0 ;key1<key2 -1
		  
*/
int data_compare(const void*key1, const void*key2)
{
	int *data1 = (int *)key1;
	int *data2 = (int *)key2;

	if ((*data1) > (*data2))
	{
		return 1;
	}
	else if ((*data1) == (*data2))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/*
 *@brief 插入排序算法函数
 *@param
	data:要排序的数组首地址
	size:数组元素的个数
	esize:每个元素占有的字节数
	compare:数据比较函数
 *@retval none
*/
void insert_sort(void *data, int size, int esize, int (*compare)(const void*key1, const void*key2))
{
	char *dat = (char *)data;
	void *key = nullptr;       //用来存放当前交换的数据
	int i, j;

	/*为当前交换的数据开辟一个内存空间*/
	key = (char *)malloc(esize);
	if (key == nullptr)
	{
		cout << "malloc esize error" << endl;
		return;
	}

	/*
		整个思想如下：
		j代表当前要进行排序的目标数组元素的下标地址，j前面的元素都是有序的，j是有序数据和无序数据的分界
		j前面的元素从后到前和j元素比较大小，如果当前的元素比j元素的值大，那么
		就将数据向后移动，为目标元素留下插入的位置，如果比j元素小，那么结束查询
		循环结束的时候，就可以把数据插入到当前结束的位置
		当j到达数组末尾的时候，数组就排序好了
	*/
	for (j = 1; j < size; j++)
	{
		memcpy(key,&dat[j*esize], esize);
		i = j - 1;        //i代表当前有序数据的下标

		while ((i >= 0) && (compare(&dat[i*esize], key) > 0))
		{
			/*后移数据*/
			memcpy(&dat[(i+1)*esize], &dat[i*esize], esize);
			i--;
		}
		/*插入数据到正确的位置*/
		memcpy(&dat[(i + 1)*esize], key, esize);
	}

	/*释放内存空间*/
	free(key);
}

int main(void)
{
	int dat[10] = {5,4,3,2,1,10,9,8,7,5};

	insert_sort(dat,10,sizeof(int), data_compare);

	for (int i = 0; i < 10; i++)
	{
		cout << dat[i] << " ";
	}
	cout << endl;

	return 0;
}