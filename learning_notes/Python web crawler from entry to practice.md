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


