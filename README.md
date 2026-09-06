# 🤖 DeskBuddy

> A tiny desk companion that watches over your work, reacts with emotions, and keeps you company while you build, study, and create.

DeskBuddy is a small **ESP32-based interactive desk companion** with an OLED face, Wi-Fi connectivity, time-aware reminders, randomized emotions, and motivational messages.

The idea is simple:

**Your desk shouldn't feel lonely.** 🫶

DeskBuddy is designed to gradually evolve from a simple OLED face into a personalized little robotic companion.

---
<img width="880" height="993" alt="de" src="https://github.com/user-attachments/assets/e5244963-be86-48ef-b992-abbf97f90aa1" />




## ✨ Current Features

- 🖥️ **OLED expressive face**
- 😊 Multiple emotional states
  - Normal
  - Happy
  - Sleepy
  - Thinking
- 👀 Randomized emotional expressions
- 💬 Motivational messages
- ❤️ Personalized messages
- 📡 ESP32 Wi-Fi connectivity
- 🕐 Internet time synchronization using NTP
- 🌅 Good Morning reminder
- 🌙 Sleep reminder
- 🔌 Offline mode when Wi-Fi is unavailable
- ⚡ Arduino-based embedded implementation

---

## 🧠 How It Works

DeskBuddy runs on an ESP32 and uses an SSD1306 OLED display as its face.

```text
                 ┌────────────────────┐
                 │      DESKBUDDY     │
                 │                    │
                 │   ESP32 Controller │
                 └─────────┬──────────┘
                           │
             ┌─────────────┼─────────────┐
             │             │             │
             ▼             ▼             ▼
          OLED Face      Wi-Fi        Time/NTP
             │             │             │
             ▼             ▼             ▼
        Expressions    Internet      Reminders
             │
             ▼
       Motivation System
