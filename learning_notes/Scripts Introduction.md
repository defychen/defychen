# Scripts Introduction

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
