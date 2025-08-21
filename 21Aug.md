Here are three separate C programs written for the **8051 microcontroller** using **Keil software**. These programs follow the general style of embedded C used in Keil and are suited for simulation/testing on 8051 platforms (e.g., using Proteus or Keil's debugger).

---

## ✅ 1. **Sort Array in Ascending Order**

```c
#include <reg51.h>

void main() {
    unsigned char i, j, temp;
    unsigned char arr[5] = {42, 10, 25, 7, 30};  // Sample array
    unsigned char n = 5;

    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Loop forever (for debugger to pause here and see the sorted array)
    while (1);
}
```

---

## ✅ 2. **Factorial of a Given Number**

```c
#include <reg51.h>

void main() {
    unsigned int num = 5;  // Change this value for different inputs
    unsigned long int fact = 1;
    unsigned char i;

    for (i = 1; i <= num; i++) {
        fact *= i;
    }

    // Now 'fact' holds the factorial result
    while (1);
}
```

> Note: Result is stored in `fact`. Use debugger/watch window to inspect.

---

## ✅ 3. **Average of N Given Numbers**

```c
#include <reg51.h>

void main() {
    unsigned char i;
    unsigned int sum = 0;
    float average;

    unsigned char numbers[5] = {10, 20, 30, 40, 50};  // Example input
    unsigned char n = 5;

    for (i = 0; i < n; i++) {
        sum += numbers[i];
    }

    average = (float)sum / n;

    // Now 'average' contains the result
    while (1);
}
```

---

## 🧠 Notes:

* These programs are meant to be run in Keil uVision (target: 8051).
* You can inspect values using **watch window** or **debugger**.
* `reg51.h` is the standard header for 8051 I/O definitions.
* For actual hardware output (e.g., via LCD, UART), you'd need additional code.

Let me know if you want versions that output data via **UART**, **LCD**, or **seven-segment display**.
