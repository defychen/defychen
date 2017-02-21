## github usage
****

**1)新建一个目录:**

	mkdir github_push

**2)初始化版本仓库(让git管理本地目录):**
	
	git init

**3)添加需要上传到github仓库的文件到该目录**

**4)将文件添加到上传队列:**
	
	git add .	//.代表所有添加的文件

**5)提交缓存(还在本地):**

	git commit -m " "	//" "表示注释,方便自我查看

**6)将本地commit后的添加到github仓库:**

	git remote add origin https://github.com/defychen/defychen

**7)push到远程仓库(github仓库):**

	git push origin master	//之后会输入帐号(username),密码(password)