# UltraISO+Ubuntu16.04 Installation

## 1.Ubuntu16.04下载

下载地址:[Ubuntu Release](http://releases.ubuntu.com/)--->这个地址国内下载很慢.

[ubuntu下载地址](http://mirrors.163.com/ubuntu-releases/)--->这个地址块.

## 2.UltraISO安装

### 2.1 UltraISO下载

下载地址:[UltraISO下载](http://www.upantool.com/qidong/2011/UltraISO_v9.5.0.2800.html)

	将网站拉到最后面,选择"普通下载地址"中的一个下载即可.

### 2.2 安装

安装常规安装即可.

## 3.制作U盘启动盘

1.打开UltraISO软件,点击"打开文件"按钮,如下图.选中下载的Ubuntu的iso文件,进行打开.

![](images/UltraISO_open_operation.png)

2.打开Ubuntu的iso文件后的效果如下图:

![](images/UltraISO_open_image.png)

3.点击"启动"菜单->选择"写入硬盘映像..."

![](images/UltraISO_writing_image.png)

4.选择写入方式为"USB-HDD+"或"USB-HDD";并选择隐藏启动分区为:"隐藏"或"高级隐藏"(推荐).

![](images/UltraISO_writing_operation.png)

	PS:写入方式以"USB-HDD+"安装的时候会报错(failed to load ldlinux.c32),改成"RAW",其他不用去选择可以
	安装成功.所以这里写入方式需要改成"RAW".第5步也直接跳过.

5.点击"便捷启动"->选择"写入新的驱动器引导扇区"->选择"Syslinux".

![](images/UltraISO_syslinux.png)

	此处会出现一个"提示",选择"是"即可.然后就会出现"引导扇区写入成功"的消息框.

6.点击"写入",选择"是".会出现提示"驱动器...所有数据将丢失".选择"是",然后就是写入到U盘的等待过程.

7.至此,U盘启动工具制作完成.

## 4.Ubuntu U盘启动

参考:[U盘启动安装Ubuntu16.04详解](https://blog.csdn.net/lingyunxianhe/article/details/81415675).

此处略.

## 5.格式化U盘

上述安装完Ubuntu后,U的格式会被污染、大小会被占用(windows显示时会出现没有空间).可以重新被格式化.方法如下:

	打开UltraISO软件->直接点击"启动"菜单(不能打开某个光盘)->选择"写入硬盘映像"->在弹出的"写入硬盘映像"
	窗口中直接点击"写入"按钮(都使用默认值)即可进行格式化,恢复到原来的大小.