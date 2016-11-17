import os, sys

folder = sys.argv[1]
files = os.listdir(folder) # use the full path to the folder as an arugument to the script

file_map = dict() 
for f in files:
  cleaned_filename = f.replace(".png","").replace("FRAME_","").replace("_VP_0_0","")
  fileNo = int(cleaned_filename)
  file_map[fileNo] = f

n = 0
for number in sorted(file_map):
  print(str(number) + " -> " + file_map[number])
  source_path = str(folder) + "/" + file_map[number]
  target_path = str(folder) + "/" + str(n) + ".png"
  print("Renaming: " + source_path)
  print("      to: " + target_path)
  os.rename(source_path, target_path)
  n += 1
  
exit()
n=1
for f in files:
  fullpath = str(folder) + "/" + str(f)
  newpath = folder +"/"+ str(n) + ".png"
  print("Renaming: " + fullpath + " -> " + newpath)
  os.rename(fullpath, newpath)
  n += 1
