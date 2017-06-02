/*
Họ và tên: Võ Sỹ Liên Thành
MSSV: 1512515

- Đồ án CTDL&GT: Chương trình quản lý tập tin, thư mục đơn giản.
*/
//Lớp cây Huffman.

#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <vector>
#include "HuffmanNode.h"
#include "SortAlgorithm.h"

#pragma pack(1)
class CHuffmanTree
{
protected:
	CHuffmanNode *pRoot;
public:
	//------------------------------NHÓM PHƯƠNG THỨC TẠO, HỦY------------------------------
	//Phương thức khởi tạo mặc định.
	CHuffmanTree();
	//Phương thức tạo cây Huffman từ danh sách các Node.
	CHuffmanTree(vector<CHuffmanNode*>);
	//Phương thức khởi tạo sao chép.
	CHuffmanTree(const CHuffmanTree&);
	//Phương thức hủy.
	~CHuffmanTree();

	//------------------------------NHÓM PHƯƠNG THỨC GET, SET------------------------------
	//Lấy pRoot.
	CHuffmanNode* getRoot() const;
	//Lấy pRoot.
	CHuffmanNode*& getRoot();

	//------------------------------NHÓM PHƯƠNG THỨC DUYỆT CÂY------------------------------
	//Phương thức duyệt cây trả về bảng code của ký tự.
	vector<string> GenerateCharCode() const;

	//------------------------------NHÓM PHƯƠNG THỨC TOÁN TỬ------------------------------
	//Toán tử gán =.
	CHuffmanTree& operator = (const CHuffmanTree&);
private:
	//------------------------------NHÓM PHƯƠNG THỨC HỔ TRỢ ẨN------------------------------
	//Hàm copy cây Huffman.
	void CopyHuffmanTree(CHuffmanNode*&, const CHuffmanNode*);
	//Hàm hủy cây.
	void DestroyHuffmanTree(CHuffmanNode*&);
	//Hàm duyệt cây tạo bảng mã.
	void genCharCode(const CHuffmanNode*, vector<string>&, string = "") const;
};
#endif