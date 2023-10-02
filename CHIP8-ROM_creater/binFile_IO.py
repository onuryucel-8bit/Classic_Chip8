def binWriter(source,binData):
    with open(source,"wb") as file:
        file.write(binData)

#reading bin file return HEX format str
def binReader(source,byteOrder):

    try:
        with open(source, "rb") as file:
            fileData = file.read()
        
        # Use the 'bytes' data type for binary data
        result = int.from_bytes(fileData, byteorder=byteOrder)

        # Convert the result to a hexadecimal string
        hexResult = hex(result)
        print(hexResult)
        return hexResult
    
    except FileNotFoundError:
        return f"File not found: {source}"
    except Exception as e:
        return f"An error occurred: {str(e)}"
    
