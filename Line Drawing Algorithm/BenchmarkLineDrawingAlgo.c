#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>

// ---------------- Timer Function ----------------
LONGLONG GetExecutionTime(void (*func)(HDC, int, int, int, int), HDC hdc, int x1, int y1, int x2, int y2)
{
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    func(hdc, x1, y1, x2, y2);

    QueryPerformanceCounter(&end);
    return (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart; // microseconds
}

void lineSlopeIntercept(HDC hdc, int x1, int y1, int x2, int y2)
{
    int count = 0;
    if (x1 == x2)
    {
        int sy = (y1 < y2) ? 1 : -1;
        for (int y = y1; y != y2 + sy; y += sy)
        {
            SetPixel(hdc, x1, y, RGB(255, 0, 0));
            count++;
        }
        return;
    }

    float m = (float)(y2 - y1) / (x2 - x1);
    float c = y1 - m * x1;

    // printf("Slope = %f\nIntercept c = %f\n", m, c);
    // printf("Points Plotting Table:\n");

    if (fabs(m) <= 1)
    {
        int sx = (x1 < x2) ? 1 : -1;
        for (int x = x1; x != x2 + sx; x += sx)
        {
            float y = m * x + c;
            // printf("%7d|%7d|%7f|%7d|%7d\n", x - x1, x, y, x, (int)(y));
            SetPixel(hdc, x, (int)(y), RGB(255, 0, 0));
            count++;
        }
    }
    else
    {
        int sy = (y1 < y2) ? 1 : -1;
        for (int y = y1; y != y2 + sy; y += sy)
        {
            float x = (y - c) / m;
            // printf("%7d|%7f|%7d|%7d|%7d\n", y - y1, x, y, (int)(x), y);
            SetPixel(hdc, (int)(x), y, RGB(255, 0, 0));
            count++;
        }
    }

    printf("slope count = %d ", count);
}

void lineDDAAlgorithm(HDC hdc, int x1, int y1, int x2, int y2)
{
    int count = 0;

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

    double x = x1, y = y1;
    int i;
    for (i = 0; i <= steps; i++)
    {
        // printf("%7d|%7f|%7f|%7d|%7d\n", i, x, y, (int)x, (int)y);
        SetPixel(hdc, (int)x, (int)y, RGB(255, 0, 0));
        x += incrementOfX;
        y += incrementOfY;
        count++;
    }

    printf("DDA count = %d ", count);
}

void swap(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void BreshenhamsLineDrawing(HDC hdc, int x1, int y1, int x2, int y2)
{
    int count = 0;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    // int sx = (x2 >= x1) ? 1 : -1;
    // int sy = (y2 >= y1) ? 1 : -1;
    int sx, sy;
    int p, k = 0;
    float m = ((float)dy) / dx;
    // printf("m = %f\ndx = %d\ndy=%d\n", m, dx, dy);
    // printf("   Step|     p|     x|     y\n");
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
        count++;
        p = (2 * dy) - dx;
        // printf("%7d|%7d|%7d|%7d\n", k, p, x, y);
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
            count++;
            if (p < 0)
            {
                p = p + (2 * dy);
            }
            else
            {
                p = p + (2 * dy) - (2 * dx);
            }
            // printf("%7d|%7d|%7d|%7d\n", k, p, x, y);
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
        count++;
        p = (2 * dx) - dy;
        // printf("%7d|%7d|%7d|%7d\n", k, p, x, y);
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
            count++;
            if (p < 0)
            {
                p = p + (2 * dx);
            }
            else
            {
                p = p + (2 * dx) - (2 * dy);
            }
            // printf("%7d|%7d|%7d|%7d\n", k, p, x, y);
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

    printf("Bresenham count = %d\n", count);
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
    int x1, x2, y1, y2,runs;
    printf("Enter how many time you want to run the bench mark : ");
    scanf("%d",&runs);
    printf("Enter starting coordinate : ");
    scanf("%d %d", &x1, &y1);
    printf("Enter Ending coordinate : ");
    scanf("%d %d", &x2, &y2);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("MyWindowClass", "Benchmark Line Drawing algorithm", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    HDC hdc = GetDC(hwnd);

    // Run benchmark
    LONGLONG totalSlope = 0, totalDDA = 0, totalBres = 0;
    for (int i = 0; i < runs; i++)
    {
        printf("%d ",(i+1));
        totalSlope += GetExecutionTime(lineSlopeIntercept, hdc, x1, y1, x2, y2);
        Sleep(1000);
        totalDDA += GetExecutionTime(lineDDAAlgorithm, hdc, x1, y1, x2, y2);
        Sleep(1000);
        totalBres += GetExecutionTime(BreshenhamsLineDrawing, hdc, x1, y1, x2, y2);
        Sleep(1000);
    }

    printf("\n=== Average Execution Time over %d runs ===\n", runs);
    printf("Slope-Intercept: %llf us\n", totalSlope / (float)runs);
    printf("DDA           : %llf us\n", totalDDA / (float)runs);
    printf("Bresenham     : %llf us\n", totalBres / (float)runs);

    ReleaseDC(hwnd, hdc);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}