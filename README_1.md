# 📡 Arduino Sonar Scanner (Sweeping Proximity Detector)

A sweeping ultrasonic "sonar" built on an Arduino UNO. A servo continuously rotates an HC-SR04 ultrasonic sensor back and forth across a 180° arc, measuring distance at every step. Depending on how close the nearest object is, the scanner lights one of three LEDs and sounds a buzzer — a live, directional proximity alarm. This was a beginner project I built to learn how servos and ultrasonic sensors work together.

> **Status:** Beginner project. Built with the help of the [Robonyx Academy](https://www.skool.com/robonyx) Arduino course, then wired and coded on my own hardware.

---

## 🎥 Demo

<!-- Drop your demo clip in the /media folder and update the link below.
     On GitHub you can also drag-and-drop the video straight into this README
     in the web editor and it will host + embed it automatically. -->



https://github.com/user-attachments/assets/9986f90f-1492-4b71-ab42-9463a6895098



---

## 🎯 The Problem

I wanted to build something like a real radar/sonar: a sensor that doesn't just look straight ahead, but **sweeps across a wide area** and reacts to whatever it finds — closer objects triggering a more urgent alert. That meant getting two components I'd never used to cooperate: a **servo motor** (for the sweep) and an **HC-SR04 ultrasonic sensor** (for the distance), synced together in one loop.

---

## 📐 How It Works

1. The servo sweeps from **0° → 180°**, then **180° → 0°**, one degree at a time (~10 ms per step).
2. At **every** degree, the HC-SR04 fires an ultrasonic pulse and times how long the echo takes to return.
3. That time is converted to a distance in centimetres.
4. Based on the distance, the scanner drives one of three LEDs and a buzzer tone.

### Distance → Response Zones

| Distance to nearest object | LED lit | Buzzer |
|----------------------------|---------|--------|
| **> 40 cm** | `Blue` — *clear* (far) | silent |
| **10 – 40 cm** | `Green` — *warning* (mid) | 100 Hz tone |
| **< 10 cm** | `Red` — *danger* (close) | 500 Hz tone |


### The distance formula

```cpp
duration = pulseIn(echo, HIGH);   // echo travel time in microseconds
distance = duration * 0.017;      // convert to centimetres
```

Sound travels at ~0.0343 cm per microsecond. Since the pulse goes **out to the object and back**, the round-trip time is halved: `0.0343 / 2 ≈ 0.017`. Multiplying the echo duration by `0.017` gives the one-way distance in cm.

---

## 🧰 Hardware / Parts

- 1 × Arduino UNO
- 1 × SG90 (or similar) servo motor
- 1 × HC-SR04 ultrasonic sensor
- 3 × LEDs (suggested: green = clear, yellow = warning, red = danger)
- 3 × 220 Ω resistors (one per LED)
- 1 × passive buzzer
- Breadboard + jumper wires
- Mounting material (see [Roadblocks](#-roadblocks--how-i-fixed-them))

---

## 🔌 Wiring / Pin Map

| Component | Arduino Pin | Mode |
|-----------|-------------|------|
| Servo signal | 3 | (Servo library) |
| HC-SR04 Trig | 5 | OUTPUT |
| HC-SR04 Echo | 6 | INPUT |
| Buzzer | 9 | OUTPUT |
| LED `p` — close / danger | 12 | OUTPUT |
| LED `t` — mid / warning | 11 | OUTPUT |
| LED `u` — far / clear | 10 | OUTPUT |

Servo: **red → 5V, brown/black → GND, orange/yellow → pin 3**.
HC-SR04: **VCC → 5V, GND → GND, Trig → 5, Echo → 6**.
Each LED: **pin → 220 Ω resistor → LED → GND**.

> ℹ️ **Note on LED labels:** 'p' means Red; 't' means Green; 'u' means BLue

---

## 🧩 Roadblocks & How I Fixed Them

### 1. Understanding how the servo actually moves

**Problem:** Before this project I didn't understand what a servo angle *meant* — what "0°" and "180°" physically were, or how to make the sensor sweep.

**Fix:** A hobby servo takes an **absolute position** command, not a speed. `s.write(angle)` tells it to move to a specific angle, where **0° is one end of its travel and 180° is the other**. To create the sweep, I step the angle up and back down in `for` loops:

```cpp
for (int i = 0;   i <= 180; i++) { s.write(i); /* ...ping... */ delay(10); } // 0 → 180
for (int i = 180; i >= 0;   i--) { s.write(i); /* ...ping... */ delay(10); } // 180 → 0
```

The small `delay(10)` gives the servo time to reach each position and keeps the sweep smooth instead of jerky.

### 2. Mounting the components (no hot glue)

**Problem:** The build guide recommended a hot glue gun to fix the ultrasonic sensor to the servo horn and hold everything in place — but I didn't have one.

**Fix:** I used **tape** instead. It got the project working, but it's the honest weak point of the build: tape flexes, so the sensor can shift slightly and the servo's aim isn't perfectly rigid. A hot glue gun, a small 3D-printed bracket, or even a stiff cardboard mount would make it far more stable and repeatable.

---

## 🚧 Honest Limitations

Known trade-offs of this beginner build:

- **No `pulseIn` timeout.** When nothing is within range, `pulseIn()` waits for an echo that never comes and can stall for up to ~1 second, making the sweep stutter. Adding a timeout fixes it: `pulseIn(echo, HIGH, 30000)`.
- **Longer-than-needed trigger delay.** The code uses `delay(10)` (10 ms) before each trigger pulse; the datasheet only needs a couple of *microseconds*. It works, but it slows the sweep down.
- **No serial output / PC visualisation.** This version reacts purely with LEDs and a buzzer. A classic next step is sending angle + distance over serial to a Processing sketch to draw a live radar sweep on screen.
- **Tape mounting** (see above) limits mechanical precision.

---

## 🔭 Future Improvements

- Add a `pulseIn` timeout and trim the trigger delay to microseconds for a faster, smoother sweep.
- Stream `angle,distance` over serial and build a Processing radar display.
- **Next project I actually want to build:** a **laser-tracking turret** — think of this sonar scanner upgraded with a **second servo** (pan *and* tilt) and a **laser**, so it doesn't just detect the nearest target but aims at it. A natural design would be a small state machine: **SCAN → DETECT → TRACK → FIRE**.

---

## 🙏 Credits

Built as a beginner project with guidance from the **[Robonyx Academy](https://www.skool.com/robonyx)** Arduino course. Wiring, debugging, and the final code are my own work.
