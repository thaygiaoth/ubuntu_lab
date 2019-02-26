#!/bin/bash

# Sử dụng các repo như bên dưới
cp /etc/apt/sources.list /etc/apt/sources.list.orig.bk
cat > /etc/apt/sources.list << EOF
deb mirror://mirrors.ubuntu.com/mirrors.txt bionic main universe multiverse
deb mirror://mirrors.ubuntu.com/mirrors.txt bionic-security main universe multiverse
deb mirror://mirrors.ubuntu.com/mirrors.txt bionic-updates main universe multiverse
EOF

# Không tải file Translation-en về
echo 'Acquire::Languages "none";' >> /etc/apt/apt.conf.d/98translations

rm -rf /var/lib/apt/lists/* &&
rm -rf /var/cache/apt/archives/* &&
rm -rf /var/cache/apt/*.bin &&
rm -f /var/lib/dpkg/lock
apt update

# Cài gói apache2 làm web server cho repo
# Xóa file index của apache
# Gói dpkg-dev chứa các lệnh dpkg-scanpackages, dpkg-scansources tạo metadata cho repo
apt -y install apache2 dpkg-dev && 
rm -f /var/www/html/index.html

# Chạy dịch vụ apache web server và xem lại
systemctl start apache2 && 
systemctl status apache2 --no-pager

# Tạo cây thư mục của repo sắp tạo
mkdir -p /var/www/html/repo/{binary-amd64,binary-i386,source}

# Tải về gói bind9 và các gói phụ thuộc để trong /var/www/html/repo/binary-amd64
apt-get install --download-only -y bind9 \
-o Dir::Cache::archives='/var/www/html/repo/binary-amd64' \
-o Dir::Cache::srcpkgcache='' \
-o Dir::Cache::pkgcache='' \
-o Debug::NoLocking=1 &&
rm -rf /var/www/html/repo/binary-amd64/partial/

# Thêm kiến trúc i386 (32 bit) để tải gói i386 về
dpkg --add-architecture i386 && dpkg --print-foreign-architectures && 
apt update

# Tải gói tree i386 và các gói phụ thuộc để trong /var/www/html/repo/binary-i386
apt-get install --download-only -y tree:i386 \
-o Dir::Cache::archives='/var/www/html/repo/binary-i386' \
-o Dir::Cache::srcpkgcache='' \
-o Dir::Cache::pkgcache='' -o Debug::NoLocking=1 &&
rm -rf /var/www/html/repo/binary-i386/partial/ 

# Xóa các repo i386 để apt update nhanh
dpkg --remove-architecture i386

# Thêm repo main universe dạng source
apt-add-repository -s 'deb http://archive.ubuntu.com/ubuntu bionic main universe' && 
apt update

# Tải gói mã nguồn bind9 để trong /var/www/html/repo/source
cd /var/www/html/repo/source && 
apt-get --download-only source bind9 && 
rm -rf *dfsg/ && cd
