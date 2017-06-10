# TS Stream Parser

TS Stream由很多的packet构成,每个packet(包)是188 byte(或204 byte, 188 + 16 byte的CRC较验).

**TS188情况分析:**

4 byte package header(4字节的包头)
	
	1)sync_byte						8 bit		同步字节(1个字节),一般为"0x47"
	2)Transport_error_indicator		1 bit		错误提示信息(为"1"至少有一位传输错误),一般为"0"
	3)payload_unit_start_indicator	1 bit		负载单元开始标志,一般为"0/1",这位不是很关心
	4)transport_priority			1 bit		传输优先级标志(1:优先级高),一般为"0"
	5)PID							13 bit		Packet ID的号码,标识不同的packet
	6)transport_scrambling_control	2 bit		加密标志,00:未加密; 10:even; 11:odd
	7)adaption_field_control		2 bit		
		附加区域.00:reserved;01:仅有payload,无调整字段;10:无payload,仅有调整字段.11:既有payload,也有调整字段.
	8)continuity_counter			2 bit		包递增计数器

**实例**

	//源数据
	0x47, 0x41, 0xFF, 0x31, 0x07, 0x90, 0x00, 0x00, 0x00, 0x10, 0x7E, 0x0D, 0x00, 0x00, 0x01, 0xE0, 
	1)0x47---同步字节
	2)0---错误提示信息
	3)1---负载单元开始标志
	4)0---传输优先级标志
	5)0x1FF(0000111111111---13 bit)---PID
	6)00---加密标志(清流)
	7)11---有payload和调整字段.包头4字节后接着的字节表示调整字段的长度(此处为"0x07":表示调整字段为7个字节).
		此处的调整字段为"0x90, 0x00, 0x00, 0x00, 0x10, 0x7E, 0x0D".调整字段之后的为payload(此处从"0x00"开始).
	8)01---包递增计数器(目前不关心).
	//加密的数据(using even key)
	0x47, 0x41, 0xFF, 0xB1, 0x07, 0x90, 0x00, 0x00, 0x00, 0x10, 0x7E, 0x0D, 0x2a, 0xba, 0xc6, 0x8a,
	//加密的数据(using odd key)
	0x47, 0x41, 0xFF, 0xF1, 0x07, 0x90, 0x00, 0x00, 0x00, 0x10, 0x7E, 0x0D, 0x75, 0xac, 0x4f, 0xa3,