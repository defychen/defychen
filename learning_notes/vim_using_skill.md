## vim使用技巧

**Q1:在windows下编辑的脚本,难免会出现"^M"这样的错误(这种错误是windows下的换行符).**

*解决办法:*

*方法1)使用vim打开该脚本,然后执行:*
	
	:set ff=unix

*方法2)使用dos2unix命令:*

	dos2unix aes_test.py

