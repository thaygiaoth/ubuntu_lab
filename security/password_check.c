/*Chương trình này đơn giản hà
 * nó kiểm tra password của user trên linux
 * nếu không có user báo không có
 * nếu có user thì báo có và đúng password thì báo đúng, không đúng thì báo không đúng
 * hết roài, á hi hi í ha ha
 * bạn nào xem và cải tiến nó thành dạng multi-thread để chạy nhanh hơn xem có được không nha
 */

#include <pwd.h> 	/*để sử dụng biến kiểu chỉ điểm (ngừ ta hay gọi là con trỏ - pointer) *pw móc vào kiểu struct passwd*/
#include <stdio.h> 	/*để sử dụng hàm printf*/
#include <shadow.h> 	/*để sử dụng biến kiểu chỉ điểm *sp móc vào kiểu struct spwd*/
#include <crypt.h> 	/*để sử dụng hàm crypt*/
#include <string.h> 	/*để sử dụng hàm strcmp so sánh 2 chuỗi*/
#include <stdlib.h> 	/*để sử dụng hàm exit để có mã trả về khác 0 (kiểm tra bằng echo $? sau khi thực hiện lệnh) */

void kiemtra_ten_mat_khau(const char *ten, const char *matkhau, struct passwd *pw) 
{ 
	/* Xem chi tiết trong man 3 shadow hoặc viết ngắn gọn là shadow(3)
	 * Biến con trỏ *sp kiểu struct để lấy thông tin của người dùng trong /etc/shadow
	 */
	struct spwd *sp;
	
    	char *mk_mahoa, *gt_salt;

	//Xem trong getpwnam(3)
    	pw = getpwnam(ten);
    	endpwent();

	/*Lấy tên người dùng có trong /etc/passwd
	 * xem chi tiết trong getspnam(3)
	 */
    	sp = getspnam(pw->pw_name);
	endspent();
	
	//Lấy giá trị salt theo tên người dùng trong /etc/shadow
	gt_salt = sp->sp_pwdp;
	
	/*Dùng hàm crypt() để mã hóa dựa vào mật khẩu nhập vào và giá trị salt 
	 * để so sánh với chuỗi mật khẩu đã mã hóa trong /etc/shadow
	 * điều ngộ ngộ là giá trị gt_salt không chỉ có salt mà là $6$rounds=xxx$salt$pass_đã_mã_hóa
	 * nhưng crypt() vẫn lấy ra được salt và xài tốt
	 */
	mk_mahoa = crypt(matkhau, gt_salt);
    
	if (strcmp(mk_mahoa, gt_salt) == 0)
        	printf("Có người dùng %s và đúng mật khẩu\n", ten);
    	else
        	printf("Có người dùng %s nhưng không đúng mật khẩu\n", ten);
}

/*Mị giải thích chút nha
 * 
 * Biên dịch chương trình này như mọi khi
 * mặc định sau khi biên dịch tạo ra file nhị phân a.out
 * nếu muốn tên khác thì thêm -o tên
 * gcc password_check.c -lcrypt
 * 
 * Chạy: ./a.out root 123
 * 
 * ./a.out là argv[0] 
 * root là argv[1]
 * mật khẩu 123 là argv[2]
 */

int main(int argc, char *argv[])
{
	/*Cái if này để ngừ ta chạy ./a.out hoặc ./a.out -h|-help|--help 
	 * sẽ in ra mấy cái dòng hướng dẫn dưới
	 * muốn chiên xâu hơn, ngon hơn thì xài getopt_long(3) nha mí bạn
	 */
	if (argc != 3 || (strcmp(argv[1], "-help") == 0) || (strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0))
	{
        	printf("\nKiểm tra tên người dùng và mật khẩu trên Linux\n");
		printf("Xài vậy nà: %s tên mật_khẩu\n\n", argv[0]);
        	exit(EXIT_FAILURE);
        }

	/*Biến con trỏ *sp kiểu struct để lấy thông tin trong /etc/passwd
 	 * ở đây vừa khai báo vừa lấy giá trị thứ 1 nhập vào
 	 * getpwnam trả về iá trị 0 nếu có người dùng, khác 0 nếu không có ngườidùng
 	 */
	struct passwd *pw=getpwnam(argv[1]);

	/*! là khác*/
        if (!pw)
        {
                printf("Không có người dùng %s trên hệ thống\n", argv[1]);
                exit(EXIT_FAILURE);
        }
		
	kiemtra_ten_mat_khau(argv[1], argv[2], pw);
}
