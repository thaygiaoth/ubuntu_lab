#!/bin/bash

# Tham khảo thêm https://help.ubuntu.com/community/Grub2/Displays

# Cài gói wget
rm -f /var/lib/dpkg/lock &&
apt -y install wget

# Thêm dấu # trước tham số GRUB_TERMINAL=console trong 50-curtin-settings
sed -i 's/^GRUB_TERMINAL=.*/#&/' /etc/default/grub.d/50-curtin-settings

# Trên Ubuntu, GRUB2 tự nhận hình nền .jpg, .jpeg, .png... trong /boot/grub 
# Sau khi dùng lệnh update-grub sẽ thấy có dòng Found background image:
wget -O /boot/grub/grub2-splash.png https://raw.githubusercontent.com/thaygiaoth/ubuntu_lab/master/grub2-splash.png

# Thêm màu sắc các dòng khởi động (entry) trong menu GRUB2
sed -i '/true\"$/a \\t\techo \"  set color_highlight=light-magenta\/black\"' /etc/grub.d/05_debian_theme
sed -i '/true\"$/a \\t\techo \"  set color_normal=light-green\/black\"' /etc/grub.d/05_debian_theme

# Ghi chú dòng echo "  true"
sed -i 's/.*true\"/#&/' /etc/grub.d/05_debian_theme

# Chỉnh thời gian chờ là 10 giây
sed -i 's/GRUB_TIMEOUT=.*/GRUB_TIMEOUT=10/' /etc/default/grub

# Giả sử có dấu # trước GRUB_TERMINAL và GRUB_GFXMODE trong /etc/default/grub
# Thêm các chế độ phân giải màn hình để chọn từ trái sang phải nếu có
# Tham khảo https://www.gnu.org/software/grub/manual/grub/html_node/gfxpayload.html#gfxpayload
echo 'GRUB_GFXMODE=1152x864,1024x768,854x480,auto' > /etc/default/grub

#Cập nhật lại cấu hình GRUB2
update-grub

# Tắt máy, do kiểm tra thấy khởi động lại nhiều khi không ăn cấu hình
echo "Tat may trong 5 giay nua"
sleep 5
init 0

###DONE###
