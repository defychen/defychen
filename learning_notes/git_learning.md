# Git Learning

# 1. git概述

## 1.1 git概述

git是目前世界上最先进的分布式版本控制系统(没有之一),是由linus开发的.

## 1.2 SVN v.s git

SVN是集中式版本控制系统,git是分布式版本控制系统.

1.SVN控制版本原理

![](images/svn_version_control.png)

2.git版本控制原理

![](images/git_version_control.png)

集中式(svn)和分布式(git)的区别:

	1.svn每一次commit都需要联网,这就需要网络的等待;断网的情况下,svn会丢掉版本控制记录,当多人的修改
		难以做快速的合并;如果SVN服务器没了,就会丢掉所有历史信息,因为本地只有当前版本以及部分历史信息;
	2.git只有在push、pull(与远程仓库交互)的时候需要联网,平时的commit可以直接操作;断网的情况下,git本
		地保存了版本记录,合并起来很方便;如果git服务器没了,不会丢掉任何git历史信息,因为本地有完整的版本
		库信息.你可以把本地的git库重新上传到另外的git服务商.

## 1.3 安装git