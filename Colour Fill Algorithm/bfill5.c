#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int xc, yc, radius, bordercolorRed, bordercolorGreen, bordercolorBlue, fillcolorRed, fillcolorGreen, fillcolorBlue;

void DrawCirclePoints(HDC hdc, int xc, int yc, int x, int y, COLORREF bordercolor)
{
    printf("Current Color at (%d, %d): R=%d, G=%d, B=%d\n", x, y,
           GetRValue(bordercolor),
           GetGValue(bordercolor),
           GetBValue(bordercolor));
    printf("pixl colored : (%d,%d)\n", xc + x, yc + y);
    SetPixel(hdc, xc + x, yc + y, bordercolor);
    printf("pixl colored : (%d,%d)\n", xc - x, yc + y);
    SetPixel(hdc, xc - x, yc + y, bordercolor);
    printf("pixl colored : (%d,%d)\n", xc + x, yc - y);
    SetPixel(hdc, xc + x, yc - y, bordercolor);
    printf("pixl colored : (%d,%d)\n", xc - x, yc - y);
    SetPixel(hdc, xc - x, yc - y, bordercolor);
    printf("pixl colored : (%d,%d)\n", xc + y, yc + x);
    SetPixel(hdc, xc + y, yc + x, bordercolor);
    printf("pixl colored : (%d,%d)\n", xc - y, yc + x);
    SetPixel(hdc, xc - y, yc + x, bordercolor);
    printf("pixl colored : (%d,%d)\n", xc + y, yc - x);
    SetPixel(hdc, xc + y, yc - x, bordercolor);
    printf("pixl colored : (%d,%d)\n", xc - y, yc - x);
    SetPixel(hdc, xc - y, yc - x, bordercolor);
}

// void boundaryFillN4(HDC hdc, int x, int y, int x1, int x2, int y1, int y2, COLORREF bordercolor, COLORREF fillColor)
void boundaryFillN4(HDC hdc, int x, int y, COLORREF bordercolor, COLORREF fillColor)
{
    printf("Pixel no : (%d, %d)\n", x, y);
    COLORREF currentColor = GetPixel(hdc, x, y);

    printf("Current Color at (%d, %d): R=%d, G=%d, B=%d\n", x, y,
           GetRValue(currentColor),
           GetGValue(currentColor),
           GetBValue(currentColor));
    // int inp = 0;
    // printf("enter something to proceed : ");
    // scanf("%d", &inp);
    // if (inp == 0)
    // {
    //     exit(0);
    // }
    if (currentColor == bordercolor || currentColor == fillColor)
    {
        // exit(0);
        return;
    }
    // if (currentColor == bordercolor || currentColor == fillColor || x > x1 || x < x2 || y > y1 || y < y2)
    // {
    //     return;
    // }
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

    // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
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
                // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
                DrawCirclePoints(hdc, xc, yc, xk, yk, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue));
            }
            else
            {
                xk = xk + 1;
                yk = yk - 1;
                // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
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
                // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
                DrawCirclePoints(hdc, xc, yc, xk, yk, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue));
            }
            else
            {
                xk = xk + 1;
                yk = yk - 1;
                // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
                DrawCirclePoints(hdc, xc, yc, xk, yk, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue));
            }
            printf("%7d|%7d|%7d|%7d|%7d|%7d\n", k, pk, xk, yk, xk + xc, yk + yc);
            k++;
        }
    }

    // boundaryFillN4(hdc, xc, yc, xc + radius, xc - radius, yc + radius, yc - radius, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue), RGB(fillcolorRed, fillcolorGreen, fillcolorBlue));
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

    // Draw circle
    // int radius = 100;
    // int xc = width / 2;
    // int yc = height / 2;
    // COLORREF borderColor = RGB(0, 0, 0);
    // COLORREF fillColor = RGB(0, 255, 0);

    MidpointCircleDrawingAlgorithm(memDC, xc, yc, radius, bordercolorRed, bordercolorGreen, bordercolorBlue, fillcolorRed, fillcolorGreen, fillcolorBlue);

    // Call boundary fill AFTER drawing
    boundaryFillN4(memDC, xc, yc, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue), RGB(fillcolorRed, fillcolorGreen, fillcolorBlue));

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
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // int xc, yc, radius, bordercolorRed, bordercolorGreen, bordercolorBlue, fillcolorRed, fillcolorGreen, fillcolorBlue;
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
        "Midpoint Circle with Boundary Fill (Fixed)",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    // UpdateWindow(hwnd);

    // HDC hdc = GetDC(hwnd);
    // MidpointCircleDrawingAlgorithm(hdc, xc, yc, radius, bordercolorRed, bordercolorGreen, bordercolorBlue, fillcolorRed, fillcolorGreen, fillcolorBlue);

    // Sleep(2000);
    // boundaryFillN4(hdc, xc, yc, xc + radius, xc - radius, yc + radius, yc - radius, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue), RGB(fillcolorRed, fillcolorGreen, fillcolorBlue));
    // ReleaseDC(hwnd, hdc);

    MSG msg ={0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}