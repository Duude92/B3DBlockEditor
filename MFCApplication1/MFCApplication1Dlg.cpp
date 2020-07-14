
// MFCApplication1Dlg.cpp : файл реализации
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "AddMat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

// Диалоговое окно CAboutDlg используется для описания сведений о приложении


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

														// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CMFCApplication1Dlg



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}





void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
	DDX_Control(pDX, IDC_TREE2, m_treeCtrl1);
}


BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OpenFile1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE2, &CMFCApplication1Dlg::OnTvnSelchangedTree2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMFCApplication1Dlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OpenFile2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::CopyBlk)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::RemBlk)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::AddMat)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CMFCApplication1Dlg::OnNMClickTree1)
	ON_NOTIFY(NM_CLICK, IDC_TREE2, &CMFCApplication1Dlg::OnNMClickTree2)
	//ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
	ON_COMMAND(ID_FILE_OPEN1, &CMFCApplication1Dlg::OpenFile1)
	ON_COMMAND(ID_FILE_OPEN2, &CMFCApplication1Dlg::OpenFile2)
	ON_COMMAND(ID_FILE_SAVE_AS, &CMFCApplication1Dlg::Save)
	ON_COMMAND(ID_ADD_MAT, &CMFCApplication1Dlg::AddMat)
	ON_COMMAND(ID_COPY_BLK, &CMFCApplication1Dlg::CopyBlk)
	ON_COMMAND(ID_REM_BLK, &CMFCApplication1Dlg::RemBlk)
	ON_COMMAND(ID_EXPORT, &CMFCApplication1Dlg::ExportBlk)
	ON_COMMAND(ID_APP_ABOUT, &CMFCApplication1Dlg::AboutBox)
	ON_COMMAND(ID_NEW05, &CMFCApplication1Dlg::ADD05)
	ON_COMMAND(ID_REPL, &CMFCApplication1Dlg::ReplBlk)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CMFCApplication1Dlg::OnNMDblclkTree1)
	ON_MESSAGE(WM_CLOSE, CloseApp)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)


END_MESSAGE_MAP()


LRESULT CMFCApplication1Dlg::CloseApp(WPARAM wParam, LPARAM lParam)
{
	UnregisterHotKey(GetSafeHwnd(), 100);
	UnregisterHotKey(GetSafeHwnd(), 200);
	UnregisterHotKey(GetSafeHwnd(), 300);
	UnregisterHotKey(GetSafeHwnd(), 400);
	UnregisterHotKey(GetSafeHwnd(), 450);
	UnregisterHotKey(GetSafeHwnd(), 500);
	DestroyWindow();
	return 0;
}

LRESULT CMFCApplication1Dlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 100:
		CopyBlk();
		break;
	case 200:
		ReplBlk();
		break;
	case 300:
		AddMat();
		break;
	case 400:
		RemBlk();
		break;
	case 450:
		RemBlk();
		break;
	case 500:
		ADD05();
		break;
	}
	return 0;
}
void CMFCApplication1Dlg::ADD05()
{
	if (op0)
	{

		CString OPath, tPath;
		LPWSTR opathx = new TCHAR[255];
		GetTempPath(255, opathx);
		OPath = (LPWSTR)(LPCWSTR)opathx;
		OPath = OPath + L"b3d.temp1";


		tPath = OPath;
		tPath.Delete(OPath.GetLength() - 1, 1);
		tPath.Append(L"2");

		CArray<HTREEITEM> items0;
		GetCheckedItems(m_treeCtrl, &items0, NULL);


		CString mat;

		ifstream input0(OPath, ios::binary);

		CAddMat dialog;

		char objName[32];




		dialog.m_text = L"Имя блока:";
		dialog.m_caption = L"Создать контейнер";

		if (dialog.DoModal() == IDOK)
		{

			CString str = dialog.GetValue();
			strcpy_s(objName, 32, CT2A(str));

			ofstream output(tPath, ios::binary);
			CString in0, in1, in2, in3;
			input0.seekg(0, ios_base::end);
			int fend = (int)input0.tellg();
			input0.seekg(0, ios_base::beg);
			char* text = new char[fend];

			int offset = itemArr[(int)m_treeCtrl.GetItemData(items0[0])].start;//смещение первого блока

			input0.read(text, offset);
			output.write(text, offset);

			int num = 333;

			output.write(reinterpret_cast<char*>(&num), sizeof(int));
			output.write(objName, 32);
			num = 5;
			output.write(reinterpret_cast<char*>(&num), sizeof(int));

			output.write("\0", 16);
			output.write("\0", 32);
			num = 0;
			output.write(reinterpret_cast<char*>(&num), sizeof(int));
			num = 555;
			output.write(reinterpret_cast<char*>(&num), sizeof(int));


			input0.read(text, fend - offset);
			output.write(text, fend - offset);
			output.close();
			input0.close();
			delete text;

			ifstream inputM(tPath, ios::binary);

			inputM.seekg(0, ios_base::end);
			fend = (int)inputM.tellg();
			inputM.seekg(0, ios_base::beg);
			char* MainFile = new char[fend];
			inputM.read(MainFile, fend);
			ofstream tempFile(OPath, ios::binary);
			tempFile.write(MainFile, fend);
			tempFile.close();
			inputM.close();

			m_treeCtrl.DeleteAllItems();
			getStr(&m_treeCtrl, OPath, &itemArr);
			delete MainFile;


		}

		delete[] opathx;
	}

}

void CMFCApplication1Dlg::AboutBox()
{
	CAboutDlg cDialog;
	cDialog.DoModal();
}

// обработчики сообщений CMFCApplication1Dlg

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	RegisterHotKey(GetSafeHwnd(), 100, NULL, VK_F5);
	RegisterHotKey(GetSafeHwnd(), 200, NULL, VK_F6);
	RegisterHotKey(GetSafeHwnd(), 300, NULL, VK_F3);
	RegisterHotKey(GetSafeHwnd(), 400, NULL, VK_F8);
	RegisterHotKey(GetSafeHwnd(), 450, NULL, VK_DELETE);
	RegisterHotKey(GetSafeHwnd(), 500, MOD_CONTROL, 'B');



	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	SetMenu(&menu);

	op0 = FALSE;
	op1 = FALSE;

	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

									// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OpenFile1()
{
	// TODO: добавьте свой код обработчика уведомлений

	bool ignoreNextSelChange = FALSE;

	CFileDialog fileDialogOpen(TRUE, NULL, L"*.b3d");
	int result = fileDialogOpen.DoModal();


	if (result == IDOK)
	{
		if (ignoreNextSelChange)
		{
			// Don't do anything, but make sure that the else block below will be executed
			// again with the next (expected) call of this function.
			ignoreNextSelChange = false;
		}
		else
		{
			CTreeCtrl* pCtrl1 = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
			HTREEITEM hItem = pCtrl1->GetSelectedItem();
			BOOL hItemm = pCtrl1->ItemHasChildren(hItem);
			if (hItem && hItemm)
			{
				HTREEITEM hChild = pCtrl1->GetChildItem(hItem);

				// Make sure that this else block won't be executed again when the function
				// SelectItem() is called below.
				ignoreNextSelChange = true;

				pCtrl1->SelectItem(hChild);
			}
		}

		Path0 = fileDialogOpen.GetPathName();
		ifstream inputM(Path0, ios::binary);

		inputM.seekg(0, ios_base::end);
		int fend = (int)inputM.tellg();
		inputM.seekg(0, ios_base::beg);
		char* MainFile = new char[fend];

		inputM.read(MainFile, fend);

		inputM.close();

		CString OPath;
		LPWSTR opathx = new TCHAR[255];


		GetTempPath(255, opathx);

		OPath = (LPWSTR)(LPCWSTR)opathx;
		OPath = OPath + L"b3d.temp1";


		ofstream tempFile(OPath, ios::binary);
		tempFile.write(MainFile, fend);
		delete MainFile;
		delete[] opathx;
		tempFile.close();
		inputM.close();

		try
		{
			if (op0)
			{
				m_treeCtrl.DeleteAllItems();
				getStr(&m_treeCtrl, OPath, &itemArr);

			}
			else
			{
				getStr(&m_treeCtrl, OPath, &itemArr);
				op0 = TRUE;
			}
		}
		catch (const std::exception& e)
		{
			CString msg;
			msg.Format(_T("%S"), e.what());
			MessageBox(msg, _T("B3D Error"), MB_OK);
		}

	}
}

