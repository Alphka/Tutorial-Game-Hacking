# Tutorial-Game-Hacking

<p align="center">
	<a href="LICENSE.md">
		<img alt="License: ISC" src="https://img.shields.io/badge/License-ISC-5271FF?style=for-the-badge">
	</a>
</p>

Small C++ exercise for Windows that follows a tutorial on process memory: one program holds an integer in memory and prints its address, and a second program overwrites that integer using the Win32 API.

> [!WARNING]
> **Educational use only.** Use this code exclusively on test programs you wrote yourself (such as `program.cpp` in this repository) or on single-player software you own and are allowed to modify.
> Do **not** use it to cheat in online or multiplayer games, or to tamper with software or processes belonging to other people. Doing so can violate terms of service and the law, and anti-cheat systems may ban your account or hardware. This project does not include, and will not add, anti-cheat evasion or injection features.

## Description

The repository contains two independent console programs:

| File | Role |
| --- | --- |
| `program.cpp` | Test target. Declares `int varInt = 123456`, prints its own process ID and the address of `varInt`, and prints the value again each time you press ENTER. |
| `hack.cpp` | Memory writer. Asks for a process ID, a memory address (hexadecimal) and an integer (decimal), then writes that integer to the given address in the given process. |

Typical flow of the exercise: run `program.cpp`, note the PID and the address it prints, then run `hack.cpp`, enter those values and a new number, and press ENTER in the first program to see the changed value.

## How it works

`hack.cpp` uses these Win32 functions:

- [`OpenProcess`](https://learn.microsoft.com/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocess) obtains a handle to the process with the given PID. The code requests `PROCESS_ALL_ACCESS`.
- [`WriteProcessMemory`](https://learn.microsoft.com/windows/win32/api/memoryapi/nf-memoryapi-writeprocessmemory) copies `sizeof(int)` bytes from the writer's own memory to the target address in the other process.
- [`GetLastError`](https://learn.microsoft.com/windows/win32/api/errhandlingapi/nf-errhandlingapi-getlasterror) is printed when one of the calls above fails.

`program.cpp` uses [`GetCurrentProcessId`](https://learn.microsoft.com/windows/win32/api/processthreadsapi/nf-processthreadsapi-getcurrentprocessid) to report its PID.

Windows only lets a process open another one if its security descriptor and privileges allow it, so the writer can fail with an access error on protected processes. The address printed by `program.cpp` is only valid for that running instance and will usually differ on the next run.

## Requirements

- Windows
- A C++ compiler with the Windows headers. (e.g. MinGW-w64 `g++` or MSVC).

## Build

Compile each file separately.

```sh
mkdir output
g++ -std=c++17 program.cpp -o output/program.exe
g++ -std=c++17 hack.cpp -o output/hack.exe
```

## Usage

1. Start `output/program.exe`. It prints its process ID and the address of its integer variable.
2. In another terminal, start `output/hack.exe` and enter the PID, the address (hexadecimal, without `0x`) and the new integer value.
3. Press ENTER in `program.exe` to print the variable again.

Run both programs only on your own machine, and only against each other.

## Project structure

```
hack.cpp      Writer: OpenProcess + WriteProcessMemory
program.cpp   Test target that prints its PID and variable address
.editorconfig Tabs, LF line endings, UTF-8
```

## License

[ISC](LICENSE.md) © 2023 Kayo Souza
