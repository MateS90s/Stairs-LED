# Stairs-LED

Autorski projekt oświetlenia schodowego oparty na mikrokontrolerze **ESP32** i taśmach **WS2811**.  
System steruje efektami świetlnymi oraz sekwencją zapalania diod w zależności od ruchu użytkownika.  
Kod został napisany modułowo z myślą o łatwej rozbudowie i integracji z **Home Assistant**.

**Technologie:** ESP32 · WS2811 · C++ · Arduino IDE  
**Status:** Ukończony – działający lokalnie  

---

💡 *W planach: automatyzacja w Home Assistant oraz integracja czujników ruchu i harmonogramów.*

---

## 🎞️ Podgląd działania

System prezentuje różne tryby oświetlenia w zależności od kierunku ruchu oraz trybu oszczędzania energii.

### Tryby działania:
- 🔹 **Wejście** – zapalanie LED od dołu schodów  
  ![Wejście](assets/stairs_led_bottom_to_top.gif)

- 🔹 **Zejście** – zapalanie LED od góry schodów  
  ![Zejście](assets/stairs_led_top_to_bottom.gif)

- 🔹 **Low Energy Mode – aktywacja**  
  ![LowEnergy ON](assets/stairs_led_lowenergy_on.gif)

- 🔹 **Low Energy Mode – dezaktywacja**  
  ![LowEnergy OFF](assets/stairs_led_lowenergy_off.gif)
