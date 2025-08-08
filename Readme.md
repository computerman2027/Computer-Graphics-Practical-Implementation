# Computer Graphics Practical Implementation

This repository contains various C implementations of fundamental computer graphics algorithms to draw and fill shapes such as lines, circles, and ellipses.

## 🔧 System Requirements

- **Operating System**: Windows
- **Compiler**: MinGW (`gcc`)
- **Editor**: VS Code or any other code editor

> **Note:** All code is currently configured to run only on **Windows OS**.

## 📥 How to Clone the Repository

Open your terminal and run:

```bash
git clone https://github.com/computerman2027/Computer-Graphics-Practical-Implementation.git
cd Computer-Graphics-Practical-Implementation
```

## 📂 Repository Structure

```
Computer-Graphics-Practical-Implementation
├── Circle Drawing Algorithm
│   ├── BresenhamCircleDrawingAlgorithm.c
│   ├── CircleDrawingByFormula.c
│   ├── CircleDrawingByPolarCoordinates.c
│   ├── MidPointCircledrawingAlgorithm.c
├── Colour Fill Algorithm
│   ├── BoundaryFillAlgorithm.c
│   ├── BoundaryFillAlgorithmEllipseN4.c
│   ├── BoundaryFillAlgorithmN4.c
│   ├── BoundaryFillAlgorithmN8.c
│   ├── FloodFillAlgorithm.c
│   ├── FloodFillAlgorithm2.c
├── Ellipse Drawing Algorithm
│   └── MidPointEllipseDrawing.c
└── Line Drawing Algorithm
    ├── BenchmarkLineDrawingAlgo.c
    ├── BresenhamsLineDrawing.c
    ├── DDA.c
    └── slopeIntercept.c
```

## 🛠️ Compilation Instructions

### For General Algorithms (e.g. Line/Circle/Ellipse Drawing)
```bash
gcc BresenhamsLineDrawing.c -lgdi32 -o p3.exe
```

### For Colour Fill Algorithms (requires large stack size due to recursion)
```bash
gcc "-Wl,--stack,8388608" BoundaryFillAlgorithmEllipseN4.c -lgdi32 -o p5.exe
```

## ⚠️ Notes

- Executable files (`.exe`) are included for initial testing but will be removed in the final version.
- Ensure your system supports **WinBGIm** or **GDI32** graphics for successful execution.

## 📎 GitHub Repository

[Computer-Graphics-Practical-Implementation](https://github.com/computerman2027/Computer-Graphics-Practical-Implementation.git)