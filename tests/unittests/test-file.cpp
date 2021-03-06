﻿/*! @file */
/*
	Copyright (C) 2018-2020 Sakura Editor Organization

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

		1. The origin of this software must not be misrepresented;
		   you must not claim that you wrote the original software.
		   If you use this software in a product, an acknowledgment
		   in the product documentation would be appreciated but is
		   not required.

		2. Altered source versions must be plainly marked as such,
		   and must not be misrepresented as being the original software.

		3. This notice may not be removed or altered from any source
		   distribution.
*/
#include <gtest/gtest.h>

#ifndef NOMINMAX
#define NOMINMAX
#endif /* #ifndef NOMINMAX */

#include <tchar.h>
#include <Windows.h>
#include <Shlwapi.h>

#include "util/file.h"

/*!
 * @brief パスがファイル名に使えない文字を含んでいるかチェックする
 */
TEST( file, IsInvalidFilenameChars )
{
	// ファイル名に使えない文字 = "\\/:*?\"<>|"
	// このうち、\\と/はパス区切りのため実質対象外になる。
	EXPECT_FALSE(IsInvalidFilenameChars(L"test.txt"));
	EXPECT_FALSE(IsInvalidFilenameChars(L".\\test.txt"));
	EXPECT_FALSE(IsInvalidFilenameChars(L"./test.txt"));
	EXPECT_FALSE(IsInvalidFilenameChars(L"C:\\test.txt"));
	EXPECT_FALSE(IsInvalidFilenameChars(L"C:/test.txt"));
	EXPECT_FALSE(IsInvalidFilenameChars(L"C:\\"));
	EXPECT_FALSE(IsInvalidFilenameChars(L"C:/"));

	EXPECT_FALSE(IsInvalidFilenameChars(L"test:001.txt"));

	EXPECT_TRUE(IsInvalidFilenameChars(L"test*.txt"));
	EXPECT_TRUE(IsInvalidFilenameChars(L"test?.txt"));
	EXPECT_TRUE(IsInvalidFilenameChars(L"test\".txt"));
	EXPECT_TRUE(IsInvalidFilenameChars(L"test<.txt"));
	EXPECT_TRUE(IsInvalidFilenameChars(L"test>.txt"));
	EXPECT_TRUE(IsInvalidFilenameChars(L"test|.txt"));
}
