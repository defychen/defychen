# Python Web Crawler from entry to practice

## Chapter 1 网络爬虫入门

### 1.1 Robots协议

#### 1.1.1 Rotos协议的概念

Robots协议(爬虫协议):全称是"网络爬虫排除标准(Robots Exclusion Protocol)".网站通过Robots协议告诉搜索引擎哪些页面可以抓取,哪些页面不能抓取.该协议是国际互联网界通行的道德规范,每个爬虫都应该遵守该协议.

#### 1.1.2 Robots协议例子

[淘宝网的robots规定网站](http://www.taobao.com/robots.txt)

**1.页面中的内容**

	User-agent:  Baiduspider  //百度爬虫引擎
	Allow:  /article  //表示允许访问/article.htm、/article/12345.com
	Allow:  /oshtml
	Allow:  /ershou
	Allow: /$
	Disallow:  /product/  //禁止访问/product/12345.com
	Disallow:  /  //禁止访问除Allow规定页面外的其他所有页面
	
	User-Agent:  Googlebot  //Google爬虫引擎
	Allow:  /article
	Allow:  /oshtml
	Allow:  /product  //允许访问/product.htm、/product/12345.com
	Allow:  /spu
	Allow:  /dianpu
	Allow:  /oversea
	Allow:  /list
	Allow:  /ershou
	Allow: /$
	Disallow:  /

**2.在百度搜索"淘宝"时会出现的现象**

在百度搜索"淘宝"时会出现"由于该网站的robots.txt文件存在限制指令（限制搜索引擎抓取），系统无法提供该页面的内容描述"说明百度很好的遵守了robot.txt协议.

![](images/robot_rule.png)

**3.在Google搜索时出现的现象**

由于淘宝的Robots协议允许Google爬取产品页面(即Allow:/product).因此在Google中搜索"淘宝 iphone x"能搜索到淘宝中的产品.

PS:爬取网站数据时,应该遵守Robots协议.

### 1.2 Python爬虫的流程

1.获取网页

通过给一个网址发送请求,得到整个网页的数据.

	基础技术:request, urlib, selenium(模拟浏览器);
	进阶技术:多进程多线程抓取,登录抓取,突破IP封禁和服务器抓取.

2.解析网页

从得到的网页数据中提取想要的数据.

	基础技术:re正则表达式, BeautifulSoup和lxml;
	进阶技术:解决中文乱码.

3.存储数据

将提取的数据存储到csv或者数据库中.

	基础技术:存入txt文件和存入csv文件;
	进阶技术:存入Mysql数据和存入MongoDB数据库.

***

## Chapter 2 编写第一个网络爬虫

### 2.1 解析网页工具的使用

解析网页的工具的安装及import:

	安装:
		pip install bs4	//BeautifulSoup位于bs4的库中
	使用方法:
		from bs4 import BeautifulSoup

### 2.2 Anaconda+Jupyter的使用

**1.Anaconda的使用**

Anaconda集成了Python的功能,并且包含了很多用于科学计算的包(e.g.Numpy,Scipy,Pandas,Matplotlib以及用于机器学习的Scikit-Learn,BioPython等),使用起来简单,因此应用比较广.

[Anaconda的下载](https://www.anaconda.com/download/)

安装注意点:

![](images/anaconda_install.png)

	勾选上这两个选项(虽然第一个会显示不推荐,但是还是要选上).安装之后,需要使用的Python,pip和Jupyter
	也一并安装上了.

**2.Jupyter的使用**

当安装了Anaconda之后,Jupyter也一并被安装上了.Jupyter相当于一个编译器,可以直接在Jupyter中写代码进行执行.

Jupyter的启动:

	1.在cmd中输入:
		jupyter notebook //输入该命令即可在浏览器中启动Jupyter主界面.地址默认为:
						 //"http://localhost:8888/tree"
	2.在Jupyter中右边"New"一个新文件	,并编写相应的Python代码.
	3."Alt+Enter"为执行.

PS:在安装Anaconda时将Python3也加入到了Windows的Path变量中,且会在前面.因此输入"python"会执行Python3的应用程序,如果需要Python2和Python3同时都可以执行,可以使用下面方法:

	将Python3的python.exe改名为"python3.exe",python2的不变.
		1.执行"python",调用为python2的应用程序;
		2.执行"python3",调用为python3的应用程序.

### 2.3 编写一个简单的爬虫

#### 2.3.1 step1:获取页面

1.启动jupyter

	在cmd中输入:jupyter notebook

2.在jupyter中输入下面代码

	#!/usr/bin/python
	# -*- coding: utf-8 -*-
	
	import requests
	link = "http://www.santostang.com/"	//此处为爬取唐松的页面,是他自己写的页面,是为了避免商业纠纷
	headers = {'User-Agent' : 'Mozilla/5.0 (Windows; U; Widows NT 6.1; en-US; rv:1.9.1.6)
				Gecko/2009/12/01 Firefox/3.5.6'}	//此处使用headers伪装成浏览器访问
	
	r = reqeusts.get(link, headers = headers)	//后面直接去掉headers结果也是一样
	print (r.text)	//python3的语法

3.结果

	<!DOCTYPE html>
	<html lang="zh-CN">
	<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
	<title>唐松 Santos</title>
	<meta name="description" content="这是唐松 Santos的个人博客，《Python 网络爬虫: 从入门到实践》
	作者" />
	<meta name="keywords" content="唐松 Santos, Python, 网络爬虫, Python 网络爬虫: 从入门到实践,
	Python 爬虫, 大数据" />
	<link rel="apple-touch-icon" href="http://www.santostang.com/wp-content/themes/JieStyle-
	Two-master/images/icon_32.png">
	<link rel="apple-touch-icon" sizes="152x152" href="http://www.santostang.com/wp-content/
	themes/JieStyle-Two-master/images/icon_152.png">
	<link rel="apple-touch-icon" sizes="167x167" href="http://www.santostang.com/wp-content/
	themes/JieStyle-Two-master/images/icon_167.png">
	<link rel="apple-touch-icon" sizes="180x180" href="http://www.santostang.com/wp-content/
	themes/JieStyle-Two-master/images/icon_180.png">
	<link rel="icon" href="http://www.santostang.com/wp-content/themes/JieStyle-Two-master/
	images/icon_32.png" type="image/x-icon">
	<link rel="stylesheet" href="http://www.santostang.com/wp-content/themes/JieStyle-Two-
	master/css/bootstrap.min.css">
	<link rel="stylesheet" href="http://www.santostang.com/wp-content/themes/JieStyle-Two-
	master/css/font-awesome.min.css">

#### 2.3.2 step2:提取需要的数据

1.代码

	import requests
	from bs4 import BeautifulSoup
	
	link = "http://www.santostang.com/"
	headers = {'User-Agent' : 'Mozilla/5.0 (Windows; U; Widows NT 6.1; en-US; rv:1.9.1.6)
			Gecko/2009/12/01 Firefox/3.5.6'}	//此处使用headers伪装成浏览器访问
	r = request.get(link, headers = headers)
	
	soup = BeautifulSoup(r.text, "lxml")
	//因为r.text里面存放的是HTML代码,BeautifulSoup主要用于解析HTML代码.并将其转为soup对象.
	title = soup.find("h1", class_="post-title").a.text.strip()
	/*
	在查找标题时,使用右键->审查元素->在弹出的页面中点击左上角的鼠标键按钮->点击第一个标题,就会显示
	下图的代码
	*/
	print (title)

2.find时应该获取的信息

![](images/get_the_title.png)

3.结果

	4.3 通过selenium 模拟浏览器抓取	//抓取的标题

#### 2.3.3 step3:存储数据

1.代码

	import requests
	from bs4 import BeautifulSoup
	
	link = "http://www.santostang.com/"
	headers = {'User-Agent' : 'Mozilla/5.0 (Windows; U; Widows NT 6.1; en-US; rv:1.9.1.6)
			Gecko/2009/12/01 Firefox/3.5.6'}	//此处使用headers伪装成浏览器访问
	r = request.get(link, headers = headers)
	
	soup = BeautifulSoup(r.text, "lxml")
	//因为r.text里面存放的是HTML代码,BeautifulSoup主要用于解析HTML代码.并将其转为soup对象.
	title = soup.find("h1", class_="post-title").a.text.strip()
	print (title)
	with open('title.txt', 'a+') as f:
		f.write(title)	//写入title文件.该文件保存在:C:\Users\pc-name\title.txt

***

## Chapter 3 静态网页抓取

静态网页:纯粹HTML格式的网页称为静态网页.网页中所有的数据都出现在HTML代码中.

	静态网页主要使用requests库来抓取数据.requests库的安装:
		pip install requests

动态网页:使用AJAX动态加载网页的数据.因此数据不一定全部出现在HTML代码中.

### 3.1 获取响应内容

	import requests
	r = requests.get('http://www.santostang.com/')
	print ('text coding: ', r.encoding)
	/*
		服务器内容使用的文本编码.
		此处返回:text coding:  UTF-8	--->表示使用utf-8编码
	*/
	print ('response status: ', r.status_code)
	/*
		响应的状态码.返回值为:
			200:表示请求成功;
			4xx:表示客户端错误;
			5xx:表示服务器响应错误.
	*/
	print ('text: ', r.text)	//服务器响应的内容.为一些HTML代码
	/*
		r.content:表示字节方式的响应体,会自动解码gzip和deflate编码的响应数据.--->目前用的较少
		r.json:是requests中内置的JSON编码器.--->目前用的较少
	*/

### 3.2 定制requests

### 3.2.1 传递URL参数

URL地址解析:

	http://httpbin.org/get?key1=value1	//"?"后面的为自己构建的信息.以key-value加入到URL中

实例:

	import requests
	key_dict = {'key1':'value1', 'key2':'value2'}
	r = requests.get('http://httpbin.org/get', params=key_dict)
	/*
		自己需要构建的参数可以先写成dict形式,在以params参数构建至URL中.
	*/
	print ('URL: ', r.url)	//此时的url为:http://httpbin.org/get?key1=value1&key2=value2
	print ('response:\n', r.text)
	/*
	响应信息为:
	response: 
	{
		"args": {
			"key1": "value1", 
			"key2": "value2"
		}, 
		"headers": {
			"Accept": "*/*", 
			"Accept-Encoding": "gzip, deflate", 
			"Connection": "close", 
			"Host": "httpbin.org", 
			"User-Agent": "python-requests/2.21.0"
		}, 
		"origin": "113.87.227.238", 
		"url": "http://httpbin.org/get?key1=value1&key2=value2"
	}
	*/

### 3.2.2 定制请求头

	import requests
	headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, 
	like Gecko) Chrome/63.0.3239.132 Safari/537.36',
	           'Host':'www.santostang.com'
	          }
	/*
	headers内容的获取:
		网页->右键->审查元素->选择Network->选择网站名字->选择"Headers"->选择"Request Headers".
		挑选里面需要的信息(e.g.User-Agent,Host等)以字典的形式填充即可.
		PS:User-Agent和user-agent效果一样,可能是因为能够兼容.
	*/
	r = requests.get('http://www.santostang.com/', headers = headers)
	print ('response status: ', r.status_code)

### 3.2.3 发送POST请求

POST请求主要用于在登录的时候保护自己的密码.因为使用GET请求会将密码暴露在URL中,POST则不会.

	import requests
	key_dict = {'key1':'value1', 'key2':'value2'}
	/*
		POST请求的数据也是以key-value形式组装
	*/
	r = requests.post('http://httpbin.org/post', data = key_dict)
	/*
		POST请求使用requests的post方法.
		data为需要保护的信息.
	*/
	print (r.url)	//此时打印出来的网址为"http://httpbin.org/post".相比get少了后面的dict中信息.
	print (r.text)
	/*
	显示为:
	{
	  "args": {}, 
	  "data": "", 
	  "files": {}, 
	  "form": {
	    "key1": "value1", 	//这些信息存放在form中
	    "key2": "value2"
	  }, 
	  "headers": {
	    "Accept": "*/*", 
	    "Accept-Encoding": "gzip, deflate", 
	    "Connection": "close", 
	    "Content-Length": "23", 
	    "Content-Type": "application/x-www-form-urlencoded", 
	    "Host": "httpbin.org", 
	    "User-Agent": "python-requests/2.21.0"
	  }, 
	  "json": null, 
	  "origin": "113.87.227.238", 
	  "url": "http://httpbin.org/post"
	}
	*/

