#ifndef STRHASHMAP_FILENODEHASH_H
#define STRHASHMAP_FILENODEHASH_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#ifdef DBG_ANSI
typedef char _SC_CHR_TYPE;
#define FindStr(strsc,tgstr) strstr(strsc,tgstr)
#define CatStr(strsc,addstr) strcat(strsc,addstr)
#else
typedef wchar_t _SC_CHR_TYPE;
#define FindStr(strsc,tgstr) wcsstr(strsc,tgstr)
#define CatStr(strsc,addstr) wcscat(strsc,addstr)
#endif


class NodeUnion{
private:
	//文件路径节点(集合,"|"连接)
	_SC_CHR_TYPE* NodeBufUnion;
	size_t strsize;
public:
	void AddItem(const _SC_CHR_TYPE *NodeName);
	int HaveNode(const _SC_CHR_TYPE *NodeName);
	int isEmpty();
	NodeUnion();
	~NodeUnion();
};


class FileRoot {
private:
	NodeUnion *nodes;
	size_t nodenum;
public:
	void AddItem(const _SC_CHR_TYPE *Path);
	int HavePathOrSubPath(const _SC_CHR_TYPE *Path);
	FileRoot();
	~FileRoot();
};


#endif //STRHASHMAP_FILENODEHASH_H
