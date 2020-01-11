<?php

/*Chạy bằng lệnh php /var/www/html/ham_crypt.php
 * Chạy trên web: http://ip/ham_crypt.php
 * để so sánh
 */

/*Dấu . là nối chuỗi
 * <br> là xuống hàng ở định dạng html trên web
 * \n là xuống hàng khi chạy bằng lệnh php
 * PHP_EOL tự đông chọn xuống hàng cho đúng 
 * vì trên Windows là \r\n
 */

echo "<br>\nMã hóa DES:" .crypt('1', '123');

echo "<br><br>\nMã hóa MD5: " . crypt('1', '$1$123456789$') . PHP_EOL;

echo "<br><br>\nMã hóa Blowfish bcrypt: " . crypt('1', '$2y$10$12345678910111213141516$') . PHP_EOL;

echo "<br><br>\nMã hóa SHA256: " . crypt('1', '$5$1234567891011121314$') . PHP_EOL;

echo "<br><br>\nMã hóa SHA512: " . crypt('1', '$6$1234567891011121314$') . PHP_EOL;

$hash = password_hash('1', PASSWORD_ARGON2I); 

echo "<br><br>\nMã hóa ARGON2I: " . $hash . PHP_EOL;; 

echo "<br><br>";

print_r(password_get_info($hash));

?>
