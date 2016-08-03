
// VihecleRecognitionVS2013Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VehicleRecognitionVS2013.h"
#include "VehicleRecognitionVS2013Dlg.h"
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


// CVehicleRecognitionVS2013Dlg �Ի���



CVehicleRecognitionVS2013Dlg::CVehicleRecognitionVS2013Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVehicleRecognitionVS2013Dlg::IDD, pParent)
	, m_chkInverseProjection(FALSE)
	, m_edtTimeRecord(_T(""))
	, m_chkShowTrack(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_vehicleState = VehicleState_Wait;
	m_bMontage = false;
}

void CVehicleRecognitionVS2013Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ComboShow, m_comboShow);
	//  DDX_Control(pDX, IDC_ComboInversProjection, m_comboInverseProject);
	DDX_Check(pDX, IDC_CheckInverseProjection, m_chkInverseProjection);
	DDX_Text(pDX, IDC_EdtInfoShow, m_edtTimeRecord);
	DDX_Check(pDX, IDC_ChkShowTrack, m_chkShowTrack);
	DDX_Control(pDX, IDC_ComboHistorgram, m_comboHistrogram);
}

BEGIN_MESSAGE_MAP(CVehicleRecognitionVS2013Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnOpen, &CVehicleRecognitionVS2013Dlg::OnBnClickedBtnopen)
	ON_BN_CLICKED(IDC_BtnPlay, &CVehicleRecognitionVS2013Dlg::OnBnClickedBtnplay)
	ON_BN_CLICKED(IDC_BtnNext, &CVehicleRecognitionVS2013Dlg::OnBnClickedBtnnext)
	ON_BN_CLICKED(IDC_BtnBefo, &CVehicleRecognitionVS2013Dlg::OnBnClickedBtnbefo)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_ComboShow, &CVehicleRecognitionVS2013Dlg::OnCbnSelchangeComboshow)
	ON_BN_CLICKED(IDC_BtnLoadCameraCalib, &CVehicleRecognitionVS2013Dlg::OnBnClickedBtnloadcameracalib)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CheckInverseProjection, &CVehicleRecognitionVS2013Dlg::OnBnClickedCheckinverseprojection)
	ON_BN_CLICKED(IDC_BtnSaveImage, &CVehicleRecognitionVS2013Dlg::OnBnClickedBtnsaveimage)
	ON_BN_CLICKED(IDC_ChkShowTrack, &CVehicleRecognitionVS2013Dlg::OnBnClickedChkshowtrack)
	ON_CBN_SELCHANGE(IDC_ComboHistorgram, &CVehicleRecognitionVS2013Dlg::OnCbnSelchangeCombohistorgram)
END_MESSAGE_MAP()


// CVehicleRecognitionVS2013Dlg ��Ϣ�������

BOOL CVehicleRecognitionVS2013Dlg::OnInitDialog()
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
	m_comboShow.AddString(_T("ԭͼ��"));
	m_comboShow.AddString(_T("�Ҷ�ͼ"));
	m_comboShow.AddString(_T("��Եͼ"));
	m_comboShow.SetCurSel(0);

	m_comboHistrogram.AddString(_T(""));
	m_comboHistrogram.AddString(_T("�켣λ��ͳ��ͼ"));
	m_comboHistrogram.AddString(_T("�켣����ͳ��ͼ"));
	m_comboHistrogram.AddString(_T("�켣λ�Ʒֲ�ͼ"));
	m_comboHistrogram.SetCurSel(1);

	m_historgram.Create(IDC_PicForDebug, this);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVehicleRecognitionVS2013Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVehicleRecognitionVS2013Dlg::OnPaint()
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
void CVehicleRecognitionVS2013Dlg::ShowImage(Mat& src, UINT ID)
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
HCURSOR CVehicleRecognitionVS2013Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVehicleRecognitionVS2013Dlg::ShowFrameCount(int nFrame, int frameCount, UINT ID)
{
	CString tempStr;
	tempStr.Format(_T("%d/%d"), nFrame, frameCount);
	GetDlgItem(ID)->SetWindowText(tempStr);
}
void CVehicleRecognitionVS2013Dlg::InitParam()
{
	if (!m_prevImage.empty()) m_prevImage.release();
	if (!m_prevInverseColor.empty()) m_prevInverseColor.release();
	if (!m_prevInverse.empty()) m_prevInverse.release();
}
void CVehicleRecognitionVS2013Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	InitParam();
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

			if (!m_imageGray.empty()) m_imageGray.release();
			m_imageGray.create(Size(m_image.cols, m_image.rows), CV_8UC1);
			if (!m_imageEdge.empty()) m_imageEdge.release();
			m_imageEdge.create(Size(m_image.cols, m_image.rows), CV_8UC1);

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


void CVehicleRecognitionVS2013Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	if (m_capture.isOpened())
	{
		m_capture.release();
	}
}

void CVehicleRecognitionVS2013Dlg::OnBnClickedBtnopen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	InitParam();
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

			if (!m_imageGray.empty()) m_imageGray.release();
			m_imageGray.create(Size(m_image.cols, m_image.rows), CV_8UC1);
			if (!m_imageEdge.empty()) m_imageEdge.release();
			m_imageEdge.create(Size(m_image.cols, m_image.rows), CV_8UC1);

			m_nChannels = m_image.channels();

			m_nFrames = 1;
			ShowFrameCount(m_nFrames, m_frameCount, IDC_StaFrameCount);

			GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("��ͣ"));
			SetTimer(1, 40, NULL);
		}
	}
}


void CVehicleRecognitionVS2013Dlg::OnBnClickedBtnplay()
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


void CVehicleRecognitionVS2013Dlg::OnBnClickedBtnnext()
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

