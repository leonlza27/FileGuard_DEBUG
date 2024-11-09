#include "FileNodeHash.h"

//NodeUnion

NodeUnion::NodeUnion() {
	NodeBufUnion = (_SC_CHR_TYPE*)calloc(5,sizeof(_SC_CHR_TYPE));
	NodeBufUnion[0] = '|';
	NodeBufUnion[1] = 0;
	strsize = 5 * sizeof(_SC_CHR_TYPE);
}

void NodeUnion::AddItem(const _SC_CHR_TYPE *NodeName) {
	if(HaveNode(NodeName)) return;
	size_t Strsize2 = sizeof(NodeName);
	void* ret;
	ret = realloc(NodeBufUnion,strsize+Strsize2-1);
	strsize += Strsize2-1;
	CatStr(NodeBufUnion,NodeName);
#ifdef DBG_ANSI
	strcat(NodeBufUnion,"|");
#else
	wcscat(NodeBufUnion,L"|");
#endif
}

int NodeUnion::isEmpty() {
	return NodeBufUnion[1] == 0;
}

int NodeUnion::HaveNode(const _SC_CHR_TYPE *NodeName) {
#ifdef DBG_ANSI
	char TgStr[strlen(NodeName)+3];
	sprintf(TgStr,"%s|",NodeName);
#else
	wchar_t TgStr[wcslen(NodeName)+3];
	swprintf(TgStr,L"%ls|",NodeName);
#endif
	return FindStr(NodeBufUnion,NodeName) == 0? 0 : 1 ;


}

NodeUnion::~NodeUnion() {
	free(NodeBufUnion);
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
#else
	size_t totallen = wcslen(Path);
	wchar_t *nodemid = new wchar_t[totallen+2];
#endif
	size_t midind = 0,nodeind = 0;
	for(size_t i =0;i<totallen;i++){
		if(Path[i] == '\\'){
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
	for(size_t i =0;i<totallen;i++){
		if(Path[i] == '\\'){
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