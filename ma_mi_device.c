/*Lấy số major và minor của các loại file là block hoặc character
 *Dùng lệnh cat /proc/partitions 
 *hoặc lệnh stat, ví dụ stat /dev/sda --> phần Device type:
 *để kiểm tra lại
*/

#include <stdio.h>		//Để chạy printf
#include <sys/stat.h>           //Để chạy stat
#include <sys/sysmacros.h>	//Để chạy major, minor

//Lấy tất cả các giá trị nhập vào
int main(int argc, char *argv[]) 
{
	//Biên dịch dạng đơn giản nhất: gcc ma_mi_device.c 
	//--> tạo ra file thực thi là a.out
	
	//Khi chạy ./a.out /dev/sda /dev/tty1 /root
	//thì a.out là argv[0], /dev/sda là argv[1], /dev/tty1 là argv[2], /root la argv[3]

	//argc (argument count) lưu số lượng các giá trị nhập vào, thường dịch là đối số
	//argv (argument vector) là mảng 1 chiều chứa từng giá trị nhập vào
	//--> các giá trị cách nhau bằng 1 hoặc nhiều khoảng trắng hoặc phím tab, kết thúc bằng phím enter
    	for (int i = 1; i < argc; i++) 
	{
		//Khai báo biến buf kiểu struct của struct stat
		struct stat buf;
        	stat(argv[i], &buf);

		//Loại file là character hoặc block mới có số major khác 0 và minor khác 0
		if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		//%-18s là biến dạng chuỗi (string) hiển thị rộng 18 kí tự, canh trái
		printf("%-18s co so major:%d va minor:%d\n\n", argv[i],major(buf.st_rdev), minor(buf.st_rdev));
        	else
		//Luôn có số major:0 và minor:0
		printf("%-18s khong phai la loai file character hoac block\n", argv[i]);
    	}
return 0;
}
