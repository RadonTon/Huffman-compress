
#include <iostream>
#include "Compress.h"
#include"Huffman.h"
using namespace std;
 
int main()
{
    system("chcp 65001");
	cout << "=========Huffman文件压缩=======" << endl;
	cout << "请输入文件名：";
	char filename[256];
	cin >> filename;
	if (Compress(filename) == 1) {
		cout << "\n压缩完成！" << endl;
	}
	else {
		cout << "\n压缩失败" << endl;
	}
    return 0;
}