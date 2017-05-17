# C Language Skill
***

## 1、malloc函数

void *malloc(size_t size);	//申请一段size字节大小的buffer,返回"void *"

	tVA_DSCR_StbSession *pStbSession;
	pStbSession = (tVA_DSCR_StbSession *)malloc(sizeof(tVA_DSCR_StbSession));

## 2、指针赋值

	char *puc_key;
	char *pEvenKey = {0xbc, 0x0c, 0x94, 0x1e, 0xbc, 0xd2, 0xa1, 0x3e, 0x89, 0xc9, 
	0x84, 0x6a, 0x51, 0x9e, 0x90, 0x8d};
	char *pOddKey = {0xbc, 0x0c, 0x94, 0x1e, 0xbc, 0xd2, 0xa1, 0x3e, 0x89, 0xc9,
	0x84, 0x6a, 0x51, 0x9e, 0x90, 0x8d};
	/*需要将pEvenKey和pOddKey拷贝给puc_key*/
	memcpy(puc_key, pOddKey, 16);
	memcpy(puc_key + 16, pEvenKey, 16);
	/*使用赋值是错误的:
	puc_key = pOddKey;
	puc_key + 16 = pEvenKey;	/*这种方式意味着将指针指向的位置变了,而不是copy内容给puc_key*/
	*/
	
## 3、结构体变量赋值

	typedef struct aui_trng_attr {
		unsigned char uc_dev_idx;
	}aui_trng_attr;
	aui_trng_attr attr = {0};	/*声明结构体变量时赋值*/

	/*The second example*/
	typedef struct aui_trng_param {
		unsigned char *puc_rand_output_buffer;
		unsigned long ul_rand_bytes;
	}aui_trng_param;
	aui_trng_param trng_data = {0, 0};	/*puc_rand_output_buffer指针为null, ul_rand_bytes值为0*/

## 4、线程的使用

**va_zapping.c函数**

	#include <pthread.h>	/*包含的线程头文件*/
	...
	typedef struct
	{
		aui_hdl dsc_hdl;	/**/
		pthread_mutex_t va_mutex;	/*linux线程互斥锁,主要用于锁住全局变量*/
		pthread_cond_t dsc_cond;	/*linux线程条件变量,主要用于某个线程等待另一个线程的消息,决定是否继续等待*/
		INT audioFlag;
		INT videoFlag;
	}T_VA_Handle;
	T_VA_Handle *g_pHandle;		/*声明一个全局变量*/

	/*va_zapping.c中g_pHandle的初始化*/
	g_pHandle = (T_VA_Handle *)malloc(sizeof(g_pHandle));
	g_pHandle->dsc_hdl = NULL;
	g_pHandle->audioFlag = 0;
	g_pHandle->videoFlag = 0;
	pthread_mutex_init(&g_pHandle->va_mutex, NULL);	/*初始化互斥锁*/
	pthread_cond_init(&g_pHandle->dsc_cond, NULL);	/*初始化条件变量*/

	pthread_t tid;	/*线程ID*/
	tid = pthread_self();	/*获得线程的ID*/
	printf("Va_zapping pthread: %lu\n", (unsigned long)tid);	/*打印线程ID,为lu(unsigned long)类型*/

	pthread_mutex_lock(&g_pHandle->va_mutex);	/*得到互斥锁,下面的代码需要访问全局变量*/
	if(!g_pHandle->dsc_hdl)
	{
		printf("Execute there: %s, %d\n", __func__, __LINE__);
		pthread_cond_wait(&g_pHandle->dsc_cond, &g_pHandle->va_mutex);
		/*等待条件变量,没有等到会自动释放互斥锁.等待被唤醒*/
	}
	pthread_mutex_unlock(&g_pHandle->va_mutex);	/*释放互斥锁*/

**va_dscr.c函数**
	
	pthread_mutex_lock(&g_pHandle->va_mutex);
	...
	pthread_cond_broadcast(&g_pHandle->dsc_cond);	/*广播条件变量,有等待的地方会被唤醒*/
	pthread_mutex_unlock(&g_pHandle->va_mutex);

## 5、调试程序方法

	1)printf("Execute there: %s, %d\n", __func__, __LINE__);	/*打印出程序执行到的函数和行数*/
	2)getchar();	/*等待终端输入一个字符*/

## 6、数据类型

	unsigned long(无符号数)的数据范围是:0~0xFFFFFFFF.
	当以"%d"打印时(是以有符号数方式打印),0xFFFFFFFF会显示"-1".
	计算方式为,最高位权重为"-1",即为:(-1)*2^31+2^30+3^29+...+=-1
	e.g. 两位(11)时:(-1)*2+1 = -1.
	所以有:0xFFFFFFFF = -1, 0xFFFFFFFE = -1, 0xFFFFFFFD = -3.
	但是当以"%x"方式打印时,就会打印正确的:0xFFFFFFFF.

## 7、写代码时printf输出的技巧

在写代码的过程中经常会有很多信息需要输出,但是当完成代码后又需要去掉这些printf,可以使用下面的"宏"技巧方便调试

	#define VO_DSCR_DEBUG_ENABLE	/*使能DEBUG宏*/
	#ifdef VO_DSCR_DEBUG_ENABLE
	#define VO_DSCR_DEBUG(fmt, args...)	\ /*类似于printf(fmt(格式), args(参数)),一定需要"\"---另起一行*/
		printf("\033[0;32;31mFILE: %s, FUNC: %s, LINE: %d\033[m"fmt, __FILE__, __func__, __LINE__, ##args)
		/*"\033[0;32;31m ... \033[m"---表示使用颜色打印调试信息,但是在做Viaccess Certification时没有成功显示不同颜色*/
		/*__FILE__:显示文件名("e.g.:src/vo_dscr.c").后面的"fmt"表示还可以继续添加后续输出打印,
		"##args"表示可变参数,可以没有参数.即VO_DSCR_DEBUG()除了添加打印头之外还可以按照默认的printf()格式输出*/
	#define VO_DSCR_DUMP(prompt, data, len)	\
		do {\
			int k, l = (len); \
			printf("\033[0;32;32m%s\033[m\n", prompt); \	/*输出提示符"字符串"*/
			for(k=0, k<l; k++){ \
				printf("0x%02x, ", *(BYTE *)((unsigned int)data+k)); \	
				/*data:指针(或数组名);(BYTE *)==(unsigned char *)---无符号字节类型指针*/
				if((k+1)%16==0)	\	/*16个输出一个换行*/
					printf("\n");
			} \
			if(k%16!=0) \	/*打印完成后,如果还有剩下的但又不是16的整数倍,就需要输出一个空格(因为整数倍的上一步的已经输出)*/
				printf("\n"); \
		}while(0)
	#else
	#define VO_DSCR_DEBUG(fmt, args...)   do{}while(0)
	#define VO_DSCR_DUMP(prompt, data, len)   do{}while(0)
	#endif
