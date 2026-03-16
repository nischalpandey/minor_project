import cv2
import numpy as np
from django.shortcuts import render
from django.http import JsonResponse, StreamingHttpResponse
from django.views.decorators.csrf import csrf_exempt
from .models import Event
from ultralytics import YOLO
import face_recognition
import pytesseract

# Load AI models
yolo = YOLO('yolov8n.pt')
known_faces = []  # Load from DB in real project

def dashboard(request):
    events = Event.objects.all()[:20]
    return render(request, 'dashboard.html', {'events': events})

def live_feed(request):
    def gen():
        while True:
            frame = cv2.VideoCapture(0).read()[1]  # Simplified
            _, jpeg = cv2.imencode('.jpg', frame)
            yield (b'--frame\r\nContent-Type: image/jpeg\r\n\r\n' + 
                   jpeg.tobytes() + b'\r\n')
    return StreamingHttpResponse(gen(), content_type='multipart/x-mixed-replace; boundary=frame')

@csrf_exempt
def detect_api(request):
    if request.method == 'POST':
        # Get image
        img = cv2.imdecode(np.frombuffer(request.body, np.uint8), cv2.IMREAD_COLOR)
        
        # YOLO detection
        results = yolo(img)
        
        for r in results:
            for box in r.boxes:
                conf = float(box.conf[0])
                cls = r.names[int(box.cls[0])]
                
                # Simple processing
                if cls == 'person':
                    # Face recognition
                    x1, y1, x2, y2 = map(int, box.xyxy[0])
                    face = img[y1:y2, x1:x2]
                    rgb = cv2.cvtColor(face, cv2.COLOR_BGR2RGB)
                    enc = face_recognition.face_encodings(rgb)
                    
                    if enc and face_recognition.compare_faces(known_faces, enc[0]):
                        Event.objects.create(event_type='known', confidence=conf)
                    else:
                        Event.objects.create(event_type='unknown', confidence=conf)
                
                elif cls in ['knife', 'gun']:
                    Event.objects.create(event_type='weapon', confidence=conf)
                    # Send SMS
                    send_sms("Weapon detected!")
                
                elif 'card' in cls:
                    # OCR
                    x1, y1, x2, y2 = map(int, box.xyxy[0])
                    card = img[y1:y2, x1:x2]
                    gray = cv2.cvtColor(card, cv2.COLOR_BGR2GRAY)
                    text = pytesseract.image_to_string(gray)
                    Event.objects.create(event_type='card', details=text, confidence=conf)
        
        return JsonResponse({'status': 'ok'})

def send_sms(msg):
    import requests
    requests.post("https://smsprovider.com/api/send", json={
        'api_key': 'your_key',
        'to': '98XXXXXXXX',
        'message': msg
    })

def events_api(request):
    events = Event.objects.values()[:50]
    return JsonResponse(list(events), safe=False)