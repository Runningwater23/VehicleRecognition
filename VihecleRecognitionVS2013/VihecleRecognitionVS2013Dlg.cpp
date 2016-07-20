
// VihecleRecognitionVS2013Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VihecleRecognitionVS2013.h"
#include "VihecleRecognitionVS2013Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CVihecleRecognitionVS2013Dlg 对话框



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


// CVihecleRecognitionVS2013Dlg 消息处理程序

BOOL CVihecleRecognitionVS2013Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVihecleRecognitionVS2013Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//////////////////////////////
/*
输入：IplImage *img //要显示的图像
输入：int id //显示图像的控件的id号
*/
//////////////////////////////
void CVihecleRecognitionVS2013Dlg::ShowImage(Mat& src, UINT ID)
{
	Mat dest = src.clone();
	if (src.empty())
	{
		AfxMessageBox(_T("没有获取图像"));
		return;
	}
	dest = cv::Scalar::all(0);
	// 计算将图片缩放到 Image 区域所需的比例因子
	double wRatio = dest.cols / (double)src.cols;
	double hRatio = dest.rows / (double)src.rows;
	double srcWH = src.cols / (double)src.rows;
	double desWH = dest.cols / (double)dest.rows;
	double scale = srcWH > desWH ? wRatio : hRatio;

	// 缩放后图片的宽和高
	int nw = (int)(src.cols * scale);
	int nh = (int)(src.rows * scale);

	// 为了将缩放后的图片存入 des 的正中部位，需计算图片在 des 左上角的期望坐标值
	int tlx = (int)((dest.cols - nw) / 2);
	int tly = (int)((dest.rows - nh) / 2);

	// 设置 des 的 ROI 区域，用来存入图片 img
	cv::Mat desRoi = dest(cv::Rect(tlx, tly, nw, nh));

	// 如果src是单通道图像，则转换为三通道图像
	if (src.channels() == 1)
	{
		cv::Mat src_c;
		cvtColor(src, src_c, CV_GRAY2BGR);
		// 对图片 src_t 进行缩放，并存入到 des 中
		resize(src_c, desRoi, desRoi.size());
	}
	else
	{
		// 对图片 src 进行缩放，并存入到 des 中
		resize(src, desRoi, desRoi.size());
	}
	CDC* pDC = GetDlgItem(ID)->GetDC();		// 获得显示控件的 DC
	HDC hDC = pDC->GetSafeHdc();				// 获取 HDC(设备句柄) 来进行绘图操作
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);	// 获取控件尺寸位置
	CvvImage image;
	IplImage cpy = desRoi;  //desRoi 是缩放后的图片，des是没有适应控件的图片
	image.CopyOf(&cpy);						// 复制图片
	image.DrawToHDC(hDC, &rect);				// 将图片绘制到显示控件的指定区域内
	ReleaseDC(pDC);/**/
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//获取文件路径并显示到编辑框中  
	TCHAR filePath[MAX_PATH] = { 0 };
	//单文件操作，第二参数置0，第三个参数返回文件路径                             
	DragQueryFile(hDropInfo, 0, filePath, MAX_PATH - 1);
	m_strFilePathName = filePath;

	m_fileName = m_strFilePathName.Mid(m_strFilePathName.ReverseFind('\\') + 1, ((m_strFilePathName.ReverseFind('.') - m_strFilePathName.ReverseFind('\\')) - 1));//用CString 成员函数来获取。  
	CString fileType = m_strFilePathName.Right(m_strFilePathName.GetLength() - m_strFilePathName.ReverseFind('.') - 1); //截取到文件的后缀（jpg格式或者rar格式等）
	char* pFilePathName = new char[2048];
	Common::TcharToChar(filePath, pFilePathName);

	if (fileType == _T("jpg") || fileType == _T("png") || fileType == _T("bmp"))
	{
		m_image = imread(pFilePathName, 1);
		ShowImage(m_image, IDC_PicSrc);

		if (m_image.channels() == 3)
		{
			cvtColor(m_image, m_imageGray, CV_BGR2GRAY);  //canny只处理灰度图
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
		MessageBox(_T("拖入图片或avi视频文件"));
	}
	//////////////////////////////////////////////////////////////

	DragFinish(hDropInfo);

	delete[] pFilePathName;

	CDialogEx::OnDropFiles(hDropInfo);
}


void CVihecleRecognitionVS2013Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	if (m_capture.isOpened())
	{
		m_capture.release();
	}
}

void CVihecleRecognitionVS2013Dlg::OnBnClickedBtnopen()
{
	// TODO:  在此添加控件通知处理程序代码
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

			GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("暂停"));
			SetTimer(1, 40, NULL);
		}
	}
}


void CVihecleRecognitionVS2013Dlg::OnBnClickedBtnplay()
{
	// TODO:  在此添加控件通知处理程序代码
	CString tempStr;
	GetDlgItem(IDC_BtnPlay)->GetWindowText(tempStr);
	if (tempStr == _T("播放"))
	{
		GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("暂停"));
		SetTimer(1, 40, NULL);
	}
	else
	{
		GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("播放"));
		KillTimer(1);
	}
}


void CVihecleRecognitionVS2013Dlg::OnBnClickedBtnnext()
{
	// TODO:  在此添加控件通知处理程序代码
	KillTimer(1);
	GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("播放"));
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
	// TODO:  在此添加控件通知处理程序代码
	KillTimer(1);
	GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("播放"));
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
