
// VihecleRecognitionVS2013Dlg.h : ͷ�ļ�
//
#pragma once

#include "common.h"
#include "CvvImage.h"
#include "opencv2\opencv.hpp"
using namespace cv;
// CVihecleRecognitionVS2013Dlg �Ի���
class CVihecleRecognitionVS2013Dlg : public CDialogEx
{
public:
	void ShowImage(Mat& src, UINT ID);
	void ShowFrameCount(int nFrame, int frameCount, UINT ID);
public:
	CString m_strFilePathName;
	CString m_fileName;//�ļ�����������ʽ��׺

	cv::Mat m_image;
	cv::Mat m_imageGray;
	int mImageHeight;
	int mImageWidth;
	VideoCapture m_capture;
	int m_nChannels;
	int m_nFrames;
	int m_frameCount;
// ����
public:
	CVihecleRecognitionVS2013Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VIHECLERECOGNITIONVS2013_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
