import serial
import time

# Initialize serial connection
ser = serial.Serial('/dev/ttyACM0', 115200)  # Use the correct port and match baud rate
time.sleep(2)  # Allow time for the serial connection to initialize

def send_command(command_type, num_blocks, blocks=[]):
    # Send the command type and number of blocks as two bytes each
    ser.write(command_type.to_bytes(2, 'little'))
    ser.write(num_blocks.to_bytes(2, 'little'))
    
    # Send the blocks of data
    for block in blocks:
        # Ensure block is in the correct format (8 hex characters)
        if len(block) == 8:
            ser.write(bytes.fromhex(block))

# Example usage
command_type = 3  # Command to read blocks of data
blocks = ['1A3C5E7F', '8B9CAD0F']  # List of blocks to send
send_command(command_type, len(blocks), blocks)

ser.close()  # Close the serial connection
