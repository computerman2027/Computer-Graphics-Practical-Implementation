#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>

void swap(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void BreshenhamsLineDrawing(HDC hdc, int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    // int sx = (x2 >= x1) ? 1 : -1;
    // int sy = (y2 >= y1) ? 1 : -1;
    int sx, sy;
    int p, k = 0;
    float m = ((float)dy) / dx;
    printf("m = %f\ndx = %d\ndy=%d\n", m, dx, dy);
    printf("   Step|     p|     x|     y\n");
    int x, y;
    if (fabs(m) < 1)
    {
        if (x1 > x2)
        {
            swap(&x1, &x2);
            swap(&y1, &y2);
        }
        x = x1;
        y = y1;
        sx = (x2 >= x1) ? 1 : -1;
        sy = (y2 >= y1) ? 1 : -1;
        SetPixel(hdc, x, y, RGB(255, 0, 0));
        p = (2 * dy) - dx;
        printf("%7d|%7d|%7d|%7d\n", k, p, x, y);
        k++;
        if (p < 0)
        {
            x += sx;
        }
        else
        {
            x += sx;
            y += sy;
        }
        while (x <= x2)
        {
            SetPixel(hdc, x, y, RGB(255, 0, 0));
            if (p < 0)
            {
                p = p + (2 * dy);
            }
            else
            {
                p = p + (2 * dy) - (2 * dx);
            }
            printf("%7d|%7d|%7d|%7d\n", k, p, x, y);
            k++;
            if (p < 0)
            {
                x += sx;
            }
            else
            {
                x += sx;
                y += sy;
            }
        }
    }
    else
    {
        if (y1 > y2)
        {
            swap(&x1, &x2);
            swap(&y1, &y2);
        }
        x = x1;
        y = y1;
        sx = (x2 >= x1) ? 1 : -1;
        sy = (y2 >= y1) ? 1 : -1;
        SetPixel(hdc, x, y, RGB(255, 0, 0));
        p = (2 * dx) - dy;
        printf("%7d|%7d|%7d|%7d\n", k, p, x, y);
        k++;
        if (p < 0)
        {
            x += sx;
        }
        else
        {
            x += sx;
            y += sy;
        }
        while (x <= x2)
        {
            SetPixel(hdc, x, y, RGB(255, 0, 0));
            if (p < 0)
            {
                p = p + (2 * dx);
            }
            else
            {
                p = p + (2 * dx) - (2 * dy);
            }
            printf("%7d|%7d|%7d|%7d\n", k, p, x, y);
            k++;
            if (p < 0)
            {
                y += sy;
            }
            else
            {
                x += sx;
                y += sy;
            }
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

    HWND hwnd = CreateWindow("MyWindowClass", "Slope Intercept Line", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    HDC hdc = GetDC(hwnd);
    BreshenhamsLineDrawing(hdc, x1, y1, x2, y2);
    ReleaseDC(hwnd, hdc);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}