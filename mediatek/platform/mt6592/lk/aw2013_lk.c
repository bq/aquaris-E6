#include <cust_leds.h>
#include <platform/mt_reg_base.h>
#include <platform/mt_i2c.h>   
#include <platform/mt_pmic.h>
#include <printf.h>

#define AW2013_I2C_ADDRESS_WRITE		0x8A
#define AW2013_I2C_ADDRESS_READ			0x8B  
#define AW2013_I2C_ID	I2C0

void hwctl_led_off();
void AW2013_init(); 
extern void led_flash_aw2013( unsigned int id );
extern void Suspend_led();

static struct mt_i2c_t aw2013_i2c;

kal_uint32 aw2013_write_byte(kal_uint8 addr, kal_uint8 value)
{
    kal_uint32 ret_code = I2C_OK;
    kal_uint8 write_data[2];
    kal_uint16 len;

    write_data[0] = addr;
    write_data[1] = value;

    aw2013_i2c.id = AW2013_I2C_ID;
    aw2013_i2c.addr = (AW2013_I2C_ADDRESS_WRITE >> 1);
    aw2013_i2c.mode = ST_MODE;
    aw2013_i2c.speed = 100;
    len = 2;

    ret_code = i2c_write(&aw2013_i2c, write_data, len);

    return ret_code;
}
static BOOL AW2013_i2c_write_reg(unsigned char reg,unsigned char data)
{
	char buf[2];

	buf[0]=reg;
	buf[1]=data;
	aw2013_write_byte(buf[0],buf[1]);
}

void hwctl_led_off()//( unsigned int id )
{
    printf("==== [aw2013]hwctl_led_off ====\n");

	AW2013_i2c_write_reg(0x30, 0);//led off	
	AW2013_i2c_write_reg(0x01,0);

}

void Suspend_led(void)
{
	hwctl_led_off();
}

void led_flash_aw2013(unsigned int id)
{
	char buf[2];
	
	buf[0]=0x01;
	buf[1]=0x01;
	AW2013_i2c_write_reg(buf[0],buf[1]);

	buf[0]=0x31+id;
	buf[1]=0x02;
	AW2013_i2c_write_reg(buf[0],buf[1]);

	buf[0]=0x34+id;
	buf[1]=0xff;
	AW2013_i2c_write_reg(buf[0],buf[1]);

	buf[0]=0x30;
	buf[1]=1<<id;
	AW2013_i2c_write_reg(buf[0],buf[1]);
    
}

void AW2013_init(void)    
{	
	//AW2013_Hw_reset();
		
	AW2013_i2c_write_reg(0x12,0x00);
	AW2013_i2c_write_reg(0x13,0x00);
	
	AW2013_i2c_write_reg(0x20,0x3f);
	AW2013_i2c_write_reg(0x21,0x3f);
	AW2013_i2c_write_reg(0x22,0x3f);
	AW2013_i2c_write_reg(0x23,0x3f);
	AW2013_i2c_write_reg(0x24,0x3f);
	AW2013_i2c_write_reg(0x25,0x3f);
	
	//AW2013_test();
}

void AW2013_OnOff()  
{   
	char buf[2];
	
	buf[0]=0x7f;
	buf[1]=0x00;
	AW2013_i2c_write_reg(buf[0],buf[1]);

}
void AW2013_AllOn(void)
{
	printf("======== AW2013_AllOn  Entry ========\r\n");

	AW2013_OnOff();
	
	AW2013_i2c_write_reg(0x12,0x00);   //OUTÅäÖÃÎªºôÎüµÆÄ£Ê\u0153
	AW2013_i2c_write_reg(0x12,0x00);   //OUTÅäÖÃÎªºôÎüµÆÄ£Ê\u0153	 
	AW2013_i2c_write_reg(0x13,0x00);   //OUTÅäÖÃÎªºôÎüµÆÄ£Ê\u0153
	AW2013_i2c_write_reg(0x13,0x00);   //OUTÅäÖÃÎªºôÎüµÆÄ£Ê\u0153
	AW2013_i2c_write_reg(0x20,0x3f);//OUT0¿Úµ÷¹â£¬µ÷¹âµÈ\u0152¶Îª0-255¡£OUT0~OUT5µÄµ÷¹âÖ\u017eÁîÒÀ\u017dÎÎª0x20~0x25. Ð\u017d0¹Ø±Õ
	AW2013_i2c_write_reg(0x21,0x3f);
	AW2013_i2c_write_reg(0x22,0x3f);
	AW2013_i2c_write_reg(0x23,0x3f);
	AW2013_i2c_write_reg(0x24,0x3f);
	AW2013_i2c_write_reg(0x25,0x3f);
}