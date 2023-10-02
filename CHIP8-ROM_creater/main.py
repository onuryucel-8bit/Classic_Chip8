import binFile_IO as bin
# Function to convert a hexadecimal string to bytes
def hex_to_bytes(hex_string):
    return bytes.fromhex(hex_string)

def romWriter(hex_data):
    
    # Prompt the user for hex data and convert it to bytes
    #print("Enter ROM data in hexadecimal format (e.g., '0A1B2C3D'):")
    #print("===========")
    #hex_data = []
    #while True:
    #    input_data = input()
    #   if not input_data:
    #        break
    #    hex_data.append(input_data)

    byte_data = bytearray()
    for hex_string in hex_data:
        byte_data += hex_to_bytes(hex_string)

    bin.binWriter("output",byte_data)

    print("Binary data has been written to 'output'")


#return list with hex_str number
def romDecoder(str):
    hexList = []

    for i in range(2,len(str) - 2,4):
        hexList.append(str[i] + str[i+1] + str[i+2] + str[i+3])
        
    return hexList

def printHex(lst):
    for i in range(len(lst)):
        print(lst[i])


def fileRead(filename):
    with open(filename,"r") as file:
        fileData = file.read()
    
    return fileData


if __name__ == "__main__":
    data = fileRead("input.txt")
    
     # Split the file content into lines
    lines = data.split("\n")
    
    # Strip each line and store them in the opcodes list
    opcodes = [line.strip() for line in lines if line.strip()]
        
    romWriter(opcodes)
    