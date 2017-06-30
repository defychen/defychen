# Encryption & Decryption Algorithm
***
## AES加解密

AES(Advanced Encryption Standard,高级加密标准):又叫Rijindael加密法,用来替代DES算法.常见的AES加密模式有ECB、CBC、CFB、OFB和CTR五种.CFB、OFB带反馈,做流加密用的多,CBC、CTR和ECB多用于独立的block加密.

AES做运算时每个块(block)都是128bit(16 byte),密钥长度支持128、192和256bit.

**AES各模式的优缺点:**

1.AES-ECB(Electronic codebook)---电码本模式

该模式将整个明文分成若干段相同的小段(128bit),然后对每段进行加密.

优点:简单、独立,每个块单独运算.适合做并行运算,传输错误只会影响当前块.

缺点:同明文输出同密文,可能导致明文攻击.

2.AES-CBC(Cipher-block chaining)---密码分组链接模式

该模式先将明文切成若干小段,然后每一小段与初始化向量(IV:Initial Vector---128bit)或者上一段密文段进行异或运算后,再与密钥进行加密.

优点:串行化运算,相同明文加密得到不同密文.

缺点:需要初始化向量,如果出现传输错误,会导致后面的全部错误.

3.AES-CTR(Counter mode)---计算器模式

有一个自增的算子(counter),这个算子与密钥加密之后的结果和明文异或得到密文.算子每做一笔(128bit)就会自增1,相当于一次一密.

优点:

同明文得到不同密文(在做加密过程中会导致算子不一样),每个块单独运算,适合并行运算.而且residual(不足16byte的情况)也会处理,没有residual的问题.

缺点:

可能导致明文攻击.

4.AES-CFB(Cipher FeedBack)---密码反馈模式

这个模式较复杂---略.

优点:

同明文不同密文,分组密钥转换为流密钥.

缺点:

串行运算不利于并行,传输错误可能导致后续传输块错误.

5.AES-OFB(Output FeedBack)---输出返回模式

这个模式较复杂---略.

优点:

同明文不同密文,分组密钥转换为流密钥.

缺点:

串行运算不利于并行,传输错误可能导致后续传输块错误.

**实例:AES-CBC/CTR加解密**

