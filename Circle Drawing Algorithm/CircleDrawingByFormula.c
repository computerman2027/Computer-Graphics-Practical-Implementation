#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>

void CircleDrawingByStandardEqualtion(HDC hdc, int xc, int yc, int radius)
{
    int x, k=1;

    double y1,y2;
    for (x = xc - radius; x <= xc + radius; x++)
    {
        double d = sqrt((radius * radius) - ((x - xc) * (x - xc)));

        y1 = yc + d;
        SetPixel(hdc, x, (int) y1, RGB(255, 0, 0));
        printf("%7d|%7d|%7f|%7d|%7d\n",k,x,y1,x,(int)y1);
        k++;
        y2 = yc - d;
        SetPixel(hdc, x, (int)y2, RGB(255, 0, 0));
        printf("%7d|%7d|%7f|%7d|%7d\n",k,x,y2,x,(int)y2);
        k++;

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
    CircleDrawingByStandardEqualtion(hdc, xc, yc, radius);
    ReleaseDC(hwnd, hdc);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}