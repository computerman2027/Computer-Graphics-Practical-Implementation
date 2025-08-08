#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int xc, yc, radius, bordercolorRed, bordercolorGreen, bordercolorBlue, fillcolorRed, fillcolorGreen, fillcolorBlue;

void DrawCirclePoints(HDC hdc, int xc, int yc, int x, int y, COLORREF bordercolor)
{
    SetPixel(hdc, xc + x, yc + y, bordercolor);
    SetPixel(hdc, xc - x, yc + y, bordercolor);
    SetPixel(hdc, xc + x, yc - y, bordercolor);
    SetPixel(hdc, xc - x, yc - y, bordercolor);
    SetPixel(hdc, xc + y, yc + x, bordercolor);
    SetPixel(hdc, xc - y, yc + x, bordercolor);
    SetPixel(hdc, xc + y, yc - x, bordercolor);
    SetPixel(hdc, xc - y, yc - x, bordercolor);
}

void boundaryFillN4(HDC hdc, int x, int y, COLORREF bordercolor, COLORREF fillColor)
{
    COLORREF currentColor = GetPixel(hdc, x, y);

    if (currentColor == bordercolor || currentColor == fillColor)
    {
        return;
    }
    else
    {
        SetPixel(hdc, x, y, fillColor);
        boundaryFillN4(hdc, x, y + 1, bordercolor, fillColor);
        boundaryFillN4(hdc, x, y - 1, bordercolor, fillColor);
        boundaryFillN4(hdc, x + 1, y, bordercolor, fillColor);
        boundaryFillN4(hdc, x - 1, y, bordercolor, fillColor);
    }
}

void MidpointCircleDrawingAlgorithm(HDC hdc, int xc, int yc, int radius, int bordercolorRed, int bordercolorGreen, int bordercolorBlue, int fillcolorRed, int fillcolorGreen, int fillcolorBlue)
{
    int k = 0, pk, xk, yk;

    xk = 0;
    yk = radius;

    DrawCirclePoints(hdc, xc, yc, xk, yk, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue));

    printf("%7d|%7d|%7d|%7d|%7d|%7d\n", 0, 0, xk, yk, xk + xc, yk + yc);

    while (xk < yk)
    {
        if (k == 0)
        {
            pk = 1 - radius;

            if (pk < 0)
            {
                xk = xk + 1;
                DrawCirclePoints(hdc, xc, yc, xk, yk, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue));
            }
            else
            {
                xk = xk + 1;
                yk = yk - 1;
                DrawCirclePoints(hdc, xc, yc, xk, yk, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue));
            }
            printf("%7d|%7d|%7d|%7d|%7d|%7d\n", k, pk, xk, yk, xk + xc, yk + yc);

            k++;
        }
        else
        {
            if (pk < 0)
            {
                pk = pk + (2 * xk) + 3;
            }
            else
            {
                pk = pk + (2 * (xk - yk)) + 5;
            }

            if (pk < 0)
            {
                xk = xk + 1;
                DrawCirclePoints(hdc, xc, yc, xk, yk, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue));
            }
            else
            {
                xk = xk + 1;
                yk = yk - 1;
                DrawCirclePoints(hdc, xc, yc, xk, yk, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue));
            }
            printf("%7d|%7d|%7d|%7d|%7d|%7d\n", k, pk, xk, yk, xk + xc, yk + yc);
            k++;
        }
    }
}

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

    MidpointCircleDrawingAlgorithm(memDC, xc, yc, radius, bordercolorRed, bordercolorGreen, bordercolorBlue, fillcolorRed, fillcolorGreen, fillcolorBlue);

    // Call boundary fill AFTER drawing
    boundaryFillN4(memDC, xc, yc, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue), RGB(fillcolorRed, fillcolorGreen, fillcolorBlue));

    printf("Completed Drawing\n");

    // Blit memory DC to screen
    BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

    // Cleanup
    DeleteObject(memBitmap);
    DeleteDC(memDC);
    EndPaint(hwnd, &ps);
}

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
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    printf("Enter center coordinate : ");
    scanf("%d %d", &xc, &yc);
    printf("Enter Radius : ");
    scanf("%d", &radius);

    printf("Enter Border Color in RGB format (R G B): ");
    scanf("%d %d %d", &bordercolorRed, &bordercolorGreen, &bordercolorBlue);
    printf("Enter fill Color in RGB format (R G B): ");
    scanf("%d %d %d", &fillcolorRed, &fillcolorGreen, &fillcolorBlue);

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
        "Midpoint Circle with Boundary Fill 4N",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}