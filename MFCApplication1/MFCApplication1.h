
// MFCApplication1.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������
#include "IBlock.h"
#include "Block05.h"
#include "Block04.h"
#include "Block14.h"
#include "Block28.h"
#include "Block29.h"
#include "Block31.h"


// CMFCApplication1App:
// � ���������� ������� ������ ��. MFCApplication1.cpp
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

	// ���������������
public:
	virtual BOOL InitInstance();

	// ����������

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;