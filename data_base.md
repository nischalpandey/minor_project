erDiagram
    EVENTS ||--o{ ALERT_LOGS : generates
    KNOWN_FACES ||--o{ EVENTS : identified_in
    
    EVENTS {
        int id PK
        datetime timestamp
        string detection_type
        float confidence
        string class_name
        string image_path
        int face_id FK
        string bbox_coordinates
        string location
    }
    
    KNOWN_FACES {
        int id PK
        string name
        string student_id
        blob face_encoding
        string threat_level
        string image_path
        datetime registered_date
        string notes
    }
    
    ALERT_LOGS {
        int id PK
        int event_id FK
        datetime timestamp
        string alert_type
        string channels_used
        string delivery_status
        float cost_incurred
        string recipient
    }
    
    SYSTEM_CONFIG {
        int id PK
        string config_key
        string config_value
        string description
        datetime updated_at
    }
    
    CAMERA_SETTINGS {
        int id PK
        string camera_name
        string ip_address
        string stream_url
        string username
        string password
        bool is_active
    }