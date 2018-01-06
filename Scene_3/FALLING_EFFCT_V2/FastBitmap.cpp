#include "FastBitmap.h"

using namespace PixelParallelProcessor;


void FastBitmap::InitGdiPlus()
{
	if (_gdiplusToken != NULL)
	{
		throw std::exception("Exception: GDI plus already initialized !!!");
	}

	if (GdiplusStartup(&_gdiplusToken, &_gdiStartupInput, nullptr) != Ok)
	{
		throw std::exception("Exception: failed to initialize GDI plus !!!");
	}

	_isGdiPlusStarted = true;
}

void FastBitmap::StopGdiPlus()
{
	_isGdiPlusStarted = false;

	if (_gdiplusToken != NULL)
	{
		GdiplusShutdown(_gdiplusToken);		
	}
	else
	{
		throw std::exception("Exception: GDI  not initialized plus !!!");
	}
}

FastBitmap::FastBitmap(Bitmap *bmp)
{
	if (bmp == nullptr)
	{
		throw std::exception("NULL EXCEPTION :BITMAP");
	}

	BitmapToPixelFormat32bppARGB(bmp);
}

FastBitmap::FastBitmap(BYTE *stream)
{
	if (stream == nullptr)
	{
		throw std::exception("NULL EXCEPTION :BITMAP");
	}

	//convert here stream to bitmap;


	//BitmapToPixelFormat32bppARGB();
}

void FastBitmap::BitmapToPixelFormat32bppARGB(Bitmap *bmp)
{
	_bitmap = bmp;

	if (bmp->GetPixelFormat() != PixelFormat32bppARGB)
	{
		auto newBmp = this->Clone();
	
		delete _bitmap;
		_bitmap = nullptr;
		
		_bitmap = newBmp;

		return;
	}
}

BOOL FastBitmap::LockBitmap()
{
	if (_lock == true)
	{
		throw std::exception("Exception: bitmap already Locked !!!");
	}

	const Rect area(0,0,this->GetWidth(), this->GetHeight());

	if (_bitmap->LockBits(&area, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppRGB, _lockedBitmapData) == Ok)
	{
		_totalBytesInRow = area.Width * sizeof(PixelData);

		if (_totalBytesInRow % 4 != 0)
			_totalBytesInRow = 4 * (_totalBytesInRow / 4 + 1);

		_pBitmap=(byte*)_lockedBitmapData->Scan0;
		
		if (_pBitmap == nullptr)
		{
			throw std::exception("Exception: null pointer !!!");
		}

		_lock = true;
	}

	return _lock;
}

BOOL  FastBitmap::UnLockBitmap()
{
	if (!_lock)
	{
		throw std::exception("Exception: bitmap not Locked !!!");
	}

	_bitmap->UnlockBits(_lockedBitmapData);
	
	delete _lockedBitmapData;
	_lockedBitmapData = nullptr;

	delete _pBitmap;
	_pBitmap = nullptr;

	_lock = false;

	return _lock;
}

FastBitmap::~FastBitmap()
{
	if (_lock)
	{
		UnLockBitmap();
	}

	if (_bitmap != nullptr)
	{
		delete _bitmap;
		_bitmap = nullptr;
	}
}

int FastBitmap::GetHeight()
{
	if (_bitmap == nullptr)
	{
		throw std::exception("Exception: bitmap already Locked !!!");
	}

	return _bitmap->GetHeight();
}

int FastBitmap::GetWidth()
{
	if (_bitmap == nullptr)
	{
		throw std::exception("Exception: bitmap already Locked !!!");
	}

	return _bitmap->GetWidth();
}

Bitmap * FastBitmap::Clone()
{
	if (_bitmap == nullptr)
	{
		throw std::exception("Exception: bitmap already Locked !!!");
	}

	const Rect area(0, 0, this->GetWidth(), this->GetHeight());
	return _bitmap->Clone(area, PixelFormat32bppARGB);
}


int FastBitmap::GetBytesInRow()
{
	return _totalBytesInRow;
}

char *FastBitmap::GetBitmapData()
{
	if (_pBitmap == nullptr)
	{
		throw std::exception("Exception: null pointer !!!");
	}
	return (char*)_pBitmap;
}