# WavProcessor-C
**A lightweight, modular Digital Signal Processing (DSP) tool for WAV files, written in pure C.**

This project is a digital signal processor capable of reading, modifying, and saving audio files in `.wav` format. It was built from scratch, focusing on binary file manipulation, memory management, and fixed-point arithmetic.

## 🚀 Features

* **Modular Architecture**: Clear separation between WAV header parsing logic and processing algorithms (DSP Engine).
* **Stereo & Mono Support**: Automatically detects the number of channels and applies filters without mixing signals (Stride Processing).
* **Low-Pass Filter**: Reduces high-frequency noise using an optimized moving average.
* **High-Pass Filter**: Eliminates low frequencies (bass) for a "vintage radio" effect.
* **Echo/Delay Effect**: Digital Delay Line implementation with feedback and saturation.
* **Saturation/Clipping Protection**: Prevents digital distortion by software-limiting the amplitude to the 16-bit threshold.
* **Interactive CLI**: Interactive menu and support for command-line arguments.

## 🛠️ Technologies Used

* **Language**: C
* **Compiler**: GCC
* **No External Libraries**: The entire process of binary reading and writing is implemented manually.



## 📋 Project Structure

```text
.
├── build/          # Build directory (CMake output)
├── include/        # Header files (.h)
│   ├── dsp_engine.h
│   └── wav_header.h
├── src/            # Source code (.c)
│   ├── main.c
│   └── dsp_engine.c
├── samples/        # Audio files for testing
└── CMakeLists.txt  # Build configuration
```
## 💻 Installation and Usage
```bash
git clone <link>
```
```bash
cd WavProcessor
```
```bash
gcc src/main.c src/dsp_engine.c -I include -o bin/WavProcessor
```
```bash
./bin/WavProcessor samples/<input>.wav samples/<output>.wav
```
```bash
#After running, follow the interactive menu instructions to choose the desired filter and gain.
```
## 🧠 Implemented Engineering Concepts
* **WAV Parsing**: Reading the RIFF structure and extracting metadata (Sample Rate, Bits Per Sample).

* **Fixed-Point Math**: Using scaling to avoid excessive use of the FPU.

* **Signal Chain**: Processing order (Filtering -> Gain -> Saturation) to maintain sound integrity.