void CMFCApplication1Dlg::OpenFile2()
{
	// TODO: добавьте свой код обработчика уведомлений

	bool ignoreNextSelChange = FALSE;

	CFileDialog fileDialogOpen(TRUE, NULL, L"*.b3d");
	int result = fileDialogOpen.DoModal();


	if (result == IDOK)
	{
		if (ignoreNextSelChange)
		{
			ignoreNextSelChange = false;
		}
		else
		{
			CTreeCtrl* pCtrl1 = (CTreeCtrl*)GetDlgItem(IDC_TREE2);
			HTREEITEM hItem = pCtrl1->GetSelectedItem();
			BOOL hItemm = pCtrl1->ItemHasChildren(hItem);
			if (hItem && hItemm)
			{
				HTREEITEM hChild = pCtrl1->GetChildItem(hItem);

				ignoreNextSelChange = true;

				pCtrl1->SelectItem(hChild);
			}
		}

		Path1 = fileDialogOpen.GetPathName();
		try
		{

			if (op1)
			{
				m_treeCtrl1.DeleteAllItems();
				getStr(&m_treeCtrl1, Path1, &itemArr1);

			}
			else
			{
				getStr(&m_treeCtrl1, Path1, &itemArr1);
				op1 = TRUE;
			}

		}
		catch (const std::exception& e)
		{
			CString msg;
			msg.Format(_T("%S"), e.what());
			MessageBox(msg, _T("Exception?"), MB_OK);
		}

	}
}


void CMFCApplication1Dlg::ExportBlk()
{
	if (op0)
	{
		CArray<HTREEITEM> items0;
		GetCheckedItems(m_treeCtrl, &items0, NULL);

		CFileDialog fileDialogOpen(TRUE, NULL, L"*.b3d");
		int result = fileDialogOpen.DoModal();

		CString Path = fileDialogOpen.GetPathName();


		ifstream input0(Path0, ios::binary);


		ofstream output(Path, ios::binary);
		CString in0, in1;
		input0.seekg(0, ios_base::end);
		int fend = (int)input0.tellg();
		input0.seekg(0, ios_base::beg);
		char* text = new char[fend];

		input0.read(text, 24);

		output.write(text, 24);
		int texNum;

		input0.read(reinterpret_cast<char*>(&texNum), sizeof(int));

		output.write(reinterpret_cast<char*>(&texNum), sizeof(int));

		input0.read(text, (texNum * 32) + 4);
		output.write(text, (texNum * 32) + 4);
		int fromP = 0, toP = 0;

		for (int i = 0; i < items0.GetCount(); i++)
		{

			in0 = m_treeCtrl.GetItemText(items0[i]);

			CString msgx;

			int num = (int)m_treeCtrl.GetItemData(items0[i]);

			ITEMStruc lvlData = itemArr[num];
			int CopyTo, CopyTo2;
			CopyTo = lvlData.start;
			CopyTo2 = lvlData.endB;

			if (!((CopyTo > fromP) & (CopyTo2 < toP)))
			{
				fromP = CopyTo;
				toP = CopyTo2;


				input0.seekg(CopyTo, ios_base::beg);
				input0.read(text, CopyTo2 - CopyTo);
				output.write(text, CopyTo2 - CopyTo);

			}
		}

		texNum = 222;
		output.write(reinterpret_cast<char*>(&texNum), sizeof(int));

		delete text;
		output.close();
		input0.close();
	}
}




void CMFCApplication1Dlg::AddMat()
{
	if (op0)
	{

		CString OPath, tPath;
		LPWSTR opathx = new TCHAR[255];
		GetTempPath(255, opathx);
		OPath = (LPWSTR)(LPCWSTR)opathx;
		OPath = OPath + L"b3d.temp1";
		delete opathx;


		tPath = OPath;
		tPath.Delete(OPath.GetLength() - 1, 1);
		tPath.Append(L"2");



		CString mat;
		int val;


		CAddMat dialog;
		if (dialog.DoModal() == IDOK)
		{
			ifstream input0(OPath, ios::binary);

			ofstream output(tPath, ios::binary);
			mat = dialog.GetValue();
			input0.seekg(0, ios_base::end);
			int fend = (int)input0.tellg();
			input0.seekg(0, ios_base::beg);
			char* text = new char[fend];

			input0.read(text, 12);
			output.write(text, 12);

			input0.read(reinterpret_cast<char*>(&val), sizeof(int));
			val = val + 8;
			output.write(reinterpret_cast<char*>(&val), 4);

			input0.read(reinterpret_cast<char*>(&val), sizeof(int));
			val = val + 8;
			output.write(reinterpret_cast<char*>(&val), 4);

			input0.read(reinterpret_cast<char*>(&val), sizeof(int));
			output.write(reinterpret_cast<char*>(&val), 4);

			input0.read(reinterpret_cast<char*>(&val), sizeof(int));
			val += 1;
			output.write(reinterpret_cast<char*>(&val), 4);

			input0.read(text, (val - 1) * 32);
			output.write(text, (val - 1) * 32);

			char* mat1 = (LPSTR)(LPCSTR)mat.GetBuffer();

			CT2A ascii(mat);
			output.write(ascii.m_psz, 32);

			int size = fend - (int)input0.tellg();
			input0.read(text, size);
			output.write(text, size);

			output.close();
			input0.close();


			ifstream inputM(tPath, ios::binary);

			inputM.seekg(0, ios_base::end);
			fend = (int)inputM.tellg();
			inputM.seekg(0, ios_base::beg);
			char* MainFile = new char[fend];
			inputM.read(MainFile, fend);
			ofstream tempFile(OPath, ios::binary);
			tempFile.write(MainFile, fend);
			tempFile.close();
			inputM.close();
			delete text;
			delete MainFile;

			m_treeCtrl.DeleteAllItems();
			getStr(&m_treeCtrl, OPath, &itemArr);
		}

	}
}

void CMFCApplication1Dlg::RemBlk()
{
	if (op0)
	{
		CString OPath, tPath;
		LPWSTR opathx = new TCHAR[255];


		GetTempPath(255, opathx);

		OPath = (LPWSTR)(LPCWSTR)opathx;
		OPath = OPath + L"b3d.temp1";
		delete opathx;

		CArray<HTREEITEM> items0;
		GetCheckedItems(m_treeCtrl, &items0, NULL);

		ifstream input0(OPath, ios::binary);

		tPath = OPath;
		tPath.Delete(OPath.GetLength() - 1, 1);
		tPath.Append(L"2");

		CString msg0;

		for (int i = 0; i < items0.GetCount(); i++)
		{
			msg0.Append((m_treeCtrl.GetItemText(items0[i]) + "\n"));
		}
		msg0.Append(L"will be removed");

		const int MsgResult = MessageBox(msg0, _T("Remove"), MB_OKCANCEL);

		if (MsgResult == IDOK)
		{
			ofstream output(tPath, ios::binary);
			CString in0, in1;
			input0.seekg(0, ios_base::end);
			int fend = (int)input0.tellg();
			input0.seekg(0, ios_base::beg);
			char* text = new char[fend * 2];
			int fromP = 0, toP = 0;
			for (int i = 0; i < items0.GetCount(); i++)
			{

				int num = (int)m_treeCtrl.GetItemData(items0[i]);

				ITEMStruc lvlData = itemArr[num];
				int CopyTo, CopyFrom, CopyTo2, CopyTo3;
				CopyTo = lvlData.start;
				CopyTo2 = lvlData.endB;

				if (i > 0)
				{
					input0.seekg(CopyTo, ios_base::beg);

				}
				else
				{
					input0.read(text, CopyTo);
					output.write(text, CopyTo);

				}


				if (!((CopyTo > fromP) & (CopyTo2 < toP)))
				{
					fromP = CopyTo;
					toP = CopyTo2;

					if (items0.GetCount() > i + 1)
					{
						int num2 = (int)m_treeCtrl.GetItemData(items0[i + 1]);

						ITEMStruc lvlData1 = itemArr[num2];
						CopyFrom = lvlData1.start;
						CopyTo3 = lvlData1.endB;
						if (!(CopyTo2 == CopyFrom))
						{
							input0.seekg(CopyTo2, ios_base::beg);
							input0.read(text, CopyFrom - CopyTo2);
							output.write(text, CopyFrom - CopyTo2);
						}
					}

				}
			}
			input0.seekg(toP, ios_base::beg);
			input0.read(text, fend - toP);
			output.write(text, fend - toP);
			output.close();
			input0.close();
			delete text;


		}

		ifstream inputM(tPath, ios::binary);

		inputM.seekg(0, ios_base::end);
		int fend = (int)inputM.tellg();
		inputM.seekg(0, ios_base::beg);
		char* MainFile = new char[fend];
		inputM.read(MainFile, fend);
		ofstream tempFile(OPath, ios::binary);
		tempFile.write(MainFile, fend);
		tempFile.close();
		inputM.close();
		m_treeCtrl.DeleteAllItems();
		getStr(&m_treeCtrl, OPath, &itemArr);
		delete MainFile;
	}
}

