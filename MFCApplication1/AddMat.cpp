// AddMat.cpp: файл реализации
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "AddMat.h"
#include "afxdialogex.h"

// диалоговое окно CAddMat

IMPLEMENT_DYNAMIC(CAddMat, CDialog)


CAddMat::CAddMat(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ADDMAT, pParent)
{

	m_text = L"Имя материала:";
	m_caption = L"Внести материалы?";
	m_value = L"";

}

CAddMat::~CAddMat()
{

}

void CAddMat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEdit);
	DDX_Control(pDX, IDC_STATIC_TEXT_CTRL, mText);
}


BEGIN_MESSAGE_MAP(CAddMat, CDialog)
	ON_BN_CLICKED(IDOK, &CAddMat::OnBnClickedOk)
	ON_BN_CLICKED(1, &CAddMat::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CAddMat::OnEnChangeEdit1)
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDCANCEL, &CAddMat::OnBnClickedCancel)
END_MESSAGE_MAP()



BOOL CAddMat::OnInitDialog()
{

	CDialog::OnInitDialog();
	SetText();
	for (int i = 0; i<NewButton.GetCount();i++)
		AddButton(NewButton[i].Rectangle, NewButton[i].caption);
	for (int i = 0; i<NewEdit.GetCount(); i++)
		AddEdit(NewEdit[i].Rectangle, NewEdit[i].caption,i);
	for (int i = 0; i<NewCap.GetCount(); i++)
		AddCap(NewCap[i].Rectangle, NewCap[i].caption, i);
	if ((WinSize.bottom>0)&(WinSize.right>0))
		MoveWindow(WinSize, TRUE);



	return TRUE;
	//SetWindowPos(NULL, 0, 0, 1000, 1000, SWP_SHOWWINDOW);
}

void CAddMat::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT1, m_value);
	for (int i = 0; i < EditItems; i++)
		if (myEdit[i])
			myEdit[i].GetWindowTextW(captions[i]);
	
	CDialog::OnOK();
}

void CAddMat::SetText()
{
	SetWindowTextW(m_caption);
	

	//wnd->SetWindowTextW(m_caption);

	CStatic *caption = (CStatic *)GetDlgItem(IDC_STATIC_TEXT_CTRL);
	caption->SetWindowTextW(m_text);
	CEdit* cedit = (CEdit*)GetDlgItem(IDC_EDIT1);
	cedit -> SetWindowTextW(m_value);

}

void CAddMat::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


int CAddMat::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}


void CAddMat::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	SetText();
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CAddMat::AddButton(CRect rectang, CString caption)
{

	myButton.Create(caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectang, this, 1);

}
void CAddMat::AddCap(CRect rectang, CString caption, int i)
{

	myCap[i].Create(caption, WS_CHILD | WS_VISIBLE | SS_LEFT, rectang, this, 1);
	myCap[i].SetFont(mEdit.GetFont(), TRUE);


}

void CAddMat::AddEdit(CRect rectang, CString caption,int i)
{

	myEdit[i].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectang, this, i);
	myEdit[i].SetWindowTextW(caption);
	myEdit[i].SetFont(mEdit.GetFont(),TRUE);
}

void CAddMat::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnCancel();
}
