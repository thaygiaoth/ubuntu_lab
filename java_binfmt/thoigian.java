import java.util.Calendar;
import java.util.Scanner;

class thoigian
//Theo tên class là thoigian, sau khi biên dịch javac thoigian.java --> tạo ra thoigian.class
//javac --help để xem chi tiết các tùy chọn
{
	public static void main(String[] args) {
        	
		//Lấy thời gian theo java.time.LocalDateTime để đúng giờ trên hệ thống

		//Ở đây sử dụng theo calendar
		Calendar cal = Calendar.getInstance();

        	int year = cal.get(Calendar.YEAR);
        	int month = cal.get(Calendar.MONTH) + 1;
        	int day = cal.get(Calendar.DATE);
        	int hour = cal.get(Calendar.HOUR_OF_DAY) + 7;
        	int minute = cal.get(Calendar.MINUTE);
		int seconds = cal.get(Calendar.SECOND);

		System.out.println("Linux DevOps I");

		//Sử dụng println dể in và xuống dòng
        	//System.out.println("Thời gian: " + hour + ":" + minute + ":" + seconds + " " + day + "/" + month + "/" + year);
		
		//%02d là in với độ rộng 2 kí tự, vd 3 thì in là 03
		System.out.format("Thời gian: %02d:%02d:%02d ngày %02d/%02d/%04d \n", hour, minute, seconds, day, month, year);
		
		Scanner s=new Scanner(System.in);

        	System.out.println("Nhấn Enter để thoát");

        	s.nextLine();
    }
}
