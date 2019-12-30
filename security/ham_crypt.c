/*Chương trình này in ra chuỗi mã hóa theo thuật toán DES, MD5, SHA256, SHA512
 * 
 * biên dịch: gcc crypt.c -o ham_crypt -lcrypt
 * 
 * chạy: ./ham_crypt mật_khẩu salt số_vòng
 * 
 * salt dài tối đa 16 kí tự trong các giá trị sau [a-zA-Z0-9./], 
 * 
 * số vòng trong [1000-999999999], mặc định của hàm crypt là 5000
 * 
 * vd: ./ham_crypt 1 0123456789111213 10000
 * 1 là argv[1], 0123456789111213 là argv[2], 10000 là argv[3]
 *
 * dùng lệnh time để xem thời gian chạy mất bao lâu, số vòng càng lớn thì chạy càng lâu
 *
 * time ./ham_crypt 1 0123456789111213 10000
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>

int main(int argc, char *argv[])
{
	char md5_salt[9]="";
	sprintf(md5_salt, "%s%s%s", "$1$", argv[2], "$");
	
	//sprintf dùng để nối chuỗi thành $id$rounds=yyy$salt$	
	char sha256_salt[37]="";
	sprintf(sha256_salt, "%s%s%s%s%s", "$5$rounds=", argv[3], "$", argv[2], "$");
	
	char sha512_salt[37]="";
	sprintf(sha512_salt, "%s%s%s%s%s", "$6$rounds=", argv[3], "$", argv[2], "$");
	
	/* Hàm crypt() mặc định là mã hóa DES, lấy salt chỉ 2 kí tự đầu tiên
	 * mật khẩu mã hóa dài 13 kí tự,  2 kí tự đầu tiên là salt
	 */
	printf("Mã hóa DES:    %s\n", crypt(argv[1], argv[2]));
	
	printf("Mã hóa MD5:    %s\n", crypt(argv[1], md5_salt));
	
	printf("Mã hóa SHA256: %s\n", crypt(argv[1], sha256_salt));
	
	printf("Mã hóa SHA512: %s\n", crypt(argv[1], sha512_salt));
}
