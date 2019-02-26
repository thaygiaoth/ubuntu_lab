#!/bin/bash

# Xóa các file metadata của repo tạo bằng dpkg-scanpackages, dpkg-scansources
cd && rm -f /var/www/html/repo/{source,binary-{amd64,i386}}/[PS]*.[gx]z

# Chuẩn bị môi trường để tạo repo bằng apt-ftparchive
cd /var/www/html && mv repo pool &&
mkdir -p dists/bionic/stable/{source,binary-{amd64,i386}} &&
mkdir indices pubkey &&
ln -s . ubuntu && cd

# Tạo Release cho component 64 bit
cat > Release_64 << EOF
Archive: bionic
Component: stable
Origin: repo02
Label: repo02
Architecture: amd64
Description: apt repo bằng apt-ftparchive
EOF

# Tạo Release cho component 32 bit
cat > Release_32 << EOF
Archive: bionic
Component: stable
Origin: repo02
Label: repo02
Architecture: i386
Description: apt repo bằng apt-ftparchive
EOF

# Tạo Release cho component source
cat > Release_source << EOF
Archive: bionic
Component: stable
Origin: repo02
Label: repo02
Architecture: source
Description: apt repo bằng apt-ftparchive
EOF

# Tạo file override cho source theo định dạng Package_name Section
cat > override.bionic.src << EOF
bind9 net1  
EOF

cat > apt_release.conf << EOF
APT::FTPArchive::Release {
Origin "repo02";
Label "repo02";
Suite "bionic";
Codename "bionic";
Architectures "amd64 i386 source";
Components "stable";
Description "apt repo bằng apt-ftparchive";
}  
EOF

# Sử dụng các repo bên dưới
cat > /etc/apt/sources.list << EOF
deb mirror://mirrors.ubuntu.com/mirrors.txt bionic main universe multiverse
deb mirror://mirrors.ubuntu.com/mirrors.txt bionic-security main universe multiverse
deb mirror://mirrors.ubuntu.com/mirrors.txt bionic-updates main universe multiverse
EOF

rm -rf /var/lib/apt/lists/* &&
rm -rf /var/cache/apt/archives/* &&
rm -rf /var/cache/apt/*.bin &&
rm -f /var/lib/dpkg/lock &&
apt update

# Cài gói chứa apt-ftparchive
apt -y install apt-utils

# Cài apt-file
apt -y install apt-file

# Cài dịch vụ tạo số ngẫu nhiên
apt -y install rng-tools && 
systemctl start rng-tools && 
systemctl status rng-tools

# Tạo cặp khóa chung/riêng (public/private)
cat << EOF | gpg --batch --gen-key
%echo Generating a default key
%no-protection
Key-Type: RSA
Key-Length: 4096
Name-Real: Linux LPI1
Name-Comment: Key cho repo apt
Name-Email: support@robusta.com
Expire-Date: $(date -d +5year +%Y-%m-%d)
%commit
%echo done
EOF

# Lấy giá trị long key id của khóa chung vừa tạo
key=$(gpg --list-keys --with-colons support@robusta.com | awk -F: '/^pub:/ { print $5 }') 

# Sử dụng key id này làm key mặc định để kí nếu hệ thống có nhiều key
echo "default-key $key" >> ~/.gnupg/gpg.conf

# Xem key mặc định trên hệ thống
# gpgconf --list-options gpg | grep default-key | cut -f2 -d'"'


# Xóa khai báo repo và cache phía client
echo -n > /etc/apt/sources.list
rm -rf /var/lib/apt/lists/* &&
rm -rf /var/cache/apt/archives/* &&
rm -rf /var/cache/apt/*.bin &&
apt update