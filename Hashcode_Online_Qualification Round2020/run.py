import os

os.system("g++ -std=c++17 -o compiled.out main.cpp")

if not os.path.exists('output'):
    os.makedirs('output')

files = os.listdir('input')
for file in files:
    input_file = os.path.join('input', file)
    output_file = os.path.join('output', file)

    os.system(f"./compiled.out {input_file} {output_file}")