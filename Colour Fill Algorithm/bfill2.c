#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// ==== Global Variables ====
int xc, yc, radius;
int bordercolorRed, bordercolorGreen, bordercolorBlue;
int fillcolorRed, fillcolorGreen, fillcolorBlue;

// ==== Drawing Function ====
void MidpointCircleDrawingAlgorithm(HDC hdc, int xc, int yc, int r, int br, int bg, int bb, int fr, int fg, int fb) {
    int x = 0;
    int y = r;
    int d = 1 - r;

    COLORREF borderColor = RGB(br, bg, bb);

    while (x <= y) {
        SetPixel(hdc, xc + x, yc + y, borderColor);
        SetPixel(hdc, xc + y, yc + x, borderColor);
        SetPixel(hdc, xc - x, yc + y, borderColor);
        SetPixel(hdc, xc - y, yc + x, borderColor);
        SetPixel(hdc, xc + x, yc - y, borderColor);
        SetPixel(hdc, xc + y, yc - x, borderColor);
        SetPixel(hdc, xc - x, yc - y, borderColor);
        SetPixel(hdc, xc - y, yc - x, borderColor);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

// ==== Boundary Fill Function ====
void boundaryFillN4(HDC hdc, int x, int y, int xmax, int xmin, int ymax, int ymin, COLORREF borderColor, COLORREF fillColor) {
    if (x > xmax || x < xmin || y > ymax || y < ymin) {
        return;
    }

    COLORREF currentColor = GetPixel(hdc, x, y);

    if (currentColor == borderColor || currentColor == fillColor) {
        return;
    }

    SetPixel(hdc, x, y, fillColor);
    boundaryFillN4(hdc, x + 1, y, xmax, xmin, ymax, ymin, borderColor, fillColor);
    boundaryFillN4(hdc, x - 1, y, xmax, xmin, ymax, ymin, borderColor, fillColor);
    boundaryFillN4(hdc, x, y + 1, xmax, xmin, ymax, ymin, borderColor, fillColor);
    boundaryFillN4(hdc, x, y - 1, xmax, xmin, ymax, ymin, borderColor, fillColor);
}

// ==== Window Procedure ====
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            MidpointCircleDrawingAlgorithm(
                hdc, xc, yc, radius,
                bordercolorRed, bordercolorGreen, bordercolorBlue,
                fillcolorRed, fillcolorGreen, fillcolorBlue
            );

            boundaryFillN4(
                hdc, xc, yc,
                xc + radius, xc - radius, yc + radius, yc - radius,
                RGB(bordercolorRed, bordercolorGreen, bordercolorBlue),
                RGB(fillcolorRed, fillcolorGreen, fillcolorBlue)
            );

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ==== Main Entry Point ====
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // === Input ===
    printf("Enter radius of the circle: ");
    scanf("%d", &radius);
    printf("Enter x center: ");
    scanf("%d", &xc);
    printf("Enter y center: ");
    scanf("%d", &yc);

    printf("Enter border color (R G B): ");
    scanf("%d %d %d", &bordercolorRed, &bordercolorGreen, &bordercolorBlue);

    printf("Enter fill color (R G B): ");
    scanf("%d %d %d", &fillcolorRed, &fillcolorGreen, &fillcolorBlue);

    // === Register Window Class ===
    const char CLASS_NAME[] = "CircleFillWindow";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // white background
    RegisterClass(&wc);

    // === Create Window ===
    HWND hwnd = CreateWindow(
        CLASS_NAME, "Midpoint Circle with Boundary Fill",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // === Message Loop ===
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
