// AdjMatrix.cpp : 实现文件
//



#include "stdafx.h"
#include "ad.h"
#include "AdjMatrixGrap.h"



// CAdjMatrix

CAdjMatrixGrap::CAdjMatrixGrap()
{
	Clear();
}

CAdjMatrixGrap::~CAdjMatrixGrap()
{
}


// CAdjMatrix 成员函数

void CAdjMatrixGrap::Clear(void)
{
	vexNum = 0;
	for (int i=0 ;i<MAX_VERTEX_NUM; i++)
	{
		vexs[i].key = "";
		vexs[i].moreInfo = "";
		vexs[i].point =CPoint(15,15);
		for (int j=0; j<MAX_VERTEX_NUM; j++)
		{
			arcs[i][j] =MAX_INT;
		}
	}
}

void CAdjMatrixGrap::CreateAdjMatrixGrap()
{
	Clear();
	OrthListArcBox *p=NULL;
	for (int index=0 ,i=0;i<MAX_VERTEX_NUM;i++)
	{
		if(OrthGrap.xlist[i].m_bUsed)
		{
			vexs[index].key = OrthGrap.xlist[i].data.key;
			vexs[index].moreInfo = OrthGrap.xlist[i].data.moreInfo;
			vexs[index].point = OrthGrap.xlist[i].DragBox->GetPoint();
			vexs[index].radius = OrthGrap.xlist[i].DragBox->GetRadius();
			p=OrthGrap.xlist[i].m_pThisTail;//只处理入弧
			while (p)
			{
				int head = OrthGrap.GetLogicPos(p->headVex);
				int tail = OrthGrap.GetLogicPos(p->tailVex);
				arcs[head][tail] = p->data.quan;
				p=p->m_pNextSameTail;
			}
			index++;
		}
	}
	vexNum = OrthGrap.m_iVexNum;

}

