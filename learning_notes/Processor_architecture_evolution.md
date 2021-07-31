# Processor Architecture Evolution

## 1. Intel处理器架构演进

### 1.1 Intel架构演进规律

大约10年前,Intel宣布了著名的"滴答"(Tick-Tock)战略模式(也叫制程-架构节奏)."嘀嗒"意为钟摆的一个周期,"嘀"(Tick)代表芯片工艺提升、晶体管变小(e.g. 22nm到14nm),而"嗒"(Tock)代表工艺不变,芯片核心架构的升级(即微架构的升级).一个"嘀嗒"代表完整的芯片发展周期,耗时两年.

但是发展到14nm制程后,Intel已经力不从心了,从skylake架构开始,Intel打破了"制程-架构"节奏,采用"制程-架构-优化"(PAO)三步走战略.

### 1.2 Intel历史架构演进图

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-9wq8{border-color:inherit;text-align:center;vertical-align:middle}
</style>
<table class="tg">
<thead>
  <tr>
    <th class="tg-9wq8" rowspan="2">Architectural change</th>
    <th class="tg-9wq8" rowspan="2">Fabrication process</th>
    <th class="tg-9wq8" rowspan="2">Micro-architecture</th>
    <th class="tg-9wq8" rowspan="2">Code names</th>
    <th class="tg-9wq8" rowspan="2">Release date</th>
    <th class="tg-9wq8" colspan="5">Processors</th>
  </tr>
  <tr>
    <td class="tg-9wq8">8P/4P<br>Server</td>
    <td class="tg-9wq8">4P/2P<br>Server/<br>Workstation</td>
    <td class="tg-9wq8">Enthusiast/<br>Workstation</td>
    <td class="tg-9wq8">Desktop</td>
    <td class="tg-9wq8">Mobile</td>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-9wq8">Tick(new<br>fabrication<br>process)</td>
    <td class="tg-9wq8" rowspan="2">65nm</td>
    <td class="tg-9wq8">P6, NetBurst</td>
    <td class="tg-9wq8">Presle,<br>Cedar,<br>Mill,<br>Yonah</td>
    <td class="tg-9wq8">2006-01-05</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8">Presler</td>
    <td class="tg-9wq8">Cedar<br>Mill</td>
    <td class="tg-9wq8">Yonah</td>
  </tr>
  <tr>
    <td class="tg-9wq8">Tock(new<br>micro-<br>architecture)</td>
    <td class="tg-9wq8" rowspan="2">Core</td>
    <td class="tg-9wq8">Merom</td>
    <td class="tg-9wq8">2006-07-27</td>
    <td class="tg-9wq8">Tigerton</td>
    <td class="tg-9wq8">Woodcrest<br>Clovertown</td>
    <td class="tg-9wq8">Kentsfield</td>
    <td class="tg-9wq8">Conroe</td>
    <td class="tg-9wq8">Merom</td>
  </tr>
  <tr>
    <td class="tg-9wq8">Tick</td>
    <td class="tg-9wq8" rowspan="2">45nm</td>
    <td class="tg-9wq8">Penryn</td>
    <td class="tg-9wq8">2007-11-11</td>
    <td class="tg-9wq8">Dunnington</td>
    <td class="tg-9wq8">Harpertown</td>
    <td class="tg-9wq8">Yorkfield</td>
    <td class="tg-9wq8">Wolfdale</td>
    <td class="tg-9wq8">Penryn</td>
  </tr>
  <tr>
    <td class="tg-9wq8">Tock</td>
    <td class="tg-9wq8" rowspan="2">Nehalem</td>
    <td class="tg-9wq8">Nehalem</td>
    <td class="tg-9wq8">2008-11-17</td>
    <td class="tg-9wq8">Beckton</td>
    <td class="tg-9wq8">Gainestown</td>
    <td class="tg-9wq8">Bloomfield</td>
    <td class="tg-9wq8">Lynnfield</td>
    <td class="tg-9wq8">Clarksfield</td>
  </tr>
  <tr>
    <td class="tg-9wq8">Tick</td>
    <td class="tg-9wq8" rowspan="2">32nm</td>
    <td class="tg-9wq8">Westmere</td>
    <td class="tg-9wq8">2010-01-04</td>
    <td class="tg-9wq8">Westmere-<br>EX</td>
    <td class="tg-9wq8">Westmere-<br>EP</td>
    <td class="tg-9wq8">Gulftown</td>
    <td class="tg-9wq8">Clarkdale</td>
    <td class="tg-9wq8">Arrandale</td>
  </tr>
  <tr>
    <td class="tg-9wq8">Tock</td>
    <td class="tg-9wq8" rowspan="2">Sandy Bridge</td>
    <td class="tg-9wq8">Sandy Bridge</td>
    <td class="tg-9wq8">2011-01-09</td>
    <td class="tg-9wq8">(Skipped)</td>
    <td class="tg-9wq8">Sandy<br>Bridge-EP</td>
    <td class="tg-9wq8">Sandy<br>Bridge-E</td>
    <td class="tg-9wq8">Sandy<br>Bridge</td>
    <td class="tg-9wq8">Sandy<br>Bridge-M</td>
  </tr>
  <tr>
    <td class="tg-9wq8">Tick</td>
    <td class="tg-9wq8" rowspan="3">22nm</td>
    <td class="tg-9wq8">Ivy Bridge</td>
    <td class="tg-9wq8">2012-04-29</td>
    <td class="tg-9wq8">Ivy Bridge-<br>EX</td>
    <td class="tg-9wq8">Ivy Bridge-<br>EP</td>
    <td class="tg-9wq8">Ivy Bridge-<br>E</td>
    <td class="tg-9wq8">Ivy Bridge</td>
    <td class="tg-9wq8">Ivy Bridge-<br>M</td>
  </tr>
  <tr>
    <td class="tg-9wq8">Tock</td>
    <td class="tg-9wq8" rowspan="3">Haswell</td>
    <td class="tg-9wq8">Haswell</td>
    <td class="tg-9wq8">2013-06-02</td>
    <td class="tg-9wq8">Haswell-EX</td>
    <td class="tg-9wq8">Haswell-EP</td>
    <td class="tg-9wq8">Haswell-E</td>
    <td class="tg-9wq8">Haswell-DT</td>
    <td class="tg-9wq8">Haswell-MB<br>(notebooks)<br>Haswell-LP<br>(ultrabooks)</td>
  </tr>
  <tr>
    <td class="tg-9wq8">Refresh</td>
    <td class="tg-9wq8">Haswell,<br>Refresh,<br>Devil's<br>Canyon</td>
    <td class="tg-9wq8">2014-05-11,<br>2014-06-02</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Tick</td>
    <td class="tg-9wq8" rowspan="5">14nm</td>
    <td class="tg-9wq8">Broadwell</td>
    <td class="tg-9wq8">2014-09-05</td>
    <td class="tg-9wq8">Broadwell-EX</td>
    <td class="tg-9wq8">Broadwell-EP</td>
    <td class="tg-9wq8">Broadwell-E</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Tock</td>
    <td class="tg-9wq8" rowspan="5">Skylake</td>
    <td class="tg-9wq8">Skylake</td>
    <td class="tg-9wq8">2015-08-05</td>
    <td class="tg-9wq8">Skylake-SP</td>
    <td class="tg-9wq8">Skylake-SP</td>
    <td class="tg-9wq8">Skylake-X</td>
    <td class="tg-9wq8">Skylake</td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8" rowspan="3">Optimizations<br>(refreshed)</td>
    <td class="tg-9wq8">Kaby Lake</td>
    <td class="tg-9wq8">2017-01-03</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8">KabyLake-X</td>
    <td class="tg-9wq8">Kaby Lake</td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Kaby Lake<br>R</td>
    <td class="tg-9wq8">2017-08-21</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Coffee Lake</td>
    <td class="tg-9wq8">2017-10-05</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8">Coffee Lake</td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Process</td>
    <td class="tg-9wq8" rowspan="3">10nm</td>
    <td class="tg-9wq8">Cannon Lake</td>
    <td class="tg-9wq8">2018</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Architecture</td>
    <td class="tg-9wq8" rowspan="3">Ice Lake</td>
    <td class="tg-9wq8">Ice Lake</td>
    <td class="tg-9wq8">2018/<br>2019?</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Optimization</td>
    <td class="tg-9wq8">Tiger Lake</td>
    <td class="tg-9wq8">2019?</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Process</td>
    <td class="tg-9wq8" rowspan="3">7nm</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Architecture</td>
    <td class="tg-9wq8" rowspan="3"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Optimization</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Process</td>
    <td class="tg-9wq8" rowspan="3">5nm</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Architecture</td>
    <td class="tg-9wq8" rowspan="2"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
  <tr>
    <td class="tg-9wq8">Optimization</td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
    <td class="tg-9wq8"></td>
  </tr>
