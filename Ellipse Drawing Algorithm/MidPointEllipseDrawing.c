#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <math.h>

void PlotEllipsePoints(HDC hdc, int cx, int cy, int x, int y)
{
    SetPixel(hdc, cx + x, cy + y, RGB(255, 0, 0)); // First quadrant
    SetPixel(hdc, cx - x, cy + y, RGB(255, 0, 0)); // Second quadrant
    SetPixel(hdc, cx + x, cy - y, RGB(255, 0, 0)); // Fourth quadrant
    SetPixel(hdc, cx - x, cy - y, RGB(255, 0, 0)); // Third quadrant
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
    int x, y, cx, cy;
    printf("Enter Radius Along x : ");
    scanf("%d", &x);
    printf("Enter Radius Along y : ");
    scanf("%d", &y);

    printf("Enter Center Point : ");
    scanf("%d %d", &cx, &cy);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("MyWindowClass", "Mid Point Elipse Drawing Algorithm", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    HDC hdc = GetDC(hwnd);
    MidPointEllipseDrawing(hdc, x, y, cx, cy);
    ReleaseDC(hwnd, hdc);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}