void CVehicleRecognitionVS2013Dlg::OnBnClickedBtnbefo()
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
Mat CVehicleRecognitionVS2013Dlg::ImageMergeCols(Mat img1, Mat img2)
{
	Mat img_merge(img1.rows, img1.cols +img2.cols, img1.type());
	Mat subMat = img_merge.colRange(0, img1.cols);
	img1.copyTo(subMat);
	subMat = img_merge.colRange(img1.cols, img1.cols + img2.cols);
	img2.copyTo(subMat);
	return img_merge;
}
void CVehicleRecognitionVS2013Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_timeRecordList.clear();
	if (m_capture.isOpened())
	{
		if (m_capture.read(m_image))
		{
			//cvtColor(m_image, m_imageGray, CV_BGR2GRAY);
			//RecordTime(m_timeRecordList, _T("��ɫͼ�ҶȻ�"));
			ShowImage(m_image, IDC_PicSrc);
			m_nFrames++;
			ShowFrameCount(m_nFrames, m_frameCount, IDC_StaFrameCount);
				
			RecordTime(m_timeRecordList, _T("timeStart"));
			if (m_yInvProPlane.isok&&m_TDMap.isok)
			{
				m_inverseColor = GetInvProPlane(m_image, m_TDMap, &m_yInvProPlane);
				RecordTime(m_timeRecordList, _T("��ɫͼ��ͶӰ"));
				if (m_prevInverseColor.empty()) m_prevInverseColor = m_inverseColor.clone();

				if (m_imageInverse.empty()) m_imageInverse.create(Size(m_inverseColor.cols, m_inverseColor.rows), CV_8UC1);
				cvtColor(m_inverseColor, m_imageInverse, CV_BGR2GRAY);	
				//m_imageInverse = GetInvProPlane(m_imageGray, m_TDMap, m_yInvProPlane);
				RecordTime(m_timeRecordList, _T("��ͶӰ�ҶȻ�"));
				if (m_prevInverse.empty()) m_prevInverse = m_imageInverse.clone();	
				//m_imageMerge = ImageMergeCols(m_prevInverse, m_imageInverse);
				m_imageMerge = ImageMergeCols(m_prevInverseColor, m_inverseColor);	
				RecordTime(m_timeRecordList, _T("��ɫͼ�ϲ�"));
			
				Tracking(m_imageInverse, m_prevInverse,  m_trajectories, &m_vehicleState);
				RecordTime(m_timeRecordList, _T("����������"));

				VehicleMontage(m_inverseColor, m_trajectories, m_vehicleState, m_vehicleImage);
                RecordTime(m_timeRecordList, _T("����ƴ��"));

				if (m_chkShowTrack)
				{
					DrawTrackLine(m_imageMerge, m_trajectories);
					RecordTime(m_timeRecordList, _T("��ʾ�켣��"));
				}
				else
				{
					DrawLKMatch(m_imageMerge, m_trajectories);
					RecordTime(m_timeRecordList, _T("��ʾƥ����"));
				}
				switch (m_comboHistrogram.GetCurSel())
				{
				case 1:	StatisticLKDistance(m_trajectories, &m_historgram);
					RecordTime(m_timeRecordList, _T("λ��ͳ��ͼ")); break;
				case 2: StatisticTrajectoriesLength(m_trajectories, &m_historgram);
					RecordTime(m_timeRecordList, _T("����ͳ��ͼ")); break;
				case 3: StatisticTrajectoriesDistance(m_trajectories, &m_historgram);
					RecordTime(m_timeRecordList, _T("λ�Ʒֲ�ͼ")); break;
				default:
					break;
				}

				cv::swap(m_prevInverse, m_imageInverse);
				cv::swap(m_prevInverseColor, m_inverseColor);
				RecordTime(m_timeRecordList, _T("ͼ�񽻻�"));
				
				ShowImage(m_imageMerge, IDC_PicDest);
			}
			else
			{
				if (m_prevImage.empty()) m_prevImage = m_image.clone();		
				m_imageMerge = ImageMergeCols(m_prevImage, m_image);
				
				RecordTime(m_timeRecordList, _T("��ɫͼ�ϲ�"));
				cv::swap(m_image, m_prevImage);
				RecordTime(m_timeRecordList, _T("ͼ�񽻻�"));

				ShowImage(m_imageMerge, IDC_PicDest);
			}
			
		}
	}
	////////////��ʾʱ���¼
	ShowTimeRecord(m_timeRecordList, m_edtTimeRecord);

	CDialogEx::OnTimer(nIDEvent);
}
void CVehicleRecognitionVS2013Dlg::ShowTimeRecord(vector<CTimeRecord> timeRecordList, CString edtStrMember)
{
	UpdateData(TRUE);
	if (timeRecordList.size() > 1)
	{
		char chTime[10];
		m_edtTimeRecord = _T("");
		for (int i = 1; i < timeRecordList.size(); i++)
		{
			m_edtTimeRecord += timeRecordList[i].timeComment + _T(":");
			sprintf_s(chTime, "%dms", (timeRecordList[i].timeClock - timeRecordList[i - 1].timeClock));
			m_edtTimeRecord += chTime;
			m_edtTimeRecord += _T("\r\n");
		}
		m_edtTimeRecord += _T("��ʱ�䣺");
		int index = timeRecordList.size() - 1;
		sprintf_s(chTime, "%dms", timeRecordList[index].timeClock - timeRecordList[0].timeClock);
		m_edtTimeRecord += chTime;
	}
	UpdateData(FALSE);
}
void CVehicleRecognitionVS2013Dlg::RecordTime(vector<CTimeRecord> &timeRecordList, CString timeComment)
{
	static CTimeRecord tempTimeRecord;
	tempTimeRecord.timeClock = clock();
	tempTimeRecord.timeComment = timeComment;
	timeRecordList.push_back(tempTimeRecord);
}
void CVehicleRecognitionVS2013Dlg::DrawTrackLine(Mat imgMerge, vector<CTrajectory> trajectories)
{
	int cols = imgMerge.cols / 2;
	int k;
	for (int i = 0; i < trajectories.size(); i++)
	{
		for (k = 1; k < trajectories[i].pointList.size(); k++)
		{
			Point2f pt1 = trajectories[i].pointList[k];
			Point2f pt2 = trajectories[i].pointList[k - 1];
			line(imgMerge, Point(pt1.x + cols, pt1.y), Point(pt2.x + cols, pt2.y), Scalar(255, 0, 255), 1);
		}	
		Point2f pt = trajectories[i].pointList[k - 1];
		circle(imgMerge, Point(pt.x + cols, pt.y), 1, Scalar(0, 0, 255), 2);
	}
}
void CVehicleRecognitionVS2013Dlg::DrawLKMatch(Mat imgMerge, vector<CTrajectory> trajectories)
{
	int cols = imgMerge.cols / 2;
	int colorCount = 1;
	int r, g, b;
	for (int i = 0; i < trajectories.size(); i++)
	{
		if (trajectories[i].pointList.size()>1)
		{
			int index1 = trajectories[i].pointList.size() - 1;
			int index2 = trajectories[i].pointList.size() - 2;
			Point2f pt1 = trajectories[i].pointList[index1];
			Point2f pt2 = trajectories[i].pointList[index2];
			r = colorCount % 2;
			g = (colorCount >> 1) % 2;;
			b = (colorCount >> 2) % 2;
			colorCount++;
			line(imgMerge, Point(pt1.x + cols, pt1.y), Point(pt2.x, pt2.y), Scalar(b*255, g*255, r*255), 1);
		}
	}
}
void CVehicleRecognitionVS2013Dlg::StatisticLKDistance(vector<CTrajectory> trajectories, CMyHistorgram *historgram)
{
	vector<CPoint> pointList;
	int disCount[100];
	memset(disCount, 0, sizeof(int)* 100);
	for (int i = 0; i < trajectories.size(); i++)
	{
		if (trajectories[i].pointList.size()>10)
		{
			int index1 = trajectories[i].pointList.size() - 1;
			int index2 = trajectories[i].pointList.size() - 2;
			Point2f pt1 = trajectories[i].pointList[index1];
			Point2f pt2 = trajectories[i].pointList[index2];

			int dis = pt1.x - pt2.x;
			if (dis > 0&&dis<100)
			{
				disCount[dis]++;
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		CPoint tempPoint;
		tempPoint.x = i;
		tempPoint.y = disCount[i];
		pointList.push_back(tempPoint);
	}
	historgram->m_pointList = pointList;
	historgram->SetLimit(0, 30, 0, 50);
	historgram->m_bShowEXDX = true;
	historgram->RenderScene();
}
void CVehicleRecognitionVS2013Dlg::StatisticTrajectoriesLength(vector<CTrajectory> trajectories, CMyHistorgram *historgram)
{
	vector<CPoint> pointList;
	int lenCount[100];
	memset(lenCount, 0, sizeof(int)* 100);
	for (int i = 0; i < trajectories.size(); i++)
	{
		lenCount[trajectories[i].pointList.size()]++;
	}
	for (int i = 0; i < 100; i++)
	{
		CPoint tempPoint;
		tempPoint.x = i;
		tempPoint.y = lenCount[i];
		pointList.push_back(tempPoint);
	}
	historgram->m_pointList = pointList;
	historgram->SetLimit(0, 100, 0, 50);
	historgram->m_bShowEXDX = true;
	historgram->RenderScene();
}
void CVehicleRecognitionVS2013Dlg::StatisticTrajectoriesDistance(vector<CTrajectory> trajectories, CMyHistorgram *historgram)
{
	vector<CPoint> pointList;
	int index, tempDistance;
	int maxDistance = 0;
	for (int i = 0; i < trajectories.size(); i++)
	{
		if (trajectories[i].pointList.size()>1)
		{
			index = trajectories[i].pointList.size() - 1;
			tempDistance = trajectories[i].pointList[index].x - trajectories[i].pointList[0].x;
			pointList.push_back(CPoint(i, tempDistance));

			if (maxDistance < tempDistance) maxDistance = tempDistance;
		}
	}
	historgram->m_pointList = pointList;
	historgram->SetLimit(0, 200, 0, 300);
	historgram->m_bShowEXDX = false;
	historgram->RenderScene();
}
void CVehicleRecognitionVS2013Dlg::Tracking(Mat imageGray, Mat prevGray, vector<CTrajectory> &trajectories, int *vehicleState)
{
	static int MAX_COUNT = 500;
	static TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	static Size subPixWinSize(10, 10), winSize(31, 31);
	static vector<Point2f> points[2];
	static CTrajectory tempTrajectory;
	static int ROICols = imageGray.cols / 4;
	static int newPointCount = 0;
	static int movePointCount = 0;
	static int stopPointCount = 0;
	static Mat surveyROI;
	static Mat survPrevROI;
	if (surveyROI.empty()) surveyROI.create(Size(imageGray.cols / 4, imageGray.rows / 4), imageGray.type());
	if (survPrevROI.empty()) survPrevROI.create(Size(imageGray.cols / 4, imageGray.rows / 4), imageGray.type());

	if (!trajectories.size())
	{
		Mat imgROI;
		cv::Rect rect(0, 0, ROICols, imageGray.rows);
		imageGray(rect).copyTo(imgROI);
		vector<Point2f> tempPoints;
		goodFeaturesToTrack(imgROI, tempPoints, MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
		cornerSubPix(imgROI, tempPoints, subPixWinSize, Size(-1, -1), termcrit);
		newPointCount = tempPoints.size();

		tempTrajectory.markFlag = 0;
		for (int i = 0; i < tempPoints.size(); i++)
		{
			points[1].push_back(tempPoints[i]);
			tempTrajectory.pointList.clear();
			tempTrajectory.pointList.push_back(tempPoints[i]);
			trajectories.push_back(tempTrajectory);

			circle(m_imageMerge, Point(tempPoints[i].x + imageGray.cols, tempPoints[i].y), 2, Scalar(0, 0, 0), 2);
		}
	}
	else
	{
		vector<uchar> status;
		vector<float> err;
		if (prevGray.empty()) imageGray.copyTo(prevGray);
		calcOpticalFlowPyrLK(prevGray, imageGray, points[0], points[1], status, err, winSize, 3, termcrit, 0, 0.001);
		int i, k;
		int leftPos = imageGray.cols;//
		movePointCount = 0;
		stopPointCount = 0;
		for (i = 0, k = 0; i < points[1].size(); i++)
		{
			if (!status[i])
				continue;
			Point2f pt1 = points[0][i];
			Point2f pt2 = points[1][i];
			if (abs(pt1.y - pt2.y) < 5 )
			{
				if (abs(pt1.x - pt2.x) > 1)//�к����ƶ��ĵ�
				{
					points[1][k] = points[1][i];
					trajectories[k] = trajectories[i];
					trajectories[k].pointList.push_back(points[1][i]);
					k++;
					/////////////
					if (points[1][i].x < leftPos)
					{
						leftPos = points[1][i].x;
					}
					/////////////
					if (newPointCount)
					{
						if (pt1.x < ROICols&&pt1.y>imageGray.rows/2) movePointCount++;
					}
				}
				else//������û���ƶ�
				{
					if (newPointCount)
					{
						if (pt1.x < ROICols&&pt1.y>imageGray.rows / 2) stopPointCount++;
					}
				}
			}
		}
		newPointCount = 0;
		points[1].resize(k);
		trajectories.resize(k);
		//////////////////////////////
		//�����Ǵ��������ߵģ��ж�����ж��Χû�и��ٵ�
		if (leftPos > imageGray.cols*0.2)
		{
			Mat imgROI;
			cv::Rect rect(0, 0, ROICols, imageGray.rows);
			imageGray(rect).copyTo(imgROI);
			vector<Point2f> tempPoints;
			goodFeaturesToTrack(imgROI, tempPoints, MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
			cornerSubPix(imgROI, tempPoints, subPixWinSize, Size(-1, -1), termcrit);
			newPointCount = tempPoints.size();
			tempTrajectory.markFlag = 0;
			for (i = 0; i < tempPoints.size(); i++)
			{
				points[1].push_back(tempPoints[i]);
				tempTrajectory.pointList.clear();
				tempTrajectory.pointList.push_back(tempPoints[i]);
				trajectories.push_back(tempTrajectory);

				//circle(m_imageMerge, Point(tempPoints[i].x + imageGray.cols, tempPoints[i].y), 2, Scalar(0, 0, 0), 2);
			}
		}
	}
	///////////////////
	//points[1]��trajectories�ǰ�����,����ͬ���޸�
	//���Ҫɾ��������trajectories��һ���켣
	//points[1]Ҳ��������Ӧ����ɾ��������ͻ����
	//��ˣ����˸ú����ڣ������κεط����ö�trajectories���޸Ĵ���
	//
	static int minTrackLength = 10;
	static float maxError = 5;
	int trackCount = 0;
	for (int i = 0; i < trajectories.size(); i++)
	{
		if (trajectories[i].pointList.size()>minTrackLength)
		{
			float absYError = 0;
			float aveYValue = 0;
			int lowerBound = trajectories[i].pointList.size() - minTrackLength - 1;
			for (int k = trajectories[i].pointList.size() - 1; k > lowerBound; k--)
			{
				aveYValue += trajectories[i].pointList[k].y;
			}
			aveYValue /= minTrackLength;
			for (int k = trajectories[i].pointList.size() - 1; k > lowerBound; k--)
			{
				absYError += abs(trajectories[i].pointList[k].y - aveYValue);
			}
			if (absYError < maxError)
			{
				trajectories[trackCount] = trajectories[i];
				points[1][trackCount] = points[1][i];
				trackCount++;
			}
		}
		else
		{
			trajectories[trackCount] = trajectories[i];
			points[1][trackCount] = points[1][i];
			trackCount++;
		}
	}
	///////////////////
	std::swap(points[0], points[1]);

	char chPointCount[128];
	sprintf_s(chPointCount, "move:%d stop:%d", movePointCount, stopPointCount);
	String tempStr = chPointCount;
	cv::putText(m_imageMerge, tempStr, Point(0, 50), 1, 1.5, Scalar(0, 0, 255),2);

	String stateStr;
	if (movePointCount>10 || stopPointCount>10)
	{
		//vehilcleState = 0-wait 1-come 2-pass 3-leave
		if (*vehicleState == 0 && (1.0*movePointCount / (movePointCount + stopPointCount)) > 0.7)
		{
			*vehicleState = 1;//����
		}
		else if (*vehicleState == 1)
		{
			*vehicleState = 2;//ͨ��
		}
		else if (*vehicleState == 2 && (1.0*stopPointCount / (movePointCount + stopPointCount)) > 0.7)
		{
			*vehicleState = 3;//�뿪
		}
		else if (*vehicleState == 3)
		{
			*vehicleState = 0;
		}
	}
	switch (*vehicleState)
	{
	case 0:stateStr = "wait"; break;
	case 1:stateStr = "come"; break;
	case 2:stateStr = "pass"; break;
	case 3:stateStr = "leave"; break;
	default:stateStr = "unknown"; break;
	}
	cv::putText(m_imageMerge, stateStr, Point(0, 80), 1, 1.5, Scalar(0, 0, 255), 2);
}
void CVehicleRecognitionVS2013Dlg::VehicleMontage(Mat& image, vector<CTrajectory>& trajectories, int vehicleSate, Mat& vehicleImage)
{
	static float moveDistance = 0;
	static float maxDistance = image.cols*0.7;

	if (vehicleSate)
	{
		int index1, index2;
		Point2f pt1, pt2;
		float distance, sumDistance = 0;
		int count = 0;

		for (int i = 0; i < trajectories.size(); i++)
		{
			if (trajectories[i].pointList.size()>1)
			{
				index1 = trajectories[i].pointList.size() - 1;
				index2 = trajectories[i].pointList.size() - 2;
				pt1 = trajectories[i].pointList[index1];
				pt2 = trajectories[i].pointList[index2];

				distance = pt1.x - pt2.x;//�����Ǵ��������ߵ�
				sumDistance += distance;
				count++;
			}
		}
		if (count) moveDistance += (sumDistance / count);
        cv::line(m_imageMerge, Point(image.cols, image.rows - 20), Point(image.cols + moveDistance, image.rows - 20), Scalar(0, 255, 0), 2);
		
		if ((moveDistance > maxDistance) || (moveDistance>image.cols*0.2&&vehicleSate==VehicleState_Leave))
		{
			moveDistance = 0;
			if (vehicleImage.empty())
			{
				vehicleImage = image.clone();
				ShowImage(vehicleImage, IDC_PicResult);
				maxDistance = image.cols*0.5;
			}
			else
			{
				Mat tempImage = vehicleImage.clone();
				vehicleImage.release();

				count = 0;
				float xLeftBorder = 0,xRightBorder = 0;
				for (int i = 0; i < trajectories.size(); i++)
				{
					if (trajectories[i].markFlag)
					{
						xLeftBorder += trajectories[i].pointList[0].x;
						index1 = trajectories[i].pointList.size() - 1;
						xRightBorder += trajectories[i].pointList[index1].x;
						count++;
					}
					else
					{
						break;
					}
				}
				if (count)
				{
					xLeftBorder /= count;
					xRightBorder /= count;
					Mat imgROI1, imgROI2;
					cv::Rect rect1(0, 0, (int)(xRightBorder), image.rows);
					image(rect1).copyTo(imgROI1);
					cv::Rect rect2((int)(xLeftBorder), 0, (int)(tempImage.cols - xLeftBorder - 1), tempImage.rows);
					tempImage(rect2).copyTo(imgROI2);

					vehicleImage = ImageMergeCols(imgROI1, imgROI2);
					ShowImage(vehicleImage, IDC_PicResult);
					KillTimer(1);
					GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("����"));
					if (vehicleSate == VehicleState_Leave)
					{
						vehicleImage.release();
						MessageBox(_T("���"));
					}
				}
				else
				{
					MessageBox(_T("xxx"));
					return;
				}
			}
			for (int i = 0; i < trajectories.size(); i++)
			{
				index1 = trajectories[i].pointList.size() - 1;
				trajectories[i].pointList[0] = trajectories[i].pointList[index1];
				trajectories[i].pointList.resize(1);
				trajectories[i].markFlag = 1;
			}
		}
		else if (vehicleSate == VehicleState_Leave)
		{
			Mat temp = vehicleImage.clone();
			ShowImage(temp, IDC_PicResult);
			MessageBox(_T("���"));
			vehicleImage.release();
			moveDistance = 0;
			maxDistance = image.cols*0.7;

			KillTimer(1);
			GetDlgItem(IDC_BtnPlay)->SetWindowText(_T("����"));
		}
		else if (vehicleSate == VehicleState_Pass)
		{
			if (!vehicleImage.empty())
			{
				Mat tempImage = vehicleImage.clone();
				Mat tempVehicle = ImageMergeCols(image, tempImage);
				for (int i = 0; i < trajectories.size(); i++)
				{
					if (trajectories[i].pointList.size()>1)
					{
						index1 = trajectories[i].pointList.size() - 1;
						pt1 = trajectories[i].pointList[0];
						pt2 = trajectories[i].pointList[index1];
						if (trajectories[i].markFlag)
						cv::line(tempVehicle, Point(pt1.x + image.cols, pt1.y), pt2, Scalar(255, 255, 255), 1);
					}
				}
				ShowImage(tempVehicle, IDC_PicResult);
			}
		}
	}
	else
	{
		moveDistance = 0;
		maxDistance = image.cols*0.7;
	}
}
/*
void CVehicleRecognitionVS2013Dlg::Tracking(Mat imageGray, Mat prevGray, int *validTrackCount, vector<vector<Point2f>> &trajectories)
{
	static int MAX_COUNT = 500;
	static TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	static Size subPixWinSize(10, 10), winSize(31, 31);
	static vector<Point2f> points[2];
	static vector<Point2f> trackLine;
	static int minTrackCount = 20;

	if (*validTrackCount < minTrackCount)
	{
		
		Mat imgROI;
		cv::Rect rect(0, 0, imageGray.cols/3, imageGray.rows);
		imageGray(rect).copyTo(imgROI);
		vector<Point2f> tempPoints;
		goodFeaturesToTrack(imgROI, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
		cornerSubPix(imgROI, points[1], subPixWinSize, Size(-1, -1), termcrit);

		//goodFeaturesToTrack(imageGray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
		//cornerSubPix(imageGray, points[1], subPixWinSize, Size(-1, -1), termcrit);

		trajectories.clear();
		for (int i = 0; i < points[1].size(); i++)
		{
			trackLine.clear();
			trackLine.push_back(points[1][i]);
			trajectories.push_back(trackLine);

			circle(m_imageMerge, Point(points[1][i].x + imageGray.cols, points[1][i].y), 2, Scalar(0, 0, 0), 2);
		}
		*validTrackCount = points[1].size();
	}
	else
	{
		vector<uchar> status;
		vector<float> err;
		if (prevGray.empty()) imageGray.copyTo(prevGray);
		calcOpticalFlowPyrLK(prevGray, imageGray, points[0], points[1], status, err, winSize, 3, termcrit, 0, 0.001);
		int i, k;
		int leftPos = imageGray.cols;//
		for (i = 0, k = 0; i < points[1].size(); i++)
		{
			if (!status[i])
				continue;
			Point2f pt1 = points[0][i];
			Point2f pt2 = points[1][i];
			if (abs(pt1.y - pt2.y) < 5 && abs(pt1.x - pt2.x) > 2)
			{
				points[1][k] = points[1][i];
				trajectories[k] = trajectories[i];
				trajectories[k].push_back(points[1][i]);
				k++;

				/////////////
				if (points[1][i].x < leftPos)
				{
					leftPos = points[1][i].x;
				}
				/////////////
			}
		}
		points[1].resize(k);
		trajectories.resize(k);
		////////////////////////////////////////
		//�����Ǵ��������ߵģ��ж�����ж��Χû�и��ٵ�
		if (leftPos > imageGray.cols*0.2)
		{
			leftPos = imageGray.cols*0.25;
			Mat imgROI;
			cv::Rect rect(0, 0, leftPos, imageGray.rows);
			imageGray(rect).copyTo(imgROI);
			vector<Point2f> tempPoints;
			goodFeaturesToTrack(imgROI, tempPoints, MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
			cornerSubPix(imgROI, tempPoints, subPixWinSize, Size(-1, -1), termcrit);
			for (i = 0; i < tempPoints.size(); i++)
			{
				points[1].push_back(tempPoints[i]);
				trackLine.clear();
				trackLine.push_back(tempPoints[i]);
				trajectories.push_back(trackLine);

				circle(m_imageMerge, Point(tempPoints[i].x + imageGray.cols, tempPoints[i].y), 2, Scalar(0, 0, 0), 2);
			}
		}
		*validTrackCount = points[1].size();
	}
	std::swap(points[0], points[1]);
}
*/

void CVehicleRecognitionVS2013Dlg::OnCbnSelchangeComboshow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (!m_image.empty())
	{
		switch (m_comboShow.GetCurSel())
		{
		case 0:ShowImage(m_image, IDC_PicSrc); break;
		case 1:cvtColor(m_image, m_imageGray, CV_BGR2GRAY);
			   ShowImage(m_imageGray, IDC_PicSrc); break;
		case 2:cvtColor(m_image, m_imageGray, CV_BGR2GRAY);
			   Canny(m_imageGray, m_imageEdge, 30, 50);
			   ShowImage(m_imageEdge, IDC_PicSrc); break;
		default:break;
		}
	}

	UpdateData(FALSE);
}


void CVehicleRecognitionVS2013Dlg::OnBnClickedBtnloadcameracalib()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog pCFileDialog(true, _T("dat"), NULL, 0, _T("TDMap(*.dat)|*.dat"));
	if (pCFileDialog.DoModal() != IDOK)
	{
		return;
	}
	else
	{
		CString strFilePath = pCFileDialog.GetPathName();
		TCHAR tchFileName[1024];

		memcpy(tchFileName, strFilePath, 2 * strFilePath.GetLength());
		tchFileName[2 * strFilePath.GetLength()] = '\0';
		char chFileName[1024];
		Common::TcharToChar(tchFileName, chFileName);
		chFileName[strFilePath.GetLength()] = '\0';

		if (CMyTDMap::ReadTDMapMatrix(chFileName, &m_TDMap))
		{
			m_TDMap.isok = true;
			MessageBox(_T("Read Success"));
		}
	}
}
void CVehicleRecognitionVS2013Dlg::Show3DCoordText(Mat& src, CPoint imgPnt, CTDMap mTDMap)
{
	int imgCoord[2];
	float realCoord[3];
	imgCoord[0] = imgPnt.x; imgCoord[1] = imgPnt.y;
	CMyTDMap::CalculateImgto3D(mTDMap, imgCoord, 0, realCoord);
	char chRealCoord[32];
	sprintf_s(chRealCoord, "(%.2f,%.2f,0)", realCoord[0], realCoord[1]);
	String tempStr = chRealCoord;

	int fontFace = cv::FONT_HERSHEY_COMPLEX;
	double fontScale = 2;
	int fontThickness = 2;

	// get text size
	int textBaseline = 0;
	cv::Size textSize = cv::getTextSize(tempStr, fontFace,
		fontScale, fontThickness, &textBaseline);
	textBaseline += fontThickness;
	// then put the text itself
	putText(src, tempStr, Point(imgPnt.x, imgPnt.y), fontFace, fontScale, Scalar(0, 0, 255), fontThickness, 1);
}

void CVehicleRecognitionVS2013Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(TRUE);
	if (!m_image.empty())
	{
		Mat image = m_image.clone();
		CRect rect;
		GetDlgItem(IDC_PicSrc)->GetWindowRect(rect);
		ClientToScreen(&point);
		CWnd *pWnd = GetDlgItem(IDC_PicSrc);
		CDC* pDC = pWnd->GetDC();

		CPoint imgPnt;
		imgPnt.x = (point.x - rect.left)*m_image.cols / rect.Width();
		imgPnt.y = (point.y - rect.top)*m_image.rows / rect.Height();

		if (m_TDMap.isok)
		{
			Show3DCoordText(image, imgPnt, m_TDMap);
			if (m_chkInverseProjection)
			{
				CalculateYInvProPlane(image, m_TDMap, imgPnt, &m_yInvProPlane);
				m_chkInverseProjection = FALSE;
			}
		}
		ShowImage(image, IDC_PicSrc);
	}
	UpdateData(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CVehicleRecognitionVS2013Dlg::CalculateYInvProPlane(Mat& src, CTDMap mTDMap, CPoint imgPnt, CYInvProPlane *yInvProPlane)
{
	//�涨���ҷ���ΪX��������,��λ�ף�M��
	int imgCoord[2];
	float realCoord[3];
	imgCoord[0] = imgPnt.x;
	imgCoord[1] = imgPnt.y;
	CMyTDMap::CalculateImgto3D(mTDMap, imgCoord, 0, realCoord);
	yInvProPlane->m_yCoord = realCoord[1];
	imgCoord[0] = 0;
	CMyTDMap::CalculateImgto3D(mTDMap, imgCoord, 0, realCoord);
	yInvProPlane->m_xLeftCoord = ((int)((realCoord[0] * 100) / 50) * 50)*0.01;
	imgCoord[0] = src.cols;
	CMyTDMap::CalculateImgto3D(mTDMap, imgCoord, 0, realCoord);
	yInvProPlane->m_xRightCoord = ((int)((realCoord[0] * 100) / 50) * 50)*0.01;
	yInvProPlane->m_zBottomCood = 0;
	yInvProPlane->m_zTopCoord = 3;
	yInvProPlane->isok = true;
	if (yInvProPlane->m_xRightCoord < yInvProPlane->m_xLeftCoord)
	{
		yInvProPlane->isRightDirecton = false;
		float tempVal = yInvProPlane->m_xLeftCoord;
		yInvProPlane->m_xLeftCoord = yInvProPlane->m_xRightCoord;
		yInvProPlane->m_xRightCoord = tempVal;
	}

	int tempImgCoord[2];
	realCoord[0] = yInvProPlane->m_xLeftCoord;
	realCoord[1] = yInvProPlane->m_yCoord;
	realCoord[2] = yInvProPlane->m_zBottomCood;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, imgCoord);
	realCoord[2] = yInvProPlane->m_zTopCoord;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, tempImgCoord);
	line(src, Point(imgCoord[0], imgCoord[1]), Point(tempImgCoord[0], tempImgCoord[1]), Scalar(0, 255, 0), 2);
	realCoord[0] = yInvProPlane->m_xRightCoord;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, imgCoord);
	line(src, Point(imgCoord[0], imgCoord[1]), Point(tempImgCoord[0], tempImgCoord[1]), Scalar(0, 255, 0), 2);
	realCoord[2] = yInvProPlane->m_zBottomCood;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, tempImgCoord);
	line(src, Point(imgCoord[0], imgCoord[1]), Point(tempImgCoord[0], tempImgCoord[1]), Scalar(0, 255, 0), 2);
	realCoord[0] = yInvProPlane->m_xLeftCoord;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, imgCoord);
	line(src, Point(imgCoord[0], imgCoord[1]), Point(tempImgCoord[0], tempImgCoord[1]), Scalar(0, 255, 0), 2);
}
Mat CVehicleRecognitionVS2013Dlg::GetInvProPlane(Mat& src, CTDMap mTDMap, CYInvProPlane *yInvProPlane)
{
	int imgCoord[2];
	float realCoord[3];
	int tempImgCoord[2];
	realCoord[0] = yInvProPlane->m_xLeftCoord;
	realCoord[1] = yInvProPlane->m_yCoord;
	realCoord[2] = yInvProPlane->m_zBottomCood;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, imgCoord);
	realCoord[2] = yInvProPlane->m_zTopCoord;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, tempImgCoord);
	line(src, Point(imgCoord[0], imgCoord[1]), Point(tempImgCoord[0], tempImgCoord[1]), Scalar(0, 255, 0), 2);
	realCoord[0] = yInvProPlane->m_xRightCoord;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, imgCoord);
	line(src, Point(imgCoord[0], imgCoord[1]), Point(tempImgCoord[0], tempImgCoord[1]), Scalar(0, 255, 0), 2);
	realCoord[2] = yInvProPlane->m_zBottomCood;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, tempImgCoord);
	line(src, Point(imgCoord[0], imgCoord[1]), Point(tempImgCoord[0], tempImgCoord[1]), Scalar(0, 255, 0), 2);
	realCoord[0] = yInvProPlane->m_xLeftCoord;//����
	CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, imgCoord);
	line(src, Point(imgCoord[0], imgCoord[1]), Point(tempImgCoord[0], tempImgCoord[1]), Scalar(0, 255, 0), 2);

	int width = (yInvProPlane->m_xRightCoord - yInvProPlane->m_xLeftCoord) * 50;//2����/1����
	int height = (yInvProPlane->m_zTopCoord - yInvProPlane->m_zBottomCood) * 100;//1����/1����

	Mat imgInvers(height, width, src.type());
	realCoord[1] = yInvProPlane->m_yCoord;

	static Coord2D *pSheet;
	static uchar *pData;
	if (yInvProPlane->bInverseSheet == false)
	{
		pSheet = new Coord2D[height*width];
		pData = new uchar[height*width*src.channels()];
		for (int i = 0; i < height; i++)
		{
			int rows = height - i - 1;
			realCoord[2] = i*0.01 + yInvProPlane->m_zBottomCood;
			for (int j = 0; j < width; j++)
			{
				realCoord[0] = j*0.02 + yInvProPlane->m_xLeftCoord;
				CMyTDMap::Calculate3DtoImg(mTDMap, realCoord, imgCoord);
				int cols = yInvProPlane->isRightDirecton == true ? j : (width - 1 - j);
				if (imgCoord[0]>0 && imgCoord[0]<src.cols&&imgCoord[1]>0 && imgCoord[1] < src.rows)
				{
					pSheet[rows*width + cols].x = imgCoord[0];
					pSheet[rows*width + cols].y = imgCoord[1];
				}
				else
				{
					pSheet[rows*width + cols].x = 0;
					pSheet[rows*width + cols].y = 0;
				}
			}
		}
		//delete[] pSheet;
		yInvProPlane->bInverseSheet = true;
	}

	int index, indexSrc;
	int rowsIndex;
	int invRowsIndex, srcRowsIndex;
	uchar *pSrcData = src.data;
	for (int i = 0; i < height; i++)
	{
		rowsIndex = i*width;
		for (int j = 0; j < width; j++)
		{
			index = rowsIndex + j;
			indexSrc = pSheet[index].y * src.cols + pSheet[index].x;

			invRowsIndex = index*imgInvers.channels();
			srcRowsIndex = indexSrc*src.channels();
			for (int k = 0; k < src.channels(); k++)
			{
				//imgInvers.data[invRowsIndex + k] = src.data[srcRowsIndex + k];
				pData[invRowsIndex + k] = pSrcData[srcRowsIndex + k];
			}
		}
	}
	imgInvers.data = pData;
	return imgInvers;
}
void CVehicleRecognitionVS2013Dlg::OnBnClickedCheckinverseprojection()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	UpdateData(FALSE);
}