### 3.2.4 超时

超时:如果服务器在设置的timeout时间内没有应答,就会返回异常.防止程序一直等待.

	import requests
	r = requests.post('http://httpbin.org/post', timeout = 0.01)
	/*
		timeout参数:用于设置超时值,单位为s.此处为0.01s,会发生超时,出现timeout的异常.
		一般timeout默认被设置为20s.
	*/

### 3.3 爬虫实践:TOP250电影数据

	import requests
	from bs4 import BeautifulSoup
	import os
	import time
	import threading
	
	picDir = r'D:\\data\\'
	
	class Picture():
		def __init__(self, picName, picSrcUrl):
			self.picName = picName
			self.picSrcUrl = picSrcUrl
	
	def downloadPicture(pictureList):
		if not os.path.isdir(picDir):
			os.makedir(picDir)
		for index in range(len(pictureList)):
			try:
				picture = pictureList[index]
				filename = picDir + picture.picName + '.webp'
				print picture.picSrcUrl
				with open(filename, 'wb') as f:	
				//必须以'wb'打开,因为图片是二进制形式.否则下载下来的图片会形成马赛克.
					f.write(requests.get(picture.picSrcUrl, timeout = 5).content)
			except:
				print picture.picSrcUrl, 'download fail'
				pass
		print 'Total time: ', time.time().__float__() - originalTime.__float__(), 's'
		/*
			time.time():得到时间值.为从格林威治时间到现在的秒数.
			time.time().__float__():转成浮点值.
			time.time().__int__():转成整数值.
		*/
	
	param = ''
	originalTime = time.time()
	listPicture = []
	while True:
		baseUrl = 'https://movie.douban.com/top250' + param
		response = requests.get(baseUrl, timeout = 5)
		response.raise_for_status()
		responseStr = response.text
		soup = BeautifulSoup(responseStr, 'lxml')
		/*
			以"lxml"形式解析.需要安装lxml模块:
			pip install lxml
		*/
		olArticle = soup.find('ol', class_='grid_view')
		liList = divItem = olArticle.find_all('li')
		for index in range(len(liList)):
			stringTitle = ''
			divItemInfo = liList[index].find('div', class_ = 'info')
			divBd = divItemInfo.find('div', class_ = 'bd')
			titleList = divItemInfo.find('div', class_ = 'hd').a.find_all('span')
			strDescription = divBd.p.getText()
			strRatingStar = divBd.div.find_all('span')[1].getText()
			strComment = divBd.div.find_all('span')[3].getText()
			if divBd.find('p', class_ = 'quote'):
				strQuote = divBd.find('p', class_ = 'quote').span.getText()
			for indexTitle in range(len(titleList)):
				stringTitle = stringTitle + titleList[indexTitle].getText()
			'''
			print 'Movie name: ' + stringTitle.encode('utf-8') \
				+ '\nMovie star: ' + strRatingStar.encode('utf-8') \
				+ '\nMovie comments: ' + strComment.encode('utf-8') \
				+ '\nMovie quote: ' + strQuote.encode('utf-8') \
				+ '\nMovie description: ' + strDescription.encode('utf-8').strip() + '\n'
			'''
			print 'Movie name: ' + stringTitle.encode('gbk', 'ignore') \
				+ '\nMovie star: ' + strRatingStar.encode('gbk', 'ignore') \
				+ '\nMovie comments: ' + strComment.encode('gbk', 'ignore') \
				+ '\nMovie quote: ' + strQuote.encode('gbk', 'ignore') \
				+ '\nMovie description: ' + strDescription.encode('gbk', 'ignore').strip() + '\n'
			/*
				windows下,中文需要:encode('gbk', 'ignore')即以gbk编码,utf-8会显示乱码.
			*/
			divItemPic = liList[index].find('div', class_ = 'pic')
			listPicture.append(Picture(divItemPic.a.img.get('alt'), divItemPic.a.img.get('src')))
		print '\n'
		divpaginator = soup.find('div', class_ = 'paginator')
		spanNext = divpaginator.find('span', class_ = 'next')
		if not spanNext.link:
			break
	
		param = spanNext.link.get('href')
	
	try:
		threadDownload = threading.Thread(target = downloadPicture, args = (listPicture, ))
		threadDownload.setDaemon(False)
		threadDownload.start()
	except:
		print 'Error: unable to start thread'