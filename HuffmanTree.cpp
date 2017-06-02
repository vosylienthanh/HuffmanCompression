/*
Họ và tên: Võ Sỹ Liên Thành
MSSV: 1512515

- Đồ án CTDL&GT: Chương trình quản lý tập tin, thư mục đơn giản.
*/
//Lớp cây Huffman.

#include "HuffmanTree.h"

//------------------------------NHÓM PHƯƠNG THỨC TẠO, HỦY------------------------------
//Phương thức khởi tạo mặc định.
CHuffmanTree::CHuffmanTree()
{
	this->pRoot = NULL;
}

//Phương thức tạo cây Huffman từ danh sách các Node.
CHuffmanTree::CHuffmanTree(vector<CHuffmanNode*> Forest)
{
	CHuffmanNode *pNode;
	int Left, Right;

	while (Forest.size() > 1)
	{
		//Sắp xếp rừng.
		CSortAlgorithm<vector<CHuffmanNode*>, CHuffmanNode*>::HeapSort(Forest, CHuffmanNode::cmpFunction, Forest.size());
		Left = Forest.size() - 1;
		Right = Forest.size() - 2;

		//Tạo cây mới.
		pNode = new CHuffmanNode(Forest[Left]->getString() + Forest[Right]->getString(), Forest[Left]->getFrequency() + Forest[Right]->getFrequency(), Forest[Left], Forest[Right]);
		Forest.pop_back(); //Bỏ cây cũ.
		//thâm cây mới vào cuối.
		Forest[Right] = pNode;
	}

	this->pRoot = Forest[0];
}

//Phương thức khởi tạo sao chép.
CHuffmanTree::CHuffmanTree(const CHuffmanTree &HuffmanTree)
{
	CopyHuffmanTree(this->pRoot, HuffmanTree.pRoot);
}

//Phương thức hủy.
CHuffmanTree::~CHuffmanTree()
{
	this->DestroyHuffmanTree(this->pRoot);
}

//------------------------------NHÓM PHƯƠNG THỨC GET, SET------------------------------
//Lấy pRoot.
CHuffmanNode* CHuffmanTree::getRoot() const
{
	return this->pRoot;
}

//Lấy pRoot.
CHuffmanNode*& CHuffmanTree::getRoot()
{
	return this->pRoot;
}

//------------------------------NHÓM PHƯƠNG THỨC DUYỆT CÂY------------------------------
//Phương thức duyệt cây trả về bảng code của ký tự.
vector<string> CHuffmanTree::GenerateCharCode() const
{
	vector<string> ListCode(UCHAR_MAX + 1);
	this->genCharCode(this->pRoot, ListCode);
	
	return ListCode;
}

//------------------------------NHÓM PHƯƠNG THỨC TOÁN TỬ------------------------------
//Toán tử gán =.
CHuffmanTree& CHuffmanTree::operator = (const CHuffmanTree &Src)
{
	if (this != &Src)
	{
		this->DestroyHuffmanTree(this->pRoot);
		this->pRoot = NULL;
		this->CopyHuffmanTree(this->pRoot, Src.pRoot);
	}

	return *this;
}

//------------------------------NHÓM PHƯƠNG THỨC HỔ TRỢ ẨN------------------------------
//Hàm copy cây Huffman.
void CHuffmanTree::CopyHuffmanTree(CHuffmanNode* &pRoot, const CHuffmanNode *Src)
{
	if (Src != NULL)
	{
		pRoot = new CHuffmanNode(*Src);
		CopyHuffmanTree(pRoot->getpLeft(), Src->getpLeft());
		CopyHuffmanTree(pRoot->getpRight(), Src->getpRight());
	}
}

//Hàm hủy cây.
void CHuffmanTree::DestroyHuffmanTree(CHuffmanNode* &pRoot)
{
	if (pRoot != NULL)
	{
		this->DestroyHuffmanTree(pRoot->getpLeft());
		this->DestroyHuffmanTree(pRoot->getpRight());
		delete pRoot;
		pRoot = NULL;
	}
}

//Hàm duyệt cây tạo bảng mã.
void CHuffmanTree::genCharCode(const CHuffmanNode *pRoot, vector<string> &ListCode, string Temp) const
{
	if (pRoot != NULL && pRoot->getpLeft() == NULL && pRoot->getpRight() == NULL)
	{
		ListCode[(unsigned char)pRoot->getString()[0]] = Temp;
	}
	else
	{
		Temp.push_back('0');
		genCharCode(pRoot->getpLeft(), ListCode, Temp);
		Temp.pop_back();

		Temp.push_back('1');
		genCharCode(pRoot->getpRight(), ListCode, Temp);
		Temp.pop_back();
	}
}