void CVehicleRecognitionVS2013Dlg::OnBnClickedBtnsaveimage()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!m_image.empty())
	{
		char chFileName[64];
		sprintf_s(chFileName, "%d.jpg", m_nFrames);
		String strFileName = m_fileName + "_" + chFileName;
		imwrite(strFileName, m_image);
	}
}
void CVehicleRecognitionVS2013Dlg::FindViewParallelLine(cv::Mat image, float votingRate, vector<CLine> &parallelLine)
{
	float ratio;
	int tempValue = 0;
	int mIndex;
	CLine tempLine;
	parallelLine.clear();
	CDynamicPlan *pStatus;
	pStatus = new CDynamicPlan[image.cols];
	for (int i = 1; i < image.rows - 2; i++)
	{
		if (image.data[i*image.cols])
		{
			tempValue = 1;
		}
		else
		{
			tempValue = -1;
		}
		pStatus[0].start = 0;
		pStatus[0].end = 0;
		pStatus[0].data = tempValue;
		mIndex = 0;
		for (int j = 1; j < image.cols; j++)
		{
			pStatus[j].start = j;
			pStatus[j].end = j;
			if (image.data[i*image.cols + j])
			{
				pStatus[j].data = 1;
			}
			else if (image.data[(i + 1)*image.cols] || image.data[(i - 1)*image.cols])
			{
				pStatus[j].data = 1;
			}
			else
			{
				pStatus[j].data = -1;
			}

			if (pStatus[j - 1].data >= 0)
			{
				pStatus[j].data += pStatus[j - 1].data;
				pStatus[j].start = pStatus[j - 1].start;
			}
			if (pStatus[j].data > tempValue)
			{
				tempValue = pStatus[j].data;
				mIndex = j;
			}
		}
		tempLine.startpnt.x = pStatus[mIndex].start;
		tempLine.endpnt.x = pStatus[mIndex].end;
		tempLine.startpnt.y = i;
		tempLine.endpnt.y = i;
		parallelLine.push_back(tempLine);
	}
	for (int i = 1; i < parallelLine.size(); i++)
	{
		if (parallelLine[i].startpnt.x>parallelLine[i - 1].endpnt.x&&parallelLine[i].startpnt.x < parallelLine[i - 1].endpnt.x + 2)
		{
			parallelLine[i].startpnt.x = parallelLine[i - 1].startpnt.x;
		}
		else if (parallelLine[i].endpnt.x<parallelLine[i - 1].endpnt.x&&parallelLine[i].endpnt.x>parallelLine[i - 1].startpnt.x - 2)
		{
			parallelLine[i].endpnt.x = parallelLine[i - 1].endpnt.x;
		}
	}
	int length;
	for (int i = 0; i < parallelLine.size(); i++)
	{
		length = parallelLine[i].endpnt.x - parallelLine[i].startpnt.x;
		ratio = 1.0*length / image.cols;
		if (ratio < votingRate)
		{
			parallelLine.erase(parallelLine.begin() + i);
			i--;
		}

	}
	delete[]pStatus;
}

void CVehicleRecognitionVS2013Dlg::OnBnClickedChkshowtrack()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	UpdateData(FALSE);
}


void CVehicleRecognitionVS2013Dlg::OnCbnSelchangeCombohistorgram()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	switch (m_comboHistrogram.GetCurSel())
	{
	case 1:	StatisticLKDistance(m_trajectories, &m_historgram); break;
	case 2: StatisticTrajectoriesLength(m_trajectories, &m_historgram); break;
	case 3: StatisticTrajectoriesDistance(m_trajectories, &m_historgram); break;
	default:break;
	}
	UpdateData(FALSE);
}
