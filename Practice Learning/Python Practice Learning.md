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
	for f in os.listdir():
	    ext = os.path.splitext(f)[-1].lower()
	    for d, exts in formats.items():
	        if not os.path.isdir(d):
	            os.mkdir(d)
	        if ext in exts:
	            shutil.move(f, "{0}/{1}".formats(d, f))
	
	print("Manage finished!")