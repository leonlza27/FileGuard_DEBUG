#include <iostream>
#include"FileNodeHash.h"

//测试数据
#if 1
const char *Testbuf[] = {"C:\\Users\\leonl\\Desktop\\glog",
						 "C:\\Users\\Public\\Desktop\\Cpolar Web UI.lnk",
						 "D:\\Everything",
						 "D:\\Games\\Kerbal Space Program\\Plugins",
						 "C:\\Program Files (x86)\\Windows Kits\\10\\Include",
						 "D:\\Git\\cmd"};

const char *ScanLst[] = {"C:\\Users\\leonl\\Desktop\\glog",
						  "C:\\Users\\Public\\Desktop\\Cpolar Web UI.lnk",
						  "C:\\Users\\leonl\\Desktop\\glog\\1",
						  "D:\\Everything",
						  "D:\\Games\\Kerbal Space Program\\Plugins",
						  "D:\\Games\\Kerbal Space Program",
						  "C:\\Program Files (x86)\\Windows Kits\\10\\Include",
						  "C:\\Program Files (x86)\\Microsoft\\Edge\\Application",
						  "C:\\Users\\Public\\Desktop\\嘉立创EDA(专业版).lnk",
						  "D:\\Git\\cmd",
						  "D:\\"};

#endif




int main() {
	FileRoot Root;
	for(int i =0;i<6;i++) {
		Root.AddItem(Testbuf[i]);
		printf("Add %s\n",Testbuf[i]);
	}
	for(int i =0;i<11;i++) {
		printf("SCAN %s : %d\n",ScanLst[i],Root.HavePathOrSubPath(ScanLst[i]));
	}
	return 0;
}
