#include <windows.h>
#include <stdio.h>

// Draws 8-way symmetric points for a circle
void DrawCirclePoints(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc + y, yc - x, color);
    SetPixel(hdc, xc - y, yc - x, color);
}

// Midpoint Circle Algorithm
void MidpointCircle(HDC hdc, int xc, int yc, int radius, COLORREF color)
{
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    DrawCirclePoints(hdc, xc, yc, x, y, color);
    while (x < y)
    {
        x++;
        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
        DrawCirclePoints(hdc, xc, yc, x, y, color);
    }
}

// 4-connected Boundary Fill
void boundaryFillN4(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor)
{
    COLORREF currentColor = GetPixel(hdc, x, y);
    if (currentColor != borderColor && currentColor != fillColor)
    {
        SetPixel(hdc, x, y, fillColor);
        boundaryFillN4(hdc, x + 1, y, borderColor, fillColor);
        boundaryFillN4(hdc, x - 1, y, borderColor, fillColor);
        boundaryFillN4(hdc, x, y + 1, borderColor, fillColor);
        boundaryFillN4(hdc, x, y - 1, borderColor, fillColor);
    }
}

// Draw everything to memory DC first
void DrawScene(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right;
    int height = rect.bottom;

    // Create compatible memory DC
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBitmap = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(memDC, memBitmap);

    // Fill background white
    HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    FillRect(memDC, &rect, whiteBrush);

    // Draw circle
    int radius = 100;
    int xc = width / 2;
    int yc = height / 2;
    COLORREF borderColor = RGB(0, 0, 0);
    COLORREF fillColor = RGB(0, 255, 0);

    MidpointCircle(memDC, xc, yc, radius, borderColor);

    // Call boundary fill AFTER drawing
    boundaryFillN4(memDC, xc, yc, borderColor, fillColor);

    // Blit memory DC to screen
    BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

    // Cleanup
    DeleteObject(memBitmap);
    DeleteDC(memDC);
    EndPaint(hwnd, &ps);
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
        DrawScene(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// WinMain: Entry Point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "CircleFillWindow";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Midpoint Circle with Boundary Fill (Fixed)",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    // Message Loop
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
