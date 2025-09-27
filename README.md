# nuphy_linux

A command-line utility for controlling lighting modes and key mappings on NuPhy 75 keyboard from Linux.

## Features

- Set keyboard animation modes (with adjustable brightness and speed)
- Set individual key mappings
- Communicates directly with the keyboard via USB HID

## Usage

```
./nuphy_linux --set-mode <mode_index> <brightness> <speed>
./nuphy_linux --set-key <key_name> <key_value>
```
*The indexing is from left to right top to bottom*

### Arguments

- `--set-mode <mode_index> <brightness> <speed>`  
  Sets the lighting animation mode.  
  - `<mode_index>`: Integer index of the animation mode (see below)
  - `<brightness>`: 0-4 (0=lowest, 4=highest)
  - `<speed>`: 0-4 (0=slowest, 4=fastest)

- `--set-key <key_index> <key_value>`  
  Sets the value for a specific key.  
  - `<key_index>`: Name of the key to set
  - `<key_value>`: Value to assign to that key

### Example

```
./nuphy_linux --set-mode 3 2 4
./nuphy_linux --set-key 2 F1
```

## Available Animation Modes

Each mode supports brightness and speed settings from 0 (lowest) to 4 (highest).

| Index | Mode Name           |
|-------|---------------------|
| 0     | on                  |
| 1     | respire             |
| 2     | rainbow             |
| 3     | flashaway           |
| 4     | raindrops           |
| 5     | rainbow_wheel       |
| 6     | ripples_shining     |
| 7     | stars_twinkle       |
| 8     | shadow_disappear    |
| 9     | retro_snake         |
| 10    | neon_stream         |
| 11    | reaction            |
| 12    | sine_wave           |
| 13    | retinue_scanning    |
| 14    | rotating_windmill   |
| 15    | colorful_waterfall  |
| 16    | blossoming          |
| 17    | rotating_storm      |
| 18    | collision           |
| 19    | perfect             |
| 20    | game_mode           |
| 21    | off                 |

## Project Structure

```
nuphy_linux/
├── src/              # C source files
├── include/          # Header files
├── build/            # Compiled output (optional)
├── nuphy_linux       # Compiled binary
├── Makefile          # Build instructions
├── README.md
```

## Building

This project uses a standard Makefile.

1. Ensure you have `gcc` and `libusb-1.0` installed.
2. Build with:

    ```
    make
    ```

3. The resulting binary `nuphy_linux` will be created.

## Dependencies

- [libusb-1.0](https://libusb.info/) (for USB communication)

On Ubuntu/Debian, install with:
```
sudo apt-get install libusb-1.0-0-dev
```

## Contributing

Pull requests are welcome! Please open issues for feature suggestions or bug reports.

## License

MIT License

---

**Note:**  
This project is not affiliated with or endorsed by NuPhy. Use at your own risk.