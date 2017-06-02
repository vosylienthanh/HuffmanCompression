/*
Họ và tên: Võ Sỹ Liên Thành
MSSV: 1512515

- Đồ án CTDL&GT: Chương trình quản lý tập tin, thư mục đơn giản.
*/
//Lớp thực hiện nén Huffman.

#include "HuffmanCoding.h"



CHuffmanCoding::CHuffmanCoding()
{
}


CHuffmanCoding::~CHuffmanCoding()
{
}

//------------------------------NHÓM PHƯƠNG THỨC TƯƠNG TÁC VỚI FILE------------------------------
//*****************************************PHA NÉN*****************************************
//Hàm đọc file trả về danh sách các node của cây Huffman.
vector<CHuffmanNode*> CHuffmanCoding::CreateListNode(const string &FileName)
{
	ifstream InFile(FileName, ios::in | ios::binary);
	vector<CHuffmanNode*> Forest;

	if (InFile)
	{
		CHuffmanNode *pTemp = NULL;
		char cTemp;
		vector<unsigned long> FreqTable;
		string ListChar;
		FreqTable.resize(UCHAR_MAX + 1);

		//Tạo bảng tấn số.
		while (InFile.read(&cTemp, sizeof(char)))
		{
			++FreqTable[(unsigned char)cTemp];
		}

		InFile.close();

		//Tạo danh sách Node.
		for (int i = 0; i <= UCHAR_MAX; i++)
		{
			if (FreqTable[i] > 0)
			{
				pTemp = new CHuffmanNode(i, FreqTable[i]);
				Forest.push_back(pTemp);
			}
		}
	}
	else
	{
		throw exception("Cannot open file!");
	}

	return Forest;
}

//Phương thức nén file trả về hệ số nén file.
float CHuffmanCoding::Compress(const string &inFileName, const string &outFileName)
{
	float CompressRate = 0;
	vector<CHuffmanNode*> Forest = CreateListNode(inFileName);
	CSortAlgorithm<vector<CHuffmanNode*>, CHuffmanNode*>::HeapSort(Forest, CHuffmanNode::cmpFunction, Forest.size());
	ifstream InFile(inFileName, ios::in | ios::binary);
	ofstream OutFile(outFileName, ios::out | ios::binary);

	if (InFile && OutFile)
	{
		CHuffmanTree HuffTree(Forest);
		vector<string> ListCode = HuffTree.GenerateCharCode();
		unsigned long sizeAfterCompress = calcZiseAfterCompress(Forest, ListCode);
		char RoundBitValue = CHAR_BIT - (sizeAfterCompress % CHAR_BIT);
		unsigned long Size = 0;
		char cTemp;
		char Bit = Bit ^ Bit;
		int Count = RoundBitValue;

		WriteHeader(OutFile, RoundBitValue, Forest);

		while (InFile.read(&cTemp, sizeof(char)))
		{
			for (int i = 0; i < ListCode[(unsigned char)cTemp].size(); i++)
			{
				Bit = Bit | (ListCode[(unsigned char)cTemp][i] - '0') << (CHAR_BIT - Count - 1);
				++Count;
				
				if (Count == CHAR_BIT)
				{
					OutFile.write(&Bit, sizeof(char));
					Bit = Bit ^ Bit;
					Count = Count ^ Count;
				}
			}
			Size = Size + 8;
		}

		CompressRate = 1 - ((1.0 * sizeAfterCompress) / Size);

		InFile.close();
		OutFile.close();
	}
	else
	{
		throw exception("Cannot open file!");
	}

	return CompressRate;
}

