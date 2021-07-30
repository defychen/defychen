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

### 1.3 各代处理器介绍

