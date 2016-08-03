
// VihecleRecognitionVS2013Dlg.h : 头文件
//
#pragma once
#include <string>
#include <vector>
using namespace std;

#include "common.h"
#include "CvvImage.h"
#include "opencv2\opencv.hpp"
#include "afxwin.h"
using namespace cv;

#include "MyTDMap.h"
#include "MyLine.h"
#include "MyHistorgramAnalyse.h"
#include "MyMath.h"

struct CTimeRecord
{
	int timeClock;
	CString timeComment;
};

struct CDynamicPlan
{
	int data;
	int start;
	int end;
};
class CYInvProPlane
{
public://单位为米（M）
	float m_yCoord;
	float m_xLeftCoord;
	float m_xRightCoord;
	float m_zBottomCood;
	float m_zTopCoord;
	bool isRightDirecton;//右为正方向
	bool isok;
	bool bInverseSheet;
public:
	CYInvProPlane()
	{
		isok = false;
		isRightDirecton = true;
		bInverseSheet = false;
	}
};

// CVehicleRecognitionVS2013Dlg 对话框
class CVehicleRecognitionVS2013Dlg : public CDialogEx
{
	struct Coord2D
	{
		int y;
		int x;
	};
	struct CTrajectory
	{
		vector<Point2f> pointList;
		int markFlag;
	};
	const int VehicleState_Wait = 0;
	const int VehicleState_Come = 1;
	const int VehicleState_Pass = 2;
	const int VehicleState_Leave = 3;
public:
	void ShowImage(Mat& src, UINT ID);
	void ShowFrameCount(int nFrame, int frameCount, UINT ID);
	void Show3DCoordText(Mat& src, CPoint imgPnt, CTDMap mTDMap);
	void InitParam();
	Mat ImageMergeCols(Mat img1, Mat img2);
	void CalculateYInvProPlane(Mat& src, CTDMap mTDMap, CPoint imgPnt, CYInvProPlane *yInvProPlane);
	Mat GetInvProPlane(Mat& src, CTDMap mTDMap, CYInvProPlane *yInvProPlane);
	void FindViewParallelLine(cv::Mat image, float votingRate, vector<CLine> &parallelLine);
	void Tracking(Mat imageGray, Mat prevGray, vector<CTrajectory> &trajectories, int *vehicleState);
	void VehicleMontage(Mat& image, vector<CTrajectory>& trajectories, int vehicleSate, Mat& vehicle);
	void DrawLKMatch(Mat imgMerge, vector<CTrajectory> trajectories);
	void DrawTrackLine(Mat imgMerge, vector<CTrajectory> trajectories);
	void StatisticLKDistance(vector<CTrajectory> trajectories,CMyHistorgram *historgram);
	void StatisticTrajectoriesLength(vector<CTrajectory> trajectories, CMyHistorgram *historgram);
	void StatisticTrajectoriesDistance(vector<CTrajectory> trajectories, CMyHistorgram *historgram);
	void RecordTime(vector<CTimeRecord> &timeRecordList, CString timeComment);
	void ShowTimeRecord(vector<CTimeRecord> timeRecordList, CString edtStrMember);
public:
	CString m_strFilePathName;
	CString m_fileName;//文件名，不带格式后缀

	cv::Mat m_image;
	cv::Mat m_imageGray;
	cv::Mat m_prevImage;
	cv::Mat m_prevGray;
	cv::Mat m_imageEdge;
	cv::Mat m_imageMerge;
	cv::Mat m_prevInverse;
	cv::Mat m_imageInverse;
	cv::Mat m_inverseColor;
	cv::Mat m_prevInverseColor;
	cv::Mat m_vehicleImage;
	bool m_bMontage;
	VideoCapture m_capture;
	int m_nChannels;
	int m_nFrames;
	int m_frameCount;

	CTDMap m_TDMap;
	CYInvProPlane m_yInvProPlane;
	vector<CLine> m_parallelLine;

	vector<CTrajectory> m_trajectories;
	int m_vehicleState;//0-wait 1-come 2-pass 3-leave

	CMyHistorgram m_historgram;
	vector<CTimeRecord> m_timeRecordList;
// 构造
public:
	CVehicleRecognitionVS2013Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VIHECLERECOGNITIONVS2013_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnopen();
	afx_msg void OnBnClickedBtnplay();
	afx_msg void OnBnClickedBtnnext();
	afx_msg void OnBnClickedBtnbefo();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox m_comboShow;
	afx_msg void OnCbnSelchangeComboshow();
	afx_msg void OnBnClickedBtnloadcameracalib();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL m_chkInverseProjection;
	afx_msg void OnBnClickedCheckinverseprojection();
	afx_msg void OnBnClickedBtnsaveimage();
	CString m_edtTimeRecord;
	BOOL m_chkShowTrack;
	afx_msg void OnBnClickedChkshowtrack();
	CComboBox m_comboHistrogram;
	afx_msg void OnCbnSelchangeCombohistorgram();
};
