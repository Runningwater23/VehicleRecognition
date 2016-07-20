
// VihecleRecognitionVS2013Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VihecleRecognitionVS2013.h"
#include "VihecleRecognitionVS2013Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVihecleRecognitionVS2013Dlg �Ի���



CVihecleRecognitionVS2013Dlg::CVihecleRecognitionVS2013Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVihecleRecognitionVS2013Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVihecleRecognitionVS2013Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVihecleRecognitionVS2013Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnOpen, &CVihecleRecognitionVS2013Dlg::OnBnClickedBtnopen)
	ON_BN_CLICKED(IDC_BtnPlay, &CVihecleRecognitionVS2013Dlg::OnBnClickedBtnplay)
	ON_BN_CLICKED(IDC_BtnNext, &CVihecleRecognitionVS2013Dlg::OnBnClickedBtnnext)
	ON_BN_CLICKED(IDC_BtnBefo, &CVihecleRecognitionVS2013Dlg::OnBnClickedBtnbefo)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CVihecleRecognitionVS2013Dlg ��Ϣ�������

BOOL CVihecleRecognitionVS2013Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVihecleRecognitionVS2013Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVihecleRecognitionVS2013Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//////////////////////////////
/*
���룺IplImage *img //Ҫ��ʾ��ͼ��
���룺int id //��ʾͼ��Ŀؼ���id��
*/
//////////////////////////////
void CVihecleRecognitionVS2013Dlg::ShowImage(Mat& src, UINT ID)
{
	Mat dest = src.clone();
	if (src.empty())
	{
		AfxMessageBox(_T("û�л�ȡͼ��"));
		return;
	}
	dest = cv::Scalar::all(0);
	// ���㽫ͼƬ���ŵ� Image ��������ı�������
	double wRatio = dest.cols / (double)src.cols;
	double hRatio = dest.rows / (double)src.rows;
	double srcWH = src.cols / (double)src.rows;
	double desWH = dest.cols / (double)dest.rows;
	double scale = srcWH > desWH ? wRatio : hRatio;

	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)(src.cols * scale);
	int nh = (int)(src.rows * scale);

	// Ϊ�˽����ź��ͼƬ���� des �����в�λ�������ͼƬ�� des ���Ͻǵ���������ֵ
	int tlx = (int)((dest.cols - nw) / 2);
	int tly = (int)((dest.rows - nh) / 2);

	// ���� des �� ROI ������������ͼƬ img
	cv::Mat desRoi = dest(cv::Rect(tlx, tly, nw, nh));

	// ���src�ǵ�ͨ��ͼ����ת��Ϊ��ͨ��ͼ��
	if (src.channels() == 1)
	{
		cv::Mat src_c;
		cvtColor(src, src_c, CV_GRAY2BGR);
		// ��ͼƬ src_t �������ţ������뵽 des ��
		resize(src_c, desRoi, desRoi.size());
	}
	else
	{
		// ��ͼƬ src �������ţ������뵽 des ��
		resize(src, desRoi, desRoi.size());
	}
	CDC* pDC = GetDlgItem(ID)->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);	// ��ȡ�ؼ��ߴ�λ��
	CvvImage image;
	IplImage cpy = desRoi;  //desRoi �����ź��ͼƬ��des��û����Ӧ�ؼ���ͼƬ
	image.CopyOf(&cpy);						// ����ͼƬ
	image.DrawToHDC(hDC, &rect);				// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC(pDC);/**/
}
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVihecleRecognitionVS2013Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVihecleRecognitionVS2013Dlg::ShowFrameCount(int nFrame, int frameCount, UINT ID)
{
	CString tempStr;
	tempStr.Format(_T("%d/%d"), nFrame, frameCount);
	GetDlgItem(ID)->SetWindowText(tempStr);
}

