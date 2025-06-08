encoded = "x_.1:.-8.4.p6-e.!-"
key = 0x42
decoded = ''.join(chr(ord(b) ^ key) for b in encoded)
print("Decoded string:", decoded)