void CAdjMatrixGrap::Save(CString pathName)
{
	/*
	if (vexNum ==0 )
	{
		MessageBox(pView->GetSafeHwnd(),"空图！\n无需导出","导出提示！",MB_ICONWARNING|MB_OK);
		return;
	}

	CString str;
	CFileDialog dlg= CFileDialog(FALSE,"grs",fileName,OFN_OVERWRITEPROMPT,"GRS(图)文档 (*.grs)|*.grs|" );
	if(dlg.DoModal()!=IDOK)
		return;*/
	CStdioFile outTxtFile;
	if( !outTxtFile.Open(pathName,CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
	{
		MessageBox(pView->GetSafeHwnd(),"打开文件失败，无法写入数据！\n文件可能有只读属性","导出失败！",MB_ICONERROR|MB_OK);
		return ;
	}
	CString str;
	str.Format("%d\n", vexNum);
	outTxtFile.WriteString(str);
	str.Format("%d\n", pView->iMaxWidth);
	outTxtFile.WriteString(str);
	str.Format("%d\n", pView->iMaxHeight);
	outTxtFile.WriteString(str);
	outTxtFile.WriteString("[VEX]\n");
	for (int i=0 ;i<vexNum ;i++)
	{
		str = vexs[i].key +"\t" ;
		outTxtFile.WriteString(str);

		str.Format("%d\t",vexs[i].point.x );
		outTxtFile.WriteString(str);

		str.Format("%d\t",vexs[i].point.y );
		outTxtFile.WriteString(str);

		str.Format("%d\t",vexs[i].radius );
		outTxtFile.WriteString(str);

		str = vexs[i].moreInfo+"\t\n";
		outTxtFile.WriteString(str);
	}

	outTxtFile.WriteString("[WEIGHT]\n");
	for (int i=0 ;i<vexNum ;i++)
	{
		for (int j=0 ;j<vexNum ;j++)
		{
			str.Format("%d\t",arcs[i][j]);
			outTxtFile.WriteString(str);
		}
		outTxtFile.WriteString("\n");
	}
	outTxtFile.Close();
	AfxGetApp()->AddToRecentFileList(pathName);

}


bool CAdjMatrixGrap::SplitString(CString str,CString& str1, CString& str2) 
{ 
	int pos = -1; 
	pos = str.Find("\t"); 
	if(pos != -1) 
	{ 
		str1 = (str.Left(pos));
		str1.Trim("\t"); 
		str.Delete(0,pos);
		str2 = str;
		str2.Trim("\t");
		return true;
	} 

	return false;
} 

bool CAdjMatrixGrap::SplitString(CString str,int num, CStringArray& outStr) 
{ 
	int pos = -1; 
	pos = str.Find("\t"); 
	for ( int i =0; i<num; i++ )
	{
		if(pos !=-1 )
		{
			CString strSun = str.Left(pos);
			outStr.Add(strSun); 
			str.Delete(0,pos+1); 
			pos = str.Find("\t"); 
			TRACE("***"+strSun+"***\n");
		}
		else
			return false;
	}
	return true;
} 


bool CAdjMatrixGrap::CreateFromFile(void)
{
	/*
	CFileDialog dlg= CFileDialog(TRUE,"grs","2邻接矩阵",OFN_OVERWRITEPROMPT,"GRS(图)文档 (*.grs)|*.grs|" );
	if(dlg.DoModal()!=IDOK)
		return false;
	return CreateFromFile(dlg.GetFileName());*/
	return true;
}


bool CAdjMatrixGrap::CreateFromFile(CString filePath)
{
	CString str;
	CStdioFile outTxtFile;
	if(pShortPathDlg)
	{
		pShortPathDlg->DestroyWindow();
		pShortPathDlg =NULL;
	}
	if( !outTxtFile.Open( filePath,CFile::modeRead|CFile::typeText))
		goto READ_ERR;
	//读取信息头
	outTxtFile.ReadString(str);
	this->vexNum = atoi(str);
	outTxtFile.ReadString(str);
	pView->iMaxWidth = atoi(str);
	outTxtFile.ReadString(str);
	pView->iMaxHeight = atoi(str);
	pView->SetAreaSize( pView->iMaxWidth ,pView->iMaxHeight );
	
	//读取顶点信息
	while( str!="[VEX]" )
	{
		if( outTxtFile.ReadString(str)== FALSE )
		{//文件结束
			goto READ_ERR;
		}
	}
	for(int i=0 ;i<vexNum ;i++)
	{
		CStringArray arr;

		if( outTxtFile.ReadString(str) == FALSE )
		{
			goto READ_ERR;
		}

		if( !SplitString(str,5, arr) )
			goto READ_ERR;

		vexs[i].key = arr[0];
		vexs[i].point.x = atoi( arr[1] );
		vexs[i].point.y = atoi( arr[2] );
		vexs[i].radius = atoi( arr[3] );
		vexs[i].moreInfo = arr[4];
	}

	//读取弧权信息
	while( str!="[WEIGHT]" )
	{
		if( outTxtFile.ReadString(str)== FALSE )//文件结束
		{
			goto READ_ERR;
		}
	}
	for(int i=0 ;i<vexNum ;i++)
	{
		CStringArray arr;

		if( outTxtFile.ReadString(str) == FALSE )
			goto READ_ERR;
		if( !SplitString(str,vexNum, arr) )
			goto READ_ERR;

		for (int j=0; j<vexNum; j++)
		{
			arcs[i][j] = atoi(arr[j]) ;
		}
	}

	outTxtFile.Close();
	AfxGetApp()->AddToRecentFileList(filePath);
	TRACE(filePath+"\n");
	return true;


READ_ERR:
	MessageBox(pView->GetSafeHwnd(),"读取文件数据失败，文件格式有误！\n文件可能已经损坏","打开文件失败！",MB_ICONERROR|MB_OK);						
	return false;
}


void CAdjMatrixGrap::ShortPath_DJJ(CString BeginKey , CStringArray &EndKey, CStringArray &pathResult ,CStringArray & pathLength  )
{
	CreateAdjMatrixGrap();
	int v0 = LocateVex( BeginKey );
	if(v0 ==-1)
		return ;
	
	pathResult.SetSize(vexNum);
	pathLength.SetSize(vexNum);
	EndKey.SetSize( vexNum);
	//bool pathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int D[MAX_VERTEX_NUM];
	bool final[MAX_VERTEX_NUM];
	for (int i=0 ;i<MAX_VERTEX_NUM; i++)
	{
		final[i]= false;
		D[i] = arcs[v0][i];
		//for (int j =0 ;j<MAX_VERTEX_NUM; j++)
		//pathMatrix[i][j]= false;
		if( arcs[v0][i] < MAX_INT)
		{
			//	pathMatrix[i][v0] = true;
			//	pathMatrix[i][i] = true;
			pathResult.SetAt(i,vexs[v0].key+"-"+vexs[i].key);
		}
	}
	D[v0] = 0;
	final[v0] = true;
	int v= v0;
	for ( int i =1; i<vexNum ; i++)
	{

		int min = MAX_INT;
		for ( int w= 0; w< vexNum; w++ )
		{
			if ( ! final[w] )
			{
				if ( D[w] <min)
				{
					v= w;	
					min = D[w];
				}
			}
		}

		final[v] = true;
		for ( int w = 0; w<vexNum ; w ++)
		{
			if ( !final[w] )
				if  (min+arcs[v][w]< D[w])
				{
					D[w] = min + arcs[v][w];

					for ( int tmp = 0; tmp < vexNum ; tmp++)
					{
						//pathMatrix[w][tmp] = pathMatrix[v][tmp];

					}
					pathResult.SetAt(w,pathResult.GetAt(v)+"-"+vexs[w].key);
					//pathMatrix[w][w] = true;	
				}
		}

	}

	CString str;
	for ( int i =0; i< vexNum ; i++)
	{
		if (D[i]==MAX_INT)
		{
			str="-";
			pathResult.SetAt( i,"-");
		}
		else
		{
			str.Format("%d",D[i]);
			
		}
		EndKey.SetAt( i, vexs[i].key);
		pathLength.SetAt(i,str);
	}
	pathLength.RemoveAt(v0);
	pathResult.RemoveAt(v0);
	EndKey.RemoveAt(v0);

}

//返回顶点的索引位置
int CAdjMatrixGrap::LocateVex(CString key)
{
	for(int i =0; i<vexNum ; i++ )
	{
		if( key == vexs[i].key )
			return i;
	}
	return -1;
}
