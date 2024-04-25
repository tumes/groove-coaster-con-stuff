# Genbu V1 Groove Coaster Arduino Conversion

This will technically work for custom controllers as well, but this is how I converted my V1 Genbu controller away from using the original board, which was notorious for its latency problems. 

## Using the custom board

Move `nintendoswitchleonardo.json` into your platformio `core_dir/platforms/atmelavr/boards` directory to use the custom board with the expected HWID/PID values. I tried to do it with in-situ configuration in platformio.ini with no luck, but I'll see if I can get that working since ideally this should require all that faffing.
