# ⚡ 2-Player Reaction Timer Game (Arduino UNO)

A simple two-player reflex game built on an Arduino UNO. Both players stare at the LEDs, wait for the "GO" signal, and slam their button — first one to react wins. It's a beginner project I built to get comfortable with digital I/O, buttons with pull-up resistors, timing with `delay()`, and generating real randomness on a microcontroller.

> **Status:** Beginner project. Built with the help of the [Robonyx Academy](https://www.skool.com/robonyx) Arduino course, then wired and coded on my own hardware.

---

## 🎥 Demo

<!-- Drop your demo clip in the /media folder and update the link below.
     On GitHub you can also drag-and-drop the video straight into this README
     in the web editor and it will host + embed it automatically. -->


https://github.com/user-attachments/assets/9d007ec8-98ea-4fe8-81b4-68647ab052e6





---

## 🎯 The Problem

I wanted a small, self-contained game that:

- runs entirely on the Arduino (no PC needed),
- gives two players a fair, identical start,
- and is **unpredictable** — if the "GO" moment happens at the same time every round, players can just memorise the timing and cheat.

That last point turned out to be the interesting engineering challenge (see [Roadblocks](#-roadblocks--how-i-fixed-them)).

---

## 🕹️ How It Works

The round runs like a drag-race start light:

| Step | LED | Buzzer | Timing |
|------|-----|--------|--------|
| 1 | 🟢 Green ON | short beep | ~1 s |
| 2 | 🟡 Yellow ON | short beep | ~1 s |
| 3 | 🔴 Red ON | short beep | **random 0.9 – 4.9 s hold** |
| 4 | ⚪ Both White ON | — | **GO! (react now)** |
| 5 | Winner's white LED stays lit, loser's turns off | victory beep | ~1.5 s, then reset |

The **random red-light hold** is what stops players from anticipating the go signal. When the two white LEDs light up, both players race to hit their button. The first press wins — the winner's white LED stays on, the loser's switches off. Then the board resets for the next round.

---

## 🧰 Hardware / Parts

- 1 × Arduino UNO
- 5 × LEDs — Green, Yellow, Red, and 2 × White
- 5 × 220 Ω resistors (one per LED)
- 2 × push buttons
- 1 × passive buzzer
- Breadboard + jumper wires

> Buttons use the Arduino's **internal pull-up resistors** (`INPUT_PULLUP`), so no external resistors are needed on the buttons — one side to the pin, the other to GND.

---

## 🔌 Wiring / Pin Map

| Component | Arduino Pin | Mode |
|-----------|-------------|------|
| Green LED | 10 | OUTPUT |
| Yellow LED | 9 | OUTPUT |
| Red LED | 8 | OUTPUT |
| White LED — Player 1 | 11 | OUTPUT |
| White LED — Player 2 | 7 | OUTPUT |
| Buzzer | 6 | OUTPUT |
| Button — Player 1 | 12 | INPUT_PULLUP |
| Button — Player 2 | 5 | INPUT_PULLUP |
| **A0 (left unconnected)** | A0 | Analog in — random seed source |

Each LED goes: **pin → 220 Ω resistor → LED → GND**.
Each button goes: **pin → button → GND** (pull-up handled in software).
Pin **A0 is intentionally left floating** — that's the trick behind the randomness, explained below.

---

## 🧩 Roadblocks & How I Fixed Them

### 1. Getting *real* randomness (the main challenge)

**Problem:** Arduino's `random()` isn't actually random on its own — every time the board powers up, it produces the **exact same sequence** of numbers. That means the "random" red-light hold would be identical every single boot, and players could memorise it.

**Fix:** Seed the random generator from electrical noise on a **floating (unconnected) analog pin**:

```cpp
randomSeed(analogRead(A0));   // A0 is left unconnected
```

An unconnected analog pin picks up tiny, unpredictable voltage fluctuations from the surrounding electrical noise. Reading it with `analogRead()` gives a different value each power-up, which seeds `random()` differently every time — so the red-light hold in step 3 is genuinely unpredictable from round to round and boot to boot.

```cpp
delay(random(900, 4901));   // random hold between 0.9 s and 4.9 s
```


### 2. Making the button logic pick a clear winner

**Problem:** Both players press at almost the same time — how do you lock in exactly one winner?

**Fix:** A `while` loop holds both white LEDs on and watches both buttons. The **first** button read as pressed sets a `buttonpressed` flag and immediately turns *off the other player's* LED, so the winner's LED stays lit and the loop exits. Because it's checked in order and the flag latches, only one winner is ever recorded.

```cpp
while (buttonpressed == 0) {
  digitalWrite(White1, HIGH);
  digitalWrite(White2, HIGH);
  if (digitalRead(button1) == 0) {        // Player 1 pressed
    buttonpressed = 1;
    digitalWrite(White2, LOW);            // Player 2's light off → P1 wins
  } else if (digitalRead(button2) == 0) { // Player 2 pressed
    buttonpressed = 1;
    digitalWrite(White1, LOW);            // Player 1's light off → P2 wins
  }
}
```

---

## 🚧 Honest Limitations

These are known trade-offs of a beginner build, not hidden bugs:

- **No false-start detection.** Button presses during the red-light hold are ignored rather than penalised. A "jump the gun and you lose" feature would make it fairer.
- **No score keeping.** Each round is independent — there's no best-of-N or running score.
- **`delay()`-based timing** blocks the whole program. Fine for this game, but it means nothing else can happen during the countdown.
- **No button debounce.** Not an issue here (first-press-wins + long reset), but worth knowing for future projects.

---

## 🔭 Future Improvements

- Add false-start detection during the red hold.
- Keep score across rounds (e.g. first to 5 wins) using a 7-segment display or the serial monitor.
- Replace blocking `delay()` calls with `millis()`-based timing.

---

## 🙏 Credits

Built as a beginner project with guidance from the **[Robonyx Academy](https://www.skool.com/robonyx)** Arduino course. Wiring, debugging, and the final code are my own work.
