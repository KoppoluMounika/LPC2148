
//CODE of lcd interfacing with 8051 microcontroller
#include<reg51.h>

void delay(unsigned int i);
void lcd_cmd(unsigned char a);
void lcd_data(unsigned char b);
void lcd_init(void);
void lcd_str(unsigned char *str);
void I2C_Start(void);
void I2C_Stop(void);
unsigned char I2C_DataRead(void);
void I2C_DataWrite(unsigned char Data);
sbit rs=P2^0;
sbit en=P2^1;
sbit SCL=P3^0;
sbit SDA=P3^1;
sfr ldata=0x90;
void main()

{
	unsigned char x;
lcd_init();
	lcd_str("   WELCOME TO   ");
	lcd_cmd(0xc0);
	lcd_str("   MY PROJECT   ");
	
	delay(65000);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
lcd_str("   YT TRAINING   ");
	lcd_cmd(0xc0);
	lcd_str("   INSTITUTE   ");
		delay(65000);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
lcd_str(" I2C PROTOCOL R/W");
	//Sending Data to a Slave Device
I2C_Start();
	I2C_DataWrite(0xA0); //1010 0000
		I2C_DataWrite(0x00); //register address or memory address
	I2C_DataWrite('A'); 
I2C_Stop();
delay(500);
	//reading Data from a Slave Device
I2C_Start();
	I2C_DataWrite(0xA0); //1010 0000
		I2C_DataWrite(0x00); //register address or memory address
I2C_Start();
	I2C_DataWrite(0xA1); //1010 0001 read
	x=I2C_DataRead();
	lcd_cmd(0xc0);
	lcd_data(x);
I2C_Stop();
	while(1);
}

void lcd_init()
{
lcd_cmd(0x38);
	lcd_cmd(0x0c);
	lcd_cmd(0x01);
	lcd_cmd(0x80);


}
void delay(unsigned int i)
{
unsigned int j;
	for(j=0;j<i;j++);
}

void lcd_cmd(unsigned char a)
{
  rs=0;//cmd 
	ldata=a;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_data(unsigned char b)
{
  rs=1;//data 
	ldata=b;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_str(unsigned char *str)
{
while(*str)
{
	lcd_data(*str++);
}

}

void I2C_Start(void)
{
SCL=1;
SDA=1;
delay(5);
SDA=0;
delay(5);
SCL=0;
}
void I2C_Stop(void)
{
SCL=0;
SDA=0;
	delay(5);
	SCL=1;
delay(5);
SDA=1;
}
//write byte of data from master to slave
void I2C_DataWrite(unsigned char Data)//0xA0 1010 0000--> 0100 0000
{
unsigned char i;
	//
for(i=0;i<8;i++)
{
	SDA= (Data&0x80)?1:0;
SCL=1;
		delay(5);
	SCL=0;
Data=Data<<1;
}
SDA=1;
SCL=1;
	delay(5);
while(SDA==1); //waiting until SDA=0 this should be set by the slave 
SCL=0;
	delay(5);
}
unsigned char I2C_DataRead(void)///1010 0000     1|0=1...101
{
bit rd_bit;
unsigned char i,Dat=0;	

	for(i=0;i<8;i++)
	{
		delay(5);
		SCL=1;
			delay(5);
	rd_bit=SDA;
		Dat=Dat<<1;
		Dat=Dat|rd_bit;
	
			SCL=0;
	}
	//NACK
SDA=1;
SCL=1;
delay(5);
SCL=0;
	return Dat;
}