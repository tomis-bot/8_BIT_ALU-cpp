# 8-bit ALU (C++)

A simple **8-bit Arithmetic Logic Unit (ALU)** implemented in C++ using only basic logic gates built from **NAND**.

---

## 📌 Features

* Built entirely from NAND-based logic
* Supports multiple operations:

  * ADD
  * SUB
  * SHIFT
  * COMPARE
  * Logical operations (XOR, OR, NOT)
* Includes:

  * Full Adder
  * Half Adder
  * Decoder (3 → 8)
  * Multiplexer (MUX)
  * Shifter
* Works on **8-bit binary numbers**

---

## ⚙️ How It Works

The ALU is constructed hierarchically:

* **Basic gates** → NAND
* **Derived gates** → AND, OR, XOR, NOT, NOR
* **Arithmetic units** → Half Adder, Full Adder
* **Control logic** → Decoder + MUX
* **Final unit** → `ALU8BIT`

Operations are selected using a 3-bit control input `D[3]`.

---

## 🧠 Control Bits (`D`)

The operation depends on the decoder output:

| D (binary) | Operation |
| ---------- | --------- |
| 001        | Compare   |
| 011        | Subtract  |
| 101        | Shift     |
| 110        | Add       |

*(based on current implementation logic)*

---

## ▶️ How to Compile

```bash
g++ main.cpp -o alu.exe
```

---

## ▶️ How to Run

```bash
alu.exe
```

---

## 📥 Input

Inside the code:

```cpp
string Astr = "00000001";
string Bstr = "00000010";
```

* Inputs are **8-bit binary strings**
* Automatically converted into internal bit arrays

---

## 📤 Output

The program prints:

* Input A
* Input B
* Result (8-bit)
* Carry flag
* Compare flag (`F`)

Example:

```txt
A: 00000001
B: 00000010
Output: 00000011
F: 0
Carry: 0
```

---

## ⚠️ Notes

* Internally, bits are stored **LSB first**, but input/output is shown normally
* All logic is built from **NAND gates only**
* This is a **learning/educational implementation**, not optimized for performance

---

## 📁 Project Structure

```txt
main.cpp
README.md
.gitignore
```

---

## 🚀 Future Improvements

* User input via console (`cin`)
* Support for more operations
* Better visualization of bit operations
* Cross-platform support (remove Windows-specific code if added later)

---

## 📜 License

Free to use for educational purposes.
