/*
Họ và tên: Võ Sỹ Liên Thành
MSSV: 1512515

- Đồ án CTDL&GT: Chương trình quản lý tập tin, thư mục đơn giản.
*/
//Lớp Node cây Huffman.

#include "HuffmanNode.h"

//------------------------------NHÓM PHƯƠNG THỨC TẠO, HỦY------------------------------
//Phương thức khởi tạo mặc định.
CHuffmanNode::CHuffmanNode()
{
	this->m_Frequency = 0;
	this->pLeft = this->pRight = NULL;
}

//Phương thức tạo bằng cách truyền vào các đối số.
CHuffmanNode::CHuffmanNode(const string &String, const unsigned long &Frequency, CHuffmanNode *Left, CHuffmanNode *Right)
{
	this->m_String = String;
	this->m_Frequency = Frequency;
	this->pLeft = Left;
	this->pRight = Right;
}

//Phương thức tạo bằng cách truyền vào các đối số.
CHuffmanNode::CHuffmanNode(const char &c, const unsigned long &Frequency, CHuffmanNode *Left, CHuffmanNode *Right)
{
	this->m_String.push_back(c);
	this->m_Frequency = Frequency;
	this->pLeft = Left;
	this->pRight = Right;
}

//Phương thức tạo sao chép.
CHuffmanNode::CHuffmanNode(const CHuffmanNode &Src)
{
	this->m_String = Src.m_String;
	this->m_Frequency = Src.m_Frequency;
	this->pLeft = this->pRight = NULL;
}

//Phương thức hủy (không có chức năng gì đặc biệt).
CHuffmanNode::~CHuffmanNode()
{
}

//------------------------------NHÓM PHƯƠNG THỨC GET, SET------------------------------
//Lấy chuỗi.
string CHuffmanNode::getString() const
{
	return this->m_String;
}

//Lấy tần số.
unsigned long CHuffmanNode::getFrequency() const
{
	return this->m_Frequency;
}

//Lấy con trái.
CHuffmanNode* CHuffmanNode::getpLeft() const
{
	return this->pLeft;
}

//Lấy con phải.
CHuffmanNode* CHuffmanNode::getpRight() const
{
	return this->pRight;
}

//Lấy con trái.
CHuffmanNode*& CHuffmanNode::getpLeft()
{
	return this->pLeft;
}

//Lấy con phải.
CHuffmanNode*& CHuffmanNode::getpRight()
{
	return this->pRight;
}

//------------------------------NHÓM PHƯƠNG THỨC TOÁN TỬ------------------------------
//Toán tử gán.
CHuffmanNode& CHuffmanNode::operator = (const CHuffmanNode &Node)
{
	if (this != &Node)
	{
		this->m_String = Node.m_String;
		this->m_Frequency = Node.m_Frequency;
		this->pLeft = Node.pLeft;
		this->pRight = Node.pRight;
	}

	return *this;
}

//Toán tử >.
bool CHuffmanNode::operator > (const CHuffmanNode &Node) const
{
	return (this->m_Frequency > Node.m_Frequency || (this->m_Frequency == Node.m_Frequency && strcmp(this->m_String.c_str(), Node.m_String.c_str()) > 0));
}

//Toán tử <.
bool CHuffmanNode::operator < (const CHuffmanNode &Node) const
{
	return (this->m_Frequency < Node.m_Frequency || (this->m_Frequency == Node.m_Frequency && this->m_String < Node.m_String));
}

//Toán tử ==.
bool CHuffmanNode::operator == (const CHuffmanNode &Node) const
{
	return (this->m_Frequency == Node.m_Frequency  && this->m_String == Node.m_String);
}

//------------------------------NHÓM PHƯƠNG THỨC KIỂM TRA------------------------------
//Kiểm tra lá.
bool CHuffmanNode::isLeaf() const
{
	return (this->pLeft == NULL && this->pRight == NULL);
}


//Phương thức so sánh.
bool CHuffmanNode::cmpFunction(CHuffmanNode* const &A, CHuffmanNode* const &B)
{
	return (*A < *B);
}