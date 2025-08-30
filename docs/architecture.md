# System Architecture

```mermaid
flowchart TD
A[User Movement] --> B[Ultrasonic Sensor]
B --> C[Arduino Board]
C -->|Alert| D[Buzzer / Vibration Motor]
D --> E[User Feels Warning]
```
