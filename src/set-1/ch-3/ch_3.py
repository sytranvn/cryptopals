str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
writeable = range(32, 127)

buff = [int(str[i:i+2], 16) for i in range(0, len(str), 2)]
rs = []
for ch in writeable:
    g = ""
    for b in buff:
        r = b ^ ch
        if r not in writeable:
            break
        g += chr(r)
    rs.append((ch, g))

rs.sort(reverse=True, key=lambda x: x[1].count(" "))
print(f"{chr(rs[0][0])} {rs[0][1]}")

rs.sort(reverse=True, key=lambda x: x[1].count("a"))
print(f"{chr(rs[0][0])} {rs[0][1]}")

rs.sort(reverse=True, key=lambda x: x[1].count("e"))
print(f"{chr(rs[0][0])} {rs[0][1]}")

rs.sort(reverse=True, key=lambda x: x[1].count("o"))
print(f"{chr(rs[0][0])} {rs[0][1]}")