void CMFCApplication1Dlg::ReplBlk()
{
	if ((op0) & (op1))
	{
		CString OPath, tPath;
		LPWSTR opathx = new TCHAR[255];
		GetTempPath(255, opathx);
		OPath = (LPWSTR)(LPCWSTR)opathx;
		OPath = OPath + L"b3d.temp1";


		tPath = OPath;
		tPath.Delete(OPath.GetLength() - 1, 1);
		tPath.Append(L"2");


		CArray<HTREEITEM> items0, items1;
		GetCheckedItems(m_treeCtrl, &items0, NULL);
		GetCheckedItems(m_treeCtrl1, &items1, NULL);


		ifstream input0(OPath, ios::binary);
		ifstream input1(Path1, ios::binary);

		CString msg0, msg1;


		msg0.Append(L"Заменить:\n");


		msg0.Append((m_treeCtrl.GetItemText(items0[0]) + "\n"));

		msg0.Append(L"Блоки:\n");
		for (int i = 0; i < items1.GetCount(); i++)
		{
			msg0.Append((m_treeCtrl.GetItemText(items1[i]) + "\n"));
		}


		int MsgResult = MessageBox(msg0, _T("item?"), MB_OKCANCEL);
		switch (MsgResult)
		{
		case IDOK:
		{
			ofstream output(tPath, ios::binary);
			CString in0, in1, in2, in3;
			input0.seekg(0, ios_base::end);
			int fend = (int)input0.tellg();
			input0.seekg(0, ios_base::beg);

			input1.seekg(0, ios_base::end);


			char* text = new char[(int)input1.tellg()];

			input1.seekg(0, ios_base::beg);


			int offset = itemArr[(int)m_treeCtrl.GetItemData(items0[0])].start;//смещение начала блока

			char* beg = new char[offset];


			input0.read(beg, offset);
			output.write(beg, offset);
			delete beg;

			int fromP = 0, toP = 0;

			for (int i = 0; i < items1.GetCount(); i++)
			{

				ITEMStruc data = itemArr1[(int)m_treeCtrl.GetItemData(items1[i])];
				if (!((data.start > fromP) & (data.endB < toP)))
				{
					input1.seekg(data.start, ios_base::beg);
					input1.read(text, data.endB - data.start);
					output.write(text, data.endB - data.start);
					fromP = data.start;
					toP = data.endB;
				}

			}

			offset = itemArr[(int)m_treeCtrl.GetItemData(items0[0])].endB;//смещение конца блока
			input0.seekg(offset, ios_base::beg);

			char* end = new char[fend - offset];
			input0.read(end, fend - offset);
			output.write(end, fend - offset);
			delete end;

			output.close();
			input0.close();
			input1.close();
			delete text;

		}
		case IDCANCEL:
			break;
		}

		ifstream inputM(tPath, ios::binary);

		inputM.seekg(0, ios_base::end);
		int fend = (int)inputM.tellg();
		inputM.seekg(0, ios_base::beg);
		char* MainFile = new char[fend];
		inputM.read(MainFile, fend);
		ofstream tempFile(OPath, ios::binary);
		tempFile.write(MainFile, fend);
		tempFile.close();
		inputM.close();

		m_treeCtrl.DeleteAllItems();
		getStr(&m_treeCtrl, OPath, &itemArr);



		delete MainFile;
		delete[] opathx;

	}
}



void CMFCApplication1Dlg::CopyBlk()
{
	if ((op0) & (op1))
	{
		CString OPath, tPath;
		LPWSTR opathx = new TCHAR[255];
		GetTempPath(255, opathx);
		OPath = (LPWSTR)(LPCWSTR)opathx;
		OPath = OPath + L"b3d.temp1";


		tPath = OPath;
		tPath.Delete(OPath.GetLength() - 1, 1);
		tPath.Append(L"2");


		CArray<HTREEITEM> items0, items1;
		GetCheckedItems(m_treeCtrl, &items0, NULL);
		GetCheckedItems(m_treeCtrl1, &items1, NULL);


		ifstream input0(OPath, ios::binary);
		ifstream input1(Path1, ios::binary);

		CString msg0, msg1;


		msg0.Append(L"Куда:\n");


		msg0.Append((m_treeCtrl.GetItemText(items0[0]) + "\n"));

		msg0.Append(L"Блоки:\n");
		for (int i = 0; i < items1.GetCount(); i++)
		{
			msg0.Append((m_treeCtrl.GetItemText(items1[i]) + "\n"));
		}


		int MsgResult = MessageBox(msg0, _T("item?"), MB_OKCANCEL);
		switch (MsgResult)
		{
		case IDOK:
		{
			ofstream output(tPath, ios::binary);
			CString in0, in1, in2, in3;
			input0.seekg(0, ios_base::end);
			int fend = (int)input0.tellg();
			input0.seekg(0, ios_base::beg);

			input1.seekg(0, ios_base::end);


			char* text = new char[(int)input1.tellg()];

			input1.seekg(0, ios_base::beg);


			msg0 = L"Скопировать внутрь блока?";

			MsgResult = MessageBox(msg0, _T("Копир"), MB_YESNO);
			int offset;

			if (MsgResult == IDYES)
			{
				offset = itemArr[(int)m_treeCtrl.GetItemData(items0[0])].end;//смещение блока к концу
			}
			else
			{
				offset = itemArr[(int)m_treeCtrl.GetItemData(items0[0])].start;//смещение начала блока
			}
			//----
			char* beg = new char[offset];
			//----
			/*
			input0.read(text, offset);
			output.write(text, offset);
			*/
			input0.read(beg, offset);
			output.write(beg, offset);
			delete beg;

			int fromP = 0, toP = 0;

			for (int i = 0; i < items1.GetCount(); i++)
			{

				ITEMStruc data = itemArr1[(int)m_treeCtrl.GetItemData(items1[i])];
				if (!((data.start > fromP) & (data.endB < toP)))
				{
					input1.seekg(data.start, ios_base::beg);
					input1.read(text, data.endB - data.start);
					output.write(text, data.endB - data.start);
					fromP = data.start;
					toP = data.endB;
				}

			}




			char* end = new char[fend - offset];
			input0.read(end, fend - offset);
			output.write(end, fend - offset);
			delete end;

			output.close();
			input0.close();
			input1.close();
			delete text;

		}
		case IDCANCEL:
			break;
		}

		ifstream inputM(tPath, ios::binary);

		inputM.seekg(0, ios_base::end);
		int fend = (int)inputM.tellg();
		inputM.seekg(0, ios_base::beg);
		char* MainFile = new char[fend];
		inputM.read(MainFile, fend);
		ofstream tempFile(OPath, ios::binary);
		tempFile.write(MainFile, fend);
		tempFile.close();
		inputM.close();

		m_treeCtrl.DeleteAllItems();
		getStr(&m_treeCtrl, OPath, &itemArr);



		delete MainFile;
		delete[] opathx;

	}
}


