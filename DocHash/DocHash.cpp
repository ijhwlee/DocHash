// DocHash.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <iostream>
#include "framework.h"
#include "commdlg.h"
#include "DocHash.h"
#include <string>
using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                GetHash(HWND, char *, int);
void                PrintHash(char*, int, int);
void                MakeHashString(char*, char*, int);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPWSTR    lpCmdLine,
  _In_ int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // TODO: 여기에 코드를 입력합니다.

  // 전역 문자열을 초기화합니다.
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_DOCHASH, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // 애플리케이션 초기화를 수행합니다:
  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DOCHASH));

  MSG msg;

  // 기본 메시지 루프입니다:
  while (GetMessage(&msg, nullptr, 0, 0))
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DOCHASH));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DOCHASH);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, WIN_SIZE_X, WIN_SIZE_Y, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd)
  {
    return FALSE;
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  char hash[HASH_SIZE /8] = { 0 };
  switch (message)
  {
  case WM_COMMAND:
  {
    int wmId = LOWORD(wParam);
    // 메뉴 선택을 구문 분석합니다:
    switch (wmId)
    {
    case IDM_OPEN:
      OutputDebugString(L"============== Open Menu\n");
      GetHash(hWnd, hash, HASH_SIZE);
      break;
    case IDM_ABOUT:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
  }
  break;
  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
    EndPaint(hWnd, &ps);
  }
  break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);
  switch (message)
  {
  case WM_INITDIALOG:
    return (INT_PTR)TRUE;

  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
    {
      EndDialog(hDlg, LOWORD(wParam));
      return (INT_PTR)TRUE;
    }
    break;
  }
  return (INT_PTR)FALSE;
}

void GetHash(HWND hWnd, char* hash, int size)
{
  char buffer[HASH_SIZE /8] = { 0 };
  memset(hash, 0x00, size / 8); // size is bit size
  OPENFILENAME OFN;
  TCHAR filePathName[256] = L"";
  TCHAR lpstrFile[256] = L"";
  static TCHAR filter[] = L"모든 파일\0*.*\0PDF 파일\0*.pdf";
  memset(&OFN, 0x00, sizeof(OPENFILENAME));
  OFN.lStructSize = sizeof(OPENFILENAME);
  OFN.hwndOwner = hWnd;
  OFN.lpstrFilter = filter;
  OFN.lpstrFile = lpstrFile;
  OFN.nMaxFile = 256;
  OFN.lpstrInitialDir = L".";
  if (GetOpenFileName(&OFN) != 0)
  {
    wsprintf(filePathName, L"%s 파일을 열겠습니까?", OFN.lpstrFile);
    MessageBox(hWnd, filePathName, L"열기 선택", MB_OK);
    TCHAR msg[256] = L"";
    wsprintf(msg, L"Files name is %s\n", OFN.lpstrFile);
    TCHAR msg1[16] = { 0 };
    OutputDebugString(msg);
    FILE* pFile = NULL;
    int count = 0;
    if (_wfopen_s(&pFile, OFN.lpstrFile, L"rb") == 0 && pFile != NULL)
    {
      while (!feof(pFile))
      {
        memset(buffer, 0x00, HASH_SIZE / 8);
        fread_s(buffer, HASH_SIZE / 8, HASH_SIZE / 8, 1, pFile);
        for (int i = 0; i < size / 8; i++)
        {
          hash[i] = hash[i] ^ buffer[i];
        }
        //wsprintf(msg1, L"Hash Resuls %d\n", count++);
        //OutputDebugString(msg1);
        //PrintHash(hash, HASH_SIZE, 32);
        //PrintHash(buffer, HASH_SIZE, 32);
      }
      fclose(pFile);
      OutputDebugString(L"============= HASH RESULT ========================\n");
      PrintHash(hash, HASH_SIZE, 32);
      FILE* hashFile = NULL;
      fopen_s(&hashFile, "hash.dat", "wb");
      if (hashFile != NULL)
      {
        fwrite(hash, sizeof(char), HASH_SIZE / 8, hashFile);
        fclose(hashFile);
      }
      char hashStr[HASH_SIZE / 8 * 2+1] = { 0 }; // include the final null character
      MakeHashString(hashStr, hash, HASH_SIZE);
      char msg2[512] = { 0 };
      for (int i = 0; i < HASH_SIZE / 8 * 2; i++)
      {
        msg2[i] = hashStr[i];
      }
      msg2[HASH_SIZE / 8 * 2] = '\n';
      OutputDebugStringA(msg2);
      FILE* hashStrFile = NULL;
      fopen_s(&hashStrFile, "hashStr.dat", "wb");
      if (hashStrFile != NULL)
      {
        fwrite(hashStr, sizeof(char), HASH_SIZE / 8 * 2 + 1, hashStrFile);
        fclose(hashStrFile);
      }
    }
    else
    {
      wsprintf(msg, L"파일 %s을 열지 못했습니다.\n", OFN.lpstrFile);
      MessageBox(hWnd, msg, L"열기 실패", MB_OK);
    }
  }
}

void PrintHash(char* hash, int size, int line_width)
{
  TCHAR msg1[16] = { 0 };
  for (int i = 0; i < size / 8; i++)
  {
    if ((i + 1) % line_width == 0)
    {
      wsprintf(msg1, L"%02X\n", hash[i] & 0xFF);
    }
    else
    {
      wsprintf(msg1, L"%02X ", hash[i] & 0xFF);
    }
    OutputDebugString(msg1);
  }
}

void MakeHashString(char* hashStr, char*hash, int size)
{
  char line[8] = { 0 };
  for (int i = 0; i < size / 8; i++)
  {
    memset(line, 0x00, 8);
    sprintf_s(line, 8, "%02X", hash[i] & 0xFF);
    hashStr[2 * i] = line[0];
    hashStr[2 * i+1] = line[1];
  }
}