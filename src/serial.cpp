#include "serial.h"

Serial::Serial() {

}
Serial::~Serial() {

}

int Serial::BaudRate(int baudrate) {
	switch (baudrate) {
	case 0:
		return (B2400);
	case 1:
		return (B4800);
	case 2:
		return (B9600);
	case 3:
		return (B19200);
	case 4:
		return (B38400);
	case 5:
		return (B57600);
	case 6:
		return (B115200);
	default:
		return (B9600);
	}
}

int Serial::SetPara(int serialfd, int speed, int databits, int stopbits,
		int parity) {
	struct termios termios_new;
	bzero(&termios_new, sizeof(termios_new)); //µÈ¼ÛÓÚmemset(&termios_new,sizeof(termios_new));
	cfmakeraw(&termios_new); //¾ÍÊÇ½«ÖÕ¶ËÉèÖÃÎªÔ­Ê¼Ä£Ê½
	termios_new.c_cflag = BaudRate(speed);
	termios_new.c_cflag |= CLOCAL | CREAD;
	//  termios_new.c_iflag = IGNPAR | IGNBRK;

	termios_new.c_cflag &= ~CSIZE;
	switch (databits) {
	case 0:
		termios_new.c_cflag |= CS5;
		break;
	case 1:
		termios_new.c_cflag |= CS6;
		break;
	case 2:
		termios_new.c_cflag |= CS7;
		break;
	case 3:
		termios_new.c_cflag |= CS8;
		break;
	default:
		termios_new.c_cflag |= CS8;
		break;
	}

	switch (parity) {
	case 0:  				//as no parity
		termios_new.c_cflag &= ~PARENB;    //Clear parity enable
		//  termios_new.c_iflag &= ~INPCK; /* Enable parity checking */  //add by fu
		break;
	case 1:
		termios_new.c_cflag |= PARENB;     // Enable parity
		termios_new.c_cflag &= ~PARODD;
		break;
	case 2:
		termios_new.c_cflag |= PARENB;
		termios_new.c_cflag |= ~PARODD;
		break;
	default:
		termios_new.c_cflag &= ~PARENB;   // Clear parity enable
		break;
	}
	switch (stopbits)   // set Stop Bit
	{
	case 1:
		termios_new.c_cflag &= ~CSTOPB;
		break;
	case 2:
		termios_new.c_cflag |= CSTOPB;
		break;
	default:
		termios_new.c_cflag &= ~CSTOPB;
		break;
	}
	tcflush(serialfd, TCIFLUSH); // Çå³ýÊäÈë»º´æ
	tcflush(serialfd, TCOFLUSH); // Çå³ýÊä³ö»º´æ
	termios_new.c_cc[VTIME] = 1; // MINÓë TIME×éºÏÓÐÒÔÏÂËÄÖÖ£º1.MIN = 0 , TIME =0  ÓÐREADÁ¢¼´»Ø´« ·ñÔò´«»Ø 0 ,²»¶ÁÈ¡ÈÎºÎ×ÖÔª
	termios_new.c_cc[VMIN] = 1; //    2¡¢ MIN = 0 , TIME >0  READ ´«»Ø¶Áµ½µÄ×ÖÔª,»òÔÚÊ®·ÖÖ®Ò»Ãëºó´«»ØTIME ÈôÀ´²»¼°¶Áµ½ÈÎºÎ×ÖÔª,Ôò´«»Ø0
	tcflush(serialfd, TCIFLUSH); //    3¡¢ MIN > 0 , TIME =0  READ »áµÈ´ý,Ö±µ½MIN×ÖÔª¿É¶Á
	return tcsetattr(serialfd, TCSANOW, &termios_new); //    4¡¢ MIN > 0 , TIME > 0 Ã¿Ò»¸ñ×ÖÔªÖ®¼ä¼ÆÊ±Æ÷¼´»á±»Æô¶¯ READ »áÔÚ¶Áµ½MIN×ÖÔª,´«»ØÖµ»ò
}

int Serial::WriteData(int fd, const char *data, int datalength) //index ´ú±í´®¿ÚºÅ 0 ´®¿Ú/dev/ttyAMA1 ......
		{
	if (fd < 0) {
		return -1;
	}
	int len = 0, total_len = 0;  //modify8.
	for (total_len = 0; total_len < datalength;) {
		len = 0;
		len = write(fd, &data[total_len], datalength - total_len);
		printf("WriteData fd = %d ,len =%d,data = %s\n", fd, len, data);
		if (len > 0) {
			total_len += len;
		} else if (len <= 0) {
			len = -1;
			break;
		}
	}
	return len;
}

int Serial::ReadData(int fd, unsigned char *data, int datalength) {
	if (fd < 0) {
		return -1;
	}
	int len = 0;
	memset(data, 0, datalength);

	int max_fd = 0;
	fd_set readset = { 0 };
	struct timeval tv = { 0 };

	FD_ZERO(&readset);
	FD_SET((unsigned int )fd, &readset);
	max_fd = fd + 1;
	tv.tv_sec = 0;
	tv.tv_usec = 1000;
	if (select(max_fd, &readset, NULL, NULL, &tv) < 0) {
		printf("ReadData: select error\n");
	}
	int nRet = FD_ISSET(fd, &readset);
	if (nRet) {
		len = read(fd, data, datalength);
	}
	return len;
}

void Serial::ClosePort(int fd) {
	struct termios termios_old;
	if (fd > 0) {
		tcsetattr(fd, TCSADRAIN, &termios_old);
		::close(fd);
	}
}

int Serial::OpenPort(int index) {
	char *device;
	struct termios termios_old;
	int fd;
	switch (index) {
	case COM0:
		device = "/dev/ttyAMA0";
		break;
	case COM1:
		device = "/dev/ttyAMA1";
		break;
	case COM2:
		device = "/dev/ttyAMA2";
		break;
	case COM3:
		device = "/dev/ttyAMA3";
		break;
	case ttyUSB0:
		device = "/dev/ttyUSB0";
		break;
	case ttyUSB1:
		device = "/dev/ttyUSB1";
		break;
	case ttyUSB2:
		device = "/dev/ttyUSB2";
		break;
	default:
		device = "/dev/ttyAMA2";
		break;
	}

	fd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK); //O_RDWR | O_NOCTTY | O_NDELAY   //O_NONBLOCK
	if (fd < 0) {
		return -1;
	}
	tcgetattr(fd, &termios_old);
	return fd;
}