void CMFCApplication1Dlg::getStr(CTreeCtrl* pCtrl1, LPCTSTR pathname, CArray<ITEMStruc, ITEMStruc>* itemArray)
{
	char b3dSig[4];
	ifstream input(pathname, ios::binary);

	input.read(b3dSig, 4);




	if (((b3dSig[0] == *"b") || (b3dSig[0] == *"B")) & (b3dSig[1] == *"3") & ((b3dSig[2] == *"d") || (b3dSig[2] == *"D")) & (b3dSig[3] == *"\0"))
	{
		input.seekg(20, ios::cur);
		int texNum, _case, type, i_null;
		input.read(reinterpret_cast<char*>(&texNum), sizeof(int));
		char texture[32], objName[32];
		HTREEITEM hMat, hBlocks;

		//itemArr.RemoveAll();
		itemArray->RemoveAll();


		hMat = pCtrl1->InsertItem(L"Materials:", TVI_ROOT);
		for (int i = 0; i < texNum; i++)
		{
			input.read((char*)&texture, 32);
			CString msg;
			msg.Format(_T("%d. %S"), i, texture);
			pCtrl1->InsertItem(msg, hMat);
			//log << texture << endl;
		}

		input.seekg(4, ios::cur);
		hBlocks = pCtrl1->InsertItem(L"Blocks:", TVI_ROOT);
		CArray<int> objectStr;
		vector <int> objString;
		vector <HTREEITEM> objects;

		int lvl = 0, objIter = 0;


		for (;;)
		{
			input.read(reinterpret_cast<char*>(&_case), sizeof(int));
			if (_case == 555) //2b02
			{
				lvl--;
				if (lvl < 0)
				{
					MessageBox(L"Case Error", L"Case error", 0);
					break;
				}
				int a = objectStr.GetSize() - 1;
				int x = objectStr.ElementAt(a);

				ITEMStruc pItem = itemArray->GetAt(x);
				pItem.endB = (int)input.tellg();

				itemArray->SetAt(x, pItem);

				objectStr.RemoveAt(a);
				continue;
			}
			else if (_case == 444)//bc01
			{
				continue;
			}
			else if (_case == 222)
			{
				input.close();
				break;
			}
			else if (_case == 333)
			{

				input.read((char*)&objName, 32);
				if (objName == '\0')
				{
					strcpy_s(objName, "Untitled");
				}

				CString msg, intM;
				int tell, tell1;
				tell = (int)input.tellg();
				tell = tell - 36;
				input.read(reinterpret_cast<char*>(&type), sizeof(int));



				HTREEITEM objectTree;
				if (lvl == 0)
				{
					objectTree = hBlocks;

				}
				else
				{
					int lastObj = objectStr.ElementAt(objectStr.GetSize() - 1);
					objectTree = objects.at(lastObj);

				}
				IBlock* block = nullptr;

				if (type == 0)
				{
					input.seekg(16, ios::cur);
					input.seekg(28, ios::cur);
				}
				else if (type == 1)
				{
					input.seekg(32, ios::cur);
					input.seekg(32, ios::cur);
				}
				else if (type == 2)
				{
					input.seekg(16, ios::cur);
					input.seekg(20, ios::cur);
				}
				else if (type == 3)
				{
					input.seekg(16, ios::cur);
					input.seekg(4, ios::cur);
				}
				else if (type == 4)
				{
					block = new Block04();
					block->Read(input);

				}
				else if (type == 5)
				{
					block = new Block05();
					block->Read(input);

				}
				else if (type == 6)
				{
					input.seekg(16, ios::cur);
					input.seekg(32, ios::cur);
					input.seekg(32, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					for (int i = 0; i < i_null; i++)
					{
						input.seekg(20, ios::cur);
					}
					input.seekg(4, ios::cur);
				}
				else if (type == 7)
				{
					input.seekg(16, ios::cur);
					input.seekg(32, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					for (int i = 0; i < i_null; i++)
					{
						input.seekg(20, ios::cur);
					}
					input.seekg(4, ios::cur);
				}
				else if (type == 8)
				{
					input.seekg(16, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					int i_null1, format;
					for (int i = 0; i < i_null; i++)
					{
						input.read(reinterpret_cast<char*>(&format), sizeof(int));
						input.seekg(12, ios::cur);
						input.read(reinterpret_cast<char*>(&i_null1), sizeof(int));
						if ((format == 178) || (format == 50))
						{
							for (int j = 0; j < i_null1; j++)
							{
								input.seekg(24, ios::cur);
							}
						}
						else if ((format == 3) || (format == 2) || (format == 131))
						{
							for (int j = 0; j < i_null1; j++)
							{
								input.seekg(12, ios::cur);
							}
						}
						else if ((format == 176) || (format == 48) || (format == 179) || (format == 51) || (format == 24))
						{
							for (int j = 0; j < i_null1; j++)
							{
								input.seekg(16, ios::cur);
							}
						}
						else if ((format == 177) || (format == 49))
						{
							for (int j = 0; j < i_null1; j++)
							{
								input.seekg(8, ios::cur);
							}
						}
						else
						{
							for (int j = 0; j < i_null1; j++)
							{
								input.seekg(4, ios::cur);
							}
						}
					}
				}
				else if (type == 9)
				{
					input.seekg(16, ios::cur);
					input.seekg(16, ios::cur);
					input.seekg(4, ios::cur);
				}
				else if (type == 10)
				{
					input.seekg(16, ios::cur);
					input.seekg(16, ios::cur);
					input.seekg(4, ios::cur);
				}

				else if (type == 11)
				{
					input.seekg(52, ios::cur);
				}
				else if (type == 12)
				{
					input.seekg(16, ios::cur);
					input.seekg(28, ios::cur);
				}
				else if (type == 13)
				{
					input.seekg(16, ios::cur);
					input.seekg(8, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					for (int i = 0; i < i_null; i++)
					{
						input.seekg(4, ios::cur);
					}
				}
				else if (type == 14)
				{
					block = new Block14();

					((Block14*)block)->objName = objName;  //Должно работать, но не обязательно будет, нужно проверить
					block->Read(input);

				}
				else if (type == 16)
				{
					input.seekg(16, ios::cur);
					input.seekg(44, ios::cur);
				}
				else if (type == 17)
				{
					input.seekg(16, ios::cur);
					input.seekg(44, ios::cur);
				}
				else if (type == 18)
				{
					input.seekg(16, ios::cur);
					input.seekg(32, ios::cur);
					input.seekg(32, ios::cur);
				}
				else if (type == 19)
				{
					input.seekg(4, ios::cur);
				}
				else if (type == 20)
				{
					input.seekg(16, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					input.seekg(8, ios::cur);
					int i_null1;
					input.read(reinterpret_cast<char*>(&i_null1), sizeof(int));
					for (int i = 0; i < i_null; i++)
					{
						input.seekg(12, ios::cur);
					}
					for (int i = 0; i < i_null1; i++)
					{
						input.seekg(4, ios::cur);
					}

				}
				else if (type == 21)
				{
					input.seekg(16, ios::cur);
					input.seekg(4, ios::cur);
					input.seekg(4, ios::cur);
					input.seekg(4, ios::cur);
				}
				else if (type == 23)
				{
					input.seekg(8, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					for (int i = 0; i < i_null; i++)
					{
						input.seekg(4, ios::cur);
					}
					int i_null1;
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					for (int i = 0; i < i_null; i++)
					{
						input.read(reinterpret_cast<char*>(&i_null1), sizeof(int));
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(12, ios::cur);
						}

					}
				}
				else if (type == 24)
				{
					input.seekg(12, ios::cur);
					input.seekg(12, ios::cur);
					input.seekg(12, ios::cur);
					input.seekg(12, ios::cur);
					input.seekg(8, ios::cur);
				}
				else if (type == 25)
				{
					input.seekg(12, ios::cur);
					input.seekg(32, ios::cur);
					input.seekg(4, ios::cur);
					input.seekg(40, ios::cur);
				}
				else if (type == 27)
				{
					input.seekg(36, ios::cur);
				}
				else if (type == 28)
				{
					block = new Block14();

					block->Read(input);

					//После всего, что между нами было, как я могу не сохранить данный кусочек сладкого кода
					//input.seekg(16, ios::cur);
					//input.seekg(12, ios::cur);
					//input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					//int i_null1, i_null2;

					//if (i_null == 1)
					//{
					//	input.read(reinterpret_cast<char*>(&i_null1), sizeof(int));
					//	input.seekg(12, ios::cur);
					//	input.read(reinterpret_cast<char*>(&i_null2), sizeof(int));

					//	if (i_null1 > 1)
					//	{
					//		for (int i = 0; i < i_null2; i++)
					//		{
					//			input.seekg(16, ios::cur);
					//		}
					//	}
					//	else
					//	{
					//		input.seekg(32, ios::cur);
					//	}
					//}
					//else if (i_null == 2)
					//{
					//	input.seekg(20, ios::cur);
					//	for (int i = 0; i < 4; i++)
					//	{
					//		input.seekg(28, ios::cur);
					//	}
					//	//input.read(reinterpret_cast<char*>(&testkey), sizeof(int));

					//	input.seekg(4, ios::cur);
					//}
					//else if ((i_null == 10) || (i_null == 6))
					//{
					//	for (int i = 0; i < i_null1; i++)
					//	{
					//		input.seekg(16, ios::cur);
					//		input.read(reinterpret_cast<char*>(&i_null2), sizeof(int));
					//		for (int j = 0; j < i_null2; j++)
					//		{
					//			input.seekg(8, ios::cur);
					//		}
					//	}
					//}

				}
				else if (type == 29)
				{
					block = new Block29();

					block->Read(input);
				}
				else if (type == 30)
				{
					input.seekg(16, ios::cur);
					input.seekg(32, ios::cur);
					input.seekg(24, ios::cur);
				}
				else if (type == 31)
				{
				block = new Block31();

				block->Read(input);

				}
				else if (type == 33)
				{
					input.seekg(16, ios::cur);
					input.seekg(12, ios::cur);
					input.seekg(64, ios::cur);
				}
				else if (type == 34)
				{
					input.seekg(16, ios::cur);
					input.seekg(4, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					for (int i = 0; i < i_null; i++)
					{
						input.seekg(16, ios::cur);
					}

				}
				else if (type == 35)
				{
					input.seekg(16, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					input.seekg(4, ios::cur);
					int i_null1, i_null2;
					input.read(reinterpret_cast<char*>(&i_null1), sizeof(int));
					if (i_null < 3)
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.read(reinterpret_cast<char*>(&i_null2), sizeof(int));
							if (i_null2 == 50)
							{
								input.seekg(88, ios::cur);
							}
							else if (i_null2 == 49)
							{
								input.seekg(40, ios::cur);
							}
							else if ((i_null2 == 1) || (i_null2 == 0))
							{
								input.seekg(28, ios::cur);
							}
							else if ((i_null2 == 2) || (i_null2 == 3))
							{
								input.seekg(52, ios::cur);
							}
							else
							{
								input.seekg(64, ios::cur);
							}
						}
					}
					else if (i_null == 3)
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(4, ios::cur);
							input.seekg(28, ios::cur);
						}
					}
				}
				else if (type == 36)
				{
					input.seekg(16, ios::cur);
					input.seekg(32, ios::cur);
					input.seekg(32, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					int i_null1;
					input.read(reinterpret_cast<char*>(&i_null1), sizeof(int));
					if (i_null == 0)
					{
						;
					}
					else if (i_null == 2)
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(32, ios::cur);
						}
					}
					else if (i_null == 3)
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(24, ios::cur);
						}
					}
					else if (i_null == 514)
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(48, ios::cur);
						}
					}
					else if ((i_null == 258) || (i_null == 515))
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(40, ios::cur);
						}
					}
					input.seekg(4, ios::cur);

				}
				else if (type == 37)
				{
					input.seekg(16, ios::cur);
					input.seekg(32, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					int i_null1;
					input.read(reinterpret_cast<char*>(&i_null1), sizeof(int));
					if (i_null == 0)
					{
						;
					}
					else if (i_null == 2)
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(32, ios::cur);
						}
					}
					else if (i_null == 3)
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(24, ios::cur);
						}
					}
					else if (i_null == 514)
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(48, ios::cur);
						}
					}
					else if ((i_null == 258) || (i_null == 515))
					{
						for (int i = 0; i < i_null1; i++)
						{
							input.seekg(40, ios::cur);
						}
					}
					input.seekg(4, ios::cur);
				}
				else if (type == 39)
				{
					input.seekg(16, ios::cur);
					input.seekg(16, ios::cur);
					input.seekg(4, ios::cur);
					input.seekg(4, ios::cur);

				}
				else if (type == 40)
				{
					input.seekg(16, ios::cur);
					input.seekg(32, ios::cur);
					input.seekg(32, ios::cur);
					input.seekg(8, ios::cur);
					input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
					for (int i = 0; i < i_null; i++)
					{
						input.seekg(4, ios::cur);
					}

				}
				else
				{
					MessageBox(_T("Type Error"), _T("b3dSig?"), NULL);
					break;
				}
				////
				//
				//
				////

				tell1 = (int)input.tellg();

				msg.Format(_T("%S (%d)"), objName, type);
				HTREEITEM objectTreeCur = (pCtrl1->InsertItem(msg, objectTree));



				ITEMStruc item;
				item.start = tell;
				item.end = tell1;
				item.lvl = lvl;
				item.type = type;


				//ITEMStruc * ItemPtr = new ITEMStruc;

				itemArray->Add(item);
				//itemArray.Add(item);

				//ItemPtr = &itemArray[objIter];

				pCtrl1->SetItemData(objectTreeCur, objIter);

				HTREEITEM ItemBack = pCtrl1->GetParentItem(objectTreeCur);

				ITEMStruc* lvlData = (ITEMStruc*)pCtrl1->GetItemData(objectTreeCur);
				DWORD_PTR lvData = (DWORD_PTR)pCtrl1->GetItemData(objectTreeCur);

				ITEMStruc* lvlData1 = (ITEMStruc*)pCtrl1->GetItemData(ItemBack);
				DWORD_PTR lvData1 = (DWORD_PTR)pCtrl1->GetItemData(ItemBack);


				objects.push_back(objectTreeCur);


				objectStr.Add(objIter);


				objIter++;
				lvl++;



				//log << type << "	" << objName << endl;



			}
			else
			{

				MessageBox(_T("Case Error"), _T("b3dSig?"), NULL);
				break;
			}

		}

		input.close();
		//log.close();
		//return texture;

	}
	else
	{
		CString msg;
		msg.Format(_T("%S"), b3dSig);
		MessageBox(_T("B3D is unknown"), _T("b3dbad"), NULL);
	}

}

