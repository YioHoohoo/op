﻿#ifndef __OP_MESSAGE_H_
#define __OP_MESSAGE_H_
#include <WinUser.h>
#define OP_MAKE_MESSAGE(msg) (WM_USER + msg)
#define OP_WM_MOUSEMOVE (WM_USER + WM_MOUSEMOVE)
#define OP_WM_LBUTTONUP (WM_USER + WM_LBUTTONUP)
#define OP_WM_LBUTTONDOWN (WM_USER + WM_LBUTTONDOWN)
#define OP_WM_MBUTTONDOWN (WM_USER + WM_MBUTTONDOWN)
#define OP_WM_MBUTTONUP (WM_USER + WM_MBUTTONUP)
#define OP_WM_RBUTTONDOWN (WM_USER + WM_RBUTTONDOWN)
#define OP_WM_RBUTTONUP (WM_USER + WM_RBUTTONUP)
#define OP_WM_MOUSEWHEEL (WM_USER + WM_MOUSEWHEEL)
#endif