使用了第三方开源源码,网址:http://www.gladman.me.uk/---该网址暂时没有找到.网上说有源码文件:aes_modes.c/aescrypt.c/aeskey.c/aestab.c等.

	#include <stdio.h>
	#include <string.h>
	#include <time.h>
	
	#include "aes/aes.h"

	typedef unsigned char 	uint8;
	typedef char 			int8;
	typedef unsigned short 	uint16;
	typedef short 			int16;
	typedef unsinged int	uint32;
	typedef int				int32;
	typedef unsigned long long uint64;
	typedef long long 		int64;

	void ctr_inc(unsinged char ctr_buf[16])	//16byte的counter(相当于IV),此处取最后4byte进行递增循环.
	{								//目前我们的硬件是整个16byte都参与递增.但是vo只取后8byte参与,一旦满了就循环重新计数.
		if(!(++(ctr_buf[15])))
			if(!(++(ctr_buf[14])))
				if(!(++(ctr_buf[13])))
					++(ctr_buf[12]);
	}
	
	//4byte nonce + 8byte iv + 4byte counter
	void ctr_init(unsigned char nonce[4], unsigned char iv[8], unsigned char ctr_buf[16])
	{
		memcpy(ctr_buf, nonce, 4);	//前4byte(即0~3byte为nonce)
		memcpy(ctr_buf + 4, iv, 8);	//接下来8byte(即4~11byte为iv)
		memset(ctr_buf + 12, 0, 4);	//最后4byte为counter(12~15byte),此处初始化为0
		ctr_inc(ctr_buf);
	}

	void print_hex(uint8 *buf, uint64 len)
	{
		for(int i = 0; i < len; i++)
		{
			printf("0x%02x ", buf[i]);
			if(15 == i % 16)
				printf("\n");	//每16个数打印出一个换行
		}
		printf("\n");
	}

	void main()
	{
		uint8 key[] = {0x10,0xa5,0x88,0x69,0xd7,0x4b,0xe5,0xa3,0x74,0xcf,0x86,0x7c,0xfb,0x47,0x38,0x59}; 
						//默认的key值
		uint8 buf[16];
		uint8 msg[] = "HelloWorld!23456";
		uint64 fsize = strlen((char *)msg);	//message的长度
		
		uint8 *dataBuf = (uint8 *)malloc(1024);
		
		//AES with CBC
		printf("AES with CBC\n");
		
		//copy data,将字符串msg拷贝进dataBuf
		memset(dataBuf, 0, 1024);
		strcpy((char *)dataBuf, (char *)msg);	//将msg中的每一个字符都拷贝进dataBuf
		uint8 *pDataBuf = dataBuf;	//临时的指针
		uint8 iv1[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint16 iEncryptTimes = fsize/16 + 1;	//加密两次
		uint8 iPaddings = 16 - fsize%16;		//Padding size = 16
		uint64 newlen = fsize + iPaddings;		//new length
		memset(pDataBuf + fsize, iPaddings, iPaddings);		//初始化为0x10
		printf("input = \n");	//输出input值
		print_hex(dataBuf, newlen);
			//输出input值:
				0x48 0x65 0x6c 0x6c 0x6f 0x57 0x6f 0x72 0x6c 0x64 0x21 0x32 0x33 0x34 0x35 0x36 
				0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10
		aes_encrypt_ctx_en_ctx[1];	//Init encrypt,初始化加密函数,属于源码库中的函数
		
		//Encrypt
		unsinged int i;
		for( i = 0; i < iEncryptTimes; i++)
		{
			aes_encrypt_key128(key, en_ctx);
			aes_cbc_encrypt(pDataBuf, buf, 16, iv1, en_ctx); //iv has been changed, ctx has been changed!解密接口
			memcpy(pDataBuf, buf, 16);	//存储在原来的位置
			pDataBuf += 16;	//将指针往后挪16byte
		}

		printf("encrypt = \n");
		print_hex(dataBuf, newlen);

		//Decrypt
		pDataBuf = dataBuf;
		uint8 iv2[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8 buf3[256] = {0};
		aes_decrypt_ctx_de_ctx[1];
		aes_decrypt_key128(key, de_ctx);
		aes_cbc_decrypt(pDataBuf, buf3, newlen, iv2, de_ctx);	//一次性全部解密完
		printf("decrypt = \n");
		print_hex(buf3, newlen);

		//============================
		printf("============================\n");	//接下来是CTR
		printf("AES with CTR\n");
		//copy data
		memset(dataBuf, 0, 1024);
		strcpy((char *)dataBuf, (char *)msg);
		pDataBuf = dataBuf;	//临时指针
		uint8 iv3[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		
		iEncryptTimes = fsize / 16;
		uint8 iRemain = fsize % 16;	//余下的
		uint8 ctr_buf[AES_BLOCK_SIZE];	//8byte大小
		printf("input = \n");
		print_hex(dataBuf, fsize);

		//Initial encrypt
		//aes_encrypt_ctx_en_ctx[1];	//不需要再init
		
		//encrypt
		for(i = 0; i < iEncryptTimes; i++)
		{
			aes_encrypt_key128(key, en_ctx);
			ctr_init(iv3, iv3 + 4, ctr_buf);	//set iv as the nonce
			aes_ctr_encrypt(pDataBuf, buf, 16, ctr_buf, ctr_inc, en_ctx);	//iv has been changed, ctx has been changed
			memcpy(pDataBuf, buf, 16);
			pDataBuf += 16;
		}

		if(iRemain != 0)	//last times
		{
			pDataBuf += i * 16;
			aes_encrypt_key128(key, en_ctx);
			ctr_init(iv3, iv3 + 4, ctr_buf);	//set iv as the nonce
			aes_ctr_encrypt(pDataBuf, buf, iRemain, ctr_buf, ctr_inc, en_ctx);
			memcpy(pDataBuf, buf, iRemain);
		}

		printf("encrypt = \n");
		print_hex(dataBuf, fsize);

		//Decrypt
		pDataBuf = dataBuf;
		uint8 iv4[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		aes_decrypt_key128(key, de_ctx);
		ctr_init(iv4, iv4 + 4, ctr_buf);
		aes_ctr_decrypt(pDataBuf, buf3, 16, ctr_buf, ctr_inc, en_ctx);
		printf("decrypt = \n");
		print_hex(buf3, fsize);
		printf("\n");
	}

	//CBC encrypt结果
	input: 
	0x48 0x65 0x6c 0x6c 0x6f 0x57 0x6f 0x72 0x6c 0x64 0x21 0x32 0x33 0x34 0x35 0x36---第一笔
	0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10---第二笔
	key:
	0x10,0xa5,0x88,0x69,0xd7,0x4b,0xe5,0xa3,0x74,0xcf,0x86,0x7c,0xfb,0x47,0x38,0x59
	iv:
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	output:(第一笔正常运算,第二笔拿第一笔的结果当作iv运算)
	0xf9,0x28,0xe0,0x98,0x84,0xaa,0x2b,0xa8,0xcc,0x4b,0x73,0xc0,0x93,0x04,0x25,0x0c,
	0xc9,0xa0,0xee,0xff,0x22,0x95,0xb5,0xd8,0x3b,0xea,0x04,0x10,0x00,0x1b,0xd7,0xc6,
	
	//CTR en/decrypt结果---ctr加密和解密数据一样(最后只做异或运算)
	0x48 0x65 0x6c 0x6c 0x6f 0x57 0x6f 0x72 0x6c 0x64 0x21 0x32 0x33 0x34 0x35 0x36---第一笔
	0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10---如果有第二笔	
	key:
	0x10,0xa5,0x88,0x69,0xd7,0x4b,0xe5,0xa3,0x74,0xcf,0x86,0x7c,0xfb,0x47,0x38,0x59
	iv:
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01---在运算之前已经"+1"
	output:(第一笔正常运算,第二笔iv值需要"+1",依此类推
	0x1c,0xa0,0x97,0x8f,0xe4,0x99,0x96,0x9c,0x76,0x9b,0x63,0x46,0xd4,0x6b,0x66,0xf9,
	0xf5,0xdb,0x35,0xd8,0xdc,0x9e,0xa8,0xaa,0x66,0xb1,0xc3,0xd0,0xa5,0x12,0xd3,0x57,