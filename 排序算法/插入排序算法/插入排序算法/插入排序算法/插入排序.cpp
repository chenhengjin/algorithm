#include <iostream>

using namespace std;

/*
 *@brief ���ݱȽϺ���
 *@param
	key1������1
	key2������2
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
 *@brief ���������㷨����
 *@param
	data:Ҫ����������׵�ַ
	size:����Ԫ�صĸ���
	esize:ÿ��Ԫ��ռ�е��ֽ���
	compare:���ݱȽϺ���
 *@retval none
*/
void insert_sort(void *data, int size, int esize, int (*compare)(const void*key1, const void*key2))
{
	char *dat = (char *)data;
	void *key = nullptr;       //������ŵ�ǰ����������
	int i, j;

	/*Ϊ��ǰ���������ݿ���һ���ڴ�ռ�*/
	key = (char *)malloc(esize);
	if (key == nullptr)
	{
		cout << "malloc esize error" << endl;
		return;
	}

	/*
		����˼�����£�
		j����ǰҪ���������Ŀ������Ԫ�ص��±��ַ��jǰ���Ԫ�ض�������ģ�j���������ݺ��������ݵķֽ�
		jǰ���Ԫ�شӺ�ǰ��jԪ�رȽϴ�С�������ǰ��Ԫ�ر�jԪ�ص�ֵ����ô
		�ͽ���������ƶ���ΪĿ��Ԫ�����²����λ�ã������jԪ��С����ô������ѯ
		ѭ��������ʱ�򣬾Ϳ��԰����ݲ��뵽��ǰ������λ��
		��j��������ĩβ��ʱ��������������
	*/
	for (j = 1; j < size; j++)
	{
		memcpy(key,&dat[j*esize], esize);
		i = j - 1;        //i����ǰ�������ݵ��±�

		while ((i >= 0) && (compare(&dat[i*esize], key) > 0))
		{
			/*��������*/
			memcpy(&dat[(i+1)*esize], &dat[i*esize], esize);
			i--;
		}
		/*�������ݵ���ȷ��λ��*/
		memcpy(&dat[(i + 1)*esize], key, esize);
	}

	/*�ͷ��ڴ�ռ�*/
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