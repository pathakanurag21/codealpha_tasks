# C++ CGPA & Semester GPA Calculator

A modular, Object-Oriented C++ command-line application that calculates individual semester GPAs and overall Cumulative Grade Point Average (CGPA) based on course credit hours and letter grades.

## Features
- Dynamic semester and course input processing using standard C++ vectors.
- Automated letter-grade-to-point mapping on a 4.0 GPA scale.
- Itemized semester summary reports using formatted table output.
- Final cumulative quality points and CGPA summary.

## How to Build & Run

### Using GCC/Clang directly:
```bash
g++ -std=c++11 src/main.cpp -o cgpa_calculator
./cgpa_calculator