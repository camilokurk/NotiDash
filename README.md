# NotiDash

Desk notification dashboard: Pro Micro + TFT display + WS2812 status LED + rotary encoder. Shows notifications (Discord, mail, weather, GitHub) pushed from a PC-side bridge over USB serial. Urgent notifications stay pinned until manually dismissed.

Personal hobby/PCB project, work in progress.

## Status

- Schematic: mostly done (KiCad, in `NotiDash/`)
- Firmware (`Firmware/NotiDash/NotiDash.ino`): encoder direction detection, debounced push button, WS2812 LED, serial protocol parser, urgent-notification persistence
- Bridge (PC-side, Python): not started
- PCB layout: not started
