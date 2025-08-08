#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int xc, yc, x, y, bordercolorRed, bordercolorGreen, bordercolorBlue, fillcolorRed, fillcolorGreen, fillcolorBlue;

void PlotEllipsePoints(HDC hdc, int cx, int cy, int x, int y)
{
    SetPixel(hdc, cx + x, cy + y, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue)); // First quadrant
    SetPixel(hdc, cx - x, cy + y, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue)); // Second quadrant
    SetPixel(hdc, cx + x, cy - y, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue)); // Fourth quadrant
    SetPixel(hdc, cx - x, cy - y, RGB(bordercolorRed, bordercolorGreen, bordercolorBlue)); // Third quadrant
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

void MidPointEllipseDrawing(HDC hdc, int rx, int ry, int cx, int cy)
{
    int x = 0, y = ry, k = 0;
    printf("Region 1 \n");
    printf("%7d | %7d | %7d | %7d | %7d | %7d\n", 0, 0, x, y, 0, 0);
    // SetPixel(hdc, x + cx, y + cy, RGB(255, 0, 0));
    PlotEllipsePoints(hdc, cx, cy, x, y);

    int region = 1, pk, c1, c2, c3 = ry * ry, c4 = rx * rx;
    pk = (ry * ry) - (rx * rx * ry) + (rx * rx * 0.25);

    while (region == 1)
    {
        if (pk < 0)
        {
            x++;
            // SetPixel(hdc, x + cx, y + cy, RGB(255, 0, 0));
            PlotEllipsePoints(hdc, cx, cy, x, y);

            c1 = 2 * ry * ry * x;
            c2 = 2 * rx * rx * y;
            printf("%7d | %7d | %7d | %7d | %7d | %7d\n", k, pk, x, y, c1, c2);
            k++;
            if (c1 >= c2)
            {
                region++;
                break;
            }
            pk = pk + c1 + c3;
        }
        else
        {
            x++;
            y--;
            // SetPixel(hdc, x + cx, y + cy, RGB(255, 0, 0));
            PlotEllipsePoints(hdc, cx, cy, x, y);

            c1 = 2 * ry * ry * x;
            c2 = 2 * rx * rx * y;
            printf("%7d | %7d | %7d | %7d | %7d | %7d\n", k, pk, x, y, c1, c2);
            k++;
            if (c1 >= c2)
            {
                region++;
                break;
            }
            pk = pk + c1 - c2 + c3;
        }
    }
    k = 0;
    printf("Region 2 \n");
    printf("%7d | %7d | %7d | %7d | %7d | %7d\n", 0, 0, x, y, 0, 0);
    pk = (ry * ry * (x + 0.5) * (x + 0.5)) + (rx * rx * (y - 1) * (y - 1)) - (rx * rx * ry * ry);

    while (region == 2 && y != 0)
    {
        if (pk > 0)
        {
            y--;
            // SetPixel(hdc, x + cx, y + cy, RGB(255, 0, 0));
            PlotEllipsePoints(hdc, cx, cy, x, y);

            c1 = 2 * ry * ry * x;
            c2 = 2 * rx * rx * y;
            printf("%7d | %7d | %7d | %7d | %7d | %7d\n", k, pk, x, y, c1, c2);
            k++;
            pk = pk - c2 + c4;
        }
        else
        {
            x++;
            y--;
            // SetPixel(hdc, x + cx, y + cy, RGB(255, 0, 0));
            PlotEllipsePoints(hdc, cx, cy, x, y);

            c1 = 2 * ry * ry * x;
            c2 = 2 * rx * rx * y;

            printf("%7d | %7d | %7d | %7d | %7d | %7d\n", k, pk, x, y, c1, c2);
            k++;
            pk = pk + c1 - c2 + c4;
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

    MidPointEllipseDrawing(memDC, x, y, xc, yc);

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
    printf("Enter Radius Along x : ");
    scanf("%d", &x);
    printf("Enter Radius Along y : ");
    scanf("%d", &y);

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