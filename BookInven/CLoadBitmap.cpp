#include "CLoadBitmap.h"



CLoadBitmap::CLoadBitmap()
{
}


CLoadBitmap::~CLoadBitmap()
{
}

void CLoadBitmap::Load(const int idb_bitmap, const float scale, cv::Mat* out_mat)
{
	CBitmap cbmp;
	cbmp.LoadBitmap(idb_bitmap);
	BITMAP bmap;
	cbmp.GetBitmap(&bmap);

	int Width = bmap.bmWidth;
	int Height = bmap.bmHeight;

	int nChannels = bmap.bmBitsPixel == 1 ? 1 : bmap.bmBitsPixel / 8;
	//int depth = bmap.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	int depth = bmap.bmBitsPixel == 1 ? 1 : 8;

	BYTE *pBuffer = new BYTE[bmap.bmHeight*bmap.bmWidth*nChannels];
	GetBitmapBits((HBITMAP)cbmp.GetSafeHandle(), bmap.bmHeight*bmap.bmWidth*nChannels, pBuffer);

	cv::Mat Channel4Mat(bmap.bmHeight, bmap.bmWidth, CV_MAKETYPE(depth, nChannels));
	memcpy(Channel4Mat.data, pBuffer, bmap.bmHeight*bmap.bmWidth*nChannels);

	//cv::Mat Channel3Mat(bmap.bmHeight, bmap.bmWidth*nChannels, CV_8UC3);
	// convert color  

	if (out_mat != NULL)
	{
		//cvtColor(Channel4Mat, (*out_mat), CV_BGRA2BGR);
		cvtColor(Channel4Mat, (*out_mat), cv::COLOR_BGRA2BGR);

		//resize
		cv::resize((*out_mat), (*out_mat), cv::Size(), scale, scale);
	}

	delete[] pBuffer;
	pBuffer = NULL;
}