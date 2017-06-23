# Markdown usage
## 1 标题--在前面加"#"，不同"#"代表几级标题
### e.g.如本usage中的各种标题
## 2 列表--无序列表文字前加"-或*",有序在文件前加"1,2,3"即可
### e.g.
##### 无序列表:
* 1
* 2
* 3
##### 有序列表:
1. 1
2. 2
3. 3
## 3 引用，文本前加">"
> 这里是引用
## 4 链接，语法为:[]()
### e.g.[baidu](http://baidu.com)
欢迎来到[百度](http://baidu.com)
## 5 粗体与斜体,**xxx**为粗体;*xxx*为斜体
### e.g. 粗体：**hello**；斜体：*hello*;  
## 6 代码框,将代码整体缩进一个tab键即可
### e.g.
 	static int dsc_fetch_streamId(struct ca_dsc_session *s)
 	{
		int ret = (-EIO);
	
		/*Get free stream ID*/
		s->stream_id = ali_dsc_get_free_stream_id(s->dsc, s->dma_mode);
		if (s->stream_id == ALI_INVALID_CRYPTO_STREAM_ID) {
			dev_dbg(s->dsc->dev, "Get free stream ID error!\n");
			goto LOCAL_CLEAR;
		}
	
		dev_dbg(s->dsc->dev, "stream_id[%x]\n", s->stream_id);
	
		return 0;
	
		 LOCAL_CLEAR:
		dsc_free_streamid(s);
		return ret;
 	}
## 7 分割线，三个"*"号
### e.g.
***