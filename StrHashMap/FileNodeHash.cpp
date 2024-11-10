#include "FileNodeHash.h"

//NodeUnion

NodeUnion::NodeUnion() {
	_SC_CHR_TYPE *strnew = new _SC_CHR_TYPE[5];
	NodeBufUnion = strnew;
	NodeBufUnion[0] = '|';
	NodeBufUnion[1] = 0;
	strsize = 5;
}

void NodeUnion::AddItem(const _SC_CHR_TYPE *NodeName) {
	if(HaveNode(NodeName)) return; 
       
#ifdef DBG_ANSI
	size_t len2 = strlen(NodeName);
	strsize+=len2;
	char *strnew = new char[strsize];
	sprintf(strnew,"%s%s|",NodeBufUnion,NodeName);
	NodeBufUnion = strnew;
#else
	size_t len2 = wcslen(NodeName);
	strsize+=len2;
	wchar_t *strnew = new wchar_t[strsize];
	swprintf(strnew,L"%ls%ls|",NodeBufUnion,NodeName);
	NodeBufUnion = strnew;
#endif
}

int NodeUnion::isEmpty() {
	return NodeBufUnion[1] == 0;
}

int NodeUnion::HaveNode(const _SC_CHR_TYPE *NodeName) {
#ifdef DBG_ANSI
	char TgStr[strlen(NodeName)+3];
	sprintf(TgStr,"|%s",NodeName);
#else
	wchar_t TgStr[wcslen(NodeName)+3];
	swprintf(TgStr,L"%ls|",NodeName);
#endif
	return FindStr(NodeBufUnion,TgStr) == 0? 0 : 1 ;

}

NodeUnion::~NodeUnion() {
	//free(NodeBufUnion);
	strsize = 0;
}

//FileRoot

FileRoot::FileRoot() {
	NodeUnion *UnionNew = new NodeUnion[20];
	nodes = UnionNew;
	nodenum = 20;
}

void FileRoot::AddItem(const _SC_CHR_TYPE *Path) {
#ifdef DBG_ANSI
	size_t totallen = strlen(Path);
	char *nodemid = new char[totallen+2];
	memset(nodemid,0,totallen+2);
#else
	size_t totallen = wcslen(Path);
	wchar_t *nodemid = new wchar_t[totallen+2];
#endif
	size_t midind = 0,nodeind = 0;
	for(size_t i =0;i<totallen;i++){
		if(Path[i] == '\\'||Path[i]==0){
			nodemid[midind] = 0;
			midind=0;
			if(nodemid[0] == 0) continue;
			if(nodenum<nodeind+1){
				NodeUnion *UnionNew = new NodeUnion[nodenum+5];
				for(size_t cpy=0;cpy<nodenum;cpy++){
					UnionNew[cpy] = nodes[cpy];
				}
				delete[] nodes;
				nodes = UnionNew;
			}
			nodes[nodeind].AddItem(nodemid);
			nodemid[0] = 0;
			nodeind++;
			continue;
		}
		nodemid[midind++] = Path[i];
	}
	nodes[nodeind].AddItem(nodemid);
}

FileRoot::~FileRoot() {
	delete[] nodes;
	nodenum = 0;
}

int FileRoot::HavePathOrSubPath(const _SC_CHR_TYPE *Path) {
#ifdef DBG_ANSI
	size_t totallen = strlen(Path);
	char *nodemid = new char[totallen+2];
#else
	size_t totallen = wcslen(Path);
	wchar_t *nodemid = new wchar_t[totallen+2];
#endif
	size_t midind = 0,nodeind = 0;
	for(size_t i =0;i<totallen + 1;i++){
		if(Path[i] == '\\' || Path[i] == 0){
			nodemid[midind] = 0;
			midind=0;
			if(nodemid[0] == 0) continue;
			if(nodes[nodeind+1].isEmpty()) return 1;
			if(!nodes[nodeind].HaveNode(nodemid)) return 0;
			nodemid[0] = 0;
			nodeind++;
			continue;
		}
		nodemid[midind++] = Path[i];
	}
	return 0;
}
