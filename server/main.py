import serial
import uvicorn
from fastapi import FastAPI, UploadFile
from enum import Enum, IntEnum
from dataclasses import dataclass
import dataclasses
from uuid import UUID, uuid4 as getId
from pydantic import BaseModel
from typing import List
from fastapi.middleware.cors import CORSMiddleware
from fastapi import Request
from wav import extract_frequencies
import time

# TODO: we convert the float frequencies into ints anyway, we can save resources by having them as ints even here
NOTES = {
    "C": [16.35, 32.7, 65.41, 130.81, 261.63, 523.25, 1046.5, 2093, 4186, ],
    "C#": [17.32, 34.65, 69.3, 138.59, 277.18, 554.37, 1108.73, 2217.46, 4434.92,],
    "D": [ 18.35, 36.71, 73.42, 146.83, 293.66, 587.33, 1174.66, 2349.32, 4698.63, ],
    "D#": [ 19.45, 38.89, 77.78, 155.56, 311.13, 622.25, 1244.51, 2489, 4978, ],
    "E": [ 20.6, 41.2, 82.41, 164.81, 329.63, 659.25, 1318.51, 2637, 5274, ],
    "F": [ 21.83, 43.65, 87.31, 174.61, 349.23, 698.46, 1396.91, 2793.83, 5587.65, ],
    "F#": [ 23.12, 46.25, 92.5, 185, 369.99, 739.99, 1479.98, 2959.96, 5919.91, ],
    "G": [ 24.5, 49, 98, 196, 392, 783.99, 1567.98, 3135.96, 6271.93, ],
    "G#": [ 25.96, 51.91, 103.83, 207.65, 415.3, 830.61, 1661.22, 3322.44, 6644.88, ],
    "A": [ 27.5, 55, 110, 220, 440, 880, 1760, 3520, 7040, ],
    "A#": [ 29.14, 58.27, 116.54, 233.08, 466.16, 932.33, 1864.66, 3729.31, 7458.62, ],
    "B": [ 30.87, 61.74, 123.47, 246.94, 493.88, 987.77, 1975.53, 3951, 7902.13, ],
}

NOTE_POINT_SIZE = 4
CHUNK_SIZE = 16 * NOTE_POINT_SIZE

class CommandType(IntEnum):
    FreqsFromSerial = 0
    TextToSpeech = 1

class Instrument(Enum):
    Piano = 0

@dataclass
class Sound:
    duration: int
    frequency: float 

@dataclass
class SoundPoint:
    # id: UUID
    sound: Sound

@dataclass
class PointModel(BaseModel):
    note: str
    octave: int
    duration: int

@dataclass
class CompositionModel(BaseModel):
    points: List[PointModel]

ser = serial.Serial('/dev/cu.usbmodem21203', 115200)
# ser = serial.Serial('/dev/serial/by-id/usb-STMicroelectronics_STM32_STLink_0670FF485251667187121236-if02', 9600)
#ser = serial.Serial('/dev/ttyACM0', 115200)
app = FastAPI()

origins = [
    "http://localhost:3000",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

def writeCommand(commandType: CommandType, unitNoteLength: int, payload: bytes):
    payloadSize = (len(payload) // NOTE_POINT_SIZE).to_bytes(4)

    ser.write(int(commandType).to_bytes())
    ser.write(unitNoteLength.to_bytes(2))
    ser.write(payloadSize)

    i = 0
    while True:
        ser.write(payload[i:i+CHUNK_SIZE])

        time.sleep(0.1)

        if len(payload) - i >= CHUNK_SIZE:
            i += CHUNK_SIZE
        else:
            break

    if i < len(payload):
        ser.write(payload[i:])        

def freqsToBytes(freqs) -> bytes:
    arrOfArrs = list(map(lambda x: int(x[0]).to_bytes(2) + x[1].to_bytes(2), freqs))

    together = []
    for arr in arrOfArrs:
        together += arr

    return bytes(together)

def pointFromModel(model: PointModel) -> SoundPoint:
    soundFrequency = NOTES[model.note][model.octave]
    sound = Sound(model.duration, soundFrequency)
    soundPoint = SoundPoint(sound)

    return soundPoint

@app.post("/serial")
async def serial_endpoint(endpoint: str):
    global ser
    try:
        new_ser = serial.Serial(endpoint, 115200)
        ser.close()
        ser = new_ser
    except Exception as e:
        return {"Failed to open serial point on new ": str(e)}

@app.post("/playComposition/")
async def play_composition(composition: CompositionModel):
    parsed = list(map(pointFromModel, composition.points))

    freqs = [(x.sound.frequency, x.sound.duration) for x in parsed]

    byteS = freqsToBytes(freqs)
    writeCommand(CommandType.FreqsFromSerial, 1, byteS)

    return composition

@app.post("/uploadfile/")
async def create_upload_file(file: UploadFile | None = None):
    if not file:
        return {"message": "No upload file sent"}

    freqs = extract_frequencies(file.file)
    print(freqs)

    byteS = freqsToBytes(freqs)
    writeCommand(CommandType.FreqsFromSerial, 50, byteS)

    return { "filename": file.filename }

@app.post("/say_text/")
async def say_text(req: Request):
    textBytes = await req.body()

    ser.write(int(CommandType.TextToSpeech).to_bytes())
    ser.write((1).to_bytes(2))
    ser.write(len(textBytes).to_bytes(4))

    ser.write(textBytes)
    # writeCommand(CommandType.TextToSpeech, 1, textBytes)

if __name__ == "__main__":
    uvicorn.run(app)
