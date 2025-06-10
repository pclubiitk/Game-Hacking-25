def transform_string(s):
    local_14 = 0x7b1
    result = []

    for c in s:
        local_14 = (local_14 * 7) % 0x10000
        offset = ((local_14 // 10) * 10) - local_14
        new_char = chr((ord(c) + offset) % 256)
        result.append(new_char)

    return ''.join(result)

input_str = input("Enter a string:")
output_str = transform_string(input_str)
print(output_str)
