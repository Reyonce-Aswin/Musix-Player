# 🎧 Musix Player (C++)

A lightweight **command-line audio player** written in **C++**, demonstrating a simple but well-structured audio playback engine using modern C++ practices.

The player uses **PortAudio** for cross-platform audio output and **libsndfile** for decoding WAV audio files.

---

## ✨ Features

* 🎵 WAV audio playback
* ⏯ Play / Pause toggle
* 🔁 Loop playback support
* 🔇 Mute / Unmute audio
* 📊 Real-time progress bar with playback duration
* ⌨ Non-blocking keyboard controls
* 🧵 Callback-based audio streaming
* 🖥 Flicker-free CLI interface

Example output:

```
State: Playing | Mute: No | Loop: Off [======>-------------] 00:41/02:35
```

---

## 🏗 Architecture

The project separates playback control from the audio engine for cleaner design.

```
Player
   │
   ▼
AudioEngine
   │
   ▼
PortAudio callback
   │
   ▼
libsndfile (audio decoding)
```

### Components

| Component   | Responsibility                            |
| ----------- | ----------------------------------------- |
| Player      | High-level playback control               |
| AudioEngine | Audio streaming and PortAudio interaction |
| PlayerState | Playback state management                 |
| main.cpp    | CLI interface and keyboard controls       |

---

## 📂 Project Structure

```
audio_player/
│
├── assets/
│   └── test.wav
│
├── include/
│   ├── AudioEngine.h
│   ├── Player.h
│   └── PlayerState.h
│
├── src/
│   ├── AudioEngine.cpp
│   ├── Player.cpp
│   └── main.cpp
│
├── build.ps1
└── README.md
```

---

## 📦 Dependencies

This project depends on:

* PortAudio
* libsndfile

Ensure both libraries are installed before building.

---

## ⚙ Build Instructions

### Linux / macOS

Install dependencies:

```
sudo apt install portaudio19-dev libsndfile1-dev
```

Compile:

```
g++ src/*.cpp -Iinclude -o player -lportaudio -lsndfile
```

Run:

```
./player assets/test.wav
```

---

### Windows (MinGW / MSYS2)

Install dependencies:

```
pacman -S mingw-w64-ucrt-x86_64-portaudio
pacman -S mingw-w64-ucrt-x86_64-libsndfile
```

Compile:

```
g++ src/*.cpp -Iinclude -o player.exe -lportaudio -lsndfile
```

Run:

```
player.exe assets/test.wav
```

---

## 🎮 Controls

| Key | Action       |
| --- | ------------ |
| p   | Play / Pause |
| l   | Toggle Loop  |
| m   | Toggle Mute  |
| q   | Quit Player  |

---

## 📊 Progress Display

The player prints playback information in a single-line terminal interface:

```
State: Playing | Mute: No | Loop: Off [======>-------------] 00:41/02:35
```

Displayed information:

* Playback state
* Mute status
* Loop status
* Progress bar
* Elapsed time
* Total duration

---

## 🚀 Future Improvements

Planned features for upcoming versions:

* ⏩ Audio seeking (forward/backward)
* 🎧 Support for additional formats (MP3 / FLAC)
* 📂 Playlist support
* 🖥 Improved terminal UI
* 🎚 Volume control

---

## 🤝 Contributing

Contributions are welcome.

1. Fork the repository
2. Create a feature branch
3. Submit a pull request

Bug reports and feature requests are appreciated.

---

## 📜 License

This project is released under the **MIT License**.

---

## 🙏 Acknowledgements

* PortAudio project
* libsndfile project
* The open source audio development community
