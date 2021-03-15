
// MFCApplication1Dlg.h : файл заголовка
//

#pragma once
#include "afxcmn.h"

struct ITEMStruc
{
int start, end, lvl, endB, type;
};



// диалоговое окно CMFCApplication1Dlg
class CMFCApplication1Dlg : public CDialogEx
{
// Создание
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OpenFile1();
	CArray<ITEMStruc, ITEMStruc> itemArr;
	CArray<ITEMStruc, ITEMStruc> itemArr1;
	CTreeCtrl m_treeCtrl;
	CTreeCtrl m_treeCtrl1;
	CString Path0, Path1;
	bool op0, op1;
	void getStr(CTreeCtrl* pCtrl1, LPCTSTR pathname, CArray<ITEMStruc, ITEMStruc> * itemArray);
	afx_msg void OnTvnSelchangedTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OpenFile2();
	afx_msg void CopyBlk();
	void GetCheckedItems(const CTreeCtrl& tree, CArray<HTREEITEM> *checkedItems, HTREEITEM startItem );
	void CheckSiblings(CTreeCtrl& tree, BOOL bCheck, HTREEITEM hItem);
	afx_msg void RemBlk();
	afx_msg void ReplBlk();
	afx_msg void AddMat();
	afx_msg void ADD05();
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void ExportBlk();
	afx_msg void Save();
	afx_msg void AboutBox();
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT CloseApp(WPARAM wParam, LPARAM lParam);
	void ClearEmptySymbols(char* input);

};
