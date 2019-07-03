import cv2
import numpy as np
import serial
cap = cv2.VideoCapture(0)
arduinoData = serial.Serial("COM3",9600)

while True:
    ret, frame = cap.read()
    blurredFrame = cv2.GaussianBlur(frame, (5, 5), 0)
    hsv = cv2.cvtColor(blurredFrame, cv2.COLOR_BGR2HSV)
    
    #greencolor
    glow=np.array([40,50,50])
    ghigh=np.array([100,255,255])
    
    #redcolor
    rlow=np.array([0,0,20])
    rhigh=np.array([10,255,255])
   
    imageMaskr = cv2.inRange(hsv,rlow,rhigh)    
    imageMaskg = cv2.inRange(hsv,glow,ghigh)
    
    
    contoursGreen,hierarchyG = cv2.findContours(imageMaskg,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
    #contoursRed,hierarchyR = cv2.findContours(imageMaskr,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
    
    
    for contour in contoursGreen :
            cv2.drawContours(frame, contour, -1, (0, 255, 0), 3)
            area = cv2.contourArea(contour)
            while area>7000:
                print(area)
                arduinoData.write(b"1")
                break
            
            
    """for contour in contoursRed:
            cv2.drawContours(frame, contour,-1, (0, 0, 255), 3)
            area = cv2.contourArea(contour)
            if area>10000:
                print(area)
                arduinoData.write(b"0")
                break"""
        
            
    cv2.imshow("Frame", frame)
    #cv2.imshow("Maskr", mask1)
    cv2.imshow("Maskg", imageMaskg)
    if cv2.waitKey(1) == 27:
        break
        
cap.release()
cv2.destroyAllWindows()