#include "CDrawToHDC.h"



CDrawToHDC::CDrawToHDC()
{
}


CDrawToHDC::~CDrawToHDC()
{
}

void CDrawToHDC::DrawToHDC(cv::Mat image, HDC hDCDst, RECT* pDstRect)
{
	if (pDstRect && !image.empty() && image.depth() == CV_8U)
	{ 
		int bpp = 8 * image.elemSize();

		int padding = 0;
		//32 bit image is always DWORD aligned because each pixel requires 4 bytes
		if (bpp < 32)
			padding = 4 - (image.cols % 4);

		if (padding == 4)
			padding = 0;

		cv::Mat tmpImg;
		if (padding > 0 || image.isContinuous() == false)
		{
			// Adding needed columns on the right (max 3 px)
			cv::copyMakeBorder(image, tmpImg, 0, 0, 0, padding, cv::BORDER_CONSTANT, 0);
		}
		else
		{
			tmpImg = image;

		}
		//printf("bpp = %d\n", bpp);

		uchar buffer[sizeof(BITMAPINFO) + 256 * 4];
		BITMAPINFO* bmi = (BITMAPINFO*)buffer;
		BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);
		memset(bmih, 0, sizeof(*bmih));
		bmih->biSize = sizeof(BITMAPINFOHEADER);
		bmih->biWidth = tmpImg.cols;
		bmih->biHeight = -tmpImg.rows;// DIB are bottom ->top
		bmih->biPlanes = 1;
		bmih->biBitCount = bpp;
		bmih->biCompression = BI_RGB;

		//Sets the palette only if image is grey scale
		if (bpp == 8)
		{
			RGBQUAD* palette = bmi->bmiColors;
			for (int i = 0; i < 256; i++)
			{
				palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
				palette[i].rgbReserved = 0;
			}
		}

		//cv::Rect dst = RectToCvRect(*pDstRect);
		cv::Rect dst;
		dst.width = pDstRect->right - pDstRect->left;
		dst.height = pDstRect->bottom - pDstRect->top;

		if (tmpImg.cols == dst.width && tmpImg.rows == dst.height)
		{
			// source and destination have same size
			// tranfer memory block
			// NOTE: the padding border will be shown here. Anyway it will be max 3px width

			SetDIBitsToDevice(hDCDst,
				//destination rectangle
				0, 0, dst.width, dst.height,
				0, 0, 0, tmpImg.rows,
				tmpImg.data, bmi, DIB_RGB_COLORS);
		}
		else
		{
			// Image is bigger or smaller than into destination rectangle
			// we use stretch in full rect

			// destination rectangle 
			int destx = 0, desty = 0;
			int destw = dst.width;
			int desth = dst.height;

			// rectangle defined on source bitmap
			// using imgWidth instead of tmpImg.cols will ignore the padding border
			int imgx = 0, imgy = 0;
			int imgWidth = tmpImg.cols;
			int imgHeight = tmpImg.rows;

			StretchDIBits(hDCDst,
				destx, desty, destw, desth,
				imgx, imgy, imgWidth, imgHeight,
				tmpImg.data, bmi, DIB_RGB_COLORS, SRCCOPY);
		}
	}

}