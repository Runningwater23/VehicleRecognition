
// VihecleRecognitionVS2013Dlg.h : 头文件
//
#pragma once

#include "common.h"
#include "CvvImage.h"
#include "opencv2\opencv.hpp"
using namespace cv;
// CVihecleRecognitionVS2013Dlg 对话框
class CVihecleRecognitionVS2013Dlg : public CDialogEx
{
public:
	void ShowImage(Mat& src, UINT ID);
	void ShowFrameCount(int nFrame, int frameCount, UINT ID);
public:
	CString m_strFilePathName;
	CString m_fileName;//文件名，不带格式后缀

	cv::Mat m_image;
	cv::Mat m_imageGray;
	int mImageHeight;
	int mImageWidth;
	VideoCapture m_capture;
	int m_nChannels;
	int m_nFrames;
	int m_frameCount;
// 构造
public:
	CVihecleRecognitionVS2013Dlg(CWnd* pParent = NULL);	// 标准构造函数

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
};
