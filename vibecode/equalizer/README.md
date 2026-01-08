# Project: NeuralAudio - AI-Powered Adaptive Equalizer

## 1. Project Overview

**NeuralAudio** is a real-time, adaptive audio processing application designed to optimize music playback based on two dynamic factors:

1. **Content:** The genre/style of the music currently playing (e.g., Rock, Jazz, Pop).
2. **Context:** The physical limitations of the playback hardware (e.g., Laptop speakers, Phone, Headphones).

Unlike traditional "static" equalizers that apply a fixed preset, NeuralAudio uses a split-architecture approach: an AI "Brain" analyzes the audio stream to determine the aesthetic goal (Target Curve), while a DSP "Engine" handles the rigorous signal processing, including psychoacoustic bass enhancement for small speakers.

---

## 2. System Architecture

The system follows an **Asynchronous Control Architecture**.

* **The Brain (High Latency):** Analysis & Decision Making. Runs every 3-5 seconds.
* **The Engine (Low Latency):** Signal Processing & Synthesis. Runs every <10ms.

### Signal Chain Flow

1. **Input:** System Audio Capture (Virtual Cable/Driver).
2. **Analysis:** Copy buffer to Ring Buffer -> STFT -> CNN Classification.
3. **Adaptive EQ:** Input FFT vs. Genre Target Curve -> Generate Filter -> Apply EQ.
4. **Hardware Calibration:**
* *High Pass Filter:* Cut frequencies the hardware cannot play (e.g., <80Hz).
* *Virtual Bass:* Synthesize harmonics for the cut frequencies (Missing Fundamental).
* *Room Correction:* Apply inverse curve for hardware resonances.


5. **Protection:** Brickwall Limiter -> Output.

---

## 3. Technology Stack

| Component | Prototype (Research) | Production (Deployment) |
| --- | --- | --- |
| **Language** | Python 3.10+ | C++ (C++17/20) |
| **Audio I/O** | `PyAudio` (PortAudio), `sounddevice` | **JUCE Framework** |
| **Math/DSP** | `NumPy`, `SciPy` | JUCE DSP Module, Eigen |
| **AI/ML** | `TensorFlow` / `Keras` | TensorFlow Lite (C++ API) |
| **Feature Extraction** | `Librosa` | Custom C++ FFT / Mel-Filterbank |
| **GUI** | `PyQt5` / `Tkinter` | JUCE GUI |

---

## 4. Implementation Roadmap (To-Do List)

### Phase 1: The "Brain" (AI Classification)

*Goal: Build a Python script that listens to a file and decides the Genre.*

* [ ] **Data Prep:** Download GTZAN or FMA dataset (Genre classification).
* [ ] **Feature Engineering:** Write script to convert audio clips to Mel-Spectrograms (images).
* [ ] **Model Training:**
* [ ] Design simple CNN architecture (Convolution -> Pool -> Flatten -> Dense).
* [ ] Train model on spectrograms.
* [ ] Evaluate accuracy (aim for >80%).
* [ ] **Alternative:** Download pre-trained model (YAMNet or similar) via Hugging Face.


* [ ] **Inference Script:** Write a function `get_genre(audio_buffer)` that returns a string label.

### Phase 2: The "Engine" Core (DSP Playground)

*Goal: Build the audio processing loop in Python to validate the math.*

* [ ] **Audio I/O:** Set up `PyAudio` loopback (Input: Virtual Cable, Output: Speakers).
* [ ] **FFT Processing:** Implement STFT (Short-Time Fourier Transform) on live blocks.
* [ ] **Target Curve Logic:**
* [ ] Define mathematical curves for "Pink Noise", "Rock V-Shape", "Pop Presence".
* [ ] Implement the `Error = Target / Input` calculation to generate dynamic filters.


* [ ] **Smoothing:** Implement temporal smoothing (Attack/Release) so EQ changes don't click/pop.

### Phase 3: Hardware Calibration Layer

*Goal: Implement the "Physics" fixes for small speakers.*

* [ ] **Device Profile System:** Create `device_config.json` structure (min_freq, max_gain).
* [ ] **Virtual Bass (Missing Fundamental):**
* [ ] Implement Low-Pass/High-Pass crossover splitter.
* [ ] Implement Harmonic Generator (Saturation/Squaring of low frequencies).
* [ ] Mix harmonics back into the high-passed signal.


* [ ] **Excursion Protection:** Add a hard High-Pass filter based on the JSON config.

### Phase 4: Integration & GUI

*Goal: Connect the Brain to the Engine and visualize it.*

* [ ] **Threading:** Move the AI "Brain" to a separate thread so it doesn't block the Audio Engine.
* [ ] **Shared State:** Create a thread-safe variable for `current_target_curve` that the Engine reads.
* [ ] **UI Visualization:**
* [ ] Plot the Real-time Input Spectrum (Gray).
* [ ] Plot the AI's Target Curve (Red).
* [ ] Plot the "Corrected" Output (Green).
* [ ] Add a dropdown to select Hardware Profile (Laptop, Phone, Hi-Fi).



---

## 5. Key Algorithms & Formulas

**1. Pink Noise Target (Baseline):**


**2. Adaptive Filter Calculation:**



*(Where  is Target,  is Input Magnitude,  is small constant)*

**3. Virtual Bass (Harmonic Generation):**



*(Filter the result to remove DC offset and original fundamental)*