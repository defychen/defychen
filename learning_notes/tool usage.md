# Tool usage

## 1. VBS脚本

VBS(Visual Basic Script):是基于Visual Basic的脚本语言.

实例---循环自动启动脚本

	/*reboot_while.vbs*/
	Sub Main()

	while(1)

	crt.screen.send "reboot"&chr(13)

	crt.screen.WaitForString "MPLG"

	wend
	End Sub

执行---在Secure CRT中执行

在Secure CRT中选择"脚本(S)"--->执行(R),然后选择该脚本所在的位置即可.

## 2. UltraEdit如何让16进制显示时每行显示32/188字节

	一般在UltraEdit显示16进制时(即一个.bin的二进制文件)每行显示16字节,修改为显示32/188字节方法:
	高级--->配置--->编辑器显示--->十六进制编辑显示--->在每行十六进制字符数中输入"32/188",确定即可.
