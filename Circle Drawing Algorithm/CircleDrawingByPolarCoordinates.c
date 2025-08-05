#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>

void CircleDrawingByPolarcoordinates(HDC hdc, int xc, int yc, int radius)
{
    int i;
    double x, y;
    for (i = 0; i < 360; i++)
    {
        double deg = i * (M_PI / 180.0);
        x = xc + (radius * cos(deg));
        y = yc + (radius * sin(deg));
        SetPixel(hdc, (int)x, (int)y, RGB(255, 0, 0));
        printf("%7d|%7f|%7f|%7d|%7d\n", i, x, y, (int)x, (int)y);
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
    CircleDrawingByPolarcoordinates(hdc, xc, yc, radius);
    ReleaseDC(hwnd, hdc);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}