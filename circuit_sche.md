graph TB
    subgraph COMPLETE["COMPLETE CIRCUIT SCHEMATIC"]
        style COMPLETE fill:#ffffff,stroke:#333333,stroke-width:2px
        
        %% Power Section
        BATT1[18650 3.7V] --> SERIES
        BATT2[18650 3.7V] --> SERIES
        SERIES[Series Connection<br/>7.4V] --> BUCK_IN[LM2596<br/>Buck Converter<br/>IN+]
        
        BUCK_IN --> BUCK[LM2596<br/>OUT: 5V 3A]
        BUCK --> 5V_RAIL(5V Power Rail)
        BUCK --> GND_RAIL(Ground Rail)
        
        %% Arduino Section
        ARDUINO[Arduino UNO] --> 5V_RAIL
        ARDUINO --> GND_RAIL
        
        %% PIR Section
        PIR[HC-SR501<br/>PIR Sensor] --> 5V_RAIL
        PIR --> GND_RAIL
        PIR -->|OUT| D2[Arduino D2]
        
        %% RTC Section
        RTC[DS3231 RTC] --> 5V_RAIL
        RTC --> GND_RAIL
        RTC -->|SDA| D3[Arduino D3]
        RTC -->|SCL| D4[Arduino D4]
        
        %% Relay Section
        RELAY[Relay Module] --> 5V_RAIL
        RELAY --> GND_RAIL
        RELAY -->|IN| D5[Arduino D5]
        
        %% Buzzer Section
        RELAY -->|COM| 5V_RAIL
        RELAY -->|NO| BUZZER[5V Buzzer +]
        BUZZER -->|Negative| GND_RAIL
        
        %% ESP32 Section
        ESP32[ESP32-CAM] --> 5V_RAIL
        ESP32 --> GND_RAIL
        ESP32 -->|U0R| TX[Arduino TX]
        ESP32 -->|U0T| RX[Arduino RX]
        
        D7[Arduino D7] -->|Trigger| ESP32
        
        %% Optional Direct Buzzer (without relay)
        D6[Arduino D6] -.->|Alternative| BUZZER
        
        %% Connections styling
        linkStyle default stroke-width:2px,stroke:#333333
        
        classDef battery fill:#d4e6f1,stroke:#2875a7,stroke-width:2px,color:#000000
        classDef regulator fill:#fef5e7,stroke:#ba6b15,stroke-width:2px,color:#000000
        classDef rail fill:#fadbd2,stroke:#b33920,stroke-width:2px,color:#000000
        classDef arduino fill:#fef5e7,stroke:#ba6b15,stroke-width:2px,color:#000000
        classDef sensor fill:#d5f0d5,stroke:#2e7d32,stroke-width:2px,color:#000000
        classDef esp32 fill:#e8daef,stroke:#6c3483,stroke-width:2px,color:#000000
        
        class BATT1,BATT2,SERIES battery
        class BUCK_IN,BUCK regulator
        class 5V_RAIL,GND_RAIL rail
        class ARDUINO,D2,D3,D4,D5,D6,D7,RX,TX arduino
        class PIR,RTC,RELAY,BUZZER sensor
        class ESP32 esp32
    end