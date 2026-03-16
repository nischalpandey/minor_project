graph TB
    subgraph HARDWARE["HARDWARE LAYER"]

        PIR["PIR Sensor<br/>Motion Detection"] --> ARDUINO["Arduino UNO<br/>• Read PIR<br/>• Trigger ESP32-CAM<br/>• Control Relay/Buzzer"]
        RTC["DS3231 RTC<br/>Time Stamping"] --> ARDUINO
        ARDUINO --> ESP32["ESP32-CAM<br/>• Video Capture<br/>• Wi-Fi Transmission<br/>• JPEG Compression"]
        ARDUINO --> RELAY["Relay Module<br/>& Buzzer"]
    end
    
    ESP32 --> ROUTER["Wi-Fi Router"]
    ROUTER --> SERVER["Laptop/Server<br/>(Processing Unit)"]
    
    subgraph PROCESSING["PROCESSING LAYER"]
        direction TB
        subgraph PIPELINE["VIDEO PROCESSING PIPELINE"]
            CAPTURE["Frame Capture"] --> YOLO["YOLOv8 Detection"]
            YOLO --> FACE["Face Recognition"]
            YOLO --> OCR["Tesseract OCR"]
            FACE --> LOG["Event Logger"]
            OCR --> LOG
        end
        
        subgraph DATABASE["DATABASE (SQLite)"]
            EVENTS["Events Table<br/>• Timestamp<br/>• Detection Type<br/>• Image Path"]
            KNOWN["Known Faces<br/>• Name/ID<br/>• Face Encoding<br/>• Threat Level"]
            ALERTS["Alert Logs<br/>• Timestamp<br/>• Alert Type<br/>• Channel Used"]
        end
        
        LOG --> EVENTS
        LOG --> KNOWN
        LOG --> ALERTS
    end
    
    subgraph APPLICATION["APPLICATION LAYER"]
        subgraph ALERTSYS["ALERT SYSTEM"]
            SMS["SMS<br/>(Critical Alerts)"]
            TG["Telegram<br/>(All Events)"]
            EMAIL["Email<br/>(Detailed Reports)"]
            BUZZER["Buzzer<br/>(Local Alarm)"]
        end
        
        subgraph DASHBOARD["WEB DASHBOARD (Django)"]
            LIVE["Live Camera Feed<br/>with Detection Overlay"]
            RECENT["Recent Alerts<br/>• Type<br/>• Time<br/>• Image"]
            HISTORY["Event History<br/>• Filter by Date/Type<br/>• Export Logs"]
            FACE_MGMT["Face Management<br/>• Add/Remove<br/>• Threat Level"]
            SETTINGS["System Settings<br/>• Alert Config<br/>• Camera Config"]
        end
        
        EVENTS --> DASHBOARD
        ALERTS --> DASHBOARD
        PROCESSING --> ALERTSYS
    end
    
    DASHBOARD --> ARDUINO
    
    classDef hardware fill:#d4e6f1,stroke:#2875a7,stroke-width:1px,color:#000000
    classDef processing fill:#fef5e7,stroke:#ba6b15,stroke-width:1px,color:#000000
    classDef database fill:#d5f0d5,stroke:#2e7d32,stroke-width:1px,color:#000000
    classDef alert fill:#fadbd2,stroke:#b33920,stroke-width:1px,color:#000000
    classDef dashboard fill:#e8daef,stroke:#6c3483,stroke-width:1px,color:#000000
    
    class PIR,ARDUINO,ESP32,RELAY,ROUTER,SERVER hardware
    class PIPELINE,YOLO,FACE,OCR,LOG processing
    class DATABASE,EVENTS,KNOWN,ALERTS database
    class ALERTSYS,SMS,TG,EMAIL,BUZZER alert
    class DASHBOARD,LIVE,RECENT,HISTORY,FACE_MGMT,SETTINGS dashboard