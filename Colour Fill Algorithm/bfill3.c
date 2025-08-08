#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void BorderFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor)
{
    COLORREF currentColor = GetPixel(hdc, x, y);
    if (currentColor == borderColor || currentColor == fillColor)
    {
        return; // Stop if we hit the border or already filled area
    }
    else
    {
        SetPixel(hdc, x, y, fillColor); // Fill the pixel
        BorderFill(hdc, x + 1, y, borderColor, fillColor);
        BorderFill(hdc, x - 1, y, borderColor, fillColor);
        BorderFill(hdc, x, y + 1, borderColor, fillColor);
        BorderFill(hdc, x, y - 1, borderColor, fillColor);
        // BorderFill(hdc, x + 1, y + 1, borderColor, fillColor);
        // BorderFill(hdc, x - 1, y - 1, borderColor, fillColor);
        // BorderFill(hdc, x + 1, y - 1, borderColor, fillColor);
        // BorderFill(hdc, x - 1, y + 1, borderColor, fillColor);
    }
}
void circle_MidPoint(HDC hdc, int r)
{
    int xc = r + 10;
    int yc = r + 10;
    int x = 0, y = r;
    int P = 1 - r;
    while (x <= y)
    {
        SetPixel(hdc, x + xc, y + yc, RGB(0, 0, 0));
        SetPixel(hdc, y + xc, x + yc, RGB(0, 0, 0));
        SetPixel(hdc, -x + xc, y + yc, RGB(0, 0, 0));
        SetPixel(hdc, -y + xc, x + yc, RGB(0, 0, 0));
        SetPixel(hdc, x + xc, -y + yc, RGB(0, 0, 0));
        SetPixel(hdc, y + xc, -x + yc, RGB(0, 0, 0));
        SetPixel(hdc, -x + xc, -y + yc, RGB(0, 0, 0));
        SetPixel(hdc, -y + xc, -x + yc, RGB(0, 0, 0));
        printf("Plotted (%d,%d)\n", xc + x, yc + y);
        if (P < 0)
        {
            x++;
            P = P + 2 * x + 3;
        }
        else
        {
            x++;
            y--;
            P = P + 2 * (x - y) + 5;
        }
    }
    BorderFill(hdc, r + 10, r + 10, RGB(0, 0, 0), RGB(0, 255, 0));
}
void circle_Bresenhams(HDC hdc, int r)
{
    int xc = r + 10;
    int yc = r + 10;
    int x = 0, y = r;
    int P = 3 - 2 * r;
    while (x <= y)
    {
        SetPixel(hdc, x + xc, y + yc, RGB(0, 0, 0));
        SetPixel(hdc, y + xc, x + yc, RGB(0, 0, 0));
        SetPixel(hdc, -x + xc, y + yc, RGB(0, 0, 0));
        SetPixel(hdc, -y + xc, x + yc, RGB(0, 0, 0));
        SetPixel(hdc, x + xc, -y + yc, RGB(0, 0, 0));
        SetPixel(hdc, y + xc, -x + yc, RGB(0, 0, 0));
        SetPixel(hdc, -x + xc, -y + yc, RGB(0, 0, 0));
        SetPixel(hdc, -y + xc, -x + yc, RGB(0, 0, 0));
        printf("Plotted (%d,%d)\n", xc + x, yc + y);
        if (P < 0)
        {
            x++;
            P = P + 4 * x + 6;
        }
        else
        {
            x++;
            y--;
            P = P + 4 * x - 4 * y + 10;
        }
    }
    BorderFill(hdc, r + 10, r + 10, RGB(0, 0, 0), RGB(255, 0, 0));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int r, ch;
    clock_t start, end;
    double total_t;
    char *name;
    printf("1. Mid-Point Circle Drawing Algorithm\n2. Bressenham's Circle Drawing Algorithm\nEnter your choice:");
    scanf("%d", &ch);
    if (ch == 1)
    {
        name = "Mid-Point Circle Drawing Algorithm";
    }
    else if (ch == 2)
    {
        name = "Bresenham's Circle Drawing Algorithm";
    }
    printf("Enter the radius:");
    scanf("%d", &r);
    start = clock();
    // Register window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    // Create window
    HWND hwnd = CreateWindow("MyWindowClass", name, WS_OVERLAPPED,
                             CW_USEDEFAULT, CW_USEDEFAULT, (2 * r + 20 + GetSystemMetrics(SM_CXSIZEFRAME)), (2 * r + 20 + GetSystemMetrics(SM_CYCAPTION)),
                             NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    HDC hdc = GetDC(hwnd);
    switch (ch)
    {
    case 1:
        circle_MidPoint(hdc, r);
        break;
    case 2:
        circle_Bresenhams(hdc, r);
        break;
    default:
        printf("Wrong choice, please choose again!\n");
        break;
    }

    end = clock();
    total_t = (double)((end - start) / CLOCKS_PER_SEC);
    printf("The total time taken is: %lf seconds\n", total_t);
    ReleaseDC(hwnd, hdc);
    MessageBox(hwnd, "Press OK to exit.", "Done", MB_OK);
    return 0;
}