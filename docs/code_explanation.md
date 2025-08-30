# Arduino Code Explanation

## Core Logic:
- Initialize ultrasonic sensor
- Continuously measure distance
- If distance < threshold → Trigger buzzer/vibration

## Pseudocode:
```
loop:
    distance = readUltrasonicSensor()
    if distance < 50cm:
        turn ON buzzer/vibration
    else:
        turn OFF buzzer/vibration
```

## Customization:
- Change distance threshold in code.
- Adjust buzzer/vibration intensity.
