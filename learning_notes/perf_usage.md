# perf usage

## 1.1 系统性能优化

系统级性能优化通常包含两个阶段:性能剖析(performance profiling)和代码优化.

```
性能剖析:寻找性能瓶颈,查找引发性能问题的原因及热点代码.
	->主要是借助现有的profiling工具(e.g. perf等).
代码优化:针对具体性能问题而优化代码或编译选项,以改善软件性能.
	->主要是借助开发者的经验,编写简洁高效的代码,甚至在汇编级别合理使用各种指令,合理安排各种指令的执行顺序等.
```

性能优化主要关注以下3种事件:

```
1.hardware event:由硬件PMU部件产生,在特定的条件下探测性能事件是否发生以及发生的次数(e.g. cache命中);
2.software event:由内核产生的事件,分析在各个功能模块种,统计和操作系统相关性能事件(e.g.进程切换、tick数等);
3.tracepoint event:由内核中静态tracepoint所触发的事件,这些tracepoint用来判断程序运行期间内核的行为细节(e.g. slab分配器的分配次数等).
```

## 1.2 perf介绍

linux构建了一个新的基于内核的子系统,叫性能计数器.该性能计数器提供一个性能分析框架,比如硬件方面包含获取CPU、PMU(Performance Monitoring Unit)等信息;软件方面包含获取软件计数器、tracepoint等信息.

perf是一款Linux性能分析工具.通过perf,应用程序可以利用PMU、tracepoint和内核中的计数器来进行性能统计.不但可以分析制定应用程序的性能问题(per thread),也可以用来分析内核的性能问题,当然也可以同时分析应用程序和内核,从而全面理解应用程序中的性能瓶颈.

```
通过perf可以分析程序运行期间发生的硬件行为(e.g. instruction retired, processor clock cycles等)和软件行为(page fault, 进程切换等).
```

## 1.3 perf的安装

### 1.3.1 错误的安装方法

在linux终端执行:

```
perf
/*
    The program 'perf' is currently not installed. You can install it by typing:
    apt install linux-tools-common
    // 提示perf没有安装
*/
```

一般情况下perf可通过以下命令安装:

```
apt install linux-tools-common	// 执行刚才提示的命令
/*
	在较新的系统中执行上述命令安装的perf还是不能用.
*/
perf
/*
    WARNING: perf not found for kernel 4.4.0-31

      You may need to install the following packages for this specific kernel:
        linux-tools-4.4.0-31-generic
        linux-cloud-tools-4.4.0-31-generic

      You may also want to install one of the following packages to keep up to date:
        linux-tools-generic
        linux-cloud-tools-generic
*/
如果按照上述提示去安装这些package,仍会提示找不到.可通过下述的编译源码的方式安装.
```

### 1.3.2 正确的安装方法

#### 1.3.2.1 下载内核源码

尽量拉与安装的linux相同的版本--->参考"Ubuntu&Qemu usage"中的1.10 linux源码下载地址.

#### 1.3.2.2 解压源码并编译

```
cd ./linux-source-dir/tools/perf
make
/*
	第一次编译make会报:
    config/Makefile:120: *** Error: flex is missing on this system, please install it.  Stop.
    Makefile:68: recipe for target 'all' failed
    即需要将flex安装上:
    	apt install flex
    	apt install bison	// flex安装后会要求安装bison
    上述依赖安装完后,再次执行make即可成功编译.
*/
// 编译完成之后,在该目录下就会生成名字叫"perf"的应用程序.
```

#### 1.3.2.3 拷贝perf到/usr/bin目录下

```
sudo cp perf /usr/bin	// 之后就可以直接使用perf了
```

## 1.4 perf的使用

perf的命令归档如下:

| 序号 | 命令          | 作用                                                         |
| ---- | ------------- | ------------------------------------------------------------ |
| 1    | annotate      | 解析perf record生成的perf.data文件，显示被注释的代码。       |
| 2    | archive       | 根据数据文件记录的build-id，将所有被采样到的elf文件打包。利用此压缩包，可以再任何机器上分析数据文件中记录的采样数据。 |
| 3    | bench         | perf中内置的benchmark，目前包括两套针对调度器和内存管理子系统的benchmark。 |
| 4    | buildid-cache | 管理perf的buildid缓存，每个elf文件都有一个独一无二的buildid。buildid被perf用来关联性能数据与elf文件。 |
| 5    | buildid-list  | 列出数据文件中记录的所有buildid。                            |
| 6    | diff          | 对比两个数据文件的差异。能够给出每个符号（函数）在热点分析上的具体差异。 |
| 7    | evlist        | 列出数据文件perf.data中所有性能事件。                        |
| 8    | inject        | 该工具读取perf record工具记录的事件流，并将其定向到标准输出。在被分析代码中的任何一点，都可以向事件流中注入其它事件。 |
| 9    | kmem          | 针对内核内存（slab）子系统进行追踪测量的工具                 |
| 10   | kvm           | 用来追踪测试运行在KVM虚拟机上的Guest OS。                    |
| 11   | list          | 列出当前系统支持的所有性能事件。包括硬件性能事件、软件性能事件以及检查点。 |
| 12   | lock          | 分析内核中的锁信息，包括锁的争用情况，等待延迟等。           |
| 13   | mem           | 内存存取情况                                                 |
| 14   | record        | 收集采样信息，并将其记录在数据文件中。随后可通过其它工具对数据文件进行分析。 |
| 15   | report        | 读取perf record创建的数据文件，并给出热点分析结果。          |
| 16   | sched         | 针对调度器子系统的分析工具。                                 |
| 17   | script        | 执行perl或python写的功能扩展脚本、生成脚本框架、读取数据文件中的数据信息等。 |
| 18   | stat          | 执行某个命令，收集特定进程的性能概况，包括CPI、Cache丢失率等。 |
| 19   | test          | perf对当前软硬件平台进行健全性测试，可用此工具测试当前的软硬件平台是否能支持perf的所有功能。 |
| 20   | timechart     | 针对测试期间系统行为进行可视化的工具                         |
| 21   | top           | 类似于linux的top命令，对系统性能进行实时分析。               |
| 22   | trace         | 关于syscall的工具。                                          |
| 23   | probe         | 用于定义动态检查点。                                         |

### 1.4.1 perf的常用命令

#### 1.4.1.1 统计程序运行时间占比

```
perf record ./test	// 统计test程序运行时间占比,只需要运行一段时间即可.
/*
	此时会在运行目录下生成:
		perf.data和perf.data.old
*/
perf report	// 会自动读取perf record记录的信息.可以看到各个函数调用的热点信息.
```































