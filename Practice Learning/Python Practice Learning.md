# Python Practice Learning

## 1. 接收命令行参数

### 1.1 代码

	import sys
	def dmi():
	    body_weight = float(sys.argv[1])
		/*
			sys.argv[0]:为python运行时的文件名;
			sys.argv[1]:运行时传入的第一个参数;
			...
		*/
	    height = float(sys.argv[2])
	    return body_weight / (height ** 2)
	
	if __name__ == "__main__":
	    result = dmi()
	    print(f"Your dmi is: {result:.3f}")
		/*
			python3.6后增加了f"xxxx{var}"用于字符串格式化.其中"{var}"在运行时会被var的值代替.
			此处表示:result会被result的值代替,".3f"表示保留小数点后3位(必须是f,因为浮点数才有小数).
		*/

### 1.2 测试

	python test.py 80 1.8	--->结果为:Your dmi is: 24.691

## 2. 格式化字符简化打印调试

### 2.1 代码

	name = 'Tom'
	age = 22
	print('name = {}, age = {}'.format(name, age))
	/*
		字符串的format函数用于格式化字符串.format的第一个参数的值会代替第一个{},第二个参数会代替第二个{};
		也可以:
		1.print('name={name}, age={age}'.format(name, age))--->直接指定代替的参数名;
		2.print('name={0}, age={1}'.format(name, age))--->使用参数名索引指定(从0开始);
		指定占用的位数及左右对齐:
		print('name = {name:>10}, age = (age:>10)'.format(name, age))
			1.":"必须是冒号开头;
			2.">"表示右对齐;
			3."10"表示占用10位.
	*/
	print(f"name = {name:>10}, age = {age:>10}")
	/*
		python3.6以后支持:f-string格式化字符串输出.
		print(f"name = {name:>10}, age = {age:>10}"):后面不用format,直接将name写入到"{}"中.
	*/

### 2.2 测试

	结果为:
	name = Tom, age = 22
	name =        Tom, age =         22		//右对齐10位

## 3. 整理文件

### 3.1 代码

	import os
	import shutil
	
	formats = {
	    "Audio" : [".mp3", ".wav"],
	    "Video" : [".mp4", ".avi", ".mov"],
	    "Picture" : [".jpeg", ".jpg", ".png", ".bmp"],
	    "Doc" : [".txt", ".pdf", ".doc", ".docx"],
	    "Application" : [".exe", ".msi"],
	    "Tar" : [".zip", ".rar"]
	}
	
	os.chdir(r"xxx")
	for f in os.listdir():	//os.listdir()列出当前目录下的所有文件,返回一个list
	    ext = os.path.splitext(f)[-1].lower()
		/*
			os.path.splitext(f):分离文件名(包括路径)和扩展名;
			os.path.splitext(f)[-1]:拿到文件的扩展名;
			os.path.splitext(f)[-1].lower():将文件的扩展名转变为小写.
		*/
	    for d, exts in formats.items():
			/*
				dict.items():遍历dict的key-value,返回一个key, value(如果value为一个list/tuple,
					也会直接返回).
			*/
	        if not os.path.isdir(d):	//not os.path.isdir():判断不是目录.
	            os.mkdir(d)
	        if ext in exts:
	            shutil.move(f, "{0}/{1}".format(d, f))
				/*
					shutil.move(src, tgt):移动文件/重命名文件
					shutil.move(f, "{0}/{1}".format(d, f)):将文件f移动到d目录下.
				*/
	
	print("Manage finished!")

### 3.2 测试

略.

## 4. 制作二维码直接联网

### 4.1 安装二维码生成器的库

	pip install segno

### 4.2 segno的简单使用

**1.micro微信码--->用的少**

	import segno
	qr = segno.make("Defy Chen")
	print(qr)
	# <segno.QRCode object at 0x00E2CEB0>
	print(qr.version)
	# M3: M代表micro,只有一个定位点(标准的二维码有3个定位点)
	print(qr.designator)
	# M3-L:容错信息(L, M, Q, H)
	qr.save("qr1.png")
	
结果:

![](images/micro_qrcode.png)

**2.标准二维码--->用的多**

	qr = segno.make("Defy Chen", micro = False)
	print(qr.version)   # 结果1:表示最小级别尺寸的标准二维码
	print(qr.designator) # 1-Q
	qr.save("qr2.png")
	qr.save("qr3.png", scale = 10) #放大尺寸为10

结果:

![](images/standard_qrcode.png)

### 4.3 segno helpers制作名片二维码

1.代码

	from segno import helpers
	qr = helpers.make_mecard(name = "Defy chen", email = "xxx@qq.com", phone = "18888888888")
	qr.save("card.png", scale = 10)

2.结果

![](images/card.png)

### 4.4 segno helpers制作wifi二维码

1.代码

	from segno import helpers
	qr = helpers.make_wifi(ssid = "My wifi", password = "123456", security = "WPA")
	print(qr)   #<segno.QRCode object at 0x00EA25B0>
	print(qr.version)   # 3
	print(qr.designator)    # 3-M
	qr.save("wifi.png", scale = 10)

2.结果

![](images/wifi.png)

## 5. 提取音视频中文本内容

### 5.1 语音识别库的安装

	pip install SpeechRecognition

### 5.2 SpeechRecognition的识别器

	recognize_bing()--->Microsoft Bing Speech
	recognize_google()--->Google Web Speech API
	recognize_google_could()---Google Cloud Speech(需要安装google-cloud-speech package)
	recognize_houndify()--->Houndify by SoundHound
	recognize_ibm()--->IBM Speech to Text
	recognize_sphinx()--->CMU Sphinx(需要安装PocketSphinx)
	recognize_wit()--->Wit.ai
	
	PS:只有recognize_sphinx()可与CMU Sphinx引擎脱机工作,其他6个需要联网--->中文识别使用这个.
