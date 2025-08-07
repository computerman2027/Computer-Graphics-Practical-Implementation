#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>

void lineDDAAlgorithm(HDC hdc, int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;

    float m = ((float)dy) / dx;

    if (fabs(m) < 1)
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }

    double incrementOfX = (double)dx / steps;
    double incrementOfY = (double)dy / steps;

    double x =x1, y = y1;
    int i;
    for (i = 0; i <= steps; i++)
    {
        printf("%7d|%7f|%7f|%7d|%7d\n", i, x, y, (int)x, (int)y);
        SetPixel(hdc,(int)x,(int)y,RGB(255,0,0));
        x+=incrementOfX;
        y+=incrementOfY;
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
    int x1, x2, y1, y2;
    printf("Enter starting coordinate : ");
    scanf("%d %d", &x1, &y1);
    printf("Enter Ending coordinate : ");
    scanf("%d %d", &x2, &y2);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("MyWindowClass", "DDA Line Drawing Algorithm", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    HDC hdc = GetDC(hwnd);
    lineDDAAlgorithm(hdc, x1, y1, x2, y2);
    ReleaseDC(hwnd, hdc);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}