void CVihecleRecognitionVS2013Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡ�ļ�·������ʾ���༭����  
	TCHAR filePath[MAX_PATH] = { 0 };
	//���ļ��������ڶ�������0�����������������ļ�·��                             
	DragQueryFile(hDropInfo, 0, filePath, MAX_PATH - 1);
	m_strFilePathName = filePath;

	m_fileName = m_strFilePathName.Mid(m_strFilePathName.ReverseFind('\\') + 1, ((m_strFilePathName.ReverseFind('.') - m_strFilePathName.ReverseFind('\\')) - 1));//��CString ��Ա��������ȡ��  
	CString fileType = m_strFilePathName.Right(m_strFilePathName.GetLength() - m_strFilePathName.ReverseFind('.') - 1); //��ȡ���ļ��ĺ�׺��jpg��ʽ����rar��ʽ�ȣ�
	char* pFilePathName = new char[2048];
	Common::TcharToChar(filePath, pFilePathName);

	if (fileType == _T("jpg") || fileType == _T("png") || fileType == _T("bmp"))
	{
		m_image = imread(pFilePathName, 1);
		ShowImage(m_image, IDC_PicSrc);

		if (m_image.channels() == 3)
		{
			cvtColor(m_image, m_imageGray, CV_BGR2GRAY);  //cannyֻ����Ҷ�ͼ
		}
		else
		{
			m_imageGray = m_image.clone();
		}

		mImageHeight = m_image.rows;
		mImageWidth = m_image.cols;

		m_fileName;
		CString fileName = m_fileName + _T(".") + fileType;
		SetWindowText(fileName);
	}
	else if (fileType == _T("avi"))
	{
		m_capture.open(pFilePathName);
		if (m_capture.isOpened())
		{
			m_capture.read(m_image);	
			ShowImage(m_image, IDC_PicSrc);

			mImageHeight = m_image.rows;
			mImageWidth = m_image.cols;

			m_nChannels = m_image.channels();

			m_frameCount = m_capture.get(CV_CAP_PROP_FRAME_COUNT);
			m_nFrames = 1;
			ShowFrameCount(m_nFrames, m_frameCount, IDC_StaFrameCount);
		}
		else
		{
			MessageBox(_T("Failed to Open"));
		}

	}
	else
	{
		MessageBox(_T("����ͼƬ��avi��Ƶ�ļ�"));
	}
	//////////////////////////////////////////////////////////////

	DragFinish(hDropInfo);

	delete[] pFilePathName;

	CDialogEx::OnDropFiles(hDropInfo);
}


void CVihecleRecognitionVS2013Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	if (m_capture.isOpened())
	{
		m_capture.release();
	}
}

void CVihecleRecognitionVS2013Dlg::OnBnClickedBtnopen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_capture.open(1);
	if (!m_capture.isOpened())
	{
		m_capture.open(0);
		if (!m_capture.isOpened())
		{
			MessageBox(_T("Failed to Open"));
			return;
		}
		else
		{
			m_capture.read(m_image);
			ShowImage(m_image, IDC_PicSrc);

			mImageHeight = m_image.rows;
			mImageWidth = m_image.cols;

			m_nChannels = m_image.channels();

			m_nFrames = 1;
			ShowFrameCount(m_nFrames, m_frameCount, IDC_StaFrameCount);

			GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("��ͣ"));
			SetTimer(1, 40, NULL);
		}
	}
}


void CVihecleRecognitionVS2013Dlg::OnBnClickedBtnplay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tempStr;
	GetDlgItem(IDC_BtnPlay)->GetWindowText(tempStr);
	if (tempStr == _T("����"))
	{
		GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("��ͣ"));
		SetTimer(1, 40, NULL);
	}
	else
	{
		GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("����"));
		KillTimer(1);
	}
}


void CVihecleRecognitionVS2013Dlg::OnBnClickedBtnnext()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("����"));
	if (m_capture.isOpened())
	{
		if (m_capture.read(m_image))
		{
			ShowImage(m_image, IDC_PicSrc);
			m_nFrames++;
			ShowFrameCount(m_nFrames, m_frameCount, IDC_StaFrameCount);
		}
		else
		{
			MessageBox(_T("Failed to Read"));
		}
	}

}


void CVihecleRecognitionVS2013Dlg::OnBnClickedBtnbefo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("����"));
	if (m_capture.isOpened())
	{
		int posFrames = m_nFrames - 2;
		if (posFrames < 0) return;
		m_capture.set(CAP_PROP_POS_FRAMES, posFrames);
		if (m_capture.read(m_image))
		{
			m_nFrames--;
			ShowImage(m_image, IDC_PicSrc);
			ShowFrameCount(m_nFrames, m_frameCount, IDC_StaFrameCount);
		}
		else
		{
			MessageBox(_T("Failed to Read"));
		}
	}
}

void CVihecleRecognitionVS2013Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_capture.isOpened())
	{
		if (m_capture.read(m_image))
		{
			ShowImage(m_image, IDC_PicSrc);
			m_nFrames++;
			ShowFrameCount(m_nFrames, m_frameCount, IDC_StaFrameCount);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