//*****************************************PHA GIẢI NÉN*****************************************
//Hàm đọc phần Header file nén trả về danh sách các Node của cây Huffman đồng thời trả về số bit đã được thêm vào để làm tròn.
vector<CHuffmanNode*> CHuffmanCoding::ReadHeader(ifstream &inStream, char &RoundBitValue)
{
	vector<CHuffmanNode*> Forest;
	
	if (inStream)
	{
		CHuffmanNode *pTemp = NULL;
		unsigned char cTemp;
		unsigned long Frequency;
		unsigned short NumOfChar;
		inStream.read(&RoundBitValue, sizeof(char));
		inStream.read(reinterpret_cast<char*>(&NumOfChar), sizeof(unsigned short));

		for (int i = 0; i < NumOfChar; i++)
		{
			inStream.read((char*)&cTemp, sizeof(char));
			inStream.read(reinterpret_cast<char*>(&Frequency), sizeof(unsigned long));
			pTemp = new CHuffmanNode(cTemp, Frequency);
			Forest.push_back(pTemp);
		}
	}

	return Forest;
}

//Phương thức giải nén file.
void CHuffmanCoding::deCompress(const string &inFileName, const string &outFileName)
{
	ifstream InFile(inFileName, ios::in | ios::binary);
	ofstream OutFile(outFileName, ios::out | ios::binary);

	if (InFile && OutFile)
	{
		char cTemp;
		char RoundBitValue;
		int i = 0;
		bool SpecialCase = false; //Trường hợp file nén chỉ chứa duy nhất một ký tự.
		vector<CHuffmanNode*> Forest = ReadHeader(InFile, RoundBitValue);
		CHuffmanTree HuffTree(Forest);
		CHuffmanNode *pTraverse = HuffTree.getRoot();

		//Bật Flag trường hợp đặc biệt lên.
		if (pTraverse->isLeaf())
		{
			SpecialCase = true;
		}

		i = RoundBitValue;
		while (InFile.read(&cTemp, sizeof(char)))
		{
			while (i < CHAR_BIT)
			{
				//Nếu đã là lá
				if (pTraverse->isLeaf())
				{
					OutFile.write(&pTraverse->getString()[0], sizeof(char));
					pTraverse = HuffTree.getRoot();
					
					if (SpecialCase)
					{
						++i;
					}
				}
				else
				{
					if ((cTemp >> (CHAR_BIT - i - 1)) & 1 == 1)
					{
						pTraverse = pTraverse->getpRight();
					}
					else
					{
						pTraverse = pTraverse->getpLeft();
					}
					++i;
				}
			}
			i = i ^ i;
		}

		//Ghi byte cuối cùng ra file giải nén.
		if (pTraverse->isLeaf()) //Có thể bỏ lệnh kiểm tra ở đây.
		{
			OutFile.write(&pTraverse->getString()[0], sizeof(char));
			pTraverse = HuffTree.getRoot();
		}
	}
	else
	{
		throw exception("Cannot open file!");
	}
}

//------------------------------NHÓM PHƯƠNG THỨC HỖ TRỢ ẨN------------------------------
//Phương thức tính dung lượng sau khi nén.
unsigned long CHuffmanCoding::calcZiseAfterCompress(const vector<CHuffmanNode*> &Forest, const vector<string> &ListCode)
{
	unsigned long Size = 0;

	for (int i = 0; i < Forest.size(); i++)
	{
		Size = Size + Forest[i]->getFrequency() * ListCode[(unsigned char)Forest[i]->getString()[0]].size();
	}

	return Size;
}

//Phương thức ghi Header của file nén.
void CHuffmanCoding::WriteHeader(ofstream &outStream, const char &RoundBit, const vector<CHuffmanNode*> &Forest)
{
	if (outStream)
	{
		unsigned short Temp = Forest.size();
		unsigned long Freq;
		outStream.write(&RoundBit, sizeof(char));
		outStream.write(reinterpret_cast<const char*>(&Temp), sizeof(unsigned short));

		for (int i = 0; i < Forest.size(); i++)
		{
			Freq = Forest[i]->getFrequency();
			outStream.write(&Forest[i]->getString()[0], sizeof(unsigned char));
			outStream.write(reinterpret_cast<const char*>(&Freq), sizeof(unsigned long));
		}
	}
}