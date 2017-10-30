### Thông tin cá nhân:
- Họ và tên: Võ Sỹ Liên Thành
- Sinh viên trường Đại học Khoa học tự nhiên - ĐHQG TP.HCM
- Khoa Công nghệ thông tin
- Chuyên ngành Kỹ thuật phần mềm

### Thông tin Project:
- Đây là project về thuật toán nén Huffman lập trình theo hướng đối tượng.
- Project này là một phần trong đồ án File & Folder management của môn Cầu trúc dữ liệu & giải thuật.

### Ý tưởng cài đặt:
##### Quá trình nén:
- Tạo cây Huffman từ dữ liệu gốc.
- Lưu Header vào file
- Chuyển dữ liệu gốc thành dữ liệu được nén dựa trên cây Huffman

##### Quá trình giải nén:
- Đọc Header
- Xây dựng lại cây Huffman từ thông tin trong Header.
- Chuyển dữ liệu nén thành dữ liệu gốc theo cây Huffman  được xây dựng trong bước trên.
- Ghi dữ liệu về file giải nén.

##### Các hoạt động xữ lý khác:
- Đọc, ghi file nhị phân
- Tạo bảng tần số.

### Cài đặt Header như thề nào?
- Số lượng bit làm tròn	(1 Byte).
- Số lượng ký tự (2 Byte).
- Bảng ký tự và tần số (1 Byte cho ký tự - 4 byte cho tần số (unsigned long))
