# !/usr/bin/env python3.7
import subprocess
import sys
# p = subprocess.call(["./Projekt1.exe", "./data1.txt"])

file_in = "./out.txt" if len(sys.argv) < 2 else sys.argv[1]
mode = '1' if len(sys.argv) < 3 else sys.argv[2]

proc = subprocess.Popen(["./Projekt1.exe", file_in], stdout=subprocess.PIPE, stdin=subprocess.PIPE,  encoding='utf8')

# out,err = proc.communicate(input=f'1\n4\n\x03')
out,err = proc.communicate(input=f'1\n4\n')
f = open('test.jpg','w')
f.write(out)
f.close()
out,err = proc.communicate(input=f'\x03')
# print('*******')
# print(out)


# # proc.stdin.write('1\n')
# proc.stdin.flush()
# proc.stdin.flush()
# proc.stdin.flush()
# proc.stdin.flush()
# # print(proc.stdout.readline())

# proc.stdin.write('1\n')
# proc.stdin.flush()
# print(proc.stdout.readline())

# proc.stdin.write('1\n')
# proc.stdin.flush()
# print(proc.stdout.readline())

# proc.stdin.close()
# proc.terminate()
# proc.wait(timeout=0.2)

# try:
#     out,err = proc.communicate(input=f"{mode}\n",timeout=15)
#     print(out.decode())
# except TimeoutError:
#     print("timeout")
#     exit()

# p = subprocess.run(["./Projekt1.exe", file_in], stdout=subprocess.PIPE, input=f'1\n1\n\x03', encoding='utf8')
# print(type(p.returncode))
# -> 0
# print(p.stdout)
