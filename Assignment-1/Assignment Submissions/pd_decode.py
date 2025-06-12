def transform_string(s: str) -> str:
    local_14 = 0x7b1  # 1969 decimal
    s = list(s)  # Convert to list for mutability
    
    for i in range(len(s)):
        local_14 = (local_14 * 7) % 0x10000  # Multiply by 7 modulo 65536
        
        # Calculate adjustment (mimicking C's char behavior)
        adj = ((local_14 // 10) * 10) - (local_14 & 0xFF)
        
        # Add adjustment to character (mod 256 to simulate byte overflow)
        s[i] = chr((ord(s[i]) + adj) % 256)
        
    return ''.join(s)

user_input = input("Enter the string to encode: ")
encoded = transform_string(user_input)
print("Encoded string:", encoded)
