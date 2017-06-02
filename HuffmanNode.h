/*
Họ và tên: Võ Sỹ Liên Thành
MSSV: 1512515

- Đồ án CTDL&GT: Chương trình quản lý tập tin, thư mục đơn giản.
*/
//Lớp Node cây Huffman.

#ifndef _HUFFMAN_NODE_H_
#define _HUFFMAN_NODE_H_

#include <iostream>

using namespace std;

#pragma pack(1)
class CHuffmanNode
{
protected:
	string m_String;
	unsigned long m_Frequency;
	CHuffmanNode *pLeft;
	CHuffmanNode *pRight;
public:
	//------------------------------NHÓM PHƯƠNG THỨC TẠO, HỦY------------------------------
	//Phương thức khởi tạo mặc định.
	CHuffmanNode();
	//Phương thức tạo bằng cách truyền vào các đối số.
	CHuffmanNode(const string&, const unsigned long&, CHuffmanNode* = NULL, CHuffmanNode* = NULL);
	//Phương thức tạo bằng cách truyền vào các đối số.
	CHuffmanNode(const char&, const unsigned long&, CHuffmanNode* = NULL, CHuffmanNode* = NULL);
	//Phương thức tạo sao chép.
	CHuffmanNode(const CHuffmanNode&);
	//Phương thức hủy (không có chức năng gì đặc biệt).
	~CHuffmanNode();

	//------------------------------NHÓM PHƯƠNG THỨC GET, SET------------------------------
	//Lấy chuỗi.
	string getString() const;
	//Lấy tần số.
	unsigned long getFrequency() const;
	//Lấy con trái.
	CHuffmanNode* getpLeft() const;
	//Lấy con phải.
	CHuffmanNode* getpRight() const;
	//Lấy con trái.
	CHuffmanNode*& getpLeft();
	//Lấy con phải.
	CHuffmanNode*& getpRight();

	//------------------------------NHÓM PHƯƠNG THỨC TOÁN TỬ------------------------------
	//Toán tử gán.
	CHuffmanNode& operator = (const CHuffmanNode&);
	//Toán tử >.
	bool operator > (const CHuffmanNode&) const;
	//Toán tử <.
	bool operator < (const CHuffmanNode&) const;
	//Toán tử ==.
	bool operator == (const CHuffmanNode&) const;

	//------------------------------NHÓM PHƯƠNG THỨC KIỂM TRA------------------------------
	//Kiểm tra lá.
	bool isLeaf() const;

	//Phương thức so sánh.
	static bool cmpFunction(CHuffmanNode* const &, CHuffmanNode* const &);
};
#endif