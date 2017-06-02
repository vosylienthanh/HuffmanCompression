/*
Họ và tên: Võ Sỹ Liên Thành
MSSV: 1512515

- Đồ án CTDL&GT: Chương trình quản lý tập tin, thư mục đơn giản.
*/
//Lớp thực hiện nén Huffman.
/*
 * Cấu trúc header file nén:
 *		Số lượng bit làm tròn	(1 Byte).
 *		Số lượng ký tự			(2 Byte).
 *		Bảng ký tự và tần số	(1 Byte cho ký tự - 4 byte cho tần số (unsigned long))
 * Cấu trúc phần nội dung:
 *		|phần bit làm tròn||phần nội dung thực tế|
*/

#ifndef _HUFFMAN_CODING_H_
#define _HUFFMAN_CODING_H_

#include <fstream>
#include <string>
#include "HuffmanTree.h"

#pragma pack(1)
class CHuffmanCoding
{
private:
	CHuffmanCoding();
	~CHuffmanCoding();
public:
	//------------------------------NHÓM PHƯƠNG THỨC TƯƠNG TÁC VỚI FILE------------------------------
	//*****************************************PHA NÉN*****************************************
	//Hàm đọc file trả về danh sách các node của cây Huffman.
	static vector<CHuffmanNode*> CreateListNode(const string&);
	//Phương thức nén file trả về hệ số nén file.
	static float Compress(const string&, const string&);

	//*****************************************PHA GIẢI NÉN*****************************************
	//Hàm đọc phần Header file nén trả về danh sách các Node của cây Huffman đồng thời trả về số bit đã được thêm vào để làm tròn.
	static vector<CHuffmanNode*> ReadHeader(ifstream&, char&);
	//Phương thức giải nén file.
	static void deCompress(const string&, const string&);
	
private:
	//------------------------------NHÓM PHƯƠNG THỨC HỖ TRỢ ẨN------------------------------
	//Phương thức tính dung lượng sau khi nén.
	static unsigned long calcZiseAfterCompress(const vector<CHuffmanNode*>&, const vector<string>&);
	//Phương thức ghi Header của file nén.
	static void WriteHeader(ofstream&, const char&, const vector<CHuffmanNode*>&);
};
#endif