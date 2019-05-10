### Minh họa UEFI shell script, chạy file này trong môi trường UEFI nha các bạn ###
#UEFI là hệ điều hành thu nhỏ dành cho firmware, hmm có khá nhiều việc để làm với nó

#nsh là viết tắt của nano shell?
#Trên EL45 cũng có nash với ý nghĩa là nano shell, xem man nash

#Chép file này vào /boot/efi
#Từ dấu Shell> gõ lệnh fs0: (dấu Shell> sẽ chuyển thành fs0:\>) để vào thư mục /boot/efi
#-->Có thể dùng lệnh ls để xem có file này chưa
#Nếu có thì thực hiện chạy file này fs0:\>detect_os.nsh

#Không hiển thị các lệnh trong script này khi thực hiện
#Thêm dấu # vào đầu dòng và chạy để thấy rõ hơn ý nghĩa của nó
@echo -off

#Xóa màn hình, thiết lập màu nền cho màn hình
#0:Black, 1:Blue, 2:Green, 3:Cyan, 4:Red, 5:Magenta, 6:Yellow, 7:Light gray
cls 5

#date lấy giá trị ngày tháng hiện tại của UEFI
#time lấy giá trị thời gian hiện tại của UEFI

echo "Ngay:"
date
echo "Thoi gian:"
time

#Minh họa cấu trúc if then
#Kiểm tra có tồn tại thư mục EFI\{ubuntu,redhat} hay không
#Có thể sử dụng not exist là kiểm tra không tồn tại

if exist EFI\ubuntu then
echo "He dieu hanh Ubuntu"
else 
    	if exist EFI\redhat then
    	echo "He dieu hanh Red Hat"
    	else
    echo "Khong ro he dieu hanh"
    	endif
endif

#Minh họa cấu trúc for, %i% là lấy giá trị biến i
#for %i run (1 5)
#     if not exist i then
#     echo "Chao ban lan %i%"
#     endif
#endfor

#Dùng lệnh set để xem giá trị các biến môi trường
#Gán giá trị cho 1 biến ta tự định nghĩa
#set so 10
#echo %so%
#Xem hướng dẫn sử dụng lệnh set: set -b -?

### Hết ###
