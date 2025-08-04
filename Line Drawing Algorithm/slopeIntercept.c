#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>

// void lineSlopeIntercept(HDC hdc, int x1, int y1, int x2, int y2)
// {
//     if (x1 > x2)
//     {
//         int temp = x1;
//         x1 = x2;
//         x2 = temp;
//         temp = y1;
//         y1 = y2;
//         y2 = temp;
//     }

//     float dx = x2 - x1;
//     float dy = y2 - y1;
//     float m = dy / ((float)dx);

//     if (m < 1)
//     {
//         dy = m * dx;
//     }
//     else
//     {
//         dx = dy / m;
//     }

//     printf("Slope = %f\ndx = %f\ndy= %f\n", m, dx, dy);
//     printf("Points Plotting Table :\n");
//     float tx1 = x1, ty1 = y1;
//     int slno = 0;
//     if (m < 1)
//     {
//         while (tx1 < (float)x2)
//         {

//             printf("%7d|%7f|%7f|%7d|%7d\n", slno, tx1, ty1, (int)tx1, (int)ty1);
//             SetPixel(hdc, (int)tx1, (int)ty1, RGB(255, 0, 0));
//             tx1 += dx;
//             ty1 += dy;
//             slno++;
//             printf("%7d|%7f|%7f|%7d|%7d\n", slno, tx1, ty1, (int)tx1, (int)ty1);
//         }
//     }
//     else
//     {
//         while (ty1 < (float)y2)
//         {

//             printf("%7d|%7f|%7f|%7d|%7d\n", slno, tx1, ty1, (int)tx1, (int)ty1);
//             SetPixel(hdc, (int)tx1, (int)ty1, RGB(255, 0, 0));
//             tx1 += dx;
//             ty1 += dy;
//             slno++;
//             printf("%7d|%7f|%7f|%7d|%7d\n", slno, tx1, ty1, (int)tx1, (int)ty1);
//         }
//     }
// }

void lineSlopeIntercept(HDC hdc, int x1, int y1, int x2, int y2)
{
    if (x1 == x2)
    { // vertical line edge case
        int sy = (y1 < y2) ? 1 : -1;
        for (int y = y1; y != y2 + sy; y += sy)
        {
            SetPixel(hdc, x1, y, RGB(255, 0, 0));
        }
        return;
    }

    float m = (float)(y2 - y1) / (x2 - x1);
    float c = y1 - m * x1;

    printf("Slope = %f\nIntercept c = %f\n", m, c);
    printf("Points Plotting Table:\n");

    if (fabs(m) <= 1)
    {
        // Iterate through x
        int sx = (x1 < x2) ? 1 : -1;
        for (int x = x1; x != x2 + sx; x += sx)
        {
            float y = m * x + c;
            printf("%7d|%7d|%7f|%7d|%7d\n", x - x1, x, y, x, (int)(y + 0.5));
            // SetPixel(hdc, x, (int)(y + 0.5), RGB(255, 0, 0));
            SetPixel(hdc, x, (int)(y), RGB(255, 0, 0));
        }
    }
    else
    {
        // Iterate through y
        int sy = (y1 < y2) ? 1 : -1;
        for (int y = y1; y != y2 + sy; y += sy)
        {
            float x = (y - c) / m;
            printf("%7d|%7f|%7d|%7d|%7d\n", y - y1, x, y, (int)(x + 0.5), y);
            // SetPixel(hdc, (int)(x + 0.5), y, RGB(255, 0, 0));
            SetPixel(hdc, (int)(x), y, RGB(255, 0, 0));
        }
    }
}

// 🧠 Define a custom window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);  // 🔴 This ensures the program exits when the window is closed
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
    // wc.lpfnWndProc = DefWindowProc;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("MyWindowClass", "Slope Intercept Line", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    HDC hdc = GetDC(hwnd);
    lineSlopeIntercept(hdc, x1, y1, x2, y2);
    ReleaseDC(hwnd, hdc);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}