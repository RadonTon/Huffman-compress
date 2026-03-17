#include "Huffman.h"
#include<iostream>
#include<malloc.h>
#include<string.h>

 

 
using namespace std;
 
//生成Huffman树
int CreateHuffmanTree(HuffmanTree pHT,int weight[],int n){
	int s1, s2,i;
	int m = 2 * n - 1;
 
	for (i = 1; i <= n; i++) {
		pHT[i].weight = weight[i - 1];
		pHT[i].lchild = 0;
		pHT[i].rchild = 0;
		pHT[i].parent = 0;
	}
	for (i=n+1; i <= m; i++) {
		pHT[i].parent = 0;
		pHT[i].lchild = 0;
		pHT[i].rchild = 0;
		pHT[i].weight = 0;
	}

 
	for (i = n + 1; i <= m; i++)
	{

		Select(pHT, i - 1, s1, s2);
		pHT[s1].parent = i;
		pHT[s2].parent = i; //修改s1和s2结点的父指针parent
 
		pHT[i].lchild = s1;
		pHT[i].rchild = s2; //修改i结点的左右孩子指针
 
		pHT[i].weight = pHT[s1].weight + pHT[s2].weight; //修改权值
//		cout << "257以及以后 修改权值后的值：" << i << "\t" << pHT[i].weight << endl;
	}
 

	return 1;
}
 
 
// int CreateHuffmanTree(HuffmanTree &pHT, int w[], int n)
// {//w存放n个结点的权值，将构造一棵哈夫曼树pHT
// 	int i, m;
// 	int s1, s2;
 
 
// //	HuffmanTree p;
 
// 	m = 2 * n - 1; //n个叶子结点的哈夫曼树，有2*n-1个结点
// 	pHT = (HuffmanTree)malloc((m +1 ) * sizeof(HTNode)); //开辟2*n各结点空间,0号单元未用
 
// 	for ( i = 1; i <= n; ++i) //进行初始化
// 	{
// 		pHT[i].weight = w[i];
// 		pHT[i].parent = 0;
// 		pHT[i].lchild = 0;
// 		pHT[i].rchild = 0;
// 	}
// 	for (; i <= m; ++i)
// 	{
// 		pHT[i].weight = 0;
// 		pHT[i].parent = 0;
// 		pHT[i].lchild = 0;
// 		pHT[i].rchild = 0;
// 	}
 
 
// 	for (i = n + 1; i <= m; ++i) //建哈夫曼树
// 	{
// 		//从pHT[1...i-1]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
// 		Select(pHT, i - 1, s1, s2);
// 		pHT[s1].parent = i;
// 		pHT[s2].parent = i; //修改s1和s2结点的父指针parent
 
// 		pHT[i].lchild = s1;
// 		pHT[i].rchild = s2; //修改i结点的左右孩子指针
 
// 		pHT[i].weight = pHT[s1].weight + pHT[s2].weight; //修改权值
// 	}
// 	return 1;
// }
 
//查找H树节点数组中权值最小的节点

 
void Select(HuffmanTree &pHT, int i, int &s1, int &s2) {
	int minValue = 0x7FFFFFFF;
 
	//找到最小的一个权值
	for (int j = 1; j <= i; j++) {
		if (pHT[j].parent == 0 && pHT[j].weight<minValue) {
			minValue = pHT[j].weight;
			s1 = j;
		}
	}
//	cout << "最小权值：" << s1;
 
	minValue = 0x7FFFFFFF;
	//找到倒数第二小的权值
	for (int j = 1; j <= i; j++) {
		if (j != s1 && pHT[j].parent == 0 && pHT[j].weight < minValue) {
			minValue = pHT[j].weight;
			s2 = j;
		}
	}
;
}
 
int HuffmanCoding(HuffmanCode &pHC, HuffmanTree &pHT)//非递归实现
{

	char cd[256] = { '\0' };	//记录访问路径
	int cdlen = 0;				//记录当前路径长度
 
	for (int i = 1; i < 512; i++) {
		pHT[i].weight = 0;	//遍历Huffman树时用做节点的状态标志
	}
 
	int p = 511;		
	while (p != 0) {
		//左
		if (pHT[p].weight == 0) {
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0) {
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			//登记叶子节点的字符的编码
			else if(pHT[p].rchild==0){
				pHC[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p], cd);//复制编码
			}
		}
		//右
		else if (pHT[p].weight == 1) {
			pHT[p].weight = 2;
			//右孩子为叶子节点
			if (pHT[p].rchild != 0) {
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		//退回父节点，编码长度减一
		else {
			pHT[p].weight = 0;
			p = pHT[p].parent;
			cdlen--;
		}
	}
	return 1;
}
 
int TestHufTree(HuffmanTree pHT) {
	cout << "Byte\t\tWeight\tParent\tLchild\tRchild\n";
	for (int i = 1; i < 512; i++) {
		if (i <= 99) {
			cout << "pHT[" << i << "]\t\t" << pHT[i].weight << "\t" << pHT[i].parent << "\t" << pHT[i].lchild << "\t" << pHT[i].rchild << endl;
		}
		else {
			cout << "pHT[" << i << "]\t" << pHT[i].weight << "\t" << pHT[i].parent << "\t" << pHT[i].lchild << "\t" << pHT[i].rchild << endl;
		}
 
	}
	return 1;
}
 
void TestHufCode(int root, HuffmanTree &pHT, HuffmanCode &pHC) {
	if (root <= 1) return;
 
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
	{
		printf("0x%02X %s\n", root - 1, pHC[root - 1]);
	}
	if (pHT[root].lchild)//访问左孩子
	{
		TestHufCode(pHT[root].lchild, pHT, pHC);
	}
	if (pHT[root].rchild)//访问右孩子
	{
		TestHufCode(pHT[root].rchild, pHT, pHC);
	}
 
 
}