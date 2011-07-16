typedef struct CSNode
{
	CString		key;
	CDragStatic* DragBox;		//¿Ø¼þÖ¸Õë;
	CSNode *firstChild;
	CSNode *nextSibling;
} CSNode, *CSTree;
