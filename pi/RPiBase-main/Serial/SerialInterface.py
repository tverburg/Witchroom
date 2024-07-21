import serial

class SerialInterface:

    serialPort: serial.Serial = None
    config: dict = None
    encodedEndmarker = None

    def __init__ (self, _config:dict):
        self.config = _config
        
        self.encodedEndmarker = str(self.config["serial"]["endMarker"]).encode("utf-8")
        
        self.serialPort = serial.Serial(port=self.config["serial"]["port"], 
                                        baudrate=self.config["serial"]["baudRate"],
                                        timeout=0.1)

    def checkForMessage(self):
        try:
            if self.serialPort.in_waiting > 0:
                messageBytes = self.serialPort.read_until(self.encodedEndmarker)
                
                messageString = messageBytes.decode('utf-8')
                
                messageString = messageString.strip("\n")
                
                return messageString
            else:
                return ""
        except Exception:
            return ""
        
        
        
    def writeStringToSerial(self, string:str):
        try:
            if string != "":
                encodedmessage = str(string).encode("utf-8")
                
                self.serialPort.write(encodedmessage)
                self.serialPort.write(self.encodedEndmarker)
                
                return "succes"
            else:
                return "failed"
        except Exception:
            return "failed"
        
    def close(self):
        self.serialPort.close()