</tbody>
</table>

### 1.3 各代处理器架构介绍

#### 1.3.1 P6架构

P6是 Intel 的第六代微架构,最早用于1995 年的Pentium Pro处理器,后面2000的NetBurst感觉应该也算是包含在P6这个大系列里面,直到 2006 年的Core为止.这个横跨了将近10年的架构系列最早是600nm的工艺,一直到最后达到了 65nm,是Intel走上比较规则的架构发展之路的一个起点.

P6相对于之前的架构加入了很多新的技术:	

```
1.预测执行(Speculation)和乱序执行;
2.14级流水线,第一代奔腾的流水线只有5级,P6的14级在当时是最深的;
3.片内的L2 cache;
4.物理地址扩展到最大36-bit,理论上这个位宽最大可以支持到64G的内存(虽然制程的地址空间还是只能用到4G);
5.寄存器重命名;
6.MMX和SSE指令集扩展,开始SIMD的思路.
```

从这代开始,奠定了Intel沿着摩尔定律发展的Tick-Tock架构演进道路:

```
Tick:改进制程工艺,微架构基本不做大改,重点在把晶体管的工艺水平往上提升;
Tock:改进微架构设计,保持工艺水平不变,重点在使用更复杂、更高级的架构设计.
```

P6的末尾阶段,首次出现了双核,不过当时的双核基本上像是把两个单核用胶水粘在一起的感觉.

