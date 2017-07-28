##=========================================================
# Compile bootloader
##=========================================================
参考文档: ALi_Boot/doc/customer/Compiling_Guide_for_BL_SDK_v1.0.pdf
	
****************************************************
## C3505 customer compile method (sdk package)---客户编译方法
****************************************************
1.configure correct board type you are using in "sabbat_dual/compiler_3505.def".
Make sure that only enable one board, disable others.
	
	#export _M36F_SINGLE_CPU=1

a:General CA project should open '_GEN_CA_ENABLE_' and close '_CAS9_CA_ENABLE_'

	#_CAS9_CA_ENABLE_ = 1
	_GEN_CA_ENABLE_ = 1

b:Conax CA project should open '_CAS9_CA_ENABLE_' and close '_GEN_CA_ENABLE_'

	_CAS9_CA_ENABLE_ = 1
	#_GEN_CA_ENABLE_ = 1

2.compile

2.1 build ota loader cmd:

	make path
	make config_3505_ota
	make new
	make ddk		    #copy sdk libs to obj/
	make product_7z		#build ota loader

2.2 build ouc loader(OTA+USB) cmd:

	make path
	make config_3505_ouc
	make new
	make ddk		    		#copy sdk libs to obj/
	make product_7z		#build ouc loader

2.3 build fw cmd:

	make path
	make config_3505
	make new
	make ddk		    #copy sdk libs to obj/
	make product_7z		#build fw

3.burn it into flash by "obj/s3505_sf_burn_sabbat.ini"

4.

(1) If you are going to run it from flash, then just power the box on.
  
(2) If you are going to run it from WinGDB instead of power on, just dowload the "obj/s3505_sabat.ini" by WinGDB to run it.

*******************************************************
## C3505 Ali internal compile method (Src label)
*******************************************************

1.configure correct board type you are using in "sabbat_dual/compiler_3505.def".

Make sure that only enable one board, disable others.

	#export _M36F_SINGLE_CPU=1

a:General CA project should open '_GEN_CA_ENABLE_' and close '_CAS9_CA_ENABLE_'
	
	#_CAS9_CA_ENABLE_ = 1
	_GEN_CA_ENABLE_ = 1

b:Conax CA project should open '_CAS9_CA_ENABLE_' and close '_GEN_CA_ENABLE_'

	_CAS9_CA_ENABLE_ = 1
	#_GEN_CA_ENABLE_ = 1

2.compile

	cd src/see/m36f
	build see ota lib cmd:
	make path config_3505_ota new; make

build see lib cmd:
	
	make path config_3505 new; make

cd prj/app/demo/combo/sabbat_dual 

build main ota lib and loader cmd:
	
	make path
	make config_3505_ota
	make new
	make sdk_clean
	make sdk            #build main ota lib
	make product_7z     #build ota loader

build main lib and fw cmd:
	make path
	make config_3505
	make new
	make sdk_clean
	make sdk            #build main lib
	make product_7z     #build fw

3.burn it into flash by "obj/s3505_sf_burn_sabbat.ini"

4.

(1) If you are going to run it from flash, then just power the box on.

(2) If you are going to run it from WinGDB instead of power on, just dowload the "obj/s3505_sabat.ini" by WinGDB to run it.	
  
5.About how to change the ddr setting by your board.

Modify the "MEM_INIT_FILE" in Makefile3505. 

prj/app/demo/combo/sabbat_dual/Makefile3505

the default "MEM_INIT_FILE" is "128.txt", you can change to "256M.txt" as follows.

MEM_INIT_FILE = C3505_DB_BGA_DB_BGA_1866Mbps\(CL13,\ CWL9\)_256M.txt