void CMFCApplication1Dlg::OnTvnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
}


void CMFCApplication1Dlg::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
}



void CMFCApplication1Dlg::GetCheckedItems(const CTreeCtrl& tree, CArray<HTREEITEM>* checkedItems, HTREEITEM startItem = NULL)
{
	if (startItem == NULL)
		startItem = tree.GetRootItem();

	for (HTREEITEM item = startItem; item != NULL; item = tree.GetNextItem(item, TVGN_NEXT))
	{
		// figure out if this item is checked or not
		UINT state = (tree.GetItemState(item, TVIS_STATEIMAGEMASK) >> 12) & 15;

		if (state == 2)
		{
			checkedItems->Add(item);
			//CString str = (LPCTSTR)tree.GetItemData(item);
			//MessageBox(str, L"data", NULL);

		}

		// deal with children if present
		HTREEITEM child = tree.GetNextItem(item, TVGN_CHILD);

		if (child != NULL)
			GetCheckedItems(tree, checkedItems, child);
	}
}







void CMFCApplication1Dlg::OnNMClickTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	CPoint    point;
	UINT      uFlags;
	HTREEITEM hItem;

	GetCursorPos(&point);
	m_treeCtrl.ScreenToClient(&point);
	hItem = m_treeCtrl.HitTest(point, &uFlags);
	BOOL bCheck;
	if (hItem)
	{
		// There is an item under the cursor.
		// See what exactly was under the cursor:
		switch (uFlags)
		{
		case TVHT_ONITEMSTATEICON://working
			if (hItem && m_treeCtrl.ItemHasChildren(hItem) && m_treeCtrl.GetCheck(hItem))
				bCheck = FALSE;
			else if (hItem && m_treeCtrl.ItemHasChildren(hItem) && !m_treeCtrl.GetCheck(hItem))
				bCheck = TRUE;
			else bCheck = FALSE;
			CheckSiblings(m_treeCtrl, bCheck, hItem);

			break;

			// ...and so on
		}
	}

	*pResult = 0;
}

void CMFCApplication1Dlg::CheckSiblings(CTreeCtrl& tree, BOOL bCheck, HTREEITEM hItem)
{
	// check or uncheck the child items recursively
	// also expand the item if checking its children
	HTREEITEM hNextItem;
	/*if (bCheck)
		tree.Expand(hItem, TVE_EXPAND);*/

	hNextItem = tree.GetChildItem(hItem);
	while (hNextItem)
	{
		tree.SetCheck(hNextItem, bCheck);
		if (tree.ItemHasChildren(hNextItem))
			CheckSiblings(tree, bCheck, hNextItem);
		hNextItem = tree.GetNextItem(hNextItem, TVGN_NEXT);
	}
}

void CMFCApplication1Dlg::OnNMClickTree2(NMHDR* pNMHDR, LRESULT* pResult)
{
	CPoint    point;
	UINT      uFlags;
	HTREEITEM hItem;

	GetCursorPos(&point);
	m_treeCtrl1.ScreenToClient(&point);
	hItem = m_treeCtrl1.HitTest(point, &uFlags);
	BOOL bCheck;
	if (hItem)
	{
		// There is an item under the cursor.
		// See what exactly was under the cursor:
		switch (uFlags)
		{
		case TVHT_ONITEMSTATEICON://working
			if (hItem && m_treeCtrl1.ItemHasChildren(hItem) && m_treeCtrl1.GetCheck(hItem))
				bCheck = FALSE;
			else if (hItem && m_treeCtrl1.ItemHasChildren(hItem) && !m_treeCtrl1.GetCheck(hItem))
				bCheck = TRUE;
			else bCheck = FALSE;
			CheckSiblings(m_treeCtrl1, bCheck, hItem);

			break;

			// ...and so on
		}
	}

	*pResult = 0;
}

