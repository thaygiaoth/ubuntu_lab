/* Thực hiện trên Ubuntu 18.04.2
 *
 * B1. Cài các gói cần thiết
 * apt -y install gnu-efi gcc make wget
 * --> gói gnu-efi chứa các thư viện efi.h, efilib.h
 * --> gói gcc để biên dịch chương trình viết bằng C
 * --> gói make để biên dịch bằng Makefile
 * 
 * B2. Tải file Makefile về
 * wget https://raw.githubusercontent.com/thaygiaoth/ubuntu_lab/master/Makefile
 * --> chú ý để cùng thư mục với file main.c này
 * 
 * B3. Dùng lệnh make biên dịch chương trình main.c này theo chỉ dẫn trong Makefile
 * --> tạo ra 3 file: main.o, uefi_ver.so, uefi_ver.efi
 * 
 * B4. Chép file uefi_ver.efi vào /boot/efi
 * cp uefi_ver.efi /boot/efi
 * 
 * DONE
 */

#include <efi.h>
#include <efilib.h>

EFI_STATUS
EFIAPI

efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) 
{
   	InitializeLib(ImageHandle, SystemTable);
	
	//Xóa màn hình
   	uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);
	
	Print(L"Thong tin UEFI\n");
	
	//Khai báo efi_main có phát sinh biến ST để gọi tới struct EFI_SYSTEM_TABLE
	//Ta truy xuất 2 giá trị trong struct đó để lấy thông tin
	Print(L"Firmware Vendor: %s\n", ST->FirmwareVendor);
	Print(L"Firmware Revision: %lx\n", ST->FirmwareRevision);

	return EFI_SUCCESS;
}

/* Các bạn cải tiến giúp mình để chương trình này tương đương với lệnh ver
 * Lệnh ver theo tài liệu của UEFI, trang 232
 * https://uefi.org/sites/default/files/resources/UEFI_Shell_2_2.pdf
 * 
 * Mình có tham khảo code từ link:
 * https://www.rodsbooks.com/efi-programming/hello.html
 */
