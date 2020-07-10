#pragma once
#define EditItems 40

struct buttonAdd
{
	CRect Rectangle;
	CString caption;
};

// диалоговое окно CAddMat

class CAddMat : public CDialog
{
	DECLARE_DYNAMIC(CAddMat)
	CButton myButton;
	CEdit myEdit[EditItems];
	CStatic myCap[EditItems];
	CString captions[EditItems];


public:
	CAddMat(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAddMat();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDMAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	CEdit mEdit;
	CRect WinSize;
	CStatic mText;
	CArray <buttonAdd> NewButton;
	CArray <buttonAdd> NewEdit;
	CArray <buttonAdd> NewCap;
	CString m_value, m_text, m_caption;
	CString GetValue() const { return m_value; }
	void SetText();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	void AddButton(CRect rectang, CString caption);
	void AddEdit(CRect rectang, CString caption, int i);
	void AddCap(CRect rectang, CString caption, int i);
	afx_msg void OnBnClickedCancel();
};
