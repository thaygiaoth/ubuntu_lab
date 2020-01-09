import java.security.MessageDigest;

public class JavaHash
{
        public static void main(String args[]) throws Exception
        {
		/*Lấy tham số thứ 2 là mật khẩu
		 * do md.update() ở dưới chỉ nhận kiểu byte
		 * nên ta phải chuyển kiểu Sring thành byte bằng getBytes()
		 */
             	byte[] pass_a = args[1].getBytes();

		//Lấy tham số thứ 3 là salt
		byte[] salt_a = args[2].getBytes();
				
		//Lấy kiểu băm MD5, SHA-256, SHA-512
		MessageDigest md = MessageDigest.getInstance(args[0]);

		//Bỏ vào bao nhiêu lần thoải mái, nó sẽ nối chuỗi theo thứ tự
                md.update(pass_a);
                md.update(salt_a);
                
		byte s[] = md.digest();

		/*Tiêu hóa xong chuỗi byte nó cũng cho ra chuỗi byte
                 * chuyển thành kiểu String xem cho nó dễ
                 */
                String result = "";
                for (int i = 0; i < s.length; i++)
			result += Integer.toHexString((0x000000ff & s[i]) | 0xffffff00).substring(6);

		//Cục thịt đã băm xong ở trên, xem nó có hình dạng gì
                System.out.println(result);
        }
}