void CMFCApplication1Dlg::Save()
{
	CFileDialog fileDialogOpen(TRUE, NULL, L"*.b3d");
	int result = fileDialogOpen.DoModal();

	CString Path_new = fileDialogOpen.GetPathName();


	CString OPath;
	LPWSTR opathx = new TCHAR[255];

	GetTempPath(255, opathx);

	OPath = (LPWSTR)(LPCWSTR)opathx;
	OPath = OPath + L"b3d.temp1";
	delete opathx;

	ifstream tempFile(OPath, ios::binary);
	ofstream inputM(Path_new, ios::binary);

	tempFile.seekg(0, ios_base::end);
	int fend = (int)tempFile.tellg();
	tempFile.seekg(0, ios_base::beg);
	char* MainFile = new char[fend];

	tempFile.read(MainFile, fend);

	tempFile.close();


	inputM.write(MainFile, fend);
	tempFile.close();
	inputM.close();
	delete MainFile;

}


void CMFCApplication1Dlg::OnNMDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	HTREEITEM item = m_treeCtrl.GetSelectedItem();
	int numIt = (int)m_treeCtrl.GetItemData(item);

	ITEMStruc itemS = itemArr[numIt];

	CString OPath, tPath;
	LPWSTR opathx = new TCHAR[255];
	GetTempPath(255, opathx);
	OPath = (LPWSTR)(LPCWSTR)opathx;
	OPath = OPath + L"b3d.temp1";
	delete opathx;
	bool reload = FALSE;

	tPath = OPath;
	tPath.Delete(OPath.GetLength() - 1, 1);
	tPath.Append(L"2");
	ifstream input0(OPath, ios_base::binary);
	ofstream output0(tPath, ios_base::binary);

	input0.seekg(0, ios_base::end);
	int fend = (int)input0.tellg();
	input0.seekg(0, ios_base::beg);
	char* MainFile = new char[fend];


	input0.read(MainFile, itemS.start + 4);//читать с 4d01
	output0.write(MainFile, itemS.start + 4);
	CAddMat dialog;
	char objName[32];

	input0.read((char*)&objName, 32);
	dialog.m_value = objName;


	dialog.m_text = L"Имя блока:";

	dialog.m_caption = L"Свойства блока";



	if (itemS.type == 5)
	{

		CString str;
		buttonAdd edit, cap;
		float num;
		int num1;

		input0.seekg(4, ios_base::cur);
		char child[32];

		cap.caption = L"Центр блока:";
		cap.Rectangle = CRect(11, 70, 180, 90);
		dialog.NewCap.Add(cap);

		input0.read(reinterpret_cast<char*>(&num), sizeof(float));
		str.Format(L"%.4f", num);
		edit.caption = str;
		edit.Rectangle = CRect(11, 90, 58, 110);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&num), sizeof(float));
		str.Format(L"%.4f", num);
		edit.caption = str;
		edit.Rectangle = CRect(60, 90, 115, 110);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&num), sizeof(float));
		str.Format(L"%.4f", num);
		edit.caption = str;
		edit.Rectangle = CRect(117, 90, 180, 110);
		dialog.NewEdit.Add(edit);

		cap.caption = L"Дальность прорисовки:";
		cap.Rectangle = CRect(11, 112, 180, 132);
		dialog.NewCap.Add(cap);

		input0.read(reinterpret_cast<char*>(&num), sizeof(float));
		str.Format(L"%.4f", num);
		edit.caption = str;
		edit.Rectangle = CRect(11, 132, 180, 152);
		dialog.NewEdit.Add(edit);




		input0.read((char*)&child, 32);

		cap.caption = L"Связаный обьект:";
		cap.Rectangle = CRect(11, 154, 180, 174);
		dialog.NewCap.Add(cap);

		edit.caption = child;
		edit.Rectangle = CRect(11, 174, 180, 194);
		dialog.NewEdit.Add(edit);



		cap.caption = L"Количество дочерних обьектов:";
		cap.Rectangle = CRect(11, 196, 180, 216);
		dialog.NewCap.Add(cap);



		input0.read(reinterpret_cast<char*>(&num1), sizeof(int));
		str.Format(L"%d", num1);
		edit.caption = str;
		edit.Rectangle = CRect(11, 216, 182, 236);
		dialog.NewEdit.Add(edit);

		CRect wR;
		this->GetWindowRect(&wR);
		int left, top;
		left = wR.left + (wR.Height() / 2) - 210 / 2;
		top = wR.top + (wR.Width() / 2) - 315 / 2;
		dialog.WinSize = CRect(left, top, left + 210, top + 315);

		if (dialog.DoModal() == IDOK)
		{
			reload = TRUE;
			str = dialog.GetValue();
			strcpy_s(objName, 32, CT2A(str));

			output0.write(objName, 32);
			output0.write(reinterpret_cast<char*>(&itemS.type), sizeof(int));

			num = (float)_ttof(dialog.captions[0]);

			output0.write(reinterpret_cast<char*>(&num), sizeof(float));

			num = (float)_ttof(dialog.captions[1]);

			output0.write(reinterpret_cast<char*>(&num), sizeof(float));

			num = (float)_ttof(dialog.captions[2]);

			output0.write(reinterpret_cast<char*>(&num), sizeof(float));

			num = (float)_ttof(dialog.captions[3]);

			output0.write(reinterpret_cast<char*>(&num), sizeof(float));


			str = dialog.captions[4];
			strcpy_s(child, 32, CT2A(str));
			output0.write(child, 32);

			num1 = (int)_ttoi(dialog.captions[5]);

			output0.write(reinterpret_cast<char*>(&num1), sizeof(int));

			input0.read(MainFile, fend - itemS.end);
			output0.write(MainFile, fend - itemS.end);
		}

	}
	else if (itemS.type == 12)
	{
		CRect wR;
		this->GetWindowRect(&wR);
		int left, top;


		float fNum;
		int iNum;
		CString str;

		buttonAdd edit, cap;

		input0.seekg(4, ios_base::cur);


		cap.caption = L"Центр блока:";
		cap.Rectangle = CRect(11, 70, 180, 90);
		dialog.NewCap.Add(cap);

		input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
		str.Format(L"%.4f", fNum);
		edit.caption = str;
		edit.Rectangle = CRect(11, 90, 58, 110);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
		str.Format(L"%.4f", fNum);
		edit.caption = str;
		edit.Rectangle = CRect(60, 90, 115, 110);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
		str.Format(L"%.4f", fNum);
		edit.caption = str;
		edit.Rectangle = CRect(117, 90, 180, 110);
		dialog.NewEdit.Add(edit);

		cap.caption = L"Настройки обьекта:";
		cap.Rectangle = CRect(11, 111, 180, 131);
		dialog.NewCap.Add(cap);

		int hPos = 131;
		int wPos = 11;
		int j = 0;

		for (int i = 0; i < 5; i++)
		{
			input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
			str.Format(L"%.4f", fNum);
			edit.caption = str;
			edit.Rectangle = CRect(wPos, hPos, wPos + 47, hPos + 20);
			dialog.NewEdit.Add(edit);

			wPos += 49;
			j++;
			if (j == 3)
			{
				hPos += 21;
				wPos = 11;
				j = 0;
			}

		}

		hPos += 21;
		wPos = 11;
		j = 0;


		for (int i = 0; i < 3; i++)
		{
			input0.read(reinterpret_cast<char*>(&iNum), sizeof(int));
			str.Format(L"%d", iNum);
			edit.caption = str;
			edit.Rectangle = CRect(wPos, hPos, wPos + 47, hPos + 20);
			dialog.NewEdit.Add(edit);

			wPos += 49;
			j++;
			if (j == 3)
			{
				hPos += 21;
				wPos = 11;
				j = 0;
			}

		}
		hPos += 21;
		wPos = 11;
		j = 0;

		left = wR.left + (wR.Height() / 2) - 210 / 2;
		top = wR.top + (wR.Width() / 2) - (hPos + 55) / 2;
		dialog.WinSize = CRect(left, top, left + 210, top + (hPos + 55));

		if (dialog.DoModal() == IDOK)
		{
			reload = TRUE;
			str = dialog.GetValue();
			strcpy_s(objName, 32, CT2A(str));

			output0.write(objName, 32);
			output0.write(reinterpret_cast<char*>(&itemS.type), sizeof(int));


			for (int i = 0; i < 8; i++)
			{
				fNum = (float)_ttof(dialog.captions[i]);
				output0.write(reinterpret_cast<char*>(&fNum), sizeof(float));
			}

			for (int i = 0; i < 3; i++)
			{
				iNum = (int)_ttoi(dialog.captions[i + 8]);
				output0.write(reinterpret_cast<char*>(&iNum), sizeof(int));
			}


			int buffer = fend - itemS.end;
			int x = (int)input0.tellg();
			input0.read(MainFile, buffer);
			output0.write(MainFile, buffer);


		}


	}

	else if (itemS.type == 18)
	{
		CRect wR;
		this->GetWindowRect(&wR);
		int left, top;
		left = wR.left + (wR.Height() / 2) - 210 / 2;
		top = wR.top + (wR.Width() / 2) - 235 / 2;
		dialog.WinSize = CRect(left, top, left + 210, top + 235);


		buttonAdd edit, cap;

		cap.caption = L"Обьект:";
		cap.Rectangle = CRect(11, 75, 180, 92);
		dialog.NewCap.Add(cap);


		input0.seekg(20, ios_base::cur);
		input0.read((char*)&objName, 32);

		edit.caption = objName;
		edit.Rectangle = CRect(11, 92, 182, 115);


		dialog.NewEdit.Add(edit);

		cap.caption = L"Настройки обьекта:";
		cap.Rectangle = CRect(11, 115, 180, 132);
		dialog.NewCap.Add(cap);


		input0.read((char*)&objName, 32);

		edit.caption = objName;
		edit.Rectangle = CRect(11, 132, 182, 156);

		dialog.NewEdit.Add(edit);


		if (dialog.DoModal() == IDOK)
		{
			reload = TRUE;
			strcpy_s(objName, CT2A(dialog.GetValue()));

			output0.write(objName, 32);
			CString str;
			output0.write(reinterpret_cast<char*>(&itemS.type), sizeof(int));
			output0.write("\0", 16);

			str = dialog.captions[0];
			output0.write(CT2A(str), 32);
			str = dialog.captions[1];
			output0.write(CT2A(str), 32);

			input0.read(MainFile, fend - itemS.end);
			output0.write(MainFile, fend - itemS.end);

		}


	}
	else if (itemS.type == 19)
	{
		CRect wR;
		this->GetWindowRect(&wR);
		int left, top;
		left = wR.left + (wR.Height() / 2) - 210 / 2;
		top = wR.top + (wR.Width() / 2) - 210 / 2;
		dialog.WinSize = CRect(left, top, left + 210, top + 210);

		buttonAdd edit, cap;
		int iNum;
		CString str;

		input0.seekg(4, ios_base::cur);

		cap.caption = L"Кол-во дочерних обьектов:";
		cap.Rectangle = CRect(11, 70, 180, 92);
		dialog.NewCap.Add(cap);

		input0.read(reinterpret_cast<char*>(&iNum), sizeof(float));
		str.Format(L"%d", iNum);
		edit.caption = str;
		edit.Rectangle = CRect(11, 92, 58, 112);
		dialog.NewEdit.Add(edit);

		if (dialog.DoModal() == IDOK)
		{
			reload = TRUE;
			str = dialog.GetValue();
			strcpy_s(objName, 32, CT2A(str));

			output0.write(objName, 32);
			output0.write(reinterpret_cast<char*>(&itemS.type), sizeof(int));
			iNum = (int)_ttoi(dialog.captions[0]);
			output0.write(reinterpret_cast<char*>(&iNum), sizeof(float));


			int buffer = fend - itemS.end;
			input0.read(MainFile, buffer);
			output0.write(MainFile, buffer);

		}

	}
	else if (itemS.type == 24)
	{
		CRect wR;
		this->GetWindowRect(&wR);
		int left, top;
		left = wR.left + (wR.Height() / 2) - 210 / 2;
		top = wR.top + (wR.Width() / 2) - 300 / 2;
		dialog.WinSize = CRect(left, top, left + 210, top + 300);

		buttonAdd edit, cap;
		float num;
		CString str;

		input0.seekg(4, ios_base::cur);

		cap.caption = L"Матрица преобразования:";
		cap.Rectangle = CRect(11, 70, 180, 92);
		dialog.NewCap.Add(cap);

		int hPos = 92;

		for (int i = 0; i < 3; i++)
		{
			input0.read(reinterpret_cast<char*>(&num), sizeof(float));
			str.Format(L"%.4f", num);
			edit.caption = str;
			edit.Rectangle = CRect(11, hPos, 58, hPos + 20);
			dialog.NewEdit.Add(edit);

			input0.read(reinterpret_cast<char*>(&num), sizeof(float));
			str.Format(L"%.4f", num);
			edit.caption = str;
			edit.Rectangle = CRect(60, hPos, 115, hPos + 20);
			dialog.NewEdit.Add(edit);

			input0.read(reinterpret_cast<char*>(&num), sizeof(float));
			str.Format(L"%.4f", num);
			edit.caption = str;
			edit.Rectangle = CRect(117, hPos, 180, hPos + 20);
			dialog.NewEdit.Add(edit);
			hPos += 21;
		}

		cap.caption = L"Позиция:";
		cap.Rectangle = CRect(11, 170, 180, 187);
		dialog.NewCap.Add(cap);


		input0.read(reinterpret_cast<char*>(&num), sizeof(float));
		str.Format(L"%.4f", num);
		edit.caption = str;
		edit.Rectangle = CRect(11, 187, 58, 209);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&num), sizeof(float));
		str.Format(L"%.4f", num);
		edit.caption = str;
		edit.Rectangle = CRect(60, 187, 115, 209);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&num), sizeof(float));
		str.Format(L"%.4f", num);
		edit.caption = str;
		edit.Rectangle = CRect(117, 187, 180, 209);
		dialog.NewEdit.Add(edit);


		if (dialog.DoModal() == IDOK)
		{
			reload = TRUE;
			str = dialog.GetValue();
			strcpy_s(objName, 32, CT2A(str));

			output0.write(objName, 32);
			output0.write(reinterpret_cast<char*>(&itemS.type), sizeof(int));
			for (int i = 0; i < 12; i++)
			{
				num = (float)_ttof(dialog.captions[i]);
				output0.write(reinterpret_cast<char*>(&num), sizeof(float));
			}

			int buffer = fend - itemS.end;
			input0.read(MainFile, buffer + 8);
			output0.write(MainFile, buffer + 8);

		}




	}
	else if (itemS.type == 33)
	{
		CRect wR;
		this->GetWindowRect(&wR);
		int left, top;
		left = wR.left + (wR.Height() / 2) - 210 / 2;
		top = wR.top + (wR.Width() / 2) - 320 / 2;
		dialog.WinSize = CRect(left, top, left + 210, top + 320);

		buttonAdd edit, cap;
		float fNum;
		int iNum;
		CString str;
		char* posns = new char[16];

		input0.seekg(4, ios_base::cur);
		input0.read(posns, 16);
		//input0.seekg(16, ios_base::cur);

		cap.caption = L"Параметры 1:";
		cap.Rectangle = CRect(11, 70, 180, 92);
		dialog.NewCap.Add(cap);

		input0.read(reinterpret_cast<char*>(&iNum), sizeof(int));
		str.Format(L"%d", iNum);
		edit.caption = str;
		edit.Rectangle = CRect(11, 92, 58, 116);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&iNum), sizeof(int));
		str.Format(L"%d", iNum);
		edit.caption = str;
		edit.Rectangle = CRect(60, 92, 115, 116);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&iNum), sizeof(int));
		str.Format(L"%d", iNum);
		edit.caption = str;
		edit.Rectangle = CRect(117, 92, 180, 116);
		dialog.NewEdit.Add(edit);

		cap.caption = L"Позиция:";
		cap.Rectangle = CRect(11, 117, 180, 137);
		dialog.NewCap.Add(cap);

		int hPos = 137;
		int wPos = 11;
		int j = 0;

		for (int i = 0; i < 15; i++)
		{
			input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
			str.Format(L"%.4f", fNum);
			edit.caption = str;
			edit.Rectangle = CRect(wPos, hPos, wPos + 47, hPos + 20);
			dialog.NewEdit.Add(edit);

			wPos += 49;
			j++;
			if (j == 3)
			{
				hPos += 21;
				wPos = 11;
				j = 0;
			}
		}

		if (dialog.DoModal() == IDOK)
		{
			reload = TRUE;
			str = dialog.GetValue();
			strcpy_s(objName, 32, CT2A(str));

			output0.write(objName, 32);
			output0.write(reinterpret_cast<char*>(&itemS.type), sizeof(int));
			output0.write(posns, 16);

			for (int i = 0; i < 3; i++)
			{
				iNum = (int)_ttoi(dialog.captions[i]);
				output0.write(reinterpret_cast<char*>(&iNum), sizeof(int));
			}


			for (int i = 0; i < 15; i++)
			{
				fNum = (float)_ttof(dialog.captions[i + 3]);
				output0.write(reinterpret_cast<char*>(&fNum), sizeof(float));
			}

			int buffer = fend - itemS.end;
			int x = (int)input0.tellg();
			input0.read(MainFile, buffer + 8);
			output0.write(MainFile, buffer + 4);

		}




	}
	else if (itemS.type == 35)
	{
		CRect wR;
		this->GetWindowRect(&wR);
		int left, top;
		left = wR.left + (wR.Height() / 2) - 210 / 2;
		top = wR.top + (wR.Width() / 2) - 190 / 2;
		dialog.WinSize = CRect(left, top, left + 210, top + 190);


		buttonAdd edit, cap1;
		int texnum, tellg;
		CString cap;

		char text[20];


		cap1.caption = L"Номер текстуры:";
		cap1.Rectangle = CRect(11, 60, 180, 77);
		dialog.NewCap.Add(cap1);


		input0.seekg(4, ios_base::cur);
		input0.read(text, 20);
		input0.read((char*)&texnum, sizeof(int));
		cap.Format(L"%d", texnum);
		edit.caption = cap;
		edit.Rectangle = CRect(11, 78, 182, 100);

		dialog.NewEdit.Add(edit);

		tellg = (int)input0.tellg();

		if (dialog.DoModal() == IDOK)
		{
			reload = TRUE;
			strcpy_s(objName, CT2A(dialog.GetValue()));

			output0.write(objName, 32);
			CString str;
			output0.write(reinterpret_cast<char*>(&itemS.type), sizeof(int));

			output0.write(text, 20);

			texnum = (int)_ttoi(dialog.captions[0]);
			output0.write(reinterpret_cast<char*>(&texnum), sizeof(int));

			input0.read(MainFile, fend - tellg);
			output0.write(MainFile, fend - tellg);

		}


	}
	else if (itemS.type == 40)
	{
		CRect wR;
		this->GetWindowRect(&wR);
		int left, top;


		buttonAdd edit, cap;
		float fNum;
		int iNum;
		CString str;
		char buffer[32];

		input0.seekg(4, ios_base::cur);


		cap.caption = L"Позиция:";
		cap.Rectangle = CRect(11, 70, 180, 92);
		dialog.NewCap.Add(cap);

		input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
		str.Format(L"%.4f", fNum);
		edit.caption = str;
		edit.Rectangle = CRect(11, 92, 58, 116);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
		str.Format(L"%.4f", fNum);
		edit.caption = str;
		edit.Rectangle = CRect(60, 92, 115, 116);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
		str.Format(L"%.4f", fNum);
		edit.caption = str;
		edit.Rectangle = CRect(117, 92, 180, 116);
		dialog.NewEdit.Add(edit);

		cap.caption = L"Масштаб:";
		cap.Rectangle = CRect(11, 117, 180, 137);
		dialog.NewCap.Add(cap);

		input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
		str.Format(L"%.4f", fNum);
		edit.caption = str;
		edit.Rectangle = CRect(11, 137, 58, 157);
		dialog.NewEdit.Add(edit);

		input0.read((char*)&buffer, 32);

		cap.caption = L"Связаный обьект:";
		cap.Rectangle = CRect(11, 158, 180, 178);
		dialog.NewCap.Add(cap);

		edit.caption = buffer;
		edit.Rectangle = CRect(11, 178, 180, 198);
		dialog.NewEdit.Add(edit);

		input0.read((char*)&buffer, 32);

		cap.caption = L"Генератор:";
		cap.Rectangle = CRect(11, 199, 180, 219);
		dialog.NewCap.Add(cap);

		edit.caption = buffer;
		edit.Rectangle = CRect(11, 219, 180, 239);
		dialog.NewEdit.Add(edit);

		cap.caption = L"Свойства генератора:";
		cap.Rectangle = CRect(11, 240, 180, 260);
		dialog.NewCap.Add(cap);

		input0.read(reinterpret_cast<char*>(&iNum), sizeof(int));
		str.Format(L"%d", iNum);
		edit.caption = str;
		edit.Rectangle = CRect(11, 260, 58, 280);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&iNum), sizeof(int));
		str.Format(L"%d", iNum);
		edit.caption = str;
		edit.Rectangle = CRect(60, 260, 115, 280);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&iNum), sizeof(int));
		str.Format(L"%d", iNum);
		edit.caption = str;
		edit.Rectangle = CRect(117, 260, 180, 280);
		dialog.NewEdit.Add(edit);

		int pCount = iNum;

		int hPos = 281;
		int wPos = 11;
		int j = 0;

		for (int i = 0; i < pCount - 2; i++)
		{
			input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
			str.Format(L"%.4f", fNum);
			edit.caption = str;
			edit.Rectangle = CRect(wPos, hPos, wPos + 47, hPos + 20);
			dialog.NewEdit.Add(edit);

			wPos += 49;
			j++;
			if (j == 3)
			{
				hPos += 21;
				wPos = 11;
				j = 0;
			}

		}
		hPos += 21;
		wPos = 11;
		j = 0;

		input0.read(reinterpret_cast<char*>(&iNum), sizeof(int));
		str.Format(L"%d", iNum);
		edit.caption = str;
		edit.Rectangle = CRect(11, hPos, 58, hPos + 20);
		dialog.NewEdit.Add(edit);

		input0.read(reinterpret_cast<char*>(&fNum), sizeof(float));
		str.Format(L"%.4f", fNum);
		edit.caption = str;
		edit.Rectangle = CRect(60, hPos, 115, hPos + 20);
		dialog.NewEdit.Add(edit);


		left = wR.left + (wR.Height() / 2) - 210 / 2;
		top = wR.top + (wR.Width() / 2) - (hPos + 100) / 2;
		dialog.WinSize = CRect(left, top, left + 210, top + (hPos + 100));

		if (dialog.DoModal() == IDOK)
		{
			reload = TRUE;
			str = dialog.GetValue();
			strcpy_s(objName, 32, CT2A(str));

			output0.write(objName, 32);
			output0.write(reinterpret_cast<char*>(&itemS.type), sizeof(int));

			for (int i = 0; i < 4; i++)
			{
				fNum = (float)_ttof(dialog.captions[i]);
				output0.write(reinterpret_cast<char*>(&fNum), sizeof(float));
			}

			str = dialog.captions[4];
			strcpy_s(objName, 32, CT2A(str));
			output0.write(objName, 32);

			str = dialog.captions[5];
			strcpy_s(objName, 32, CT2A(str));
			output0.write(objName, 32);




			for (int i = 0; i < 3; i++)
			{
				iNum = (int)_ttoi(dialog.captions[i + 6]);
				output0.write(reinterpret_cast<char*>(&iNum), sizeof(int));
			}


			for (int i = 0; i < pCount - 2; i++)
			{
				fNum = (float)_ttof(dialog.captions[i + 9]);
				output0.write(reinterpret_cast<char*>(&fNum), sizeof(float));
			}

			for (int i = 0; i < 2; i++)
			{
				iNum = (int)_ttoi(dialog.captions[i + 9 + pCount - 2]);
				output0.write(reinterpret_cast<char*>(&iNum), sizeof(int));
			}

			int buffer = fend - itemS.end;
			int x = (int)input0.tellg();
			input0.read(MainFile, buffer);
			output0.write(MainFile, buffer);

		}




	}

	else
	{
		CRect wR;
		this->GetWindowRect(&wR);
		int left, top;
		left = wR.left + (wR.Height() / 2) - 210 / 2;
		top = wR.top + (wR.Width() / 2) - 150 / 2;
		dialog.WinSize = CRect(left, top, left + 210, top + 150);

		if (dialog.DoModal() == IDOK)
		{
			reload = TRUE;

			strcpy_s(objName, CT2A(dialog.GetValue()));



			output0.write(objName, 32);


			input0.read(MainFile, fend - itemS.start - 36);
			output0.write(MainFile, fend - itemS.start - 3);
		}


	}

	input0.close();
	output0.close();

	if (reload == TRUE)
	{
		ifstream inputM(tPath, ios::binary);

		inputM.seekg(0, ios_base::end);
		fend = (int)inputM.tellg();
		inputM.seekg(0, ios_base::beg);
		MainFile = new char[fend];
		inputM.read(MainFile, fend);
		ofstream tempFile(OPath, ios::binary);
		tempFile.write(MainFile, fend);
		tempFile.close();
		inputM.close();

		m_treeCtrl.DeleteAllItems();
		getStr(&m_treeCtrl, OPath, &itemArr);
		delete MainFile;
	}


	*pResult = 0;
}
