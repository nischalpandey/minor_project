graph LR
    subgraph INPUT[Input Layer]
        A[Camera] --> B[Video Capture]
        C[PIR Sensor] --> D[Arduino]
    end
    
    subgraph PROCESS[Processing Layer]
        B --> E[YOLOv8 Detection]
        E --> F[Face Recognition]
        E --> G[OCR Processing]
        F --> H[Event Decision]
        G --> H
    end
    
    subgraph OUTPUT[Output Layer]
        H --> I[(Database)]
        H --> J[SMS/Telegram/Email]
        H --> K[Buzzer/Relay]
        I --> L[Web Dashboard]
        J --> L
    end
    
    D --> B
    
    classDef input fill:#d4e6f1,stroke:#2875a7,stroke-width:1px,color:#000000
    classDef process fill:#fef5e7,stroke:#ba6b15,stroke-width:1px,color:#000000
    classDef output fill:#d5f0d5,stroke:#2e7d32,stroke-width:1px,color:#000000
    
    class A,B,C,D input
    class E,F,G,H process
    class I,J,K,L output