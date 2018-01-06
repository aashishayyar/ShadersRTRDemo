#include<Windows.h>
#include<stdio.h>
#include<gdiplus.h>
#include <iostream>
#include <objidl.h>

#pragma comment (lib,"Gdiplus.lib")

using namespace  Gdiplus;

namespace PixelParallelProcessor
{

	struct PixelData
	{
		byte B;
		byte G;
		byte R;
		byte A;
	};


	class FastBitmap
	{

	public:
		
		static void InitGdiPlus();

		FastBitmap(Bitmap *bmp);

		FastBitmap(BYTE *stream);
	
		BOOL LockBitmap();

		char *GetBitmapData();

		BOOL UnLockBitmap();

		Bitmap *Clone();

		int GetWidth();

		int GetHeight();

		int GetBytesInRow();

		~FastBitmap();

		static void StopGdiPlus();

	private:

		void BitmapToPixelFormat32bppARGB(Bitmap *bmp);

		Bitmap *_bitmap;
		BitmapData *_lockedBitmapData;
		int _totalBytesInRow;
		byte *_pBitmap;

		BOOL _lock;
		int _width;
		int _height;

		static bool _isGdiPlusStarted;
		static ULONG_PTR _gdiplusToken;
		static GdiplusStartupInput _gdiStartupInput;
	};
}