#### 1.3.2 Core架构

![](images/Intel_core2_architecture.png)

最早的名字里面带Core这个牌子的处理器是Core Duo,它的架构代号是Yonah,其实是NetBurst的改版,只是跟后期的NetBurst走向了不同的发展道路.虽然名字上有Core但不是Core架构.

```
主要的设计目标是面向移动平台,因此很多设计都是偏向低功耗、高能效.
```

再后来的Core 2 Duo才是采用Core架构的新一代处理器,全线 65nm,然后微架构在Yonah之上做了比较大的改动.

```
1.Core架构把NetBurst做深了的流水线级数砍下来;
2.主频虽然降下来了(即使后来工艺提升到45nm主频也没有超过NetBurst的水平),但是却提高了整个流水线中的资源利用率,所以性能还是提升了;
3.把奔腾4上曾经用过的超线程也砍掉了;
4.双核共享L2 cache.
```

从Core架构开始Intel是真的走向多核了,不再是以前“胶水粘的”伪双核了,这时候已经有最高4核的处理器设计.

#### 1.3.3 Nehalem架构

![](images/Intel_nahalem_architecture.png)

Core从65nm改到45nm之后,基于45nm又推出了新一代架构叫Nehalem,这一代的提升引入了相当多的新技术,是一个非常重要的里程碑.

Core这个名字变成了桌面PC以及笔记本处理器的系列名,后面架构继续更新.Core(酷睿)这个名字就留下来了,并推出了第一代的Core i7.

相对上一代的主要改进:

```
1.引入了片内4-12MB的L3 cache;
2.重新加入超线程(奔腾4代有,后来砍掉了,这一代又重新引入);
3.Intel Turbo Boost 1.0;
4.分支预测器分级;
5.二级的TLB;
6.每个核上有3个整数ALU,2个向量ALU和2个AGU;
7.采用Intel QPI来代替原来的前端总线;
8.PCIe和DMI控制器直接做到片内了,不再需要北桥;
9.IMC(集成内存控制器),内存控制也从北桥移到了片内;
10.第二代的Intel虚拟化技术;
11.流水线加到20到24级;
12.其他指令扩展升级等等.
```

相比上一代的性能:

```
1.同等功耗下,10-25%的单线程性能提升,20-100%的多线程性能提升;
2.同等性能下功耗降低30%;
3.15-20%的clock-to-clock性能提升.
```

工艺提升到32nm的Westmere后,推出了第一代的i5和i3.

Xeon系列也从Westmere开始推出了第一代E命名的E7-x8xx系列.

#### 1.3.4 Sandy Bridge

![](images/Intel_sandy_bridge_architecture.png)

32nm的下一代Tock是Sandy Bridge.二代Core i系列以及第一代Xeon E3、E5 系列也基于这个架构:

```
1.Intel Turbo Boost 2.0;
2.增大了L1和L2 cache;
3.共享的L3 cache也同时支持片上的核芯显卡;
4.IMC强化成了GMCH(integrated graphics and memory controller),片上显卡共用主存作为它的显存;
5.每个核上的运算部件增强;
6.分支预测增强;
7.微操作译码部分新增了一个cache(uop cache);
8.14到19级指令流水线;
9.多个核间、核芯显卡、cache间用了环状总线(ring bus);
10.Intel Quick Sync Video,支持视频的硬解码;
11.其他指令扩展升级等等.
```

**Ring Bus**
