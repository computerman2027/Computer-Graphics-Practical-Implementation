#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>

void DrawCirclePoints(HDC hdc, int xc, int yc, int x, int y)
{
    SetPixel(hdc, xc + x, yc + y, RGB(255, 0, 0));
    SetPixel(hdc, xc - x, yc + y, RGB(255, 0, 0));
    SetPixel(hdc, xc + x, yc - y, RGB(255, 0, 0));
    SetPixel(hdc, xc - x, yc - y, RGB(255, 0, 0));
    SetPixel(hdc, xc + y, yc + x, RGB(255, 0, 0));
    SetPixel(hdc, xc - y, yc + x, RGB(255, 0, 0));
    SetPixel(hdc, xc + y, yc - x, RGB(255, 0, 0));
    SetPixel(hdc, xc - y, yc - x, RGB(255, 0, 0));
}

void BresenhamCircleDrawingAlgorithm(HDC hdc, int xc, int yc, int radius)
{
    int k = 0, pk, xk, yk;

    xk = 0;
    yk = radius;

    // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
    DrawCirclePoints(hdc, xc, yc, xk, yk);

    printf("%7d|%7d|%7d|%7d|%7d|%7d\n", 0, 0, xk, yk, xk + xc, yk + yc);

    while (xk < yk)
    {
        if (k == 0)
        {
            pk = 3 - (2*radius);

            if (pk < 0)
            {
                xk = xk + 1;
                // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
                DrawCirclePoints(hdc, xc, yc, xk, yk);
            }
            else
            {
                xk = xk + 1;
                yk = yk - 1;
                // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
                DrawCirclePoints(hdc, xc, yc, xk, yk);
            }
            printf("%7d|%7d|%7d|%7d|%7d|%7d\n", k, pk, xk, yk, xk + xc, yk + yc);

            k++;
        }
        else
        {
            if (pk < 0)
            {
                pk = pk + (5 * xk) + 6;
            }
            else
            {
                pk = pk + (4 * (xk - yk)) + 10;
            }

            if (pk < 0)
            {
                xk = xk + 1;
                // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
                DrawCirclePoints(hdc, xc, yc, xk, yk);
            }
            else
            {
                xk = xk + 1;
                yk = yk - 1;
                // SetPixel(hdc, xk + xc, yk + yc, RGB(255, 0, 0));
                DrawCirclePoints(hdc, xc, yc, xk, yk);
            }
            printf("%7d|%7d|%7d|%7d|%7d|%7d\n", k, pk, xk, yk, xk + xc, yk + yc);
            k++;
        }
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int xc, yc, radius;
    printf("Enter center coordinate : ");
    scanf("%d %d", &xc, &yc);
    printf("Enter Radius : ");
    scanf("%d", &radius);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("MyWindowClass", "Slope Intercept Line", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    HDC hdc = GetDC(hwnd);
    BresenhamCircleDrawingAlgorithm(hdc, xc, yc, radius);
    ReleaseDC(hwnd, hdc);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}